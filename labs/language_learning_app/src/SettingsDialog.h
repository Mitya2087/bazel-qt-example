#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include <QComboBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>

class SettingsDialog : public QDialog {
    Q_OBJECT

public:
    explicit SettingsDialog(QWidget *parent = nullptr);

    int getDifficulty() const; // 0: Easy, 1: Medium, 2: Hard

private:
    QComboBox *m_comboDifficulty;
    QPushButton *m_btnOk;
    QPushButton *m_btnCancel;
};

#endif // SETTINGSDIALOG_H
