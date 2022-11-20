/*
  ==============================================================================

    PluginARAEditorRenderer.cpp
    Created: 1 Nov 2022 12:46:25pm
    Author:  Ryan Devens

  ==============================================================================
*/

#include "DemoEditorRenderer.h"

DemoEditorRenderer::DemoEditorRenderer (ARA::PlugIn::DocumentController* documentController)
	: juce::ARAEditorRenderer (documentController)
{
}

DemoEditorRenderer::~DemoEditorRenderer()
{
	for (const auto& rs : regionSequences)
		rs->removeListener (this);
}

void DemoEditorRenderer::didAddPlaybackRegionToRegionSequence (juce::ARARegionSequence*, juce::ARAPlaybackRegion*)
{
}

void DemoEditorRenderer::didAddRegionSequence (ARA::PlugIn::RegionSequence* rs) noexcept
{
	auto* sequence = dynamic_cast<ARARegionSequence*> (rs);
	sequence->addListener (this);
	regionSequences.insert (sequence);
}

void DemoEditorRenderer::didAddPlaybackRegion (ARA::PlugIn::PlaybackRegion*) noexcept
{
}

void DemoEditorRenderer::prepareToPlay (double sampleRateIn,
					int maximumExpectedSamplesPerBlock,
					int numChannels,
					AudioProcessor::ProcessingPrecision,
					AlwaysNonRealtime alwaysNonRealtime)
{
	sampleRate = sampleRateIn;
	ignoreUnused (maximumExpectedSamplesPerBlock, alwaysNonRealtime);
}


void DemoEditorRenderer::releaseResources()
{
	audioSourceReaders.clear();
}

void DemoEditorRenderer::reset()
{
}

bool DemoEditorRenderer::processBlock (AudioBuffer<float>& buffer,
				   AudioProcessor::Realtime realtime,
				   const AudioPlayHead::PositionInfo& positionInfo) noexcept
{
	return true;
}




//=========================
// PRIVATE FUNCTIONS



