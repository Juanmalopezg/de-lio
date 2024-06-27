#include <juce_dsp/juce_dsp.h>

static const float PI = juce::MathConstants<float>::pi;

class Panning {
private:
    float panningValue{juce::MathConstants<float>::pi / 4.0f};
public:
    Panning();

    ~Panning();

    float getValue() const;

    void setValue(float value);

    void process(juce::AudioBuffer<float> &buffer);
};