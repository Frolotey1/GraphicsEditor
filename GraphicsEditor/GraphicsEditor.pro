QT += widgets multimedia sql pdf printsupport

CONFIG += c++17

SOURCES += \
    AccessibilityMenu.cpp \
    CollectAllActions.cpp \
    ConfigureGraphicsColorWindow.cpp \
    DocumentationGithubInstructionsLists.cpp \
    GraphicsButtonLists.cpp \
    GridMenu.cpp \
    InstrumentsListStyleBrushMenu.cpp \
    InstrumentsListStyleCircuitMenu.cpp \
    InstrumentsMenu.cpp \
    ObjectSettingsLists.cpp \
    OrderObjectButtons.cpp \
    ScaleMenu.cpp \
    ScaleSizePdfFileLists.cpp \
    StyleBrushLists.cpp \
    StyleEdgeCircuitLists.cpp \
    StyleJoinCircuitLists.cpp \
    StyleLineCircuitLists.cpp \
    WindowThemeManager.cpp \
    main.cpp \
    mainwindow.cpp \
    BrushOwnColorWindow.cpp \
    TextObject.cpp \
    CreateInFormatWindow.cpp \
    SaveInFileWindow.cpp \
    OpenFileWindow.cpp \
    ConfigureFontWindow.cpp \
    FilesActionsMenu.cpp \
    CustomShapeItem.cpp \
    GridScene.cpp \
    ObjectSettings.cpp \
    OwnTextPixel.cpp \
    PdfActionsWindow.cpp \
    ReferenceMenu.cpp \
    CircuitOwnColorWindow.cpp \
    CommonSettingsMenu.cpp

HEADERS += \
    AccessibilityMenu.h \
    CollectAllActions.h \
    ConfigureGraphicsColorWindow.h \
    DocumentationGithubInstructionsLists.h \
    GraphicsButtonLists.h \
    GridMenu.h \
    InstrumentsListStyleBrushMenu.h \
    InstrumentsListStyleCircuitMenu.h \
    InstrumentsMenu.h \
    ObjectSettingsLists.h \
    OrderObjectButtons.h \
    ScaleMenu.h \
    ScaleSizePdfFileLists.h \
    StyleBrushLists.h \
    StyleEdgeCircuitLists.h \
    StyleJoinCircuitLists.h \
    StyleLineCircuitLists.h \
    WindowThemeManager.h \
    mainwindow.h \
    OwnTextPixel.h \
    CircuitOwnColorWindow.h \
    ConfigureFontWindow.h \
    BrushOwnColorWindow.h \
    FilesActionsMenu.h \
    ReferenceMenu.h \
    PdfActionsWindow.h \
    SaveInFileWindow.h \
    ShapeType.h \
    TextObject.h \
    GridScene.h \
    CustomShapeItem.h \
    CommonSettingsMenu.h \
    CreateInFormatWindow.h \
    ObjectSettings.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target