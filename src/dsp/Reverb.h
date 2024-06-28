#include <juce_dsp/juce_dsp.h>
#include "BinaryData.h"


class Reverb {
public:
    void prepare(juce::dsp::ProcessSpec spec);

    void update(float value);

    void process(juce::AudioBuffer<float> &buffer);

    void setActive(bool value);

    bool isActive() const;


private:
    juce::dsp::Convolution convolution{juce::dsp::Convolution::NonUniform{512}};

    bool isReverbActive = false;
};
