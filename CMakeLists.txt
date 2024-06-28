cmake_minimum_required(VERSION 3.22.1)

set(PROJECT_NAME "Multifilter")
set(FORMATS Standalone VST3)

project(${PROJECT_NAME} VERSION 0.0.1)

include(FetchContent)
FetchContent_Declare(
        JUCE
        GIT_REPOSITORY https://github.com/juce-framework/JUCE
        GIT_TAG 7.0.10
)
FetchContent_MakeAvailable(JUCE)

juce_add_plugin("${PROJECT_NAME}"
        # VERSION ...                               # Set this if the plugin version is different to the project version
        # ICON_BIG ...                              # ICON_* arguments specify a path to an image file to use as an icon for the Standalone
        # ICON_SMALL ...
        COMPANY_NAME jmlpzg
        # IS_SYNTH TRUE/FALSE                       # Is this a synth or an effect?
        # NEEDS_MIDI_INPUT TRUE/FALSE               # Does the plugin need midi input?
        # NEEDS_MIDI_OUTPUT TRUE/FALSE              # Does the plugin need midi output?
        # IS_MIDI_EFFECT TRUE/FALSE                 # Is this plugin a MIDI effect?
        # EDITOR_WANTS_KEYBOARD_FOCUS TRUE/FALSE    # Does the editor need keyboard focus?
        COPY_PLUGIN_AFTER_BUILD TRUE # On MacOS, plugin will be copied to /Users/you/Library/Audio/Plug-Ins/
        PLUGIN_MANUFACTURER_CODE Jmlp               # This has to be one uppercase, rest lower for AU formats
        PLUGIN_CODE J002                            # A unique four-character plugin id with at least one upper-case character
        FORMATS "${FORMATS}"
        PRODUCT_NAME "${PROJECT_NAME}")        # The name of the final executable, which can differ from the target name

# Manually list all .h and .cpp files for the plugin
set(SourceFiles
        src/PluginEditor.h
        src/PluginProcessor.h
        src/PluginEditor.cpp
        src/PluginProcessor.cpp
        src/dsp/Volume.h
        src/dsp/Volume.cpp
        src/dsp/Panning.h
        src/dsp/Panning.cpp
        src/dsp/Filter.h
        src/dsp/Filter.cpp
        src/dsp/LFO.h
        src/dsp/LFO.cpp
        src/dsp/Tremolo.h
        src/dsp/Tremolo.cpp
        src/dsp/Reverb.h
        src/dsp/Reverb.cpp
        src/gui/KnobLookAndFeel.h
        src/gui/KnobLookAndFeel.cpp
)
target_sources("${PROJECT_NAME}" PRIVATE ${SourceFiles})

target_compile_definitions("${PROJECT_NAME}"
        PUBLIC
        # JUCE_WEB_BROWSER and JUCE_USE_CURL would be on by default, but you might not need them.
        JUCE_WEB_BROWSER=0  # If you remove this, add `NEEDS_WEB_BROWSER TRUE` to the `juce_add_plugin` call
        JUCE_USE_CURL=0     # If you remove this, add `NEEDS_CURL TRUE` to the `juce_add_plugin` call
        JUCE_VST3_CAN_REPLACE_VST2=0)

juce_add_binary_data("${PROJECT_NAME}Data" SOURCES ${CMAKE_CURRENT_SOURCE_DIR}\\assets\\IR.wav)

target_link_libraries("${PROJECT_NAME}"
        PRIVATE
        "${PROJECT_NAME}Data"
        PUBLIC
        juce::juce_audio_utils
        juce::juce_audio_processors
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags
        juce::juce_dsp
        juce::juce_gui_basics)