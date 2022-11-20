/*
  ==============================================================================

    ARA_PlaybackRegionWidget.h
    Created: 18 Nov 2022 1:02:34pm
    Author:  Ryan Devens

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "ARA_ObjectWidget.h"
//==============================================================================
/*
*/
class ARA_PlaybackRegionWidget  : public ARA_ObjectWidget
{
public:
    ARA_PlaybackRegionWidget(juce::ARAPlaybackRegion& region);
    ~ARA_PlaybackRegionWidget() override;

//    void paint (juce::Graphics&) override;
//    void resized() override;

private:
	juce::ARAPlaybackRegion& playbackRegion;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ARA_PlaybackRegionWidget)
};
