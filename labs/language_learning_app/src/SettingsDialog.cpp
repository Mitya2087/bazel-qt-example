#include "SettingsDialog.h"

SettingsDialog::SettingsDialog(QWidget *parent) : QDialog(parent) {
    setWindowTitle("Settings");

    auto *mainLayout = new QVBoxLayout(this);

    auto *difficultyLayout = new QHBoxLayout();
    difficultyLayout->addWidget(new QLabel("Difficulty:", this));

    m_comboDifficulty = new QComboBox(this);
    m_comboDifficulty->addItem("Easy (5 Lives, 60s)");
    m_comboDifficulty->addItem("Medium (3 Lives, 45s)");
    m_comboDifficulty->addItem("Hard (1 Life, 30s)");
    difficultyLayout->addWidget(m_comboDifficulty);

    mainLayout->addLayout(difficultyLayout);

    auto *buttonLayout = new QHBoxLayout();
    m_btnOk = new QPushButton("OK", this);
    m_btnCancel = new QPushButton("Cancel", this);
    buttonLayout->addWidget(m_btnOk);
    buttonLayout->addWidget(m_btnCancel);

    mainLayout->addLayout(buttonLayout);

    connect(m_btnOk, &QPushButton::clicked, this, &QDialog::accept);
    connect(m_btnCancel, &QPushButton::clicked, this, &QDialog::reject);
}

int SettingsDialog::getDifficulty() const {
    return m_comboDifficulty->currentIndex();
}
