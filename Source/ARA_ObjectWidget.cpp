/*
  ==============================================================================

    ARA_ComponentWidget.cpp
    Created: 18 Nov 2022 1:00:59pm
    Author:  Ryan Devens

  ==============================================================================
*/

#include <JuceHeader.h>
#include "ARA_ObjectWidget.h"

//==============================================================================
ARA_ObjectWidget::ARA_ObjectWidget()
{
	objectLabel = std::make_unique<juce::Label>("OBJECT LABEL", "ARA Object");
}

ARA_ObjectWidget::~ARA_ObjectWidget()
{
}

void ARA_ObjectWidget::paint (juce::Graphics& g)
{
	g.setColour(juce::Colours::grey);
	g.fillAll();
}

void ARA_ObjectWidget::resized()
{
	objectLabel->setBoundsRelative(0.1f, 0.1f, 0.8f, 0.8f);

}

void ARA_ObjectWidget::_setText(juce::StringRef newText)
{
	objectLabel->setText(newText, juce::NotificationType::sendNotificationAsync);
}
