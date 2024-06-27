#include "Volume.h"

Volume::Volume() = default;

Volume::~Volume() = default;

float Volume::getValue() const {
    return value;
}

void Volume::setValue(float value) {
    Volume::value = value;
}

void Volume::process(juce::AudioBuffer<float> &buffer) {
    for (int channel = 0; channel < buffer.getNumChannels(); ++channel)
    {
        for (int i = 0; i < buffer.getNumSamples(); ++i)
        {
            buffer.getWritePointer(channel)[i] *= value;
        }
    }
}
