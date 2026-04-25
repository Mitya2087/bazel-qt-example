#include "mainwindow.h"

#include <QAction>
#include <QHBoxLayout>
#include <QKeyEvent>
#include <QLabel>
#include <QMenuBar>
#include <QMessageBox>
#include <QPushButton>
#include <QVBoxLayout>

#include "difficulty_dialog.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
  SetupUi();
  SetupMenuBar();
  setWindowTitle("SynthLang // Neoxul");
}

void MainWindow::SetupUi() {
  QWidget* central = new QWidget(this);
  setCentralWidget(central);

  QHBoxLayout* main_layout = new QHBoxLayout(central);
  main_layout->setContentsMargins(0, 0, 0, 0);
  main_layout->setSpacing(0);

  // ── Left sidebar ──
  QWidget* sidebar = new QWidget();
  sidebar->setFixedWidth(240);
  sidebar->setStyleSheet(
      "background: #09090b; border-left: 1px solid #27272a;");

  QVBoxLayout* sidebar_layout = new QVBoxLayout(sidebar);
  sidebar_layout->setContentsMargins(16, 20, 16, 20);
  sidebar_layout->setSpacing(12);

  // App title
  QLabel* app_title = new QLabel("⚡ SYNTHLANG");
  app_title->setStyleSheet(
      "font-size: 20px; font-weight: 900; color: #00ffcc; "
      "letter-spacing: 2px; padding-bottom: 8px; border: none; font-family: monospace;");
  sidebar_layout->addWidget(app_title);

  // Score display
  QWidget* score_card = new QWidget();
  score_card->setStyleSheet(
      "background: #18181b; border-radius: 4px; border: 1px solid #27272a;");
  QVBoxLayout* score_layout = new QVBoxLayout(score_card);
  score_layout->setContentsMargins(12, 10, 12, 10);

  QLabel* score_title = new QLabel("CREDITS");
  score_title->setStyleSheet(
      "font-size: 11px; font-weight: bold; color: #a1a1aa; letter-spacing: 1px; border: none; font-family: monospace;");
  score_layout->addWidget(score_title);

  score_label_ = new QLabel("000");
  score_label_->setStyleSheet(
      "font-size: 28px; font-weight: 900; color: #ff00ff; border: none; font-family: monospace;");
  score_layout->addWidget(score_label_);

  sidebar_layout->addWidget(score_card);

  // Difficulty display
  QWidget* diff_card = new QWidget();
  diff_card->setStyleSheet(
      "background: #18181b; border-radius: 4px; border: 1px solid #27272a;");
  QVBoxLayout* diff_layout = new QVBoxLayout(diff_card);
  diff_layout->setContentsMargins(12, 10, 12, 10);

  QLabel* diff_title = new QLabel("THREAT LEVEL");
  diff_title->setStyleSheet(
      "font-size: 11px; font-weight: bold; color: #a1a1aa; letter-spacing: 1px; border: none; font-family: monospace;");
  diff_layout->addWidget(diff_title);

  difficulty_label_ = new QLabel("LOW");
  difficulty_label_->setStyleSheet(
      "font-size: 16px; font-weight: 900; color: #00ffcc; border: none; font-family: monospace;");
  diff_layout->addWidget(difficulty_label_);
  sidebar_layout->addWidget(diff_card);

  // Separator
  QFrame* separator = new QFrame();
  separator->setFrameShape(QFrame::HLine);
  separator->setStyleSheet("color: #27272a; border: none; max-height: 1px; "
                           "background: #27272a;");
  sidebar_layout->addWidget(separator);

  // Exercise label
  QLabel* exercises_label = new QLabel("MODULES");
  exercises_label->setStyleSheet(
      "font-size: 12px; font-weight: 900; color: #52525b; "
      "letter-spacing: 2px; padding-top: 4px; border: none; font-family: monospace;");
  sidebar_layout->addWidget(exercises_label);

  // Translation button
  QPushButton* translation_btn = new QPushButton(">> DECRYPT");
  translation_btn->setFixedHeight(48);
  translation_btn->setCursor(Qt::PointingHandCursor);
  translation_btn->setStyleSheet(
      "QPushButton { background: #09090b; color: #e4e4e7; border: 1px solid #27272a; "
      "border-radius: 4px; font-size: 14px; font-weight: bold; font-family: monospace; "
      "text-align: left; padding-left: 14px; }"
      "QPushButton:hover { background: #18181b; border-color: #00ffcc; color: #00ffcc; }"
      "QPushButton:pressed { background: #27272a; }");
  sidebar_layout->addWidget(translation_btn);

  // Grammar button
  QPushButton* grammar_btn = new QPushButton(">> SYNTAX");
  grammar_btn->setFixedHeight(48);
  grammar_btn->setCursor(Qt::PointingHandCursor);
  grammar_btn->setStyleSheet(
      "QPushButton { background: #09090b; color: #e4e4e7; border: 1px solid #27272a; "
      "border-radius: 4px; font-size: 14px; font-weight: bold; font-family: monospace; "
      "text-align: left; padding-left: 14px; }"
      "QPushButton:hover { background: #18181b; border-color: #ff00ff; color: #ff00ff; }"
      "QPushButton:pressed { background: #27272a; }");
  sidebar_layout->addWidget(grammar_btn);

  sidebar_layout->addStretch();

  // Help hint
  QLabel* help_hint = new QLabel("[H] FOR OVERRIDE");
  help_hint->setStyleSheet(
      "font-size: 10px; font-weight: bold; color: #3f3f46; border: none; font-family: monospace;");
  help_hint->setAlignment(Qt::AlignCenter);
  sidebar_layout->addWidget(help_hint);

  // ── Left content area (stacked widget) ──
  stack_ = new QStackedWidget();
  stack_->setStyleSheet("background: #000000; border: none;");

  // Welcome page
  welcome_page_ = new QWidget();
  QVBoxLayout* welcome_layout = new QVBoxLayout(welcome_page_);
  welcome_layout->setAlignment(Qt::AlignCenter);

  QLabel* welcome_emoji = new QLabel("///");
  welcome_emoji->setStyleSheet("font-size: 80px; font-weight: 900; color: #00ffcc; border: none; font-family: monospace;");
  welcome_emoji->setAlignment(Qt::AlignCenter);
  welcome_layout->addWidget(welcome_emoji);

  QLabel* welcome_title = new QLabel("SYSTEM_READY");
  welcome_title->setStyleSheet(
      "font-size: 32px; font-weight: 900; color: #e4e4e7; border: none; font-family: monospace;");
  welcome_title->setAlignment(Qt::AlignCenter);
  welcome_layout->addWidget(welcome_title);

  QLabel* welcome_sub = new QLabel(
      "Establish connection via language modules.\n"
      "Select >> DECRYPT or >> SYNTAX from the panel.");
  welcome_sub->setStyleSheet(
      "font-size: 16px; font-weight: normal; color: #a1a1aa; border: none; font-family: monospace;");
  welcome_sub->setAlignment(Qt::AlignCenter);
  welcome_sub->setWordWrap(true);
  welcome_layout->addWidget(welcome_sub);

  QLabel* welcome_hint = new QLabel(
      "\n> Adjust THREAT LEVEL via SYSTEM menu.\n"
      "> Use override key [H] for tactical assistance.");
  welcome_hint->setStyleSheet(
      "font-size: 12px; font-weight: normal; color: #52525b; border: none; font-family: monospace;");
  welcome_hint->setAlignment(Qt::AlignCenter);
  welcome_hint->setWordWrap(true);
  welcome_layout->addWidget(welcome_hint);

  stack_->addWidget(welcome_page_);       // index 0
  translation_widget_ = new TranslationWidget();
  stack_->addWidget(translation_widget_); // index 1
  grammar_widget_ = new GrammarWidget();
  stack_->addWidget(grammar_widget_);     // index 2

  main_layout->addWidget(stack_, 1);
  main_layout->addWidget(sidebar);

  // ── Connections ──
  connect(translation_btn, &QPushButton::clicked, this,
          &MainWindow::OnTranslationClicked);
  connect(grammar_btn, &QPushButton::clicked, this,
          &MainWindow::OnGrammarClicked);
  connect(translation_widget_, &TranslationWidget::ExerciseFinished, this,
          &MainWindow::OnExerciseFinished);
  connect(grammar_widget_, &GrammarWidget::ExerciseFinished, this,
          &MainWindow::OnExerciseFinished);

  // Global stylesheet
  central->setStyleSheet("background: #000000; color: #e4e4e7;");
}

