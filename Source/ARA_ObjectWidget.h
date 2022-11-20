/*
  ==============================================================================

    ARA_ComponentWidget.h
    Created: 18 Nov 2022 1:00:59pm
    Author:  Ryan Devens

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class ARA_ObjectWidget  : public juce::Component
{
public:
	ARA_ObjectWidget();
    ~ARA_ObjectWidget() override;

    void paint (juce::Graphics&) override;
    void resized() override;

	
protected:
	std::unique_ptr<juce::Label> objectLabel;
	void _setText(juce::StringRef newText);
	
private:
	
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ARA_ObjectWidget)
};
