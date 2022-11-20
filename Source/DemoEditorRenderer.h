/*
  ==============================================================================

    PluginARAEditorRenderer.h
    Created: 1 Nov 2022 12:46:25pm
    Author:  Ryan Devens

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "AsyncCallback.h"
#include "UtilObjects.h"

class DemoEditorRenderer  : public ARAEditorRenderer,
						private ARARegionSequence::Listener
{
public:
	DemoEditorRenderer (ARA::PlugIn::DocumentController* documentController);

	~DemoEditorRenderer() override;

	void didAddPlaybackRegionToRegionSequence (ARARegionSequence*, ARAPlaybackRegion*) override;

	void didAddRegionSequence (ARA::PlugIn::RegionSequence* rs) noexcept override;

	void didAddPlaybackRegion (ARA::PlugIn::PlaybackRegion*) noexcept override;


	void prepareToPlay (double sampleRateIn,
						int maximumExpectedSamplesPerBlock,
						int numChannels,
						AudioProcessor::ProcessingPrecision,
						AlwaysNonRealtime alwaysNonRealtime) override;

	void releaseResources() override;

	void reset() override;

	bool processBlock (AudioBuffer<float>& buffer,
					   AudioProcessor::Realtime realtime,
					   const AudioPlayHead::PositionInfo& positionInfo) noexcept override;

	using ARAEditorRenderer::processBlock;

private:

	juce::int64 getSamplePositionInAudioSource();
	
	juce::ARAPlaybackRegion* lastPlaybackRegion = nullptr;

	double sampleRate = 48000.0;
	juce::SharedResourcePointer<SharedTimeSliceThread> timeSliceThread;
	std::map<ARA::PlugIn::AudioSource*, std::unique_ptr<BufferingAudioReader>> audioSourceReaders;

	std::set<juce::ARARegionSequence*> regionSequences;
};
