/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "DocumentView.h"
#include "ARA_HelperView.h"

//==============================================================================
ARAHelper_Editor::ARAHelper_Editor (ARAHelper_Processor& p)
    : AudioProcessorEditor (&p), AudioProcessorEditorARAExtension(&p), audioProcessor (p)
{
	if (auto* editorView = getARAEditorView())
	{
		auto* document = ARADocumentControllerSpecialisation::getSpecialisedDocumentController(editorView->getDocumentController())->getDocument();
		
		documentView = std::make_unique<DocumentView> (*document, p.playHeadState );
		helperView = std::make_unique<ARA_HelperView>(*document);
	}

	addAndMakeVisible (documentView.get());
	addAndMakeVisible(helperView.get());
	
	// ARA requires that plugin editors are resizable to support tight integration
	// into the host UI
	setResizable (true, false);
	setSize (400, 300);
}

ARAHelper_Editor::~ARAHelper_Editor()
{
}

//==============================================================================
void ARAHelper_Editor::paint (juce::Graphics& g)
{
	auto outline = this->getBounds();
	g.setColour(juce::Colours::blue);
	g.drawRect(outline, 2.f);


	g.setColour (Colours::white);
	g.setFont (15.0f);
	g.drawFittedText ("Audio Processor Editor",
					  getLocalBounds(),
					  Justification::centred,
					  1);
	
	if (! isARAEditorView())
	{
		g.setColour (Colours::white);
		g.setFont (15.0f);
		g.drawFittedText ("ARA host isn't detected. This plugin only supports ARA mode",
						  getLocalBounds(),
						  Justification::centred,
						  1);
	}
}

void ARAHelper_Editor::resized()
{
	if (documentView != nullptr)
		documentView->setBoundsRelative(0.f, 0.f, 1.f, 0.7f);
	
	if (helperView != nullptr)
		helperView->setBoundsRelative(0.f, 0.7f, 1.f, 0.25f);
}
