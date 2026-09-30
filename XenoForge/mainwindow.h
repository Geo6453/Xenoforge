#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "clickablelabel.h"
#include "jsonmanager.h"
#include <QMainWindow>
#include <QAction>
#include <QMenu>
#include <QCheckBox>
#include <QPushButton>
#include <QGridLayout>
#include <QDesktopServices>
#include <QMessageBox>
#include <QApplication>
#include <QMenuBar>
#include <QDockWidget>
#include <QLabel>
#include <QPixmap>
//#include <QString>
#include <QWidget>
#include <Qt>
#include <QStackedLayout>
#include <QLineEdit>
#include <QFileDialog>
#include <QFileSystemModel>
#include <QTreeView>
#include <QHeaderView>

class MainWindow : public QMainWindow
{
    Q_OBJECT

private slots:

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QWidget* getCentralWidget() const {return centralWidget;}
    void saveSettings();

private:
    QMenu *menuFiles;
    QMenu *menuHelp;
    QWidget *centralWidget;
    QStackedLayout *stack;
    JsonManager m_jsonManager;

    QFileSystemModel *modelExplorer;
};
#endif // MAINWINDOW_H
