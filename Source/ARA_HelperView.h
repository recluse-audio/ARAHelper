/*
  ==============================================================================

    ARA_HelperView.h
    Created: 16 Nov 2022 3:37:16pm
    Author:  Ryan Devens

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class ARA_DocumentListBoxModel;
class ARA_ListenerCallbackDisplay;
class ARA_ObjectWidget;

//==============================================================================
/*
*/
class ARA_HelperView  : public juce::Component
, private juce::ARADocument::Listener
{
public:
    ARA_HelperView(juce::ARADocument& document);
    ~ARA_HelperView() override;

    void paint (juce::Graphics&) override;
    void resized() override;

	void didEndEditing(juce::ARADocument*) override;
private:
	std::unique_ptr<ARA_ObjectWidget> objectWidget;
	std::unique_ptr<juce::TableListBox>	 tableListBox;
	std::unique_ptr<ARA_DocumentListBoxModel>	 boxModel;
	std::unique_ptr<ARA_ListenerCallbackDisplay> callbackDisplay;

	
	juce::ARADocument& araDocument;
	
	void _update();
	void _updateRegions();
	void _updateRegionLabel();
	void _updateSequenceLabel();
	void _resizeTableHeader();
	
	enum class ARAObjectID
	{
		DocumentController = 1,
		EditorView,
		PlaybackRenderer,
		EditorRenderer,
		RegionSequence,
		PlaybackRegion,
		AudioModification,
		AudioSource,
		TotalNumIDs,
		
	};
	
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ARA_HelperView)
};
