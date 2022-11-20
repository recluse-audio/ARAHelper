/*
  ==============================================================================

    ARADemoPluginDocumentControllerSpecialisation.h
    Created: 2 Nov 2022 10:52:41am
    Author:  Ryan Devens

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "DemoEditorRenderer.h"
#include "DemoPlaybackRenderer.h"
#include "ARAHelper_AudioMod.h"

class ARAHelper_AudioMod;

class DemoDocumentControllerSpecialisation  : public ARADocumentControllerSpecialisation
{
public:
	using ARADocumentControllerSpecialisation::ARADocumentControllerSpecialisation;	

protected:
	DemoPlaybackRenderer* doCreatePlaybackRenderer() noexcept override;

	DemoEditorRenderer* doCreateEditorRenderer() noexcept override;
	
	ARAHelper_AudioMod* doCreateAudioModification(juce::ARAAudioSource* audioSource,
												  ARA::ARAAudioModificationHostRef hostRef,
												  const juce::ARAAudioModification* optionalModificationToClone) noexcept override;

	bool doRestoreObjectsFromStream (ARAInputStream& input,
									 const ARARestoreObjectsFilter* filter) noexcept override;

	bool doStoreObjectsToStream (ARAOutputStream& output, const ARAStoreObjectsFilter* filter) noexcept override;
};
