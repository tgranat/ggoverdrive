cmake_minimum_required(VERSION 3.12)
project(GgOverdrive VERSION 1.1.0)

# Use FIND_PACKAGE if JUCE is installed globally
# Set global JUCE location:
#  cmake -B cmake-build -DCMAKE_PREFIX_PATH=/path/to/JUCE/install
find_package(JUCE CONFIG REQUIRED)

# Use add_subdirectory(JUCE) if JUCE is available in the source tree
# add_subdirectory(JUCE)
add_subdirectory(Source)
