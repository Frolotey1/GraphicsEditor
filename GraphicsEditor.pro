QT += widgets multimedia sql pdf printsupport

CONFIG += c++17

SOURCES += \
    src/Menu/AccessibilityMenu.cpp \
    ApplicationWindow.cpp \
    src/Search/CollectAllActions.cpp \
    src/Dialogs/ConfigureGraphicsColorWindow.cpp \
    src/Dialogs/PdfActionsWindow.cpp \
    src/GithubWiki/DocumentationGithubInstructionsLists.cpp \
    src/Buttons/GraphicsButtonLists.cpp \
    src/Menu/GridMenu.cpp \
    src/Menu/InstrumentsListStyleBrushMenu.cpp \
    src/Menu/InstrumentsListStyleCircuitMenu.cpp \
    src/Menu/InstrumentsMenu.cpp \
    src/Settings/ObjectSettingsLists.cpp \
    src/Buttons/OrderObjectButtons.cpp \
    src/Dialogs/OwnTextPixelWindow.cpp \
    src/Menu/ScaleMenu.cpp \
    src/Pdf/ScaleSizePdfFileLists.cpp \
    src/Styles/StyleBrushLists.cpp \
    src/Styles/StyleEdgeCircuitLists.cpp \
    src/Styles/StyleJoinCircuitLists.cpp \
    src/Styles/StyleLineCircuitLists.cpp \
    src/Settings/WindowThemeManager.cpp \
    main.cpp \
    mainwindow.cpp \
    src/Dialogs/BrushOwnColorWindow.cpp \
    src/Graphics/TextObject.cpp \
    src/Dialogs/CreateInFormatWindow.cpp \
    src/Dialogs/SaveInFileWindow.cpp \
    src/Dialogs/OpenFileWindow.cpp \
    src/Dialogs/ConfigureFontWindow.cpp \
    src/Menu/FilesActionsMenu.cpp \
    src/Graphics/CustomShapeItem.cpp \
    src/Graphics/GridScene.cpp \
    src/Settings/ObjectSettings.cpp \
    src/Menu/ReferenceMenu.cpp \
    src/Dialogs/CircuitOwnColorWindow.cpp \
    src/Menu/CommonSettingsMenu.cpp

HEADERS += \
    include/Menu/AccessibilityMenu.h \
    ApplicationWindow.h \
    include/Search/CollectAllActions.h \
    include/Dialogs/ConfigureGraphicsColorWindow.h \
    include/GithubWiki/DocumentationGithubInstructionsLists.h \
    include/Buttons/GraphicsButtonLists.h \
    include/Menu/GridMenu.h \
    include/Menu/InstrumentsListStyleBrushMenu.h \
    include/Menu/InstrumentsListStyleCircuitMenu.h \
    include/Menu/InstrumentsMenu.h \
    include/Settings/ObjectSettingsLists.h \
    include/Buttons/OrderObjectButtons.h \
    include/Dialogs/OwnTextPixelWindow.h \
    include/Menu/ScaleMenu.h \
    include/Pdf/ScaleSizePdfFileLists.h \
    include/Styles/StyleBrushLists.h \
    include/Styles/StyleEdgeCircuitLists.h \
    include/Styles/StyleJoinCircuitLists.h \
    include/Styles/StyleLineCircuitLists.h \
    include/Settings/WindowThemeManager.h \
    mainwindow.h \
    include/Dialogs/CircuitOwnColorWindow.h \
    include/Dialogs/ConfigureFontWindow.h \
    include/Dialogs/BrushOwnColorWindow.h \
    include/Menu/FilesActionsMenu.h \
    include/Menu/ReferenceMenu.h \
    include/Dialogs/PdfActionsWindow.h \
    include/Dialogs/SaveInFileWindow.h \
    include/Graphics/ShapeType.h \
    include/Graphics/TextObject.h \
    include/Graphics/GridScene.h \
    include/Graphics/CustomShapeItem.h \
    include/Menu/CommonSettingsMenu.h \
    include/Dialogs/CreateInFormatWindow.h \
    include/Settings/ObjectSettings.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target