#include <juce_dsp/juce_dsp.h>
#include "BinaryData.h"


class Reverb {
public:
    void prepare(juce::dsp::ProcessSpec spec);

    void update(float mix, float size);

    void process(juce::AudioBuffer<float> &buffer);

    void setActive(bool value);

    bool isActive() const;


private:
    juce::Reverb reverb;
    juce::dsp::DryWetMixer<float> dryWetMixer;
    bool isReverbActive = false;
};
