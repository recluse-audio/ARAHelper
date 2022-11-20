/*
  ==============================================================================

    ARA_PlaybackRegionWidget.cpp
    Created: 18 Nov 2022 1:02:34pm
    Author:  Ryan Devens

  ==============================================================================
*/

#include <JuceHeader.h>
#include "ARA_PlaybackRegionWidget.h"
#include "GlobalDefines.h"

//==============================================================================
ARA_PlaybackRegionWidget::ARA_PlaybackRegionWidget(juce::ARAPlaybackRegion& region) : playbackRegion(region)
{
	auto regionMemoryAddress = HexStringForPointer(&region);
	this->_setText(regionMemoryAddress);
}

ARA_PlaybackRegionWidget::~ARA_PlaybackRegionWidget()
{
}

//void ARA_PlaybackRegionWidget::paint (juce::Graphics& g)
//{
//	g.setColour(juce::Colours::pink);
//	g.fillAll();
//}
//
//void ARA_PlaybackRegionWidget::resized()
//{
//    // This method is where you should set the bounds of any child
//    // components that your component contains..
//
//}
