#ifndef GRAMMAREXERCISE_H
#define GRAMMAREXERCISE_H

#include "ExerciseBase.h"
#include <QLabel>
#include <QRadioButton>
#include <QButtonGroup>
#include <QPushButton>
#include <QVBoxLayout>
#include <vector>

struct GrammarQuestion {
    QString prompt;
    std::vector<QString> options;
    int correctOptionIndex;
};

class GrammarExercise : public ExerciseBase {
    Q_OBJECT

public:
    explicit GrammarExercise(QWidget *parent = nullptr);

    void startExercise() override;
    void evaluateAnswer() override;
    QString getHelpMessage() const override;
    int getTotalQuestions() const override;

private:
    void loadNextQuestion();

    QLabel *m_lblPrompt;
    QButtonGroup *m_btnGroup;
    QVBoxLayout *m_optionsLayout;
    QPushButton *m_btnSubmit;

    std::vector<GrammarQuestion> m_questions;
    int m_currentIndex;
};

#endif // GRAMMAREXERCISE_H
