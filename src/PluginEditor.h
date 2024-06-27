#pragma once

#include "PluginProcessor.h"

//==============================================================================
class AudioPluginAudioProcessorEditor
        : public juce::AudioProcessorEditor, public juce::Slider::Listener {
public:
    explicit AudioPluginAudioProcessorEditor(AudioPluginAudioProcessor &);

    ~AudioPluginAudioProcessorEditor() override;

    //==============================================================================
    void paint(juce::Graphics &) override;

    void resized() override;

private:
    AudioPluginAudioProcessor &audioProcessor;

    juce::Slider lfoFreqSlider;
    juce::TextButton lfoOnOffButton;
    juce::ComboBox lfoChoiceCombo;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> lfoOnOffButtonAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> lfoFrequencyAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> lfoChoiceAttachment;

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

    void prepareComboBox();

    void prepareSlider();

    void prepareLFO();

    void prepareFilters();

    void sliderValueChanged(juce::Slider *) override;
};
