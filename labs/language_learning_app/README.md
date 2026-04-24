# Language Learning App

A DuoLingo clone implemented in C++ using the Qt Framework.

## Features

*   **Dynamic UI:** Uses `QStackedWidget` for seamless transitions between the main menu and exercises.
*   **Translation Exercises:** Translate sentences with a text box. Features a Levenshtein distance algorithm to allow for minor typos.
*   **Grammar Exercises:** Multiple-choice questions using radio buttons.
*   **Progress Tracking:** Progress bar tracking completion of N tasks per session.
*   **Grading & Lives System:** Earn points for correct answers, lose lives (hearts) for mistakes. The game ends if you lose all lives.
*   **Timer:** A countdown timer for each exercise.
*   **Hotkeys:** Press 'H' during an exercise for a hint/help.
*   **Settings:** Configure difficulty via a settings dialog.

## Requirements

*   C++17 or higher
*   CMake 3.5 or higher
*   Qt 5 (Core, Gui, Widgets)

## Building and Running

1.  Navigate to the project directory:
    ```bash
    cd labs/language_learning_app
    ```
2.  Create a build directory:
    ```bash
    mkdir build
    cd build
    ```
3.  Run CMake:
    ```bash
    cmake ..
    ```
4.  Compile the project:
    ```bash
    make
    ```
5.  Run the application:
    ```bash
    ./LanguageLearningApp
    ```
