#include "Filter.h"

void Filter::prepare(juce::dsp::ProcessSpec &spec) {

    bandPassFilter.prepare(spec);
    *bandPassFilter.state = juce::dsp::IIR::ArrayCoefficients<float>::makeBandPass(
            spec.sampleRate, 1000.0f);

    highpassFilter.prepare(spec);
    *highpassFilter.state = juce::dsp::IIR::ArrayCoefficients<float>::makeHighPass(
            spec.sampleRate, 2000.0f);

    lowPassFilter.prepare(spec);
    lowPassFilter.setType(juce::dsp::StateVariableTPTFilterType::lowpass);
    lowPassFilter.setCutoffFrequency(500.0f);
}

void Filter::processHighPass(juce::AudioBuffer<float> &buffer) {
    auto audioBlock = juce::dsp::AudioBlock<float>(buffer);
    auto context = juce::dsp::ProcessContextReplacing<float>(audioBlock);
    highpassFilter.process(context);
}

void Filter::processBandPass(juce::AudioBuffer<float> &buffer) {
    auto audioBlock = juce::dsp::AudioBlock<float>(buffer);
    auto context = juce::dsp::ProcessContextReplacing<float>(audioBlock);
    bandPassFilter.process(context);
}

void Filter::processLowPass(juce::AudioBuffer<float> &buffer) {
    auto audioBlock = juce::dsp::AudioBlock<float>(buffer);
    auto context = juce::dsp::ProcessContextReplacing<float>(audioBlock);
    lowPassFilter.process(context);
}

void Filter::setActive(bool active) {
    isFilterActive = active;
}

bool Filter::isActive() const {
    return isFilterActive;
}
