#include "Tremolo.h"

void Tremolo::update(float value) {
    lfoLeft.setFrequency(value);
    lfoRight.setFrequency(value);
}

void Tremolo::setActive(bool value) {
    isTremoloActive = value;
}

void Tremolo::prepare(double sampleRate, int samplesPerBlock,
                      juce::dsp::ProcessSpec spec) {
    lowPassFilter.prepare(spec);
    lfoLeft.prepareToPlay(sampleRate, samplesPerBlock);
    lfoRight.prepareToPlay(sampleRate, samplesPerBlock);
}

void Tremolo::process(juce::AudioBuffer<float> &buffer) {
    int numChannels = buffer.getNumChannels();

    for (int i = 0; i < buffer.getNumSamples(); ++i)
    {
        auto leftSample = lfoLeft.getLfoSine().processSample(0);
        auto rightSample = numChannels > 1 ? lfoRight.getLfoSine().processSample(1) : leftSample;

        for (int channel = 0; channel < numChannels; ++channel)
        {
            auto *channelData = buffer.getWritePointer(channel);
            channelData[i] *= ((channel == 0 ? leftSample : rightSample) + 1.f) * 0.5f;
        }
    }

    lowPassFilter.processLowPass(buffer);
}

bool Tremolo::isActive() {
    return isTremoloActive;
}