#include "difficulty_dialog.h"

#include <QDialogButtonBox>
#include <QGroupBox>
#include <QLabel>
#include <QVBoxLayout>

DifficultyDialog::DifficultyDialog(Difficulty current, QWidget* parent)
    : QDialog(parent) {
  setWindowTitle("SYSTEM CONFIG: THREAT LEVEL");
  setFixedSize(320, 260);
  setStyleSheet(
      "QDialog { background: #000000; }"
      "QLabel { color: #e4e4e7; font-size: 16px; font-weight: bold; font-family: monospace; }"
      "QGroupBox { border: 1px solid #27272a; border-radius: 0px; "
      "margin-top: 10px; padding: 16px 12px 12px 12px; color: #a1a1aa; "
      "font-size: 14px; font-weight: bold; font-family: monospace; }"
      "QGroupBox::title { subcontrol-origin: margin; left: 12px; "
      "padding: 0 6px; }"
      "QRadioButton { color: #a1a1aa; font-size: 14px; font-weight: bold; font-family: monospace; spacing: 8px; "
      "padding: 8px 0; }"
      "QRadioButton::indicator { width: 16px; height: 16px; }"
      "QRadioButton:checked { color: #00ffcc; }"
      "QPushButton { background: #00ffcc; color: #000000; border: none; "
      "border-radius: 0px; padding: 8px 20px; font-weight: 900; "
      "font-size: 15px; font-family: monospace; letter-spacing: 1px; }"
      "QPushButton:hover { background: #33ffdb; }"
      "QPushButton:pressed { background: #00ccaa; }");

  QVBoxLayout* layout = new QVBoxLayout(this);
  layout->setSpacing(12);

  QLabel* title = new QLabel("SELECT THREAT LEVEL:");
  title->setStyleSheet("font-size: 18px; font-weight: 900; color: #e4e4e7; font-family: monospace;");
  layout->addWidget(title);

  QGroupBox* group = new QGroupBox("THREAT_MATRIX");
  QVBoxLayout* group_layout = new QVBoxLayout(group);

  easy_radio_ = new QRadioButton("[LOW]      -- 5 CYCLES, 2 MIN");
  medium_radio_ = new QRadioButton("[MODERATE] -- 8 CYCLES, 1.5 MIN");
  hard_radio_ = new QRadioButton("[CRITICAL] -- 10 CYCLES, 1 MIN");

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
