//
// Created by Juan Manuel López Gargiulo on 23/03/2024.
//
#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_core/juce_core.h>


class KnobLookAndFeel : public juce::LookAndFeel_V4 {
public:
    KnobLookAndFeel();

public:
    void drawRotarySlider(juce::Graphics &g,
                          int x, int y, int width, int height, float sliderPos,
                          float rotaryStartAngle, float rotaryEndAngle,
                          juce::Slider &slider) override;

private:
    juce::Image knobImage;
};