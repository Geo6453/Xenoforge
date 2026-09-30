/*#include "mainwindow.h"
#include "jsonmanager.h"
#include "clickablelabel.h"
#include "settingsdialog.h"
#include <QFileDialog>
#include <QTabWidget>
#include <QGroupBox>

SettingsDialog::SettingsDialog(JsonManager& jsonManager, QWidget *parent)
    : QDialog(parent), m_jsonManager(jsonManager)
{
    setWindowTitle(tr("Repository Settings"));
    resize(1000, 600);

    QTabWidget *tabWidget = new QTabWidget(this);

        QWidget *nspTab = new QWidget();

    QHBoxLayout *mainLayout = new QHBoxLayout(nspTab);

    QWidget *leftWidget = new QWidget(this);
    QGridLayout *imageLayout = new QGridLayout(leftWidget);

    QWidget *rightWidget = new QWidget(this);
    QGridLayout *repoLayout = new QGridLayout(rightWidget);

    mainLayout->addWidget(leftWidget);
    mainLayout->addWidget(rightWidget);

    mainLayout->setStretch(0, 3); // leftWidget take 30% space
    mainLayout->setStretch(1, 7); // rightWidget take 70% space

//Structure du QDialog
    // QTabWidget
        // NSP/XCI files
            // QGroupBox
                // Main game
                // Updates
                // DLC
        // Extracted romFS
            // QGroupBox
                // Main game
                // Updates
                // DLC
        // Extracted ARD/ARH
            // QGroupBox
                // Main game
                // Updates
                // DLC


    QLabel *XC1_logo_test = new QLabel(this);
    configureImageLabel(XC1_logo_test, ":/logos/XC1_logo.png");
    imageLayout->addWidget(XC1_logo_test, 0, 0, 1, 2);

    QLabel *XC1_DE_logo_test = new QLabel(this);
    configureImageLabel(XC1_DE_logo_test, ":/logos/XC1_icon.png");
    imageLayout->addWidget(XC1_DE_logo_test, 1, 0);

    QLabel *XCX_logo_test = new QLabel(this);
    configureImageLabel(XCX_logo_test, ":/logos/XC1_DE_icon.png");
    imageLayout->addWidget(XCX_logo_test, 1, 1);


    repoLayout->addWidget(new QLabel("Xenoblade 3 Main Game :", this), 0, 0);
        QLineEdit *editMainXC3 = new QLineEdit(this);
        editMainXC3->setPlaceholderText("Select a folder...");
        editMainXC3->setReadOnly(true);
        editMainXC3->setText(m_jsonManager.loadPath("XC3_Main_path"));
        repoLayout->addWidget(editMainXC3, 0, 1);

        QPushButton *browseMainXC3 = new QPushButton("...", this);
        browseMainXC3->setFixedWidth(30);
        connect(browseMainXC3, &QPushButton::clicked, this, [this, editMainXC3]()
        {
            QString dir = QFileDialog::getExistingDirectory(this, "Select folder", QDir::homePath());
            if (!dir.isEmpty()) {editMainXC3->setText(dir); m_jsonManager.savePath("XC3_Main_path", dir);}
        });
        repoLayout->addWidget(browseMainXC3, 0, 2);

    repoLayout->addWidget(new QLabel("Updates:", this), 1, 0);
        QLineEdit *editUpdatesXC3 = new QLineEdit(this);
        editUpdatesXC3->setPlaceholderText("Select a folder...");
        editUpdatesXC3->setReadOnly(true);
        editUpdatesXC3->setText(m_jsonManager.loadPath("XC3_Updates_path"));
        repoLayout->addWidget(editUpdatesXC3, 1, 1);

        QPushButton *browseUpdatesXC3 = new QPushButton("...", this);
        browseUpdatesXC3->setFixedWidth(30);
        connect(browseUpdatesXC3, &QPushButton::clicked, this, [this, editUpdatesXC3]()
        {
            QString dir = QFileDialog::getExistingDirectory(this, "Select folder", QDir::homePath());
            if (!dir.isEmpty()) {editUpdatesXC3->setText(dir); m_jsonManager.savePath("XC3_Updates_path", dir);}
        });
        repoLayout->addWidget(browseUpdatesXC3, 1, 2);

    repoLayout->addWidget(new QLabel("DLCs:", this), 2, 0);
        QLineEdit *editDlcsXC3 = new QLineEdit(this);
        editDlcsXC3->setPlaceholderText("Select a folder...");
        editDlcsXC3->setReadOnly(true);
        editDlcsXC3->setText(m_jsonManager.loadPath("XC3_DLCs_path"));
        repoLayout->addWidget(editDlcsXC3, 2, 1);

        QPushButton *browseDlcsXC3 = new QPushButton("...", this);
        browseDlcsXC3->setFixedWidth(30);
        connect(browseDlcsXC3, &QPushButton::clicked, this, [this, editDlcsXC3]()
        {
            QString dir = QFileDialog::getExistingDirectory(this, "Select folder", QDir::homePath());
            if(!dir.isEmpty()) {editDlcsXC3->setText(dir); m_jsonManager.savePath("XC3_DLCs_path", dir);}
        });
        repoLayout->addWidget(browseDlcsXC3, 2, 2);

    tabWidget->addTab(nspTab, "NSP/XCI Files");
    setLayout(mainLayout);
}*/
#include "settingsdialog.h"
#include <QFileDialog>
#include <QGridLayout>
#include <QTabWidget>
#include <QGroupBox>

