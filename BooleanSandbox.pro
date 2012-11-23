RC_FILE = BooleanSandbox.rc

SOURCES += \
    main.cpp

HEADERS += \
    AbsComponent.h \
    AbsComponentElectronic.h \
    AbsPin.h \
    AbsComponentToggleable.h \
    AbsComponentToggleableManual.h \
    AbsComponentToggleableManualEF.h \
    AbsPinsConnector.h \
    _GameConfiguration.h \
    _GameWindow.h \
    AbsWire.h \
    _AboutWindow.h \
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
    AbsSceneDependentObject.h

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

