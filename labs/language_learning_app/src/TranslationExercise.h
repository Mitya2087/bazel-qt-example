#ifndef TRANSLATIONEXERCISE_H
#define TRANSLATIONEXERCISE_H

#include "ExerciseBase.h"
#include <QLabel>
#include <QTextEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <vector>
#include <string>
#include <utility>

class TranslationExercise : public ExerciseBase {
    Q_OBJECT

public:
    explicit TranslationExercise(QWidget *parent = nullptr);

    void startExercise() override;
    void evaluateAnswer() override;
    QString getHelpMessage() const override;
    int getTotalQuestions() const override;

private:
    void loadNextQuestion();
    int levenshteinDistance(const QString& s1, const QString& s2) const;

    QLabel *m_lblPrompt;
    QTextEdit *m_txtAnswer;
    QPushButton *m_btnSubmit;

    std::vector<std::pair<QString, QString>> m_questions;
    int m_currentIndex;
};

#endif // TRANSLATIONEXERCISE_H
