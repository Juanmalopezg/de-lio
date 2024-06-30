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
    tremoloOnOffButton.setBounds(20, 20, 50, 50);
    tremoloFreqSlider.setBounds(100, 0, 100, 100);

    reverbOnOffButton.setBounds(20, 120, 50, 50);
    dryWetSlider.setBounds(100, 100, 100, 100);
    roomSizeSlider.setBounds(200, 100, 100, 100);

//    lfoChoiceCombo.setBounds(350, 40, 100, 20);


//    lowPassOnOffButton.setBounds(20, 120, 50, 50);
//    bandPassOnOffButton.setBounds(80, 120, 50, 50);
//    highPassOnOffButton.setBounds(140, 120, 50, 50);

    volumeSlider.setBounds(0, 200, 100, 100);
    panSlider.setBounds(100, 200, 100, 100);
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

void AudioPluginAudioProcessorEditor::prepareTremolo() {
    tremoloOnOffButton.setButtonText("Tremolo");
    tremoloOnOffButton.setClickingTogglesState(true);

    addAndMakeVisible(tremoloOnOffButton);
    tremoloOnOffButtonAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(
            audioProcessor.state, "Tremolo", tremoloOnOffButton);


    tremoloFreqSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    tremoloFreqSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 20);
    tremoloFreqSlider.setValue(2.0f);
    addAndMakeVisible(tremoloFreqSlider);
    tremoloFreqSlider.addListener(this);
    tremoloFrequencyAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
            audioProcessor.state, "TremoloFreq", tremoloFreqSlider);
}

void AudioPluginAudioProcessorEditor::prepareReverb() {
    reverbOnOffButton.setButtonText("Reverb");
    reverbOnOffButton.setClickingTogglesState(true);

    addAndMakeVisible(reverbOnOffButton);
    reverbOnOffButtonAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(
            audioProcessor.state, "Reverb", reverbOnOffButton);


    roomSizeSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    roomSizeSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 20);
    roomSizeSlider.setValue(0.5f);
    addAndMakeVisible(roomSizeSlider);
    roomSizeSlider.addListener(this);
    roomSizeAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
            audioProcessor.state, "Size", roomSizeSlider);

    dryWetSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    dryWetSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 20);
    dryWetSlider.setValue(0.5f);
    addAndMakeVisible(dryWetSlider);
    dryWetSlider.addListener(this);
    dryWetAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
            audioProcessor.state, "DryWet", dryWetSlider);
}

void AudioPluginAudioProcessorEditor::sliderValueChanged(juce::Slider *s) {
    if (s == &tremoloFreqSlider)
    {
        DBG(s->getValue());
    }
}


