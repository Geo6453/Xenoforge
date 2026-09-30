#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <jsonmanager.h>
#include <clickablelabel.h>
#include <QDialog>
#include <QTabWidget>
#include <QCheckBox>
#include <QComboBox>
#include <QGroupBox>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>

class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsDialog(JsonManager& jsonManager, QWidget *parent = nullptr);
    void addPathField(QGridLayout *layout, int row, const QString& labelText, const QString& jsonKey);
    QWidget* mainWidget() const {return m_mainWidget;}

private:
    JsonManager& m_jsonManager;
    QWidget *m_mainWidget;
};
#endif
