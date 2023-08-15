#pragma once

#include "BiquadCoeff.h"

namespace cw::Filter {

	void BiquadLPCoeff::setTargetParams(const float& cutoffFreq, const float& QValue) {
		this->cutoffFreq = cutoffFreq;
		this->QValue = QValue;
	}

	void BiquadLPCoeff::setCoeffs(std::array<float, 6>& inArr) {
		inArr[0] = 1;
		inArr[1] = 2;
		inArr[2] = 1;

		float srCutRatio = sampleRate / (cutoffFreq * 2. * CW_PI);
		inArr[3] = 4 * srCutRatio * srCutRatio + 2 * srCutRatio / QValue + 1;
		inArr[4] = 2 - 8 * srCutRatio*srCutRatio;
		inArr[5] = 4 * srCutRatio * srCutRatio - 2 * srCutRatio / QValue + 1;
	}

	std::string BiquadLPCoeff::getType() {
		return "BiquadLP";
	}

	void BiquadHPCoeff::setTargetParams(const float& cutoffFreq, const float& QValue) {
		this->cutoffFreq = cutoffFreq;
		this->QValue = QValue;
	}

	void BiquadHPCoeff::setCoeffs(std::array<float, 6>& inArr) {

		float srCutRatio = sampleRate / (cutoffFreq * 2. * CW_PI);

		inArr[0] = 4 * srCutRatio * srCutRatio + 2. / QValue * srCutRatio;
		inArr[1] = -8 * srCutRatio * srCutRatio;
		inArr[2] = 4 * srCutRatio * srCutRatio - 2 / QValue * srCutRatio;

		inArr[3] = 4 * srCutRatio * srCutRatio + 2 * srCutRatio / QValue + 1;
		inArr[4] = 2 - 8 * srCutRatio * srCutRatio;
		inArr[5] = 4 * srCutRatio * srCutRatio - 2 * srCutRatio / QValue + 1;
	}

	std::string BiquadHPCoeff::getType() {
		return "BiquadHP";
	}

	void BiquadBPCoeff::setTargetParams(const float& centerFreq, const float& bandwidth) {
		this->centerFreq = centerFreq;
		this->bandwidth = bandwidth;
	}

	void BiquadBPCoeff::setCoeffs(std::array<float, 6>& inArr) {
		float QValue = 1.;

		float hpCutoffFreq = centerFreq - 1. / 2 * bandwidth;
		float lpCutoffFreq = centerFreq + 1. / 2 * bandwidth;

		float lpSrCutRatio = sampleRate / (lpCutoffFreq * 2. * CW_PI);
		float hpSrCutRatio = sampleRate / (hpCutoffFreq * 2. * CW_PI);

		inArr[0] = 1;
		inArr[1] = 4;
		inArr[2] = 1;
		inArr[3] = (4 * lpSrCutRatio * lpSrCutRatio + 2 * lpSrCutRatio / QValue + 1)
			* (4 * hpSrCutRatio * hpSrCutRatio + 2 * hpSrCutRatio / QValue + 1) / 2.;
		inArr[4] = (2 - 8 * lpSrCutRatio * lpSrCutRatio)
			* (2 - 8 * hpSrCutRatio * hpSrCutRatio);
		inArr[5] = (4 * lpSrCutRatio * lpSrCutRatio - 2 * lpSrCutRatio / QValue + 1)
			* (4 * hpSrCutRatio * hpSrCutRatio - 2 * hpSrCutRatio / QValue + 1);
	}

	std::string BiquadBPCoeff::getType() {
		return "BiquadBP";
	}

	void BiquadBRCoeff::setTargetParams(const float& centerFreq, const float& bandwidth) {
		this->centerFreq = centerFreq;
		this->bandwidth = bandwidth;
	}

	void BiquadBRCoeff::setCoeffs(std::array<float, 6>& inArr) {
		inArr[0] = 1;
		inArr[1] = 1;
		inArr[2] = 1;
		inArr[3] = 100;
		inArr[4] = 0;
		inArr[5] = 0;
	}

	std::string BiquadBRCoeff::getType() {
		return "BiquadBR";
	}

} // cw::Filter