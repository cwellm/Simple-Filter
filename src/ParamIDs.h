#pragma once

#include <JuceHeader.h>

// IDs for the Processor
#define IDCutoffFreq "idCutoffFreq"
#define IDSteepness "idSteepness"
#define IDCenterFrequency "idCenterFrequency"
#define IDBandwidth "idBandwidth"
#define IDFilterType "idFilterType"

// Constants for the parameter mapping
#define MAPLPName "LP"
#define MAPHPName "HP"
#define MAPBPName "BP"
#define MAPBRName "BR"

// Filter type choices
#define filterTypeChoiceItems juce::StringArray{ MAPLPName, MAPHPName, MAPBPName, MAPBRName }

