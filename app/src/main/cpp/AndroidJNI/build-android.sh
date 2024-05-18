#!/bin/bash

# Define paths
ANDROID_NDK=~/Library/Android/sdk/ndk/27.0.11718014

ANDROID_API_LEVEL=24
ANDROID_ABI=armeabi-v7a

# Create a build directory
mkdir -p build-android
cd build-android

# Run CMake to configure the build
cmake -DASSIMP_ANDROID_JNIIOSYSTEM=ON \
      -DANDROID_ABI=${ANDROID_ABI} \
      -DANDROID_NDK=${ANDROID_NDK} \
      -DCMAKE_TOOLCHAIN_FILE=${ANDROID_NDK}/build/cmake/android.toolchain.cmake \
      -DANDROID_NATIVE_API_LEVEL=android-${ANDROID_API_LEVEL} \
      ..

# Build the project
cmake --build .
