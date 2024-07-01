#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
AudioPluginAudioProcessorEditor::AudioPluginAudioProcessorEditor(
        AudioPluginAudioProcessor &p)
        : AudioProcessorEditor(&p), audioProcessor(p) {

    prepareSlider();
    prepareComboBox();
    prepareTremolo();
    prepareReverb();

    juce::ignoreUnused(audioProcessor);
    setSize(350, 400);
}

AudioPluginAudioProcessorEditor::~AudioPluginAudioProcessorEditor() {
    volumeSlider.setLookAndFeel(nullptr);
}

//==============================================================================
void AudioPluginAudioProcessorEditor::paint(juce::Graphics &g) {
    g.fillAll(juce::Colour(0xFF303030));


    g.setColour(juce::Colour(0xFFFFD700));
    g.setFont(15.0f);
}

void AudioPluginAudioProcessorEditor::resized() {
    tremoloOnOffButton.setBounds(((getWidth() / 5) * 1), 50, 50, 50);
    tremoloFreqSlider.setBounds(((getWidth() / 5) * 2), 20, 120, 120);

    reverbOnOffButton.setBounds(((getWidth() / 5) * 1), 175, 50, 50);
    dryWetSlider.setBounds(((getWidth() / 5) * 2), 150, 100, 100);
    roomSizeSlider.setBounds(((getWidth() / 5) * 3), 150, 100, 100);

    volumeSlider.setBounds(((getWidth() / 4) * 1), 260, 100, 100);
    panSlider.setBounds(((getWidth() / 4) * 2), 260, 100, 100);
}

void AudioPluginAudioProcessorEditor::prepareComboBox() {
    lfoChoiceCombo.addItem("Sine", 1);
    lfoChoiceCombo.addItem("Square", 2);
    lfoChoiceCombo.addItem("Saw", 3);
    lfoChoiceCombo.addItem("Triangle", 4);
    lfoChoiceCombo.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(lfoChoiceCombo);

    lfoChoiceAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(
            audioProcessor.state,
            "Waveform",
            lfoChoiceCombo);
}

void AudioPluginAudioProcessorEditor::prepareSlider() {
    volumeSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    volumeSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 20);
    volumeSlider.setTextValueSuffix(" dB");
    addAndMakeVisible(volumeSlider);
    volumeSlider.setLookAndFeel(&knobLookAndFeel);
    volumeAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
            audioProcessor.state,
            "Volume", volumeSlider);

    panSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    panSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 20);
    panSlider.setTextValueSuffix(" Pan");
    addAndMakeVisible(panSlider);
    panSlider.setLookAndFeel(&knobLookAndFeel);
    panningAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
            audioProcessor.state,
            "Panning", panSlider);
}

void AudioPluginAudioProcessorEditor::prepareTremolo() {
    tremoloOnOffButton.setClickingTogglesState(true);
    tremoloOnOffButton.setLookAndFeel(&switchLookAndFeel);

    addAndMakeVisible(tremoloOnOffButton);
    tremoloOnOffButtonAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(
            audioProcessor.state, "Tremolo", tremoloOnOffButton);


    tremoloFreqSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    tremoloFreqSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 20);
    tremoloFreqSlider.setValue(2.0f);
    addAndMakeVisible(tremoloFreqSlider);
    tremoloFreqSlider.setLookAndFeel(&knobLookAndFeel);
    tremoloFrequencyAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
            audioProcessor.state, "TremoloFreq", tremoloFreqSlider);
}

void AudioPluginAudioProcessorEditor::prepareReverb() {
    reverbOnOffButton.setClickingTogglesState(true);
    reverbOnOffButton.setLookAndFeel(&switchLookAndFeel);
    addAndMakeVisible(reverbOnOffButton);
    reverbOnOffButtonAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(
            audioProcessor.state, "Reverb", reverbOnOffButton);


    roomSizeSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    roomSizeSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 20);
    roomSizeSlider.setValue(0.5f);
    addAndMakeVisible(roomSizeSlider);
    roomSizeSlider.setLookAndFeel(&knobLookAndFeel);
    roomSizeAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
            audioProcessor.state, "Size", roomSizeSlider);


    dryWetSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    dryWetSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 20);
    dryWetSlider.setValue(0.5f);
    addAndMakeVisible(dryWetSlider);
    dryWetSlider.setLookAndFeel(&knobLookAndFeel);
    dryWetAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
            audioProcessor.state, "DryWet", dryWetSlider);
}