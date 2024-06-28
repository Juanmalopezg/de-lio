
#include "Reverb.h"


void Reverb::prepare(juce::dsp::ProcessSpec spec) {
    convolution.reset();
    convolution.prepare(spec);
    convolution.loadImpulseResponse(
            BinaryData::IR_wav,
            BinaryData::IR_wavSize,
            juce::dsp::Convolution::Stereo::yes,
            juce::dsp::Convolution::Trim::yes,
            BinaryData::IR_wavSize/3,
            juce::dsp::Convolution::Normalise::no
    );

}

void Reverb::process(juce::AudioBuffer<float> &buffer) {
    juce::dsp::AudioBlock<float> block(buffer);
    juce::dsp::ProcessContextReplacing<float> context(block);
    convolution.process(context);
}

void Reverb::setActive(bool value) {
    isReverbActive = value;
}

bool Reverb::isActive() const {
    return isReverbActive;
}

void Reverb::update(float value) {

}
