/*
  ==============================================================================

    ARA_DocumentListBoxModel.h
    Created: 17 Nov 2022 6:42:19pm
    Author:  Ryan Devens

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class ARA_DocumentListBoxModel : public juce::TableListBoxModel
{
public:
	ARA_DocumentListBoxModel();
	~ARA_DocumentListBoxModel();
	
	int getNumRows() override;
	void paintRowBackground (juce::Graphics&, int rowNumber, int width, int height, bool rowIsSelected) override;
	void paintCell (juce::Graphics&, int rowNumber, int columnId, int width, int height, bool rowIsSelected) override;

};
