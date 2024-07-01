//
// Created by Juan Manuel López Gargiulo on 01/07/2024.
//

#include "SwitchLookAndFeel.h"
#include "BinaryData.h"

SwitchLookAndFeel::SwitchLookAndFeel() {
    switchImage = juce::ImageCache::getFromMemory(BinaryData::switch_png, BinaryData::switch_pngSize);
}

void
SwitchLookAndFeel::drawButtonBackground(juce::Graphics &g, juce::Button &button,
                                        const juce::Colour &backgroundColour,
                                        bool isMouseOverButton,
                                        bool isButtonDown) {
    int drawPosition = button.getToggleState() ? 0 : switchImage.getHeight() / 2;
    g.drawImage(switchImage, 0, 0, button.getWidth(), button.getHeight(), 0,
                drawPosition, switchImage.getWidth(), switchImage.getHeight() / 2);

}

