/*
  ==============================================================================

    DemoRegionSequenceView.cpp
    Created: 1 Nov 2022 12:48:09pm
    Author:  Ryan Devens

  ==============================================================================
*/

#include <JuceHeader.h>
#include "DemoRegionSequenceView.h"

//==============================================================================
DemoRegionSequenceView::DemoRegionSequenceView(ARARegionSequence& rs, WaveformCache& cache, double pixelPerSec)
: regionSequence (rs), waveformCache (cache), zoomLevelPixelPerSecond (pixelPerSec)
{
	regionSequence.addListener (this);

	for (auto* playbackRegion : regionSequence.getPlaybackRegions())
		createAndAddPlaybackRegionView (playbackRegion);

	updatePlaybackDuration();
}

DemoRegionSequenceView::~DemoRegionSequenceView()
{
	regionSequence.removeListener (this);

	for (const auto& it : playbackRegionViewsMap)
		it.first->removeListener (this);
}

void DemoRegionSequenceView::paint(juce::Graphics &g)
{
	auto outline = this->getBounds();
	g.setColour(juce::Colours::yellow);
	g.drawRect(outline, 2.f);


	g.setColour (Colours::white);
	g.setFont (15.0f);
	g.drawFittedText ("Region Sequence View",
					  getLocalBounds(),
					  Justification::centred,
					  1);
}

//==============================================================================
// ARA Document change callback overrides
void DemoRegionSequenceView::willRemovePlaybackRegionFromRegionSequence (juce::ARARegionSequence* regionSequence, juce::ARAPlaybackRegion* playbackRegion)
{
	playbackRegion->removeListener (this);
	removeChildComponent (playbackRegionViewsMap[playbackRegion].get());
	playbackRegionViewsMap.erase (playbackRegion);
	updatePlaybackDuration();
}

void DemoRegionSequenceView::didAddPlaybackRegionToRegionSequence (juce::ARARegionSequence* regionSequence, juce::ARAPlaybackRegion* playbackRegion)
{
	createAndAddPlaybackRegionView (playbackRegion);
	updatePlaybackDuration();
}

void DemoRegionSequenceView::willDestroyPlaybackRegion (ARAPlaybackRegion* playbackRegion)
{
	playbackRegion->removeListener (this);
	removeChildComponent (playbackRegionViewsMap[playbackRegion].get());
	playbackRegionViewsMap.erase (playbackRegion);
	updatePlaybackDuration();
}

void DemoRegionSequenceView::willUpdatePlaybackRegionProperties (juce::ARAPlaybackRegion* playbackRegion, juce::ARAPlaybackRegion::PropertiesPtr regionProperties)
{
}

void DemoRegionSequenceView::didUpdatePlaybackRegionProperties (juce::ARAPlaybackRegion*)
{
	updatePlaybackDuration();
}

void DemoRegionSequenceView::resized()
{
	for (auto& pbr : playbackRegionViewsMap)
	{
		const auto playbackRegion = pbr.first;
		auto regionView = pbr.second.get();
		
		const auto trimThisMuchFromLeft = roundToInt(playbackRegion->getStartInPlaybackTime() * zoomLevelPixelPerSecond);
		const auto regionViewWidth = roundToInt (playbackRegion->getDurationInPlaybackTime() * zoomLevelPixelPerSecond);
		
		auto regionViewBounds = getLocalBounds().withTrimmedLeft(trimThisMuchFromLeft).withWidth(regionViewWidth);
		regionView->setBounds(regionViewBounds);
	}
}

double DemoRegionSequenceView::getPlaybackDuration() const noexcept
{
	return playbackDuration;
}

void DemoRegionSequenceView::setZoomLevel (double pixelPerSecond)
{
	zoomLevelPixelPerSecond = pixelPerSecond;
	resized();
}




//========================
// PRIVATE FUNCTIONS

void DemoRegionSequenceView::createAndAddPlaybackRegionView (ARAPlaybackRegion* playbackRegion)
{
	playbackRegionViewsMap[playbackRegion] = std::make_unique<DemoPlaybackRegionView> (*playbackRegion, waveformCache);
	playbackRegion->addListener (this);
	addAndMakeVisible (*playbackRegionViewsMap[playbackRegion]);
}


void DemoRegionSequenceView::updatePlaybackDuration()
{
	const auto iter = std::max_element (
		playbackRegionViewsMap.begin(),
		playbackRegionViewsMap.end(),
		[] (const auto& a, const auto& b) { return a.first->getEndInPlaybackTime() < b.first->getEndInPlaybackTime(); });

	playbackDuration = iter != playbackRegionViewsMap.end() ? iter->first->getEndInPlaybackTime() : 0.0;

	sendChangeMessage();
}



