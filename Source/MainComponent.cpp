#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{

    /* Display header */
    header.setColour(juce::TextButton::buttonColourId, juce::Colours::black);
    header.setButtonText("Guess my number");
    header.setVisible(true);
    addAndMakeVisible(header);

    /* Display sidebar */
    sidebar.setColour(juce::TextButton::buttonColourId, juce::Colours::grey);
    addAndMakeVisible(sidebar);

    /* Start and stop buttons */
    playButton.setToggleState(true, juce::NotificationType::dontSendNotification);
    playButton.setButtonText("Play");
    playButton.onClick = [this]() {play(); };
    addAndMakeVisible(playButton);

    stopButton.setToggleState(true, juce::NotificationType::dontSendNotification);
    stopButton.setButtonText("Stop");
    stopButton.onClick = [this]() {stop(); };
    addAndMakeVisible(stopButton);

    /* Difficulty level buttons */
    easyButton.setToggleState(true, juce::NotificationType::dontSendNotification);
    easyButton.setButtonText("Easy");
    easyButton.onClick = [this]() {easy(); };
    easyButton.setVisible(false);
    addAndMakeVisible(easyButton);

    normalButton.setToggleState(true, juce::NotificationType::dontSendNotification);
    normalButton.setButtonText("Normal");
    normalButton.onClick = [this]() {normal(); };
    normalButton.setVisible(false);
    addAndMakeVisible(normalButton);

    hardButton.setToggleState(true, juce::NotificationType::dontSendNotification);
    hardButton.setButtonText("Hard");
    hardButton.onClick = [this]() {hard(); };
    hardButton.setVisible(false);
    addAndMakeVisible(hardButton);

    /* Title of new game */
    addAndMakeVisible(newGameLabel);
    newGameLabel.setText("Start new game", juce::dontSendNotification);
    newGameLabel.setColour(juce::Label::textColourId, juce::Colours::white);
    newGameLabel.setJustificationType(juce::Justification::centred);

    /* Results texts for less or greater and remaining text */
    addAndMakeVisible(gameLabel);
    gameLabel.attachToComponent(&gameText, false);
    gameLabel.setColour(juce::Label::textColourId, juce::Colours::white);
    gameLabel.setVisible(false);

    addAndMakeVisible(gameText);
    gameText.setColour(juce::Label::textColourId, juce::Colours::white);
    gameText.setEditable(false);

    addAndMakeVisible(resultLabel);
    resultLabel.attachToComponent(&resultText, false);
    resultLabel.setColour(juce::Label::textColourId, juce::Colours::white);
    resultLabel.setVisible(false);

    addAndMakeVisible(resultText);
    resultText.setColour(juce::Label::textColourId, juce::Colours::white);
    resultText.setEditable(false);

    /* Screen size */
    setSize(300, 300);

}

MainComponent::~MainComponent()
{
}

void MainComponent::play() {

    if (playState == PlayState::Stop) {

        playState = PlayState::Play;

        juce::Rectangle<int> bounds = getLocalBounds();

        auto headerHeight = 36;
        header.setBounds(bounds.removeFromTop(headerHeight));

        /* Sidebar on the right hand side */
        auto sideBarArea = bounds.removeFromRight(juce::jmax(80, bounds.getWidth() / 4));
        sidebar.setBounds(sideBarArea);

        /* Buttons on top of the sidebar */
        auto sideItemHeight = 65;
        auto sideItemMargin = 5;

        easyButton.setBounds(sideBarArea.removeFromTop(sideItemHeight).reduced(sideItemMargin));
        normalButton.setBounds(sideBarArea.removeFromTop(sideItemHeight).reduced(sideItemMargin));
        hardButton.setBounds(sideBarArea.removeFromTop(sideItemHeight).reduced(sideItemMargin));
        stopButton.setBounds(sideBarArea.removeFromTop(sideItemHeight).reduced(sideItemMargin));

        yourGuessInput.setEnabled(true);

        byeLabel.setVisible(false);

    }

}

void MainComponent::easy() {

    if (playState == PlayState::Play || easyLevel == DifficultyLevel::Easy || playState == PlayState::Stop) {
        
        playState = PlayState::Play;

        byeLabel.setVisible(false);
        newGameLabel.setVisible(false);
        resultLabel.setVisible(false);
        header.setButtonText("Guess a number between 1 and 10");

        juce::Random random;
        secretNumber = random.nextInt(10) + 1; // generate a number between 1 and 10
        guessesRemaining = 10;

        addAndMakeVisible(yourGuessLabel);
        yourGuessLabel.setText("Your Guess:", juce::dontSendNotification);
        yourGuessLabel.attachToComponent(&yourGuessInput, true);
        yourGuessLabel.setColour(juce::Label::textColourId, juce::Colours::white);
        yourGuessLabel.setJustificationType(juce::Justification::right);

        addAndMakeVisible(yourGuessInput);
        yourGuessInput.setColour(juce::Label::textColourId, juce::Colours::white);
        yourGuessInput.onTextChange = [this] { checkGuess(); };
        yourGuessInput.setEditable(true);
    }

}

