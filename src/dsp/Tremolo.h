//
// Created by Juan Manuel López Gargiulo on 27/06/2024.
//

#ifndef MULTIFILTER_TREMOLO_H
#define MULTIFILTER_TREMOLO_H


#include "LFO.h"

class Tremolo {
public:

    void setValue(float value);

    void process(juce::AudioBuffer<float> &buffer);

    void setActive(bool value);

    void prepare(double sampleRate, int samplesPerBlock);

    bool isActive();

private:
    float freq;
    LFO lfo;
    bool isTremoloActive = false;

};


#endif //MULTIFILTER_TREMOLO_H
