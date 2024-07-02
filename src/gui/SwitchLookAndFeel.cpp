//
// Created by Juan Manuel López Gargiulo on 01/07/2024.
//

#include "SwitchLookAndFeel.h"
#include "BinaryData.h"

SwitchLookAndFeel::SwitchLookAndFeel() {
    switchImage = juce::ImageCache::getFromMemory(BinaryData::switch_png, BinaryData::switch_pngSize);
    ledImage = juce::ImageCache::getFromMemory(BinaryData::led_png, BinaryData::led_pngSize);
}

void
SwitchLookAndFeel::drawButtonBackground(juce::Graphics &g, juce::Button &button,
                                        const juce::Colour &backgroundColour,
                                        bool isMouseOverButton,
                                        bool isButtonDown) {
    ledDrawPosition = button.getToggleState() ? ledImage.getHeight() / 2 : 0;
    switchDrawPosition = button.getToggleState() ? 0 : switchImage.getHeight() /2;
    g.drawImage(ledImage, 0, 0, button.getWidth(), button.getHeight() / 2, 0,
                ledDrawPosition, ledImage.getWidth(), ledImage.getHeight() / 2);
    g.drawImage(switchImage, 0, (button.getHeight() / 2) - 10,
                button.getWidth(), button.getHeight() / 2, 0,
                switchDrawPosition, switchImage.getWidth(),
                switchImage.getHeight() / 2);
}

