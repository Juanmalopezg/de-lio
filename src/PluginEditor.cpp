#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
AudioPluginAudioProcessorEditor::AudioPluginAudioProcessorEditor(
        AudioPluginAudioProcessor &p)
        : AudioProcessorEditor(&p), audioProcessor(p) {

    prepareSlider();
    prepareTremolo();
    prepareReverb();

    juce::ignoreUnused(audioProcessor);
    setSize(300, 450);
}

AudioPluginAudioProcessorEditor::~AudioPluginAudioProcessorEditor() {
    volumeSlider.setLookAndFeel(nullptr);
}

//==============================================================================
void AudioPluginAudioProcessorEditor::paint(juce::Graphics &g) {
    g.fillAll(juce::Colour(0xFF212121));
    g.setColour(juce::Colour(0xFFFFD700));
    g.setFont(15.0f);

    bg = juce::Drawable::createFromImageData(
            BinaryData::bg_png, BinaryData::bg_pngSize);
    addAndMakeVisible(*bg);

    juce::String versionString = "1.0.0";
    versionLabel.setText("v " + versionString, juce::dontSendNotification);
    versionLabel.setColour(juce::Label::textColourId,juce::Colour(0xFFFFD95A));
    addAndMakeVisible(versionLabel);
}

void AudioPluginAudioProcessorEditor::resized() {
    tremoloOnOffButton.setBounds(((getWidth() / 5) * 1) - 35, 65, 50, 100);
    tremoloFreqSlider.setBounds(((getWidth() / 5) * 2) - 45, 65, 90, 90);

    reverbOnOffButton.setBounds(((getWidth() / 5) * 1) - 35, 185, 50, 100);
    dryWetSlider.setBounds(((getWidth() / 5) * 2) - 45, 185, 90, 90);
    roomSizeSlider.setBounds(((getWidth() / 5) * 3) - 25, 185, 90, 90);

    volumeSlider.setBounds(((getWidth() / 5) * 2) - 45, 300, 90, 90);
    panSlider.setBounds(((getWidth() / 5) * 3) - 25, 300, 90, 90);

    versionLabel.setBounds((getWidth() / 2) - 25, 400, 50, 50);
}

void AudioPluginAudioProcessorEditor::prepareSlider() {
    volumeSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    volumeSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 30, 15);
    addAndMakeVisible(volumeSlider);
    volumeSlider.setLookAndFeel(&knobLookAndFeel);
    volumeAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
            audioProcessor.valueTreeState,
            "Volume", volumeSlider);

    panSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    panSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 30, 15);
    addAndMakeVisible(panSlider);
    panSlider.setLookAndFeel(&knobLookAndFeel);
    panningAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
            audioProcessor.valueTreeState,
            "Panning", panSlider);
}

void AudioPluginAudioProcessorEditor::prepareTremolo() {
    tremoloOnOffButton.setClickingTogglesState(true);
    tremoloOnOffButton.setLookAndFeel(&switchLookAndFeel);

    addAndMakeVisible(tremoloOnOffButton);
    tremoloOnOffButtonAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(
            audioProcessor.valueTreeState, "Tremolo", tremoloOnOffButton);


    tremoloFreqSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    tremoloFreqSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 30, 15);
    tremoloFreqSlider.setValue(2.0f);
    addAndMakeVisible(tremoloFreqSlider);
    tremoloFreqSlider.setLookAndFeel(&knobLookAndFeel);
    tremoloFrequencyAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
            audioProcessor.valueTreeState, "TremoloFreq", tremoloFreqSlider);
}

void AudioPluginAudioProcessorEditor::prepareReverb() {
    reverbOnOffButton.setClickingTogglesState(true);
    reverbOnOffButton.setLookAndFeel(&switchLookAndFeel);
    addAndMakeVisible(reverbOnOffButton);
    reverbOnOffButtonAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(
            audioProcessor.valueTreeState, "Reverb", reverbOnOffButton);


    roomSizeSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    roomSizeSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 30, 15);
    roomSizeSlider.setValue(0.5f);
    addAndMakeVisible(roomSizeSlider);
    roomSizeSlider.setLookAndFeel(&knobLookAndFeel);
    roomSizeAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
            audioProcessor.valueTreeState, "Size", roomSizeSlider);


    dryWetSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    dryWetSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 30, 15);
    dryWetSlider.setValue(0.5f);
    addAndMakeVisible(dryWetSlider);
    dryWetSlider.setLookAndFeel(&knobLookAndFeel);
    dryWetAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
            audioProcessor.valueTreeState, "DryWet", dryWetSlider);
}