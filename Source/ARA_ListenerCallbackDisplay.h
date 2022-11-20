/*
  ==============================================================================

    ARA_ListenerCallbackDisplay.h
    Created: 19 Nov 2022 2:59:33pm
    Author:  Ryan Devens

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
	Listens to every ARA callback and displays the name of the calling function
 
*/
class ARA_ListenerCallbackDisplay  : public juce::Component,
private juce::ARADocument::Listener
{
public:
    ARA_ListenerCallbackDisplay(juce::ARADocument& document);
    ~ARA_ListenerCallbackDisplay() override;

    void paint (juce::Graphics&) override;
    void resized() override;

	void didEndEditing(juce::ARADocument* document) override;
	void didAddRegionSequenceToDocument(juce::ARADocument* document, juce::ARARegionSequence* sequence) override;

private:
	std::unique_ptr<juce::Label> displayLabel;
	juce::ARADocument& araDocument;
	
	void _updateLabelText(juce::ARADocument* document, juce::StringRef text);
	
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ARA_ListenerCallbackDisplay)
};
