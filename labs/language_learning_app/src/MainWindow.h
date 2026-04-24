#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QProgressBar>
#include <QLabel>
#include <QTimer>
#include <QShortcut>

class ExerciseBase;

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void openSettings();
    void startTranslationExercise();
    void startGrammarExercise();
    void handleQuestionCompleted(bool isCorrect);
    void handleExerciseFinished();
    void updateTimer();
    void showHelp();

private:
    void setupUi();
    void setupMenuBar();
    void updateStatusUI();
    void endSession(bool won);

    QStackedWidget *m_stackedWidget;
    QWidget *m_mainMenuWidget;
    ExerciseBase *m_translationExercise;
    ExerciseBase *m_grammarExercise;

    QProgressBar *m_progressBar;
    QLabel *m_lblScore;
    QLabel *m_lblLives;
    QLabel *m_lblTimer;

    QTimer *m_timer;
    QShortcut *m_helpShortcut;

    int m_score;
    int m_lives;
    int m_maxLives;
    int m_timeRemaining;
    int m_initialTime;
    int m_questionsCompleted;
    int m_totalQuestions;

    ExerciseBase *m_currentExercise;
};

#endif // MAINWINDOW_H
