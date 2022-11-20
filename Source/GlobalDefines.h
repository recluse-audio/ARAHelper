/*
  ==============================================================================

    GlobalDefines.h
    Created: 18 Nov 2022 1:16:11pm
    Author:  Ryan Devens

  ==============================================================================
*/

#pragma once

#define HexStringForPointer( ptr ) juce::String::toHexString((unsigned long long)(void*)ptr)
