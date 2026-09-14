QT += widgets multimedia sql pdf printsupport

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    BrushOwnColorWindow.cpp \
    CircuitOwnColorWindow.cpp \
    CommonSettingsMenu.cpp \
    ConfigureColorWindow.cpp \
    ConfigureFontWindow.cpp \
    CreateInFormatWindow.cpp \
    CustomShapeItem.cpp \
    FilesActionsMenu.cpp \
    GraphicsActionLists.cpp \
    GridScene.cpp \
    ObjectSettings.cpp \
    ObjectSettingsLists.cpp \
    OpenFileWindow.cpp \
    OwnGridSizeWindow.cpp \
    OwnTextPixel.cpp \
    PdfActionsWindow.cpp \
    ReferenceMenu.cpp \
    SaveInFileWindow.cpp \
    TextObject.cpp \
    ViewWindowMenu.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    BrushOwnColorWindow.h \
    CircuitOwnColorWindow.h \
    CommonSettingsMenu.h \
    ConfigureColorWindow.h \
    ConfigureFontWindow.h \
    CreateInFormatWindow.h \
    CustomShapeItem.h \
    FilesActionsMenu.h \
    GraphicsActionLists.h \
    GridScene.h \
    ObjectSettings.h \
    ObjectSettingsLists.h \
    OpenFileWindow.h \
    OwnGridSizeWindow.h \
    OwnTextPixel.h \
    PdfActionsWindow.h \
    ReferenceMenu.h \
    SaveInFileWindow.h \
    ShapeType.h \
    TextObject.h \
    ViewWindowMenu.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
