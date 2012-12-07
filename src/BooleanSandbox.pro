RC_FILE = BooleanSandbox.rc

SOURCES += \
    main.cpp \
    _Configuration.cpp

HEADERS += \
    AEventFilter.h \
    AGraphicsController.h \
    AGraphicsSandbox.h \
    AInteractiveScene.h \
    BooleanController.h \
    BooleanEventFilter.h \
    BooleanSandbox.h \
    AbsComponent.h \
    AbsComponentElectronic.h \
    AbsPin.h \
    AbsComponentToggleable.h \
    AbsComponentToggleableManual.h \
    AbsComponentToggleableManualEF.h \
    AbsWire.h \
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
    _Configuration.h \
    AbsComponentController.h \
    AbsComponentSandbox.h

QT += xml

RESOURCES += \
    resources.qrc

FORMS += \
    WindowMain.ui \
    WindowAbout.ui

TRANSLATIONS += \
    BooleanSandbox_ru.ts \
    BooleanSandbox_en.ts \
    BooleanSandbox_de.ts \
    BooleanSandbox_fr.ts

