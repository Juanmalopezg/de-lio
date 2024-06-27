#include <juce_dsp/juce_dsp.h>
#include <juce_audio_processors/juce_audio_processors.h>

class LFO {
public:
    enum Waveform {
        Sine = 0,
        Square = 1,
        Saw = 2,
        Triangle = 3
    };

    juce::dsp::Oscillator<float> lfoSine, lfoSquare, lfoSaw, lfoTriangle;
    juce::dsp::Gain<float> gain;
    juce::dsp::Oscillator<float> *currentOscillator;

    void prepareToPlay(double sampleRate, int samplesPerBlock);

    void setFrequency(float freq);

    void setActive(bool active);

    bool isActive() const;

    void process(juce::AudioBuffer<float> &buffer, Waveform waveform);

private:
    bool isLFOActive = false;

    static float sineWave(float x);

    static float squareWave(float x);

    static float sawtoothWave(float x);

    static float triangleWave(float x);

};