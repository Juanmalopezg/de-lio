#include "LFO.h"
#include <cmath>


void LFO::prepareToPlay(double sampleRate, int samplesPerBlock) {
    juce::dsp::ProcessSpec spec{sampleRate,
                                static_cast<juce::uint32> (samplesPerBlock), 2};
    lfoSine.prepare(spec);
    lfoSquare.prepare(spec);
    lfoSaw.prepare(spec);
    lfoTriangle.prepare(spec);
    gain.prepare(spec);

    lfoSine.initialise([](float x)
                       { return LFO::sineWave(x); });
    lfoSquare.initialise([](float x)
                         { return LFO::squareWave(x); });
    lfoSaw.initialise([](float x)
                      { return LFO::sawtoothWave(x); });
    lfoTriangle.initialise([](float x)
                           { return LFO::triangleWave(x); });
    currentOscillator = &lfoSine;
}

void LFO::process(juce::AudioBuffer<float> &buffer, Waveform waveform) {
    switch (waveform)
    {
        case LFO::Sine:
            currentOscillator = &lfoSine;
            break;
        case LFO::Square:
            currentOscillator = &lfoSquare;
            break;
        case LFO::Saw:
            currentOscillator = &lfoSaw;
            break;
        case LFO::Triangle:
            currentOscillator = &lfoTriangle;
            break;
    }

    for (int channel = 0; channel < buffer.getNumChannels(); ++channel)
    {
        auto *channelData = buffer.getWritePointer(channel);
        for (int i = 0; i < buffer.getNumSamples(); ++i)
        {
            auto sample = currentOscillator->processSample(0);
            channelData[i] += sample;
        }
    }
}

void LFO::setFrequency(float freq) {
    currentOscillator->setFrequency(freq);
}

float LFO::sineWave(float x) {
    return sinf(x);
}

float LFO::squareWave(float x) {
    return x < 0.0f ? -1.0f : 1.0f;
}

float LFO::triangleWave(float x) {
    return 2.0f * std::abs(x / juce::MathConstants<float>::pi) - 1.0f;
}

float LFO::sawtoothWave(float x) {
    return x / juce::MathConstants<float>::pi;
}

bool LFO::isActive() const { return isLFOActive; }

void LFO::setActive(bool active) { isLFOActive = active; }