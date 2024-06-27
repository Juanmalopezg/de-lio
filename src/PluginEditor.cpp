#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
AudioPluginAudioProcessorEditor::AudioPluginAudioProcessorEditor(
        AudioPluginAudioProcessor &p)
        : AudioProcessorEditor(&p), audioProcessor(p) {

    prepareSlider();
    prepareComboBox();
    prepareLFO();
    prepareFilters();

    juce::ignoreUnused(audioProcessor);
    setSize(600, 400);
}

AudioPluginAudioProcessorEditor::~AudioPluginAudioProcessorEditor() {
    volumeSlider.setLookAndFeel(nullptr);
    volumeSlider.removeListener(this);
}

//==============================================================================
void AudioPluginAudioProcessorEditor::paint(juce::Graphics &g) {
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll(getLookAndFeel().findColour(
            juce::ResizableWindow::backgroundColourId));

    g.setColour(juce::Colours::white);
    g.setFont(15.0f);
}

void AudioPluginAudioProcessorEditor::resized() {
    lfoOnOffButton.setBounds(20, 20, 50, 50);
    lfoChoiceCombo.setBounds(80, 40, 100, 20);
    lfoFreqSlider.setBounds(180, 0, 100, 100);


    lowPassOnOffButton.setBounds(20, 120, 50, 50);
    bandPassOnOffButton.setBounds(80, 120, 50, 50);
    highPassOnOffButton.setBounds(140, 120, 50, 50);

    volumeSlider.setBounds(0, 170, 100, 100);
    panSlider.setBounds(100, 170, 100, 100);
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
    volumeSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 20);
    volumeSlider.setTextValueSuffix(" dB");
    addAndMakeVisible(volumeSlider);
    volumeSlider.addListener(this);
    volumeAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
            audioProcessor.state,
            "Volume", volumeSlider);

    panSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    panSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 20);
    panSlider.setTextValueSuffix(" Pan");
    addAndMakeVisible(panSlider);
    panSlider.addListener(this);
    panningAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
            audioProcessor.state,
            "Panning", panSlider);
}

void AudioPluginAudioProcessorEditor::prepareFilters() {
    lowPassOnOffButton.setButtonText("LowPass");
    lowPassOnOffButton.setClickingTogglesState(true);
    addAndMakeVisible(lowPassOnOffButton);

    lowPassOnOffButtonAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(
            audioProcessor.state, "LowPass", lowPassOnOffButton);

    bandPassOnOffButton.setButtonText("BandPass");
    bandPassOnOffButton.setClickingTogglesState(true);
    addAndMakeVisible(bandPassOnOffButton);

    bandPassOnOffButtonAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(
            audioProcessor.state, "BandPass", bandPassOnOffButton);

    highPassOnOffButton.setButtonText("HighPass");
    highPassOnOffButton.setClickingTogglesState(true);
    addAndMakeVisible(highPassOnOffButton);
    highPassOnOffButtonAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(
            audioProcessor.state, "HighPass", highPassOnOffButton);

}

void AudioPluginAudioProcessorEditor::prepareLFO() {
    lfoOnOffButton.setButtonText("LFO");
    lfoOnOffButton.setClickingTogglesState(true);

    addAndMakeVisible(lfoOnOffButton);
    lfoOnOffButtonAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(
            audioProcessor.state, "LFO", lfoOnOffButton);


    lfoFreqSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    lfoFreqSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 20);
    lfoFreqSlider.setValue(440.0f);
    addAndMakeVisible(lfoFreqSlider);
    lfoFreqSlider.addListener(this);
    lfoFrequencyAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
            audioProcessor.state, "LFOFreq", lfoFreqSlider);
}

void AudioPluginAudioProcessorEditor::sliderValueChanged(juce::Slider *s) {
    if (s == &lfoFreqSlider)
    {
        DBG(s->getValue());
    }
}