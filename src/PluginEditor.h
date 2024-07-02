#pragma once

#include "PluginProcessor.h"
#include "gui/KnobLookAndFeel.h"
#include "gui/SwitchLookAndFeel.h"
#include <juce_core/system/juce_TargetPlatform.h> // Este archivo incluye AppConfig.h


//==============================================================================
class AudioPluginAudioProcessorEditor
        : public juce::AudioProcessorEditor {
public:
    explicit AudioPluginAudioProcessorEditor(AudioPluginAudioProcessor &);

    ~AudioPluginAudioProcessorEditor() override;

    //==============================================================================
    void paint(juce::Graphics &) override;

    void resized() override;

private:
    AudioPluginAudioProcessor &audioProcessor;

    juce::Slider tremoloFreqSlider;
    juce::TextButton tremoloOnOffButton;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> tremoloOnOffButtonAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> tremoloFrequencyAttachment;

    juce::Slider dryWetSlider;
    juce::TextButton reverbOnOffButton;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> reverbOnOffButtonAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> dryWetAttachment;

    juce::Slider roomSizeSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> roomSizeAttachment;

    juce::TextButton lowPassOnOffButton;
    juce::TextButton bandPassOnOffButton;
    juce::TextButton highPassOnOffButton;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> lowPassOnOffButtonAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> bandPassOnOffButtonAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> highPassOnOffButtonAttachment;

    juce::Slider volumeSlider;
    juce::Slider panSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> volumeAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> panningAttachment;

    KnobLookAndFeel knobLookAndFeel;
    SwitchLookAndFeel switchLookAndFeel;
    std::unique_ptr<juce::Drawable> bg;
    juce::Label versionLabel;

    void prepareSlider();

    void prepareTremolo();

    void prepareReverb();
};
