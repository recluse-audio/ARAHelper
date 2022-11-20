/*
  ==============================================================================

    ARAHelper_AudioMod.cpp
    Created: 20 Nov 2022 12:07:56pm
    Author:  Ryan Devens

  ==============================================================================
*/

#include "ARAHelper_AudioMod.h"

ARAHelper_AudioMod::ARAHelper_AudioMod(juce::ARAAudioSource* audioSource, ARA::ARAAudioModificationHostRef hostRef, const juce::ARAAudioModification* optionalModificationToClone) : juce::ARAAudioModification(audioSource, hostRef, optionalModificationToClone)
{
	generateRandomColor();
}

ARAHelper_AudioMod::~ARAHelper_AudioMod()
{
	
}

void ARAHelper_AudioMod::generateRandomColor()
{
	auto randomValue = juce::Random();
	juce::uint8 r = randomValue.nextInt(255);
	juce::uint8 g = randomValue.nextInt(255);
	juce::uint8 b = randomValue.nextInt(255);

	modColor = {r, g, b};
}

juce::Colour ARAHelper_AudioMod::getColor() const
{
	return modColor;
}
