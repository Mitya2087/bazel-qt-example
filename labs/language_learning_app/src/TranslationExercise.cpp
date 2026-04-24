#include "TranslationExercise.h"
#include <algorithm>
#include <numeric>

TranslationExercise::TranslationExercise(QWidget *parent)
    : ExerciseBase(parent), m_currentIndex(0)
{
    auto *layout = new QVBoxLayout(this);

    m_lblPrompt = new QLabel("Translate this text:", this);
    m_lblPrompt->setWordWrap(true);
    layout->addWidget(m_lblPrompt);

    m_txtAnswer = new QTextEdit(this);
    m_txtAnswer->setMaximumHeight(100);
    layout->addWidget(m_txtAnswer);

    m_btnSubmit = new QPushButton("Submit", this);
    layout->addWidget(m_btnSubmit);

    connect(m_btnSubmit, &QPushButton::clicked, this, &TranslationExercise::evaluateAnswer);

    m_questions = {
        {"The cat is on the table", "Кошка на столе"},
        {"I am learning C++", "Я изучаю C++"},
        {"Qt is a great framework", "Qt отличный фреймворк"}
    };
}

void TranslationExercise::startExercise() {
    m_currentIndex = 0;
    loadNextQuestion();
}

void TranslationExercise::loadNextQuestion() {
    if (m_currentIndex < m_questions.size()) {
        m_lblPrompt->setText(QString("Translate: %1").arg(m_questions[m_currentIndex].first));
        m_txtAnswer->clear();
    } else {
        emit exerciseFinished();
    }
}

int TranslationExercise::getTotalQuestions() const {
    return m_questions.size();
}

void TranslationExercise::evaluateAnswer() {
    if (m_currentIndex >= m_questions.size()) return;

    QString expected = m_questions[m_currentIndex].second.trimmed().toLower();
    QString actual = m_txtAnswer->toPlainText().trimmed().toLower();

    int distance = levenshteinDistance(actual, expected);

    // Allow a small margin of error for typos (e.g. distance <= 2)
    int maxAllowedErrors = std::max(1, static_cast<int>(expected.length() / 5));
    bool isCorrect = distance <= maxAllowedErrors;

    emit questionCompleted(isCorrect);

    m_currentIndex++;
    loadNextQuestion();
}

QString TranslationExercise::getHelpMessage() const {
    return "Enter the translation of the phrase in Russian. Minor typos are allowed!";
}

int TranslationExercise::levenshteinDistance(const QString& s1, const QString& s2) const {
    const std::size_t len1 = s1.size(), len2 = s2.size();
    std::vector<std::vector<unsigned int>> d(len1 + 1, std::vector<unsigned int>(len2 + 1));

    for(unsigned int i = 1; i <= len1; ++i) d[i][0] = i;
    for(unsigned int i = 1; i <= len2; ++i) d[0][i] = i;

    for(unsigned int i = 1; i <= len1; ++i) {
        for(unsigned int j = 1; j <= len2; ++j) {
            d[i][j] = std::min({ d[i - 1][j] + 1,
                                 d[i][j - 1] + 1,
                                 d[i - 1][j - 1] + (s1[i - 1] == s2[j - 1] ? 0 : 1) });
        }
    }
    return d[len1][len2];
}
