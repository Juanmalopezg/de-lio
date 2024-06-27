#include <juce_dsp/juce_dsp.h>


class Filter {
public:

    void prepare(juce::dsp::ProcessSpec &inSpec);

//    void setActive(bool active);

//    bool isActive() const;

    void processLowPass(juce::AudioBuffer<float> &buffer);

//    void processBandPass(juce::AudioBuffer<float> &buffer);
//
//    void processHighPass(juce::AudioBuffer<float> &buffer);

private:
    juce::dsp::ProcessorDuplicator<juce::dsp::IIR::Filter<float>, juce::dsp::IIR::Coefficients<float>> bandPassFilter;

    juce::dsp::ProcessorDuplicator<juce::dsp::IIR::Filter<float>, juce::dsp::IIR::Coefficients<float>> highpassFilter;

    juce::dsp::StateVariableTPTFilter<float> lowPassFilter;

    bool isFilterActive = false;
};