#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
AudioPluginAudioProcessor::AudioPluginAudioProcessor()
        : AudioProcessor(BusesProperties()
#if !JucePlugin_IsMidiEffect
#if !JucePlugin_IsSynth
                                 .withInput("Input",
                                            juce::AudioChannelSet::stereo(),
                                            true)
#endif
                                 .withOutput("Output",
                                             juce::AudioChannelSet::stereo(),
                                             true)
#endif
), state(*this, nullptr, "Parameters", createParameters()) {
}

AudioPluginAudioProcessor::~AudioPluginAudioProcessor() = default;

juce::AudioProcessorValueTreeState::ParameterLayout
AudioPluginAudioProcessor::createParameters() {
    juce::AudioProcessorValueTreeState::ParameterLayout parameters;

    // Tremolo parameters
    parameters.add(std::make_unique<juce::AudioParameterBool>(
            juce::ParameterID{"Tremolo", 1}, "Tremolo On/Off", false));
    parameters.add(std::make_unique<juce::AudioParameterFloat>(
            juce::ParameterID{"TremoloFreq", 1}, "Tremolo Freq", 0.0f, 12.0f,
            2.0f));

    // Reverb parameters
    parameters.add(std::make_unique<juce::AudioParameterBool>(
            juce::ParameterID{"Reverb", 1}, "Reverb On/Off", false));
    parameters.add(std::make_unique<juce::AudioParameterFloat>(
            juce::ParameterID{"ReverbRate", 1}, "Reverb Rate", 0.1f, 500.0f,
            5.0f));

    // Oscillator parameters
    parameters.add(std::make_unique<juce::AudioParameterChoice>(
            juce::ParameterID{"Waveform", 1}, "Waveform",
            juce::StringArray("Sine", "Square", "Saw", "Triangle"), 1));
    parameters.add(std::make_unique<juce::AudioParameterFloat>(
            juce::ParameterID{"DryWet", 1}, "DryWet", 0.0f, 100.0f, 100.0f));

    // Filter parameters
    parameters.add(std::make_unique<juce::AudioParameterBool>(
            juce::ParameterID{"LowPass", 1}, "LowPass On/Off", false));
    parameters.add(std::make_unique<juce::AudioParameterBool>(
            juce::ParameterID{"PassBand", 1}, "PassBand On/Off", false));
    parameters.add(std::make_unique<juce::AudioParameterBool>(
            juce::ParameterID{"HighPass", 1}, "HighPass On/Off", false));

    // General parameters
    parameters.add(std::make_unique<juce::AudioParameterFloat>(
            juce::ParameterID{"Volume", 1}, "Volume", 0.0f, 1.0f, 0.5f));
    parameters.add(std::make_unique<juce::AudioParameterFloat>(
            juce::ParameterID{"Panning", 1}, "Panning", 0.0f,
            juce::MathConstants<float>::pi / 2.0f,
            juce::MathConstants<float>::pi / 4.0f));

    return parameters;
}

void AudioPluginAudioProcessor::updateParameters() {
    float frequency = *state.getRawParameterValue("TremoloFreq");
    tremolo.setActive(
            static_cast<bool>(*state.getRawParameterValue("Tremolo")));
    tremolo.update(frequency);

    float rate = *state.getRawParameterValue("ReverbRate");
    reverb.setActive(
            static_cast<bool>(*state.getRawParameterValue("Reverb")));
    reverb.update(rate);

//    bandPassFilter.setActive(
//            static_cast<bool>(*state.getRawParameterValue("PassBand")));
//    highPassFilter.setActive(
//            static_cast<bool>(*state.getRawParameterValue("HighPass")));

    float v = *state.getRawParameterValue("Volume");
    float p = *state.getRawParameterValue("Panning");
    volume.setValue(v);
    panning.setValue(p);

}

//==============================================================================
const juce::String AudioPluginAudioProcessor::getName() const {
    return JucePlugin_Name;
}

bool AudioPluginAudioProcessor::acceptsMidi() const {
#if JucePlugin_WantsMidiInput
    return true;
#else
    return false;
#endif
}

bool AudioPluginAudioProcessor::producesMidi() const {
#if JucePlugin_ProducesMidiOutput
    return true;
#else
    return false;
#endif
}

bool AudioPluginAudioProcessor::isMidiEffect() const {
#if JucePlugin_IsMidiEffect
    return true;
#else
    return false;
#endif
}

double AudioPluginAudioProcessor::getTailLengthSeconds() const {
    return 0.0;
}

int AudioPluginAudioProcessor::getNumPrograms() {
    return 1; // NB: some hosts don't cope very well if you tell them there are 0 programs,
    // so this should be at least 1, even if you're not really implementing programs.
}

int AudioPluginAudioProcessor::getCurrentProgram() {
    return 0;
}

void AudioPluginAudioProcessor::setCurrentProgram(int index) {
    juce::ignoreUnused(index);
}

const juce::String AudioPluginAudioProcessor::getProgramName(int index) {
    juce::ignoreUnused(index);
    return {};
}

void AudioPluginAudioProcessor::changeProgramName(int index,
                                                  const juce::String &newName) {
    juce::ignoreUnused(index, newName);
}

//==============================================================================
void AudioPluginAudioProcessor::prepareToPlay(double sampleRate,
                                              int samplesPerBlock) {
    juce::dsp::ProcessSpec spec{};
    spec.sampleRate = sampleRate;
    spec.maximumBlockSize = samplesPerBlock;
    spec.numChannels = getTotalNumOutputChannels();

    tremolo.prepare(sampleRate, samplesPerBlock, spec);
    reverb.prepare(spec);
//    bandPassFilter.prepare(spec);
//    highPassFilter.prepare(spec);
}

void AudioPluginAudioProcessor::releaseResources() {
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

bool AudioPluginAudioProcessor::isBusesLayoutSupported(
        const BusesLayout &layouts) const {
#if JucePlugin_IsMidiEffect
    juce::ignoreUnused(layouts);
    return true;
#else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono() &&
        layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
#if !JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
#endif

    return true;
#endif
}

void AudioPluginAudioProcessor::processBlock(juce::AudioBuffer<float> &buffer,
                                             juce::MidiBuffer &midiMessages) {
    juce::ignoreUnused(midiMessages);

    updateParameters();

    if (reverb.isActive())
    {
        reverb.process(buffer);
    }

    if (tremolo.isActive())
    {
        tremolo.process(buffer);
    }

//    if (lowPassFilter.isActive())
//    {
//        lowPassFilter.processLowPass(buffer);
//    }
//
//    if (bandPassFilter.isActive())
//    {
//        bandPassFilter.processBandPass(buffer);
//    }
//
//    if (highPassFilter.isActive())
//    {
//        highPassFilter.processHighPass(buffer);
//    }

    volume.process(buffer);
    panning.process(buffer);
}

//==============================================================================
bool AudioPluginAudioProcessor::hasEditor() const {
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor *AudioPluginAudioProcessor::createEditor() {
    return new AudioPluginAudioProcessorEditor(*this);
}

//==============================================================================
void
AudioPluginAudioProcessor::getStateInformation(juce::MemoryBlock &destData) {
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    juce::ignoreUnused(destData);
}

void AudioPluginAudioProcessor::setStateInformation(const void *data,
                                                    int sizeInBytes) {
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    juce::ignoreUnused(data, sizeInBytes);
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor *JUCE_CALLTYPE createPluginFilter() {
    return new AudioPluginAudioProcessor();
}
