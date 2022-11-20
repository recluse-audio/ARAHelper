/*
  ==============================================================================

    ARA_HelperView.cpp
    Created: 16 Nov 2022 3:37:16pm
    Author:  Ryan Devens

  ==============================================================================
*/

#include <JuceHeader.h>
#include "ARA_HelperView.h"
#include "ARA_DocumentListBoxModel.h"
#include "ARA_ObjectWidget.h"
#include "ARA_PlaybackRegionWidget.h"
#include "ARA_ListenerCallbackDisplay.h"

//==============================================================================
ARA_HelperView::ARA_HelperView(juce::ARADocument& document) : araDocument(document)
{
	//objectWidget = std::make_unique<ARA_ObjectWidget>();
	
	boxModel = std::make_unique<ARA_DocumentListBoxModel>();
	tableListBox = std::make_unique<juce::TableListBox>("LIST BOX", boxModel.get());
	addAndMakeVisible(tableListBox.get());
	
	callbackDisplay = std::make_unique<ARA_ListenerCallbackDisplay>(document);
	addAndMakeVisible(callbackDisplay.get());
	
	araDocument.addListener(this);
	_update();
}

ARA_HelperView::~ARA_HelperView()
{
	araDocument.removeListener (this);
}

void ARA_HelperView::paint (juce::Graphics& g)
{
	g.setColour(juce::Colours::whitesmoke);
	g.fillAll();
}

void ARA_HelperView::resized()
{
	callbackDisplay->setBoundsRelative(0.f, 0.f, 0.3f, 1.f);
	tableListBox->setBoundsRelative(0.3f, 0.f, 0.7f, 1.f);

	_resizeTableHeader();
}

void ARA_HelperView::didEndEditing(juce::ARADocument*)
{
	_update();
}

void ARA_HelperView::_update()
{
	this->repaint();
}

void ARA_HelperView::_updateRegions()
{
	auto regionSequences = araDocument.getRegionSequences();
}



void ARA_HelperView::_resizeTableHeader()
{
	int tableWidth = tableListBox->getWidth();
	int numColumns = static_cast<int>(ARAObjectID::TotalNumIDs) - 1;
	float columnWidth = (float)tableWidth / (float)numColumns;
	
	std::unique_ptr<juce::TableHeaderComponent> tableHeader = std::make_unique<juce::TableHeaderComponent>();
	
	tableHeader->addColumn("ARA Documents: ", 		static_cast<int>(ARAObjectID::DocumentController), columnWidth);
	tableHeader->addColumn("Editor Renderers:", 	static_cast<int>(ARAObjectID::EditorRenderer), columnWidth);
	tableHeader->addColumn("Playback Renderers:", 	static_cast<int>(ARAObjectID::PlaybackRenderer), columnWidth);
	tableHeader->addColumn("Editor Views:", 		static_cast<int>(ARAObjectID::EditorView), columnWidth);
	tableHeader->addColumn("Region Sequences:", 	static_cast<int>(ARAObjectID::RegionSequence), columnWidth);
	tableHeader->addColumn("Playback Regions:", 	static_cast<int>(ARAObjectID::PlaybackRegion), columnWidth);
	tableHeader->addColumn("Audio Mods:", 			static_cast<int>(ARAObjectID::AudioModification), columnWidth);
	tableHeader->addColumn("Audio Sources:", 		static_cast<int>(ARAObjectID::AudioSource), columnWidth);
	
//	int headerHeight = (int)getLocalBounds().getHeight();
//	tableListBox->setHeaderHeight(headerHeight);
	tableListBox->setHeader(std::move(tableHeader));
}


//void ARA_HelperView::_updateRegionLabel()
//{
//	auto regionSequences = araDocument.getRegionSequences();
//	int numRegions = 0;
//
//	for(auto sequence : regionSequences)
//	{
//		auto playbackRegions = sequence->getPlaybackRegions();
//		numRegions += playbackRegions.size();
//	}
//
//	juce::String numPlaybackRegions (numRegions);
//
//	juce::String regionText("Playback Regions: ");
//	regionLabel->setText(regionText + numPlaybackRegions, juce::NotificationType::sendNotificationAsync);
//}
//
//void ARA_HelperView::_updateSequenceLabel()
//{
//	auto regionSequences = araDocument.getRegionSequences();
//	juce::String numRegionSequences (regionSequences.size());
//
//	juce::String sequenceText("Region Sequences: ");
//	sequenceLabel->setText(sequenceText + numRegionSequences, juce::NotificationType::sendNotificationAsync);
//
//}
