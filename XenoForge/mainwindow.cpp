#include "settingsdialog.h"
#include "clickablelabel.h"
#include "mainwindow.h"
#include <QLabel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    menuFiles(nullptr),
    menuHelp(nullptr),
    centralWidget(new QWidget(this))
{
    setCentralWidget(centralWidget);

    menuFiles = menuBar()->addMenu("&Files");
    QMenu *recentFiles = menuFiles->addMenu("&Recent files");
        recentFiles->addAction("PlaceHolder 1");
        recentFiles->addAction("PlaceHolder 2");
        recentFiles->addAction("PlaceHolder 3");

    QAction *actionRepositories = new QAction("&Repositories", this);
        connect(actionRepositories, &QAction::triggered, this, [this]() {SettingsDialog dialog(m_jsonManager, this); dialog.exec();});
        menuBar()->addAction(actionRepositories);

    menuHelp = menuBar()->addMenu("&Help");
    QAction *actionUpdate = new QAction("&Search Update", this);
        menuHelp->addAction(actionUpdate);
        connect(actionUpdate, &QAction::triggered, this, []() {QDesktopServices::openUrl(QUrl("https://github.com/Geo6453/XenoForge/releases"));});
    QAction *actionRepoGithub = new QAction("&Github Repo", this);
        menuHelp->addAction(actionRepoGithub);
        connect(actionRepoGithub, &QAction::triggered, this, []() {QDesktopServices::openUrl(QUrl("https://github.com/Geo6453/XenoForge"));});
    QAction *actionDiscord = new QAction("&Discord Server", this);
        menuHelp->addAction(actionDiscord);
        connect(actionDiscord, &QAction::triggered, this, []() {QDesktopServices::openUrl(QUrl("https://discord.gg/27Wz4QB"));});
    QAction *actionQt = new QAction("About &Qt", this);
        menuHelp->addAction(actionQt);
        connect(actionQt, &QAction::triggered, this, [this] () {QMessageBox::aboutQt(this);});
    QAction *actionXenoForge = new QAction("About &XenoForge", this);
        menuHelp->addAction(actionXenoForge);
        connect(actionXenoForge, &QAction::triggered, this, []() {QDesktopServices::openUrl(QUrl("https://github.com/Geo6453/XenoForge/main/README.md"));});

    QStackedLayout *stack = new QStackedLayout(centralWidget);

    QWidget *home = new QWidget();
    QGridLayout *gridLayout = new QGridLayout(home);
    home->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

        ClickableLabel *XC1_logo_home = new ClickableLabel(home);
            configureImageLabel(XC1_logo_home, ":/logos/XC1_logo.png");
            gridLayout->addWidget(XC1_logo_home, 1, 0);
            connect(XC1_logo_home, &ClickableLabel::clicked, this, [this, stack]()
                    {stack->setCurrentIndex(0);});

        ClickableLabel *XC1_DE_logo_home = new ClickableLabel(home);
            configureImageLabel(XC1_DE_logo_home, ":/logos/XC1_DE_logo.png");
            gridLayout->addWidget(XC1_DE_logo_home, 1, 1);
            connect(XC1_DE_logo_home, &ClickableLabel::clicked, this, [this, stack]()
                {stack->setCurrentIndex(0);});

        ClickableLabel *XCX_logo_home = new ClickableLabel(home);
            configureImageLabel(XCX_logo_home, ":/logos/XCX_logo.png");
            gridLayout->addWidget(XCX_logo_home, 2, 0);
            connect(XCX_logo_home, &ClickableLabel::clicked, this, [this, stack]()
                {stack->setCurrentIndex(0);});

        ClickableLabel *XCX_DE_logo_home = new ClickableLabel(home);
            configureImageLabel(XCX_DE_logo_home, ":/logos/XCX_DE_logo.png");
            gridLayout->addWidget(XCX_DE_logo_home, 2, 1);
            connect(XCX_DE_logo_home, &ClickableLabel::clicked, this, [this, stack]()
                {stack->setCurrentIndex(0);});

        ClickableLabel *XC2_logo_home = new ClickableLabel(home);
            configureImageLabel(XC2_logo_home, ":/logos/XC2_logo.png");
            gridLayout->addWidget(XC2_logo_home, 3, 0);
            connect(XC2_logo_home, &ClickableLabel::clicked, this, [this, stack]()
                {stack->setCurrentIndex(0);});

        ClickableLabel *XC3_logo_home = new ClickableLabel(home);
            configureImageLabel(XC3_logo_home, ":/logos/XC3_logo.png");
            gridLayout->addWidget(XC3_logo_home, 3, 1);
            connect(XC3_logo_home, &ClickableLabel::clicked, this, [this, stack]()
                {stack->setCurrentIndex(1);});

    stack->addWidget(home);

    QWidget *test = new QWidget();
    QGridLayout *testGridLayout = new QGridLayout(test);
    test->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

        ClickableLabel *XC3_Map = new ClickableLabel(test);
        configureImageLabel(XC3_Map, ":/logos/XC3_Map.jpg");
        testGridLayout->addWidget(XC3_Map, 0, 0);
        connect(XC3_Map, &ClickableLabel::clicked, this, [this, stack]()
                {stack->setCurrentIndex(0);});

        ClickableLabel *XC3_Music = new ClickableLabel(test);
        configureImageLabel(XC3_Music, ":/logos/XC3_Music.jpg");
        testGridLayout->addWidget(XC3_Music, 0, 1);
        connect(XC3_Music, &ClickableLabel::clicked, this, [this, stack]()
                {stack->setCurrentIndex(2);});

    stack->addWidget(test);

// Répliquer la structure d'une page puis la personnaliser au lieu d'en faire manuellement à 100%
    //Exemple : les "6" jeux auront tous une page de gestion des OST

    QWidget *musicXC3 = new QWidget();
    QGridLayout *musicXC3GridLayout = new QGridLayout(musicXC3);
    musicXC3->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

        modelExplorer = new QFileSystemModel(this);
        modelExplorer->setRootPath(QDir::homePath());
            //modelExplorer->setFilter(QDir::Files | QDir::NoDotAndDotDot);

        QTreeView *treeExplorer = new QTreeView();
        treeExplorer->setModel(modelExplorer);
        //treeExplorer->setRootIndex(modelExplorer->index(QDir::homePath()));
        treeExplorer->header()->setSectionResizeMode(QHeaderView::Stretch);
        treeExplorer->setRootIndex(modelExplorer->index(m_jsonManager.loadPath("XC3_ARD_Main_path")));
        musicXC3GridLayout->addWidget(treeExplorer, 0, 0);

    stack->addWidget(musicXC3);

    QWidget *avatarXC3 = new QWidget();
    QGridLayout *avatarXC3GridLayout = new QGridLayout(avatarXC3);
    avatarXC3->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

        QFrame *avatarPlaceHolder = new QFrame();
        avatarXC3GridLayout->addWidget(avatarPlaceHolder, 0, 0, 2, 1);
        avatarPlaceHolder->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);

        QFrame *avatarPlaceHolder1 = new QFrame();
        avatarXC3GridLayout->addWidget(avatarPlaceHolder1, 0, 1);
        avatarPlaceHolder1->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);

        QFrame *avatarPlaceHolder2 = new QFrame();
        avatarXC3GridLayout->addWidget(avatarPlaceHolder2, 0, 2);
        avatarPlaceHolder2->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);

        QFrame *avatarPlaceHolder3 = new QFrame();
        avatarXC3GridLayout->addWidget(avatarPlaceHolder3, 0, 3);
        avatarPlaceHolder3->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);



    stack->addWidget(avatarXC3);

    stack->setCurrentIndex(3); //Index start with 0
    showMaximized();
}

MainWindow::~MainWindow(){}
