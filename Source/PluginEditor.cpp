#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
SimpleMidiplayerAudioProcessorEditor::SimpleMidiplayerAudioProcessorEditor (SimpleMidiplayerAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // -------------------------------------------------------------------------
    // Click on this button to select a MIDI file to play in the processor
    buttonLoadMIDIFile = std::make_unique<juce::TextButton>("Load a MIDI file");
    addAndMakeVisible(buttonLoadMIDIFile.get());
    buttonLoadMIDIFile->addListener(this);

    // Click on this combo box to select the track that needs to be played
    comboTrack = std::make_unique<juce::ComboBox>();
    addAndMakeVisible(comboTrack.get());
    comboTrack->addListener(this);
    updateTrackComboBox();
    
    // -------------------------------------------------------------------------
    setSize (400, 300);
}

SimpleMidiplayerAudioProcessorEditor::~SimpleMidiplayerAudioProcessorEditor()
{
}

void SimpleMidiplayerAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
}

void SimpleMidiplayerAudioProcessorEditor::resized()
{
    juce::Rectangle<int> rect = getLocalBounds();
    
    buttonLoadMIDIFile->setBounds(rect.removeFromTop(rect.getHeight() / 2).withSizeKeepingCentre(200, 24));
    comboTrack->setBounds(rect.withSizeKeepingCentre(200, 24));
}

void SimpleMidiplayerAudioProcessorEditor::buttonClicked(juce::Button * button)
{
    if (button == buttonLoadMIDIFile.get())
    {
        juce::FileChooser theFileChooser("Find a MIDI file", juce::File(), "*.mid");
        
        if (theFileChooser.browseForFileToOpen())
        {
            processor.loadMIDIFile(theFileChooser.getResult());
            updateTrackComboBox();
        }
    }
}

void SimpleMidiplayerAudioProcessorEditor::comboBoxChanged(juce::ComboBox* combo)
{
    if (combo == comboTrack.get())
    {
        processor.setCurrentTrack(combo->getSelectedId() - 1);
    }
}

void SimpleMidiplayerAudioProcessorEditor::updateTrackComboBox()
{
    comboTrack->clear();

    for (auto i = 0; i < processor.getNumTracks(); i++)
        comboTrack->addItem("Track number " + juce::String(i + 1), i + 1);

    comboTrack->setSelectedId(processor.getCurrentTrack() + 1, juce::dontSendNotification);
}
