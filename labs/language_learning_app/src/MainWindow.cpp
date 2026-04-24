#include "MainWindow.h"
#include "TranslationExercise.h"
#include "GrammarExercise.h"
#include "SettingsDialog.h"
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QMessageBox>
#include <QKeySequence>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), m_score(0), m_lives(5), m_maxLives(5),
      m_timeRemaining(60), m_initialTime(60), m_questionsCompleted(0),
      m_totalQuestions(3), m_currentExercise(nullptr)
{
    setupUi();
    setupMenuBar();
    updateStatusUI();

    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, &MainWindow::updateTimer);

    m_helpShortcut = new QShortcut(QKeySequence("H"), this);
    connect(m_helpShortcut, &QShortcut::activated, this, &MainWindow::showHelp);
}

MainWindow::~MainWindow() {}

void MainWindow::setupUi() {
    auto *centralWidget = new QWidget(this);
    auto *mainLayout = new QVBoxLayout(centralWidget);

    // Status Bar Area (Top)
    auto *statusLayout = new QHBoxLayout();
    m_progressBar = new QProgressBar(this);
    m_progressBar->setMaximum(m_totalQuestions);
    m_progressBar->setValue(0);

    m_lblScore = new QLabel("Score: 0", this);
    m_lblLives = new QLabel("Lives: 5", this);
    m_lblTimer = new QLabel("Time: 60s", this);

    statusLayout->addWidget(m_progressBar);
    statusLayout->addWidget(m_lblScore);
    statusLayout->addWidget(m_lblLives);
    statusLayout->addWidget(m_lblTimer);
    mainLayout->addLayout(statusLayout);

    // Stacked Widget Area
    m_stackedWidget = new QStackedWidget(this);

    // Main Menu
    m_mainMenuWidget = new QWidget(this);
    auto *menuLayout = new QVBoxLayout(m_mainMenuWidget);
    auto *btnTrans = new QPushButton("Translation Exercise", this);
    auto *btnGrammar = new QPushButton("Grammar Exercise", this);
    menuLayout->addWidget(btnTrans);
    menuLayout->addWidget(btnGrammar);
    m_stackedWidget->addWidget(m_mainMenuWidget);

    // Exercises
    m_translationExercise = new TranslationExercise(this);
    m_grammarExercise = new GrammarExercise(this);
    m_stackedWidget->addWidget(m_translationExercise);
    m_stackedWidget->addWidget(m_grammarExercise);

    mainLayout->addWidget(m_stackedWidget);
    setCentralWidget(centralWidget);

    // Connections
    connect(btnTrans, &QPushButton::clicked, this, &MainWindow::startTranslationExercise);
    connect(btnGrammar, &QPushButton::clicked, this, &MainWindow::startGrammarExercise);

    connect(m_translationExercise, &ExerciseBase::questionCompleted, this, &MainWindow::handleQuestionCompleted);
    connect(m_translationExercise, &ExerciseBase::exerciseFinished, this, &MainWindow::handleExerciseFinished);

    connect(m_grammarExercise, &ExerciseBase::questionCompleted, this, &MainWindow::handleQuestionCompleted);
    connect(m_grammarExercise, &ExerciseBase::exerciseFinished, this, &MainWindow::handleExerciseFinished);
}

void MainWindow::setupMenuBar() {
    QMenu *settingsMenu = menuBar()->addMenu("Options");
    QAction *settingsAction = settingsMenu->addAction("Settings");
    connect(settingsAction, &QAction::triggered, this, &MainWindow::openSettings);
}

void MainWindow::openSettings() {
    bool timerWasRunning = m_timer->isActive();
    if (timerWasRunning) m_timer->stop();

    SettingsDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        int diff = dialog.getDifficulty();
        if (diff == 0) { m_maxLives = 5; m_initialTime = 60; }
        else if (diff == 1) { m_maxLives = 3; m_initialTime = 45; }
        else if (diff == 2) { m_maxLives = 1; m_initialTime = 30; }

        // Only update lives if not currently in an exercise to avoid cheating
        if (!m_currentExercise) {
            m_lives = m_maxLives;
        }
        updateStatusUI();
    }

    if (timerWasRunning) m_timer->start(1000);
}

void MainWindow::startTranslationExercise() {
    m_currentExercise = m_translationExercise;
    m_stackedWidget->setCurrentWidget(m_translationExercise);

    m_totalQuestions = m_translationExercise->getTotalQuestions();
    m_progressBar->setMaximum(m_totalQuestions);

    m_translationExercise->startExercise();

    m_questionsCompleted = 0;
    m_timeRemaining = m_initialTime;
    m_lives = m_maxLives;
    updateStatusUI();
    m_timer->start(1000);
}

void MainWindow::startGrammarExercise() {
    m_currentExercise = m_grammarExercise;
    m_stackedWidget->setCurrentWidget(m_grammarExercise);

    m_totalQuestions = m_grammarExercise->getTotalQuestions();
    m_progressBar->setMaximum(m_totalQuestions);

    m_grammarExercise->startExercise();

    m_questionsCompleted = 0;
    m_timeRemaining = m_initialTime;
    m_lives = m_maxLives;
    updateStatusUI();
    m_timer->start(1000);
}

void MainWindow::handleQuestionCompleted(bool isCorrect) {
    m_questionsCompleted++;

    if (!isCorrect) {
        m_lives--;
        if (m_lives <= 0) {
            endSession(false);
            return;
        }
    }
    updateStatusUI();
}

void MainWindow::handleExerciseFinished() {
    // Only award points if the exercise finished successfully (all questions attempted)
    // and the user has not lost all their lives
    if (m_lives > 0) {
        m_score += m_totalQuestions * 10;
        updateStatusUI();
    }
    endSession(true);
}

void MainWindow::updateTimer() {
    m_timeRemaining--;
    updateStatusUI();
    if (m_timeRemaining <= 0) {
        endSession(false);
    }
}

void MainWindow::showHelp() {
    if (m_currentExercise && m_stackedWidget->currentWidget() != m_mainMenuWidget) {
        QMessageBox::information(this, "Help", m_currentExercise->getHelpMessage());
    }
}

void MainWindow::updateStatusUI() {
    m_progressBar->setValue(m_questionsCompleted);
    m_lblScore->setText(QString("Score: %1").arg(m_score));
    m_lblLives->setText(QString("Lives: %1").arg(m_lives));
    m_lblTimer->setText(QString("Time: %1s").arg(m_timeRemaining));
}

void MainWindow::endSession(bool won) {
    m_timer->stop();
    m_currentExercise = nullptr;

    if (won) {
        QMessageBox::information(this, "Session Finished", "Congratulations! You completed the exercise.");
    } else if (m_lives <= 0) {
        QMessageBox::warning(this, "Game Over", "You ran out of lives!");
    } else {
        QMessageBox::warning(this, "Time Up", "Time's up!");
    }

    // Reset for next session (keep overall score for fun, reset lives)
    m_lives = m_maxLives;
    m_questionsCompleted = 0;
    updateStatusUI();
    m_stackedWidget->setCurrentWidget(m_mainMenuWidget);
}
