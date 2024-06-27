
#include "Tremolo.h"

void Tremolo::update(float value) {
    lfo.setFrequency(value);
}

void Tremolo::setActive(bool value) {
    isTremoloActive = value;
}

void Tremolo::prepare(double sampleRate, int samplesPerBlock,
                      juce::dsp::ProcessSpec spec) {
    lowPassFilter.prepare(spec);
    lfo.prepareToPlay(sampleRate, samplesPerBlock);
}

void Tremolo::process(juce::AudioBuffer<float> &buffer) {
//    lfo.process(buffer, LFO::Sine);
    lowPassFilter.processLowPass(buffer);

    for (int channel = 0; channel < buffer.getNumChannels(); ++channel)
    {
        auto *channelData = buffer.getWritePointer(channel);
        for (int i = 0; i < buffer.getNumSamples(); ++i)
        {
            auto sample = lfo.getLfoSine().processSample(0);
            channelData[i] *= (sample + 1.f) * 0.5f;
        }
    }
}

bool Tremolo::isActive() {
    return isTremoloActive;
}
