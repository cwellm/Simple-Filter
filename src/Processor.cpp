/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "Processor.h"
#include "Editor.h"
#include "ParamIDs.h"
#include "ParameterMappings.h"

#include "BandpassFilter.h"
#include "BandRejectFilter.h"

//==============================================================================
Processor::Processor()
#ifndef JucePlugin_PreferredChannelConfigurations
    : AudioProcessor(BusesProperties()
#if ! JucePlugin_IsMidiEffect
#if ! JucePlugin_IsSynth
        .withInput("Input", juce::AudioChannelSet::stereo(), true)
#endif
        .withOutput("Output", juce::AudioChannelSet::stereo(), true)
#endif
    ),
    apvts(*this, nullptr, juce::Identifier{ "ProcessorState" }, {
        std::make_unique<juce::AudioParameterFloat>(IDCutoffFreq,
            IDCutoffFreq,
            juce::NormalisableRange<float>{20., 20000., 1., 0.5},
            1000),
        std::make_unique<juce::AudioParameterFloat>(IDSteepness,
            IDSteepness,
            juce::NormalisableRange<float>{0.05, 12, 0.01, 0.7},
            1),
        std::make_unique<juce::AudioParameterFloat>(IDCenterFrequency,
            IDCenterFrequency,
            juce::NormalisableRange<float>{50., 19500., 1., 0.5},
            1000),
        std::make_unique<juce::AudioParameterFloat>(IDBandwidth,
            IDBandwidth,
            juce::NormalisableRange<float>{50., 10000., 1., 0.7},
            500),
        std::make_unique<juce::AudioParameterChoice>(IDFilterType,
            IDFilterType,
            filterTypeChoiceItems, 
            0)
        }
        )
#endif
{  
    
    pmCutoffFreq = apvts.getRawParameterValue(IDCutoffFreq);
    pmSteepness = apvts.getRawParameterValue(IDSteepness);
    pmCenterFreq = apvts.getRawParameterValue(IDCenterFrequency);
    pmBandWidth = apvts.getRawParameterValue(IDBandwidth);
    pmFilterTypeChoice = apvts.getRawParameterValue(IDFilterType);
    
}

Processor::~Processor()
{
}

//==============================================================================
const juce::String Processor::getName() const
{
    return JucePlugin_Name;
}

bool Processor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool Processor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool Processor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double Processor::getTailLengthSeconds() const
{
    return 0.0;
}

int Processor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int Processor::getCurrentProgram()
{
    return 0;
}

void Processor::setCurrentProgram (int index)
{
}

const juce::String Processor::getProgramName (int index)
{
    return {};
}

void Processor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void Processor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
   
    if (biquadFilterL == nullptr) {
        biquadFilterL.reset(new cw::Filter::BiquadFilter());
    }

    if (biquadFilterR == nullptr) {
        biquadFilterR.reset(new cw::Filter::BiquadFilter());
    }

    // ONLY FOR TESTING ###########
    biquadFilterL->setFilterCoeffType(std::make_unique<cw::Filter::BiquadLPCoeff>());
    biquadFilterR->setFilterCoeffType(std::make_unique<cw::Filter::BiquadLPCoeff>());
    // ############################

    biquadFilterL->resetFilter();
    biquadFilterR->resetFilter();

    biquadFilterL->setSampleRate(sampleRate);
    biquadFilterR->setSampleRate(sampleRate);

    // reserve memory
    biquadFilterL->reserveMemory(samplesPerBlock);
    biquadFilterR->reserveMemory(samplesPerBlock);
    maxExpectedBlockSize = samplesPerBlock;
}

void Processor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool Processor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void Processor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{

    // Set parameters - depends on filter type
    filterTypeIndex = *apvts.getRawParameterValue(IDFilterType);

    // Single Biquad Filters: LP or HP
    if (filterTypeIndex == 0 || filterTypeIndex == 1) {
        if (previousFilterTypeIndex != filterTypeIndex) {
            biquadFilterL.reset(new cw::Filter::BiquadFilter());
            biquadFilterR.reset(new cw::Filter::BiquadFilter());
            biquadFilterL->reserveMemory(maxExpectedBlockSize);
            biquadFilterR->reserveMemory(maxExpectedBlockSize);
            previousFilterTypeIndex = filterTypeIndex;
        }

        biquadFilterL->setFilterCoeffType(cw::Filter::mapFilterTypes
            .at(filterTypeChoiceItems[filterTypeIndex].toStdString()));
        biquadFilterR->setFilterCoeffType(cw::Filter::mapFilterTypes
            .at(filterTypeChoiceItems[filterTypeIndex].toStdString()));

        biquadFilterL->setTargetParams(*pmCutoffFreq, *pmSteepness);
        biquadFilterR->setTargetParams(*pmCutoffFreq, *pmSteepness);
    }

    // BiquadFilterChain: BP or BR
    else {
        if (previousFilterTypeIndex != filterTypeIndex) {
            if (filterTypeIndex == 2) {
                biquadFilterL.reset(new cw::Filter::BandpassFilter());
                biquadFilterR.reset(new cw::Filter::BandpassFilter());
                biquadFilterL->reserveMemory(maxExpectedBlockSize);
                biquadFilterR->reserveMemory(maxExpectedBlockSize);
            }
            else {
                biquadFilterL.reset(new cw::Filter::BandRejectFilter());
                biquadFilterR.reset(new cw::Filter::BandRejectFilter());
                biquadFilterL->reserveMemory(maxExpectedBlockSize);
                biquadFilterR->reserveMemory(maxExpectedBlockSize);
            }
            previousFilterTypeIndex = filterTypeIndex;
        }
        biquadFilterL->setTargetParams(*pmCenterFreq, *pmBandWidth);
        biquadFilterR->setTargetParams(*pmCenterFreq, *pmBandWidth);
    }

    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);

        if (channel == 0) {
            biquadFilterL->processBlock(channelData, buffer.getNumSamples());
        }
        if (channel == 1) {
            biquadFilterR->processBlock(channelData, buffer.getNumSamples());
        }

    }
}

//==============================================================================
bool Processor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* Processor::createEditor()
{
    return new Editor (*this, apvts);
}

//==============================================================================
void Processor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void Processor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new Processor();
}