void MainWindow::SetupMenuBar() {
  QMenuBar* menu_bar = menuBar();
  menu_bar->setStyleSheet(
      "QMenuBar { background: #09090b; color: #a1a1aa; font-size: 12px; font-family: monospace; "
      "border-bottom: 1px solid #27272a; }"
      "QMenuBar::item { padding: 6px 14px; }"
      "QMenuBar::item:selected { background: #18181b; color: #e4e4e7; }"
      "QMenu { background: #09090b; color: #a1a1aa; border: 1px solid #27272a; font-family: monospace; }"
      "QMenu::item { padding: 6px 24px; }"
      "QMenu::item:selected { background: #18181b; color: #e4e4e7; }");

  // File menu
  QMenu* file_menu = menu_bar->addMenu("&File");
  QAction* exit_action = file_menu->addAction("Exit");
  exit_action->setShortcut(QKeySequence("Ctrl+Q"));
  connect(exit_action, &QAction::triggered, this, &QWidget::close);

  // Settings menu
  QMenu* settings_menu = menu_bar->addMenu("&Settings");
  QAction* difficulty_action = settings_menu->addAction("Difficulty...");
  connect(difficulty_action, &QAction::triggered, this,
          &MainWindow::OnDifficultyAction);
}

void MainWindow::UpdateScoreDisplay() {
  score_label_->setText(QString::number(total_score_));
}

