cmake_minimum_required(VERSION 3.22.1)

set(PROJECT_NAME "DeLio")
set(FORMATS Standalone VST3)

project(${PROJECT_NAME} VERSION 0.0.1)

include(FetchContent)
FetchContent_Declare(
        JUCE
        GIT_REPOSITORY https://github.com/juce-framework/JUCE
        GIT_TAG 8.0.0
)
FetchContent_MakeAvailable(JUCE)

juce_add_plugin("${PROJECT_NAME}"
        # VERSION ...                               # Set this if the plugin version is different to the project version
        # ICON_BIG ...                              # ICON_* arguments specify a path to an image file to use as an icon for the Standalone
        # ICON_SMALL ...
        COMPANY_NAME jmlpzg
        COPY_PLUGIN_AFTER_BUILD TRUE # On MacOS, plugin will be copied to /Users/you/Library/Audio/Plug-Ins/
        PLUGIN_MANUFACTURER_CODE Jmlp               # This has to be one uppercase, rest lower for AU formats
        PLUGIN_CODE J002                            # A unique four-character plugin id with at least one upper-case character
        FORMATS "${FORMATS}"
        PRODUCT_NAME "${PROJECT_NAME}")        # The name of the final executable, which can differ from the target name

file(GLOB_RECURSE SourceFiles
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)
target_sources("${PROJECT_NAME}" PRIVATE ${SourceFiles})

target_compile_definitions("${PROJECT_NAME}"
        PUBLIC
        # JUCE_WEB_BROWSER and JUCE_USE_CURL would be on by default, but you might not need them.
        JUCE_WEB_BROWSER=0  # If you remove this, add `NEEDS_WEB_BROWSER TRUE` to the `juce_add_plugin` call
        JUCE_USE_CURL=0     # If you remove this, add `NEEDS_CURL TRUE` to the `juce_add_plugin` call
        JUCE_VST3_CAN_REPLACE_VST2=0)

juce_add_binary_data("${PROJECT_NAME}Data" SOURCES ${CMAKE_CURRENT_SOURCE_DIR}\\assets\\knob.png ${CMAKE_CURRENT_SOURCE_DIR}\\assets\\switch.png ${CMAKE_CURRENT_SOURCE_DIR}\\assets\\bg.png ${CMAKE_CURRENT_SOURCE_DIR}\\assets\\led.png)

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
        juce::juce_gui_basics
        juce::juce_core)