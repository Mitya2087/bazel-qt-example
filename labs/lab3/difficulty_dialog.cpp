#include "difficulty_dialog.h"

#include <QDialogButtonBox>
#include <QGroupBox>
#include <QLabel>
#include <QVBoxLayout>

DifficultyDialog::DifficultyDialog(Difficulty current, QWidget* parent)
    : QDialog(parent) {
  setWindowTitle("Select Difficulty");
  setFixedSize(320, 260);
  setStyleSheet(
      "QDialog { background: #1e1e2e; }"
      "QLabel { color: #cdd6f4; font-size: 14px; }"
      "QGroupBox { border: 1px solid #45475a; border-radius: 8px; "
      "margin-top: 10px; padding: 16px 12px 12px 12px; color: #cdd6f4; "
      "font-size: 13px; }"
      "QGroupBox::title { subcontrol-origin: margin; left: 12px; "
      "padding: 0 6px; }"
      "QRadioButton { color: #cdd6f4; font-size: 13px; spacing: 8px; "
      "padding: 4px 0; }"
      "QRadioButton::indicator { width: 16px; height: 16px; }"
      "QPushButton { background: #89b4fa; color: #1e1e2e; border: none; "
      "border-radius: 6px; padding: 8px 20px; font-weight: bold; "
      "font-size: 13px; }"
      "QPushButton:hover { background: #74c7ec; }"
      "QPushButton:pressed { background: #89dceb; }");

  QVBoxLayout* layout = new QVBoxLayout(this);
  layout->setSpacing(12);

  QLabel* title = new QLabel("Choose difficulty level:");
  title->setStyleSheet("font-size: 15px; font-weight: bold; color: #cdd6f4;");
  layout->addWidget(title);

  QGroupBox* group = new QGroupBox("Difficulty");
  QVBoxLayout* group_layout = new QVBoxLayout(group);

  easy_radio_ = new QRadioButton("🟢  Easy — 5 tasks, 2 min, relaxed");
  medium_radio_ = new QRadioButton("🟡  Medium — 8 tasks, 1.5 min, balanced");
  hard_radio_ = new QRadioButton("🔴  Hard — 10 tasks, 1 min, strict");

  group_layout->addWidget(easy_radio_);
  group_layout->addWidget(medium_radio_);
  group_layout->addWidget(hard_radio_);
  layout->addWidget(group);

  switch (current) {
    case Difficulty::Easy:
      easy_radio_->setChecked(true);
      break;
    case Difficulty::Medium:
      medium_radio_->setChecked(true);
      break;
    case Difficulty::Hard:
      hard_radio_->setChecked(true);
      break;
  }

  QDialogButtonBox* buttons =
      new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
  layout->addWidget(buttons);

  connect(buttons, &QDialogButtonBox::accepted, this, &QDialog::accept);
  connect(buttons, &QDialogButtonBox::rejected, this, &QDialog::reject);
}

Difficulty DifficultyDialog::GetSelectedDifficulty() const {
  if (hard_radio_->isChecked()) {
    return Difficulty::Hard;
  }
  if (medium_radio_->isChecked()) {
    return Difficulty::Medium;
  }
  return Difficulty::Easy;
}
