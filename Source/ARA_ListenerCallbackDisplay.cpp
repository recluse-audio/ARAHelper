/*
  ==============================================================================

    ARA_ListenerCallbackDisplay.cpp
    Created: 19 Nov 2022 2:59:33pm
    Author:  Ryan Devens

  ==============================================================================
*/

#include <JuceHeader.h>
#include "ARA_ListenerCallbackDisplay.h"
#include "GlobalDefines.h"

//==============================================================================
ARA_ListenerCallbackDisplay::ARA_ListenerCallbackDisplay(juce::ARADocument& document) : araDocument(document)
{
	displayLabel = std::make_unique<juce::Label>("LABEL", "Listener Callback Display:");
	displayLabel->setColour(juce::Label::ColourIds::backgroundColourId, juce::Colours::darkgrey);
	addAndMakeVisible(displayLabel.get());

	araDocument.addListener(this);
}

ARA_ListenerCallbackDisplay::~ARA_ListenerCallbackDisplay()
{
	araDocument.removeListener(this);
}

void ARA_ListenerCallbackDisplay::paint (juce::Graphics& g)
{



}

void ARA_ListenerCallbackDisplay::resized()
{
	displayLabel->setBoundsRelative(0.f, 0.f, 1.f, 1.f);

}

void ARA_ListenerCallbackDisplay::didEndEditing(juce::ARADocument* document)
{
	_updateLabelText(document, "didEndEditing();");
}

void ARA_ListenerCallbackDisplay::didAddRegionSequenceToDocument(juce::ARADocument* document, juce::ARARegionSequence* sequence)
{
	_updateLabelText(document, "didAddRegionSequenceToDocument();");
}

void ARA_ListenerCallbackDisplay::_updateLabelText(juce::ARADocument *document, juce::StringRef text)
{
	auto newText = juce::String("ARA Document: " + HexStringForPointer(document) + " - - " + text);
	displayLabel->setText(newText, juce::NotificationType::dontSendNotification);
}
