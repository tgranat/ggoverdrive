set (BaseTargetName ${PROJECT_NAME})

# Example:
#  1)   cmake -B cmake-build
#  2)   cmake --build cmake-build
#
# How to build Release on Windows (Debug is default)
#  cmake --build cmake-build --config Release

juce_add_plugin("${BaseTargetName}"
        # VERSION ...                               # Set this if the plugin version is different to the project version
        # ICON_BIG ...                              # ICON_* arguments specify a path to an image file to use as an icon for the Standalone
        # ICON_SMALL ...
        COMPANY_NAME "GranatGuitar"
        IS_SYNTH FALSE
        NEEDS_MIDI_INPUT FALSE
        NEEDS_MIDI_OUTPUT FALSE
        IS_MIDI_EFFECT FALSE
        EDITOR_WANTS_KEYBOARD_FOCUS FALSE
        COPY_PLUGIN_AFTER_BUILD TRUE               #
		VST3_COPY_DIR C:/VST3_development_plugins  # Change this location if you want. Or remove.
        PLUGIN_MANUFACTURER_CODE GgFx
        PLUGIN_CODE GgOd
        FORMATS AU VST3 Standalone
		VST3_CATEGORIES Distortion
        PRODUCT_NAME "Systech Overdrive Simulator")

juce_generate_juce_header(${BaseTargetName})

target_sources(${BaseTargetName} PRIVATE
        PluginProcessor.cpp
        PluginEditor.cpp)

target_compile_definitions(${BaseTargetName} PUBLIC
        JUCE_WEB_BROWSER=0
        JUCE_USE_CURL=0
        JUCE_VST3_CAN_REPLACE_VST2=0)

target_link_libraries(${BaseTargetName} PRIVATE 
        juce::juce_audio_utils
		juce::juce_dsp
		juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags)