/*
  ==============================================================================

    ARAHelper_AudioMod.h
    Created: 20 Nov 2022 12:07:56pm
    Author:  Ryan Devens

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class ARAHelper_AudioMod : public juce::ARAAudioModification
{
public:
	ARAHelper_AudioMod(juce::ARAAudioSource* audioSource,
					   ARA::ARAAudioModificationHostRef hostRef,
					   const juce::ARAAudioModification* optionalModificationToClone);
	~ARAHelper_AudioMod() override;
	
	void generateRandomColor();
	juce::Colour getColor() const;
private:
	juce::Colour modColor;
};
