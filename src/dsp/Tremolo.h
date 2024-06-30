#include "LFO.h"
#include "Filter.h"

class Tremolo {
public:

    void update(float value);

    void process(juce::AudioBuffer<float> &buffer);

    void setActive(bool value);

    void prepare(double sampleRate, int samplesPerBlock,
                 juce::dsp::ProcessSpec spec);

    bool isActive();

private:
    LFO lfoLeft, lfoRight;
    Filter lowPassFilter;

    bool isTremoloActive = false;
};