void MainComponent::normal() {

    if (playState == PlayState::Play || normalLevel == DifficultyLevel::Normal || playState == PlayState::Stop) {

        playState = PlayState::Play;

        byeLabel.setVisible(false);
        newGameLabel.setVisible(false);
        resultLabel.setVisible(false);
        header.setButtonText("Guess a number between 1 and 100");

        juce::Random random;
        secretNumber = random.nextInt(100) + 1; // generate a number between 1 and 100
        guessesRemaining = 10;
        resultLabel.setVisible(false);

        addAndMakeVisible(yourGuessLabel);
        yourGuessLabel.setText("Your Guess:", juce::dontSendNotification);
        yourGuessLabel.attachToComponent(&yourGuessInput, true);
        yourGuessLabel.setColour(juce::Label::textColourId, juce::Colours::white);
        yourGuessLabel.setJustificationType(juce::Justification::right);

        addAndMakeVisible(yourGuessInput);
        yourGuessInput.setColour(juce::Label::textColourId, juce::Colours::white);
        yourGuessInput.onTextChange = [this] { checkGuess(); };
        yourGuessInput.setEditable(true);
    }

}

void MainComponent::hard() {

    if (playState == PlayState::Play || hardLevel == DifficultyLevel::Hard || playState == PlayState::Stop) {

        playState = PlayState::Play;

        byeLabel.setVisible(false);
        newGameLabel.setVisible(false);
        resultLabel.setVisible(false);
        header.setButtonText("Guess a number between 1 and 1000");

        juce::Random random;
        secretNumber = random.nextInt(1000) + 1; // generate a number between 1 and 1000
        guessesRemaining = 10;
        resultLabel.setVisible(false);

        addAndMakeVisible(yourGuessLabel);
        yourGuessLabel.setText("Your Guess:", juce::dontSendNotification);
        yourGuessLabel.attachToComponent(&yourGuessInput, true);
        yourGuessLabel.setColour(juce::Label::textColourId, juce::Colours::white);
        yourGuessLabel.setJustificationType(juce::Justification::right);

        addAndMakeVisible(yourGuessInput);
        yourGuessInput.setColour(juce::Label::textColourId, juce::Colours::white);
        yourGuessInput.onTextChange = [this] { checkGuess(); };
        yourGuessInput.setEditable(true);
    }

}

void MainComponent::stop() {

    if (playState == PlayState::Play) {

        playState = PlayState::Stop;

        newGameLabel.setVisible(false);
        yourGuessInput.setVisible(false);
        yourGuessLabel.setVisible(false);
        resultLabel.setVisible(false);
        gameLabel.setVisible(false);

        header.setButtonText("Bye");

        addAndMakeVisible(byeLabel);
        byeLabel.setText("Thank you for playing with me. :)", juce::dontSendNotification);
        byeLabel.setColour(juce::Label::textColourId, juce::Colours::white);
        byeLabel.setJustificationType(juce::Justification::right);

    }

}

void MainComponent::checkGuess() {

    int guess = yourGuessInput.getText().getIntValue();

    /* Game logic */
    if (guess > secretNumber) {
        gameLabel.setText("Less!", juce::dontSendNotification);
        yourGuessInput.setEnabled(true);
    }
    else if (guess < secretNumber) {
        gameLabel.setText("Greater!", juce::dontSendNotification);
        yourGuessInput.setEnabled(true);
    }
    else
    {
        gameLabel.setText("You win!", juce::dontSendNotification);
        yourGuessInput.setEnabled(false);
    }

    /* Tries */
    if (guessesRemaining == 1)
    {
        resultLabel.setText("You lose! The secret number was " + juce::String(secretNumber), juce::dontSendNotification);
        yourGuessInput.setEnabled(false);
    }
    else if (guessesRemaining != 1)
    {
        --guessesRemaining;
        resultLabel.setText(juce::String(guessesRemaining) + " guesses remaining", juce::dontSendNotification);
    }

    resultLabel.setVisible(true);

}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setFont (juce::Font (16.0f));
    g.setColour (juce::Colours::white);

}

void MainComponent::resized()
{
    juce::Rectangle<int> bounds = getLocalBounds();

    auto headerHeight = 36;
    header.setBounds(bounds.removeFromTop(headerHeight));

    /* Sidebar on the right hand side */
    auto sideBarArea = bounds.removeFromRight(juce::jmax(80, bounds.getWidth() / 4));
    sidebar.setBounds(sideBarArea);

    /* Buttons on top of the sidebar */
    auto sideItemHeight = 65;
    auto sideItemMargin = 5;
    playButton.setBounds(sideBarArea.removeFromTop(sideItemHeight).reduced(sideItemMargin));


    newGameLabel.setBounds(10, 50, getWidth() - 100, 20);
    byeLabel.setBounds(10, 50, getWidth() - 100, 20);
    yourGuessLabel.setBounds(100, 20, getWidth() - 110, 20);
    yourGuessInput.setBounds(100, 50, getWidth() - 200, 20);
    gameText.setBounds(10, 100, getWidth() - 110, 20);
    resultText.setBounds(10, 120, getWidth() - 110, 20);
}