void MainWindow::OnTranslationClicked() {
  grammar_widget_->StopExercise();
  stack_->setCurrentIndex(Page::Translation);
  translation_widget_->StartExercise(difficulty_);
}

void MainWindow::OnGrammarClicked() {
  translation_widget_->StopExercise();
  stack_->setCurrentIndex(Page::Grammar);
  grammar_widget_->StartExercise(difficulty_);
}

void MainWindow::OnDifficultyAction() {
  DifficultyDialog dialog(difficulty_, this);
  if (dialog.exec() == QDialog::Accepted) {
    difficulty_ = dialog.GetSelectedDifficulty();
    switch (difficulty_) {
      case Difficulty::Easy:
        difficulty_label_->setText("LOW");
        difficulty_label_->setStyleSheet(
            "font-size: 16px; font-weight: 900; color: #00ffcc; "
            "border: none; font-family: monospace;");
        break;
      case Difficulty::Medium:
        difficulty_label_->setText("MODERATE");
        difficulty_label_->setStyleSheet(
            "font-size: 16px; font-weight: 900; color: #ffaa00; "
            "border: none; font-family: monospace;");
        break;
      case Difficulty::Hard:
        difficulty_label_->setText("CRITICAL");
        difficulty_label_->setStyleSheet(
            "font-size: 16px; font-weight: 900; color: #ff00ff; "
            "border: none; font-family: monospace;");
        break;
    }
  }
}

void MainWindow::OnExerciseFinished(int points) {
  total_score_ += points;
  UpdateScoreDisplay();
}

void MainWindow::keyPressEvent(QKeyEvent* event) {
  if (event->key() == Qt::Key_H) {
    QString hint;
    int current_page = stack_->currentIndex();

    if (current_page == Page::Translation) {
      hint = translation_widget_->GetCurrentHint();
    } else if (current_page == Page::Grammar) {
      hint = grammar_widget_->GetCurrentHint();
    } else {
      hint = "Start an exercise first to get hints!";
    }

    QMessageBox hint_box(this);
    hint_box.setWindowTitle("💡 Hint");
    hint_box.setText(hint);
    hint_box.setIcon(QMessageBox::Information);
    hint_box.setStyleSheet(
        "QMessageBox { background: #1e1e2e; }"
        "QMessageBox QLabel { color: #cdd6f4; font-size: 14px; }"
        "QPushButton { background: #89b4fa; color: #1e1e2e; border: none; "
        "border-radius: 6px; padding: 6px 18px; font-weight: bold; }"
        "QPushButton:hover { background: #74c7ec; }");
    hint_box.exec();
    return;
  }
  QMainWindow::keyPressEvent(event);
}