SettingsDialog::SettingsDialog(JsonManager& jsonManager, QWidget *parent)
    : QDialog(parent), m_jsonManager(jsonManager)
{
    setWindowTitle(tr("Repository Settings"));
    resize(800, 600);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QTabWidget *tabWidget = new QTabWidget(this);

    // 1. NSP/XCI files tab
    QWidget *nspTab = new QWidget();
    QVBoxLayout *nspLayout = new QVBoxLayout(nspTab);

    QGroupBox *xeno1Group = new QGroupBox("Xenoblade 1 DE", nspTab);
    QGridLayout *xeno1Grid = new QGridLayout(xeno1Group);
        addPathField(xeno1Grid, 0, "Main Game:", "XC1_Main_path");
        addPathField(xeno1Grid, 1, "Updates:", "XC1_Updates_path");
        xeno1Grid->addWidget(new QLabel("    - Latest : 1.1.2"), 2, 0);

        nspLayout->addWidget(xeno1Group);
        nspLayout->addStretch();

    QGroupBox *xeno2Group = new QGroupBox("Xenoblade 2", nspTab);
    QGridLayout *xeno2Grid = new QGridLayout(xeno2Group);
        addPathField(xeno2Grid, 0, "Main Game:", "XC2_Main_path");
        addPathField(xeno2Grid, 1, "Updates:", "XC2_Updates_path");
        xeno2Grid->addWidget(new QLabel("    - Latest : 2.1.0"), 2, 0);
        addPathField(xeno2Grid, 3, "DLCs:", "XC2_DLCs_path");
        xeno2Grid->addWidget(new QLabel("    - Torna"), 4, 0);

        nspLayout->addWidget(xeno2Group);
        nspLayout->addStretch();

    QGroupBox *xeno3Group = new QGroupBox("Xenoblade 3", nspTab);
    QGridLayout *xeno3Grid = new QGridLayout(xeno3Group);
        addPathField(xeno3Grid, 0, "Main Game:", "XC3_Main_path");
        addPathField(xeno3Grid, 1, "Updates:", "XC3_Updates_path");
        xeno3Grid->addWidget(new QLabel("    - Latest : 2.2.1"), 2, 0);
        addPathField(xeno3Grid, 3, "DLCs:", "XC3_DLCs_path");
        xeno3Grid->addWidget(new QLabel("    - Future Redeemed"), 4, 0);

        nspLayout->addWidget(xeno3Group);
        nspLayout->addStretch();

    QGroupBox *xenoXGroup = new QGroupBox("Xenoblade X DE", nspTab);
    QGridLayout *xenoXGrid = new QGridLayout(xenoXGroup);
        addPathField(xenoXGrid, 0, "Main Game:", "XCX_Main_path");
        addPathField(xenoXGrid, 1, "Updates:", "XCX_Updates_path");
        xenoXGrid->addWidget(new QLabel("    - Latest : 1.0.2"), 2, 0);

        nspLayout->addWidget(xenoXGroup);
        nspLayout->addStretch();

    tabWidget->addTab(nspTab, "NSP/XCI Files");

    // 2. Extracted romFS tab
    QWidget *romfsTab = new QWidget();
    QVBoxLayout *romfsLayout = new QVBoxLayout(romfsTab);

    QGroupBox *romfsGroup = new QGroupBox("Extracted romFS", romfsTab);
    QGridLayout *romfsGrid = new QGridLayout(romfsGroup);

    addPathField(romfsGrid, 0, "Main Game:", "XC3_romFS_Main_path");
    addPathField(romfsGrid, 1, "Updates:", "XC3_romFS_Updates_path");
    addPathField(romfsGrid, 2, "DLCs:", "XC3_romFS_DLCs_path");

    romfsLayout->addWidget(romfsGroup);
    romfsLayout->addStretch();
    tabWidget->addTab(romfsTab, "Extracted romFS");

    // 3. Extracted ARD/ARH tab
    QWidget *ardTab = new QWidget();
    QVBoxLayout *ardLayout = new QVBoxLayout(ardTab);

    QGroupBox *ardGroup = new QGroupBox("Extracted ARD/ARH", ardTab);
    QGridLayout *ardGrid = new QGridLayout(ardGroup);

    addPathField(ardGrid, 0, "Main Game:", "XC3_ARD_Main_path");
    addPathField(ardGrid, 1, "Updates:", "XC3_ARD_Updates_path");
    addPathField(ardGrid, 2, "DLCs:", "XC3_ARD_DLCs_path");

    ardLayout->addWidget(ardGroup);
    ardLayout->addStretch();
    tabWidget->addTab(ardTab, "Extracted ARD/ARH");

    mainLayout->addWidget(tabWidget);
}

void SettingsDialog::addPathField(QGridLayout *layout, int row, const QString& labelText, const QString& jsonKey)
{
    QLabel *label = new QLabel(labelText, this);
    QLineEdit *edit = new QLineEdit(this);
    edit->setPlaceholderText("Select a folder...");
    edit->setReadOnly(true);
    edit->setText(m_jsonManager.loadPath(jsonKey));

    QPushButton *button = new QPushButton("...", this);
    button->setFixedWidth(30);
    connect(button, &QPushButton::clicked, this, [=]()
    {
        QString dir = QFileDialog::getExistingDirectory(this, "Select folder", QDir::homePath());
        if (!dir.isEmpty())
        {
            edit->setText(dir);
            m_jsonManager.savePath(jsonKey, dir);
        }
    });

    layout->addWidget(label, row, 0);
    layout->addWidget(edit, row, 1);
    layout->addWidget(button, row, 2);
}
