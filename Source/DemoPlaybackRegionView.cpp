/*
  ==============================================================================

    DemoPlaybackRegionView.cpp
    Created: 1 Nov 2022 12:47:47pm
    Author:  Ryan Devens

  ==============================================================================
*/

#include <JuceHeader.h>
#include "DemoPlaybackRegionView.h"
#include "DemoDocumentControllerSpecialisation.h"
#include "GlobalDefines.h"


//==============================================================================
DemoPlaybackRegionView::DemoPlaybackRegionView(ARAPlaybackRegion& region, WaveformCache& cache)
: playbackRegion (region), waveformCache (cache)
{
	auto* audioSource = playbackRegion.getAudioModification()->getAudioSource();

	waveformCache.getOrCreateThumbnail (audioSource).addChangeListener (this);
	
	juce::String regionAddress = HexStringForPointer(&region);
	juce::String labelText ("Memory Address: ");
	memoryAddressLabel = std::make_unique<juce::Label>("MEMORY ADDRESS LABEL", labelText + regionAddress);
	memoryAddressLabel->setColour(juce::Label::ColourIds::textColourId, juce::Colours::black);
	addAndMakeVisible(memoryAddressLabel.get());
	
	notificationLabel = std::make_unique<juce::Label>();
	addAndMakeVisible(notificationLabel.get());
	
	playbackRegion.addListener(this);
}

DemoPlaybackRegionView::~DemoPlaybackRegionView()
{
	waveformCache.getOrCreateThumbnail (playbackRegion.getAudioModification()->getAudioSource())
		.removeChangeListener (this);
	
	playbackRegion.removeListener(this);
}

void DemoPlaybackRegionView::mouseDown (const juce::MouseEvent& m)
{
	const auto percentOfRegion = (double) m.getMouseDownX() / getLocalBounds().getWidth();
	const auto samplePosOfMouseWithinPlaybackRegion = percentOfRegion * playbackRegion.getDurationInPlaybackTime();
	const auto previewTime = playbackRegion.getStartInPlaybackTime() + samplePosOfMouseWithinPlaybackRegion;
	
	auto docController = ARADocumentControllerSpecialisation::getSpecialisedDocumentController<DemoDocumentControllerSpecialisation>
							(playbackRegion.getDocumentController());
	
	auto& previewState = docController->previewState;
	
	previewState.previewTime.store (previewTime);
	previewState.previewedRegion.store (&playbackRegion);
}

void DemoPlaybackRegionView::mouseUp (const juce::MouseEvent&)
{
	auto docController = ARADocumentControllerSpecialisation::getSpecialisedDocumentController<DemoDocumentControllerSpecialisation>
							(playbackRegion.getDocumentController());
	
	auto& previewState = docController->previewState;
	
	previewState.previewTime.store (0.0);
	previewState.previewedRegion.store (nullptr);
}

void DemoPlaybackRegionView::changeListenerCallback(juce::ChangeBroadcaster* changeBroadcaster)
{
	repaint();
}



void DemoPlaybackRegionView::paint (juce::Graphics& g)
{
	g.fillAll (Colours::darkgrey.darker());
	
	g.setColour (Colours::whitesmoke.darker());
	
	/**
		TO DO: Make this thumbnail into a component
	 */
	auto& thumbnail = waveformCache.getOrCreateThumbnail (playbackRegion.getAudioModification()->getAudioSource());
	
	auto thumbnailHeight = getLocalBounds().proportionOfHeight(0.6f);
	thumbnail.drawChannels (g, getLocalBounds().withHeight(thumbnailHeight),
							playbackRegion.getStartInAudioModificationTime(),
							playbackRegion.getEndInAudioModificationTime(),
							1.0f);
	
	g.setColour (Colours::black);
	g.drawRect (getLocalBounds());
	
//	auto outline = this->getLocalBounds();
//	g.setColour(juce::Colours::orange);
//	g.drawRect(outline, 2.f);

}

void DemoPlaybackRegionView::updateAddressLabel(juce::StringRef newAddress)
{
	juce::String labelText("Playback Region - Memory Address: ");
	memoryAddressLabel->setText(labelText + newAddress, juce::NotificationType::sendNotification);
}

void DemoPlaybackRegionView::resized()
{
	memoryAddressLabel->setBoundsRelative(0.05f, 0.65f, 0.4f, 0.25f);
	notificationLabel->setBoundsRelative(0.5f, 0.65f, 0.4f, 0.25f);
	repaint();
}

void DemoPlaybackRegionView::didUpdatePlaybackRegionProperties(juce::ARAPlaybackRegion* updatedRegion)
{
	if(&playbackRegion == updatedRegion)
	{
		numNotifications++;
		auto numNotificationsString = juce::String(numNotifications);
		notificationLabel->setText("Number of Notifications: " + numNotificationsString , juce::NotificationType::sendNotificationAsync);
	}

}
