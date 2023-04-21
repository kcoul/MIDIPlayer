#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"


//==============================================================================
/**
*/
class SimpleMidiplayerAudioProcessorEditor : public juce::AudioProcessorEditor,
public juce::Button::Listener, public juce::ComboBox::Listener
{
public:
    //==============================================================================
    SimpleMidiplayerAudioProcessorEditor (SimpleMidiplayerAudioProcessor&);
    ~SimpleMidiplayerAudioProcessorEditor();

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

    //==============================================================================
    void buttonClicked(juce::Button* button) override;
    void comboBoxChanged(juce::ComboBox* combo) override;

private:
    //==============================================================================
    void updateTrackComboBox();
    
    //==============================================================================
    std::unique_ptr<juce::TextButton> buttonLoadMIDIFile;
    std::unique_ptr<juce::ComboBox> comboTrack;
    
    //==============================================================================
    SimpleMidiplayerAudioProcessor& processor;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SimpleMidiplayerAudioProcessorEditor)
};
