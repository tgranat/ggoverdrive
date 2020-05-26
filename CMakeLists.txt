cmake_minimum_required(VERSION 3.12)
project(GgOverdrive VERSION 1.1.0)

# Example:
#  1)   cmake -B cmake-build
#  2)   cmake --build cmake-build
#
# How to build Release on Windows (Debug is default)
#  cmake --build cmake-build --config Release
#
#
# Install JUCE globally:
# cd /path/to/clone/JUCE
# Configure build with library components only
# cmake -B cmake-build-install -DCMAKE_INSTALL_PREFIX=/path/to/JUCE/install
# Run the installation
# cmake --build cmake-build-install --target install
#
#
#
# Build JUCE stuff on Linux (Ubuntu):
# sudo apt install build-essential libssl-dev  
# 
# sudo apt install pkg-config libxrandr-dev libxcursor-dev
# sudo apt install libasound2-dev libcurl4-openssl-dev libx11-dev libxinerama-dev libxext-dev libfreetype6-dev
#
# If LADSPA plug-in support needed (which seems to be necessary even if you don't build LADSPA plug-ins)
# sudo apt install ladspa-sdk
# 
# https://forum.juce.com/t/list-of-juce-dependencies-under-linux/15121/44
# +-----------------------------+---------------------------------------------------------+
# | JUCE module                 | Packages                                                |
# +-----------------------------+---------------------------------------------------------+
# | juce_audio_devices          | libasound2-dev                                          |
# +-----------------------------+---------------------------------------------------------+
# | juce_core                   | libcurl4-openssl-dev                                    |
# | (unless JUCE_USE_CURL=0)    |                                                         |
# +-----------------------------+---------------------------------------------------------+
# | juce_graphics               | libx11-dev libxinerama-dev libxext-dev libfreetype6-dev |
# +-----------------------------+---------------------------------------------------------+
# | juce_gui_extra              | libwebkit2gtk-4.0-dev                                   |
# | (unless JUCE_WEB_BROWSER=0) |                                                         |
# +-----------------------------+---------------------------------------------------------+
# | juce_opengl                 | libglu1-mesa-dev                                        |
# +-----------------------------+---------------------------------------------------------+


# Use FIND_PACKAGE if JUCE is installed globally
# Set global JUCE location:
#  cmake -B cmake-build -DCMAKE_PREFIX_PATH=/path/to/JUCE/install
find_package(JUCE CONFIG REQUIRED)

# Use add_subdirectory(JUCE) if JUCE is available in the source tree
# add_subdirectory(JUCE)
add_subdirectory(Source)
