cmake_minimum_required(VERSION 3.5)
project(LanguageLearningApp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find Qt5
find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)

# Include current directory
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Enable Qt automoc, autouic, and autorcc
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Define source files
set(SOURCES
    src/main.cpp
    src/MainWindow.cpp
    src/ExerciseBase.cpp
    src/TranslationExercise.cpp
    src/GrammarExercise.cpp
    src/SettingsDialog.cpp
)

set(HEADERS
    src/MainWindow.h
    src/ExerciseBase.h
    src/TranslationExercise.h
    src/GrammarExercise.h
    src/SettingsDialog.h
)

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Link libraries
target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Widgets)
