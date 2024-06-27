#include "Panning.h"

Panning::~Panning() = default;

float Panning::getValue() const {
    return panningValue;
}

void Panning::process(juce::AudioBuffer<float> &buffer) {
    for (int channel = 0; channel < buffer.getNumChannels(); ++channel)
    {
        for (int i = 0; i < buffer.getNumSamples(); ++i)
        {
            float sample = buffer.getSample(channel, i);

            if (channel == 0)
            {
                sample *= sqrt((PI / 2.0f - panningValue) * (2.0f / PI) *
                               (cos(panningValue)));
            }
            if (channel == 1)
            {
                sample *= sqrt(panningValue * (2.0f / PI) * sin(panningValue));
            }

            buffer.setSample(channel, i, sample);
        }
    }
}

Panning::Panning() {

}

void Panning::setValue(float value) {
    panningValue = value;
}

