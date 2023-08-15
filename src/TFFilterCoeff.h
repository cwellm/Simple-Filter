#pragma once

#include <array>
#include <string>

namespace cw::Filter {

    template <typename ... Param>
    struct TFFilterCoeff {
        virtual void setCoeffs(std::array<float, 6>& inArr) = 0;
        virtual void setTargetParams(const Param&... params) = 0;
        
        void setSampleRate(const float& sampleRate) { this->sampleRate = sampleRate; }
        virtual std::string getType() = 0;

    protected:
        float sampleRate{ 44100.f };
    };

} // cw::Filter