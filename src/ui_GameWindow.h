/********************************************************************************
** Form generated from reading UI file 'GameWindow.ui'
**
** Created: Sun 25. Nov 00:09:16 2012
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GAMEWINDOW_H
#define UI_GAMEWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGraphicsView>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GameWindow
{
public:
    QAction *addLogicConjunction;
    QAction *addLogicDisjunction;
    QAction *addLogicNegation;
    QAction *addLogicSourceToggleable;
    QAction *addLogicIndicator;
    QAction *addLogicImplication;
    QAction *addLogicBiconditional;
    QAction *setLanguageEn;
    QAction *setLanguageRu;
    QAction *setLanguageFr;
    QAction *setLanguageDe;
    QAction *informationAbout;
    QAction *actionHelp;
    QAction *addLogicSplitterDouble;
    QAction *addLogicSplitterTripple;
    QAction *addLogicTautology;
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QGraphicsView *graphicsView;
    QMenuBar *menubar;
    QMenu *menuLogical_elements;
    QMenu *menuLogical_sources;
    QMenu *menuLogical_indicators;
    QMenu *menuLanguages;
    QMenu *menuLanguages_2;
    QMenu *infoAbout;

    void setupUi(QMainWindow *GameWindow)
    {
        if (GameWindow->objectName().isEmpty())
            GameWindow->setObjectName(QString::fromUtf8("GameWindow"));
        GameWindow->resize(640, 501);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(GameWindow->sizePolicy().hasHeightForWidth());
        GameWindow->setSizePolicy(sizePolicy);
        GameWindow->setMinimumSize(QSize(0, 0));
        GameWindow->setMaximumSize(QSize(16777215, 16777215));
        GameWindow->setSizeIncrement(QSize(10, 10));
        GameWindow->setBaseSize(QSize(640, 501));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/resources/images/icons/MainWindow.png"), QSize(), QIcon::Normal, QIcon::Off);
        GameWindow->setWindowIcon(icon);
        GameWindow->setLayoutDirection(Qt::LeftToRight);
        GameWindow->setStyleSheet(QString::fromUtf8(""));
        GameWindow->setIconSize(QSize(32, 32));
        addLogicConjunction = new QAction(GameWindow);
        addLogicConjunction->setObjectName(QString::fromUtf8("addLogicConjunction"));
        addLogicDisjunction = new QAction(GameWindow);
        addLogicDisjunction->setObjectName(QString::fromUtf8("addLogicDisjunction"));
        addLogicNegation = new QAction(GameWindow);
        addLogicNegation->setObjectName(QString::fromUtf8("addLogicNegation"));
        addLogicSourceToggleable = new QAction(GameWindow);
        addLogicSourceToggleable->setObjectName(QString::fromUtf8("addLogicSourceToggleable"));
        addLogicIndicator = new QAction(GameWindow);
        addLogicIndicator->setObjectName(QString::fromUtf8("addLogicIndicator"));
        addLogicImplication = new QAction(GameWindow);
        addLogicImplication->setObjectName(QString::fromUtf8("addLogicImplication"));
        addLogicBiconditional = new QAction(GameWindow);
        addLogicBiconditional->setObjectName(QString::fromUtf8("addLogicBiconditional"));
        setLanguageEn = new QAction(GameWindow);
        setLanguageEn->setObjectName(QString::fromUtf8("setLanguageEn"));
        setLanguageRu = new QAction(GameWindow);
        setLanguageRu->setObjectName(QString::fromUtf8("setLanguageRu"));
        setLanguageFr = new QAction(GameWindow);
        setLanguageFr->setObjectName(QString::fromUtf8("setLanguageFr"));
        setLanguageDe = new QAction(GameWindow);
        setLanguageDe->setObjectName(QString::fromUtf8("setLanguageDe"));
        informationAbout = new QAction(GameWindow);
        informationAbout->setObjectName(QString::fromUtf8("informationAbout"));
        actionHelp = new QAction(GameWindow);
        actionHelp->setObjectName(QString::fromUtf8("actionHelp"));
        actionHelp->setEnabled(true);
        addLogicSplitterDouble = new QAction(GameWindow);
        addLogicSplitterDouble->setObjectName(QString::fromUtf8("addLogicSplitterDouble"));
        addLogicSplitterTripple = new QAction(GameWindow);
        addLogicSplitterTripple->setObjectName(QString::fromUtf8("addLogicSplitterTripple"));
        addLogicTautology = new QAction(GameWindow);
        addLogicTautology->setObjectName(QString::fromUtf8("addLogicTautology"));
        centralwidget = new QWidget(GameWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(centralwidget->sizePolicy().hasHeightForWidth());
        centralwidget->setSizePolicy(sizePolicy1);
        centralwidget->setMinimumSize(QSize(645, 480));
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        graphicsView = new QGraphicsView(centralwidget);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
        sizePolicy.setHeightForWidth(graphicsView->sizePolicy().hasHeightForWidth());
        graphicsView->setSizePolicy(sizePolicy);
        graphicsView->setMaximumSize(QSize(16777215, 16777215));
        graphicsView->setStyleSheet(QString::fromUtf8(""));
        graphicsView->setFrameShape(QFrame::NoFrame);
        graphicsView->setFrameShadow(QFrame::Plain);
        graphicsView->setLineWidth(0);
        graphicsView->setInteractive(true);
        graphicsView->setSceneRect(QRectF(0, 0, 0, 0));
        graphicsView->setRenderHints(QPainter::Antialiasing);

        horizontalLayout->addWidget(graphicsView);

        GameWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(GameWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 640, 21));
        menubar->setDefaultUp(false);
        menubar->setNativeMenuBar(true);
        menuLogical_elements = new QMenu(menubar);
        menuLogical_elements->setObjectName(QString::fromUtf8("menuLogical_elements"));
        menuLogical_sources = new QMenu(menubar);
        menuLogical_sources->setObjectName(QString::fromUtf8("menuLogical_sources"));
        menuLogical_indicators = new QMenu(menubar);
        menuLogical_indicators->setObjectName(QString::fromUtf8("menuLogical_indicators"));
        menuLanguages = new QMenu(menubar);
        menuLanguages->setObjectName(QString::fromUtf8("menuLanguages"));
        menuLanguages_2 = new QMenu(menuLanguages);
        menuLanguages_2->setObjectName(QString::fromUtf8("menuLanguages_2"));
        infoAbout = new QMenu(menubar);
        infoAbout->setObjectName(QString::fromUtf8("infoAbout"));
        GameWindow->setMenuBar(menubar);

        menubar->addAction(menuLogical_sources->menuAction());
        menubar->addAction(menuLogical_elements->menuAction());
        menubar->addAction(menuLogical_indicators->menuAction());
        menubar->addAction(menuLanguages->menuAction());
        menubar->addAction(infoAbout->menuAction());
        menuLogical_elements->addAction(addLogicNegation);
        menuLogical_elements->addAction(addLogicTautology);
        menuLogical_elements->addAction(addLogicSplitterDouble);
        menuLogical_elements->addAction(addLogicSplitterTripple);
        menuLogical_elements->addSeparator();
        menuLogical_elements->addAction(addLogicConjunction);
        menuLogical_elements->addAction(addLogicDisjunction);
        menuLogical_elements->addAction(addLogicImplication);
        menuLogical_elements->addAction(addLogicBiconditional);
        menuLogical_sources->addAction(addLogicSourceToggleable);
        menuLogical_indicators->addAction(addLogicIndicator);
        menuLanguages->addAction(menuLanguages_2->menuAction());
        menuLanguages_2->addAction(setLanguageRu);
        menuLanguages_2->addAction(setLanguageEn);
        menuLanguages_2->addAction(setLanguageDe);
        menuLanguages_2->addAction(setLanguageFr);
        infoAbout->addAction(informationAbout);

        retranslateUi(GameWindow);

        QMetaObject::connectSlotsByName(GameWindow);
    } // setupUi

    void retranslateUi(QMainWindow *GameWindow)
    {
        GameWindow->setWindowTitle(QApplication::translate("GameWindow", "Boolean sandbox", 0, QApplication::UnicodeUTF8));
        addLogicConjunction->setText(QApplication::translate("GameWindow", "Conjunction", 0, QApplication::UnicodeUTF8));
        addLogicDisjunction->setText(QApplication::translate("GameWindow", "Disjunction", 0, QApplication::UnicodeUTF8));
        addLogicNegation->setText(QApplication::translate("GameWindow", "Negation", 0, QApplication::UnicodeUTF8));
        addLogicSourceToggleable->setText(QApplication::translate("GameWindow", "Toggleable source", 0, QApplication::UnicodeUTF8));
        addLogicIndicator->setText(QApplication::translate("GameWindow", "Indicator", 0, QApplication::UnicodeUTF8));
        addLogicImplication->setText(QApplication::translate("GameWindow", "Implication", 0, QApplication::UnicodeUTF8));
        addLogicBiconditional->setText(QApplication::translate("GameWindow", "Biconditional", 0, QApplication::UnicodeUTF8));
        setLanguageEn->setText(QApplication::translate("GameWindow", "English", 0, QApplication::UnicodeUTF8));
        setLanguageRu->setText(QApplication::translate("GameWindow", "\320\240\321\203\321\201\321\201\320\272\320\270\320\271", 0, QApplication::UnicodeUTF8));
        setLanguageFr->setText(QApplication::translate("GameWindow", "Fran\303\247ais", 0, QApplication::UnicodeUTF8));
        setLanguageDe->setText(QApplication::translate("GameWindow", "Deutsch", 0, QApplication::UnicodeUTF8));
        informationAbout->setText(QApplication::translate("GameWindow", "About", 0, QApplication::UnicodeUTF8));
        actionHelp->setText(QApplication::translate("GameWindow", "Help", 0, QApplication::UnicodeUTF8));
        addLogicSplitterDouble->setText(QApplication::translate("GameWindow", "Tautology x2", 0, QApplication::UnicodeUTF8));
        addLogicSplitterTripple->setText(QApplication::translate("GameWindow", "Tautology x3", 0, QApplication::UnicodeUTF8));
        addLogicTautology->setText(QApplication::translate("GameWindow", "Tautology", 0, QApplication::UnicodeUTF8));
        menuLogical_elements->setTitle(QApplication::translate("GameWindow", "Logic gates", 0, QApplication::UnicodeUTF8));
        menuLogical_sources->setTitle(QApplication::translate("GameWindow", "Logic source", 0, QApplication::UnicodeUTF8));
        menuLogical_indicators->setTitle(QApplication::translate("GameWindow", "Logic indicators", 0, QApplication::UnicodeUTF8));
        menuLanguages->setTitle(QApplication::translate("GameWindow", "Settings", 0, QApplication::UnicodeUTF8));
        menuLanguages_2->setTitle(QApplication::translate("GameWindow", "Language", 0, QApplication::UnicodeUTF8));
        infoAbout->setTitle(QApplication::translate("GameWindow", "Information", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class GameWindow: public Ui_GameWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAMEWINDOW_H
