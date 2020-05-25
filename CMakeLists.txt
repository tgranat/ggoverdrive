cmake_minimum_required(VERSION 3.12)
project(GgOverdrive VERSION 1.1.0)

#find_package(JUCE CONFIG REQUIRED)
# (cmake -B cmake-build -DCMAKE_PREFIX_PATH=/path/to/JUCE/install)
add_subdirectory(JUCE)
add_subdirectory(Source)
