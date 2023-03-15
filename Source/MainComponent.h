#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent  : public juce::Component
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

    void play();
    void stop();

    void easy();
    void normal();
    void hard();

    void checkGuess();

private:
    //==============================================================================
    // Your private member variables go here...
    enum class PlayState {
        Play,
        Stop
    };

    enum class DifficultyLevel {
        Easy,
        Normal,
        Hard
    };

    PlayState playState{ PlayState::Stop };
    juce::TextButton playButton;
    juce::TextButton stopButton;

    DifficultyLevel easyLevel{ DifficultyLevel::Easy};
    DifficultyLevel normalLevel{ DifficultyLevel::Normal };
    DifficultyLevel hardLevel{ DifficultyLevel::Hard };
    juce::TextButton easyButton;
    juce::TextButton normalButton;
    juce::TextButton hardButton;

    juce::TextButton header;
    juce::TextButton sidebar;


    juce::Label newGameLabel;
    juce::Label byeLabel;
    juce::Label gameLabel;
    juce::Label gameText;
    juce::Label yourGuessLabel;
    juce::Label yourGuessInput;
    juce::Label resultLabel;
    juce::Label resultText;
    int secretNumber;
    int guessesRemaining;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
