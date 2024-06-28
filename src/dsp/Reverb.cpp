
#include "Reverb.h"


void Reverb::prepare(juce::dsp::ProcessSpec spec) {
    convolution.reset();
    convolution.prepare(spec);
    convolution.loadImpulseResponse(
            BinaryData::IR_wav,
            BinaryData::IR_wavSize,
            juce::dsp::Convolution::Stereo::yes,
            juce::dsp::Convolution::Trim::yes,
            BinaryData::IR_wavSize / 3,
            juce::dsp::Convolution::Normalise::no);

    dryWetMixer.prepare(spec);
    dryWetMixer.setWetMixProportion(0.5);
    dryWetMixer.setWetLatency(0.0f);
}

void Reverb::process(juce::AudioBuffer<float> &buffer) {
    juce::AudioBuffer<float> dryBuffer = buffer;
    juce::dsp::AudioBlock<float> dryBlock(dryBuffer);
    dryWetMixer.pushDrySamples(dryBlock);

    juce::dsp::AudioBlock<float> wetBlock(buffer);
    juce::dsp::ProcessContextReplacing<float> wetContext(wetBlock);
    convolution.process(wetContext);

    juce::dsp::AudioBlock<float> mixBlock(buffer);
    dryWetMixer.mixWetSamples(mixBlock);
}

void Reverb::setActive(bool value) {
    isReverbActive = value;
}

bool Reverb::isActive() const {
    return isReverbActive;
}

void Reverb::update(float value) {
    dryWetMixer.setWetMixProportion(value);
}
