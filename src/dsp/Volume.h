#pragma once

#include <juce_dsp/juce_dsp.h>

//==============================================================================
class Volume {
public:
    //==============================================================================
    Volume();

    ~Volume();

private:
    float value{};
public:
    [[nodiscard]] float getValue() const;

    void setValue(float value);

    void process(juce::AudioBuffer<float> &buffer);
};
