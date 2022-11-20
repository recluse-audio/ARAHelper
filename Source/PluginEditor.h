/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

class ARA_HelperView;

//==============================================================================
/**
*/
class ARAHelper_Editor  : public juce::AudioProcessorEditor,
public juce::AudioProcessorEditorARAExtension
{
public:
    ARAHelper_Editor (ARAHelper_Processor&);
    ~ARAHelper_Editor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
	std::unique_ptr<juce::Component> documentView;
	std::unique_ptr<ARA_HelperView> helperView;
	
	
    ARAHelper_Processor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ARAHelper_Editor)
};
