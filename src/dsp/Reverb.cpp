
#include "Reverb.h"


void Reverb::prepare(juce::dsp::ProcessSpec spec) {
    dryWetMixer.prepare(spec);
    dryWetMixer.setWetMixProportion(0.5);
    dryWetMixer.setWetLatency(0.0f);

    reverb.setSampleRate(spec.sampleRate);
}

void Reverb::process(juce::AudioBuffer<float> &buffer) {
    juce::AudioBuffer<float> dryBuffer = buffer;
    juce::dsp::AudioBlock<float> dryBlock(dryBuffer);
    dryWetMixer.pushDrySamples(dryBlock);

    juce::dsp::AudioBlock<float> wetBlock(buffer);
    reverb.processStereo(wetBlock.getChannelPointer(0), wetBlock.getChannelPointer(1), wetBlock.getNumSamples());

    juce::dsp::AudioBlock<float> mixBlock(buffer);
    dryWetMixer.mixWetSamples(mixBlock);
}

void Reverb::setActive(bool value) {
    isReverbActive = value;
}

bool Reverb::isActive() const {
    return isReverbActive;
}

void Reverb::update(float mix, float size) {
    dryWetMixer.setWetMixProportion(mix);
    reverb.setParameters(juce::Reverb::Parameters({size}));
}
