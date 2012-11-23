RC_FILE = BooleanSandbox.rc

SOURCES += \
    main.cpp \
    _Configuration.cpp

HEADERS += \
    AbsComponent.h \
    AbsComponentElectronic.h \
    AbsPin.h \
    AbsComponentToggleable.h \
    AbsComponentToggleableManual.h \
    AbsComponentToggleableManualEF.h \
    AbsPinsConnector.h \
    AbsWire.h \
    LogicTautology.h \
    LogicSplitter.h \
    LogicSource.h \
    LogicNegation.h \
    LogicIndicator.h \
    LogicImplication.h \
    LogicDisjunction.h \
    LogicConjunction.h \
    LogicBiconditional.h \
    LogicPin.h \
    AbsPathFinder.h \
    AbsGrid.h \
    AbsSceneDependentObject.h \
    _WindowMain.h \
    _WindowAbout.h \
    _Configuration.h

QT += xml

RESOURCES += \
    resources.qrc

FORMS += \
    GameWindow.ui \
    AboutWindow.ui

TRANSLATIONS += \
    BooleanSandbox_ru.ts \
    BooleanSandbox_en.ts \
    BooleanSandbox_de.ts \
    BooleanSandbox_fr.ts

