
#include "Tremolo.h"

void Tremolo::setValue(float value) {
    lfo.setFrequency(value);
}

void Tremolo::setActive(bool value) {
    isTremoloActive = value;
}

void Tremolo::prepare(double sampleRate, int samplesPerBlock) {
    lfo.prepareToPlay(sampleRate, samplesPerBlock);
}

void Tremolo::process(juce::AudioBuffer<float> &buffer) {
    lfo.process(buffer, LFO::Sine);
}

bool Tremolo::isActive() {
    return isTremoloActive;
}
