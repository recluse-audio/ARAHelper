/*
  ==============================================================================

    ARA_DocumentListBoxModel.cpp
    Created: 17 Nov 2022 6:42:19pm
    Author:  Ryan Devens

  ==============================================================================
*/

#include "ARA_DocumentListBoxModel.h"

ARA_DocumentListBoxModel::ARA_DocumentListBoxModel()
{
	
}

ARA_DocumentListBoxModel::~ARA_DocumentListBoxModel()
{
	
}

int ARA_DocumentListBoxModel::getNumRows()
{
	return 5;
}

void ARA_DocumentListBoxModel::paintRowBackground(juce::Graphics& g, int rowNumber, int width, int height, bool rowIsSelected)
{
	g.setColour(juce::Colours::black);
	g.drawLine(0, height-1, width, height-1);
//	int red = 0, green = 0, blue = 0;
//	switch(rowNumber)
//	{
//		case 0: red = 255; break;
//		case 1: green = 255; break;
//		case 2: blue = 255; break;
//	}
//
//	auto color = juce::Colour(red, green, blue);
//	g.fillAll(color);
}

void ARA_DocumentListBoxModel::paintCell(juce::Graphics& g,  int rowNumber, int columnId, int width, int height, bool rowIsSelected)
{
	g.setColour(juce::Colours::black);
	g.drawLine(0, 0, 0, height);
}
