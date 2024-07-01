//
// Created by Juan Manuel López Gargiulo on 01/07/2024.
//

#ifndef DELIO_SWITCHLOOKANDFEEL_H
#define DELIO_SWITCHLOOKANDFEEL_H

#include <juce_gui_basics/juce_gui_basics.h>


class SwitchLookAndFeel : public juce::LookAndFeel_V4 {
public:
    SwitchLookAndFeel();

    void drawButtonBackground(juce::Graphics &g, juce::Button &button,
                              const juce::Colour &backgroundColour,
                              bool isMouseOverButton,
                              bool isButtonDown) override;

private:
    juce::Image switchImage;

};


#endif //DELIO_SWITCHLOOKANDFEEL_H
