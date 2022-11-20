/*
  ==============================================================================

    PluginARAEditorRenderer.cpp
    Created: 1 Nov 2022 12:46:25pm
    Author:  Ryan Devens

  ==============================================================================
*/

#include "DemoEditorRenderer.h"

DemoEditorRenderer::DemoEditorRenderer (ARA::PlugIn::DocumentController* documentController, const PreviewState* previewStateIn)
	: juce::ARAEditorRenderer (documentController), previewState (previewStateIn), previewBuffer()
{
	jassert (previewState != nullptr);
}

DemoEditorRenderer::~DemoEditorRenderer()
{
	for (const auto& rs : regionSequences)
		rs->removeListener (this);
}

void DemoEditorRenderer::didAddPlaybackRegionToRegionSequence (juce::ARARegionSequence*, juce::ARAPlaybackRegion*)
{
	asyncCallback.startCallback();
}

void DemoEditorRenderer::didAddRegionSequence (ARA::PlugIn::RegionSequence* rs) noexcept
{
	auto* sequence = dynamic_cast<ARARegionSequence*> (rs);
	sequence->addListener (this);
	regionSequences.insert (sequence);
	asyncCallback.startCallback();
}

void DemoEditorRenderer::didAddPlaybackRegion (ARA::PlugIn::PlaybackRegion*) noexcept
{
	asyncCallback.startCallback();
}

void DemoEditorRenderer::prepareToPlay (double sampleRateIn,
					int maximumExpectedSamplesPerBlock,
					int numChannels,
					AudioProcessor::ProcessingPrecision,
					AlwaysNonRealtime alwaysNonRealtime)
{
	sampleRate = sampleRateIn;
	previewBuffer = std::make_unique<AudioBuffer<float>> (numChannels, (int) (2 * sampleRateIn));

	ignoreUnused (maximumExpectedSamplesPerBlock, alwaysNonRealtime);
}


void DemoEditorRenderer::releaseResources()
{
	audioSourceReaders.clear();
}

void DemoEditorRenderer::reset()
{
	previewBuffer->clear();
}

bool DemoEditorRenderer::processBlock (AudioBuffer<float>& buffer,
				   AudioProcessor::Realtime realtime,
				   const AudioPlayHead::PositionInfo& positionInfo) noexcept
{
	ignoreUnused (realtime);

	return asyncCallback.withLock ([&] (bool locked)
	{
		if (! locked)
			return true;

		if (positionInfo.getIsPlaying())
			return true;

		const auto previewedRegion = previewState->previewedRegion.load();
		if(previewedRegion == nullptr)
			return true;

		bool previewedRegionIsAssignedToEditor = this->_checkIfRegionIsAssignedToThisEditor(previewedRegion);
		if (!previewedRegionIsAssignedToEditor)
			return true;
		
		
		const auto previewPosInTimeline = previewState->previewTime.load();

		if (lastPreviewTime != previewPosInTimeline || lastPlaybackRegion != previewedRegion)
			this->_setNewPreviewRange(previewPosInTimeline, previewedRegion);
		else
			previewLooper.writeInto (buffer);
		

		return true;
	});
}




//=========================
// PRIVATE FUNCTIONS

void DemoEditorRenderer::_configure()
{
	// Preparing our map of audio sources and the buffering audio reader used to read them
	forEachPlaybackRegion ([this, maximumExpectedSamplesPerBlock = 1000] (const auto& playbackRegion)
	{
		const auto audioSource = playbackRegion->getAudioModification()->getAudioSource();

		if (audioSourceReaders.find (audioSource) == audioSourceReaders.end())
		{
			auto sourceReader = new ARAAudioSourceReader (playbackRegion->getAudioModification()->getAudioSource());
			
			int samplesToBuffer = (int) (sampleRate * 4.0); //std::max (4 * maximumExpectedSamplesPerBlock, (int) sampleRate);
			
			audioSourceReaders[audioSource] = std::make_unique<BufferingAudioReader> ( sourceReader, *timeSliceThread, samplesToBuffer);
		}

		return true;
	});
}

//--------------------
bool DemoEditorRenderer::_checkIfRegionIsAssignedToThisEditor(juce::ARAPlaybackRegion* newPreviewRegion)
{
	bool regionIsAssigned = false;

	auto isPlaybackRegionAssignedToThisEditorRenderer = [&newPreviewRegion, &regionIsAssigned] (const auto& region)
	{
		if (region == newPreviewRegion)
		{
			regionIsAssigned = true;
			return false;
		}

		return true;
	};
	
	forEachPlaybackRegion(isPlaybackRegionAssignedToThisEditorRenderer);

	return regionIsAssigned;
}

//--------------------
void DemoEditorRenderer::_setNewPreviewRange( double previewPosInTimeline, juce::ARAPlaybackRegion* newPreviewRegion)
{
	juce::Range<double> previewRangeInPlaybackTime { previewPosInTimeline - 1.25, previewPosInTimeline + 1.25 };

	previewBuffer->clear();

	auto sourceReaderFunction = [this] (auto* source) -> auto*
	{
	   const auto iter = audioSourceReaders.find (source);
	   return iter != audioSourceReaders.end() ? iter->second.get() : nullptr;
	};

	const auto rangeInOutput = readPlaybackRangeIntoBuffer (previewRangeInPlaybackTime, newPreviewRegion, *previewBuffer, sourceReaderFunction);

	if (rangeInOutput)
	{
		lastPreviewTime = previewPosInTimeline;
		lastPlaybackRegion = newPreviewRegion;
		previewLooper = Looper (previewBuffer.get(), *rangeInOutput);
	}
}
