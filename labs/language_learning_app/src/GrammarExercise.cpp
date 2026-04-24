#include "GrammarExercise.h"

GrammarExercise::GrammarExercise(QWidget *parent)
    : ExerciseBase(parent), m_currentIndex(0)
{
    auto *mainLayout = new QVBoxLayout(this);

    m_lblPrompt = new QLabel("Select the correct grammar option:", this);
    m_lblPrompt->setWordWrap(true);
    mainLayout->addWidget(m_lblPrompt);

    m_optionsLayout = new QVBoxLayout();
    mainLayout->addLayout(m_optionsLayout);

    m_btnGroup = new QButtonGroup(this);

    m_btnSubmit = new QPushButton("Submit", this);
    mainLayout->addWidget(m_btnSubmit);

    connect(m_btnSubmit, &QPushButton::clicked, this, &GrammarExercise::evaluateAnswer);

    m_questions = {
        {"He ___ to the store yesterday.", {"goes", "went", "gone", "going"}, 1},
        {"I have ___ seen that movie.", {"already", "yet", "still", "ever"}, 0},
        {"If I ___ you, I would study harder.", {"am", "was", "were", "be"}, 2}
    };
}

void GrammarExercise::startExercise() {
    m_currentIndex = 0;
    loadNextQuestion();
}

void GrammarExercise::loadNextQuestion() {
    // Clear existing radio buttons
    QLayoutItem *item;
    while ((item = m_optionsLayout->takeAt(0)) != nullptr) {
        if (QWidget *widget = item->widget()) {
            m_btnGroup->removeButton(static_cast<QAbstractButton*>(widget));
            widget->deleteLater();
        }
        delete item;
    }

    if (m_currentIndex < m_questions.size()) {
        const auto& q = m_questions[m_currentIndex];
        m_lblPrompt->setText(q.prompt);

        for (int i = 0; i < q.options.size(); ++i) {
            auto *radioBtn = new QRadioButton(q.options[i], this);
            m_btnGroup->addButton(radioBtn, i);
            m_optionsLayout->addWidget(radioBtn);
        }
    } else {
        emit exerciseFinished();
    }
}

int GrammarExercise::getTotalQuestions() const {
    return m_questions.size();
}

void GrammarExercise::evaluateAnswer() {
    if (m_currentIndex >= m_questions.size()) return;

    int selectedId = m_btnGroup->checkedId();
    if (selectedId == -1) return; // No option selected

    bool isCorrect = (selectedId == m_questions[m_currentIndex].correctOptionIndex);

    emit questionCompleted(isCorrect);

    m_currentIndex++;
    loadNextQuestion();
}

QString GrammarExercise::getHelpMessage() const {
    return "Select the word that best completes the sentence grammatically.";
}
