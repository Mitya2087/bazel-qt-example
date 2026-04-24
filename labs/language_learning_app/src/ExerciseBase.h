#ifndef EXERCISEBASE_H
#define EXERCISEBASE_H

#include <QWidget>
#include <QString>

class ExerciseBase : public QWidget {
    Q_OBJECT

public:
    explicit ExerciseBase(QWidget *parent = nullptr);
    virtual ~ExerciseBase() = default;

    // Start or restart the exercise
    virtual void startExercise() = 0;

    // Evaluate current user input
    virtual void evaluateAnswer() = 0;

    // Provide help message for current task
    virtual QString getHelpMessage() const = 0;

    // Get total number of questions
    virtual int getTotalQuestions() const = 0;

signals:
    // Emitted when a single question is answered (true if correct)
    void questionCompleted(bool isCorrect);

    // Emitted when all N questions of the exercise are done
    void exerciseFinished();
};

#endif // EXERCISEBASE_H
