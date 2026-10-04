#ifndef APPLICATIONWINDOW_H
#define APPLICATIONWINDOW_H
#include <QApplication>
#include <QMainWindow>
#include <QStyleFactory>
#include <QDesktopServices>
#include <QStandardPaths>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QShortcut>
#include <QMenu>
#include <QAction>
#include <QToolBar>
#include <QToolButton>
#include <QStatusBar>
#include <QLineEdit>
#include <QCompleter>
#include <QMessageBox>
#include <QComboBox>
#include <QSettings>
#include <QRandomGenerator>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QUrl>

#include "include/Graphics/GridScene.h"
#include "include/Menu/CommonSettingsMenu.h"
#include "include/Menu/FilesActionsMenu.h"
#include "include/Dialogs/PdfActionsWindow.h"
#include "include/Menu/ScaleMenu.h"
#include "include/Menu/AccessibilityMenu.h"
#include "include/Menu/ReferenceMenu.h"
#include "include/Dialogs/ConfigureGraphicsColorWindow.h"
#include "include/Dialogs/ConfigureFontWindow.h"
#include "include/Dialogs/CircuitOwnColorWindow.h"
#include "include/Dialogs/BrushOwnColorWindow.h"
#include "include/Settings/ObjectSettings.h"
#include "include/Settings/ObjectSettingsLists.h"
#include "include/Buttons/GraphicsButtonLists.h"
#include "include/Graphics/CustomShapeItem.h"
#include "include/Graphics/ShapeType.h"
#include "include/Graphics/TextObject.h"
#include "include/Dialogs/CreateInFormatWindow.h"
#include "include/Dialogs/OpenFileWindow.h"
#include "include/Dialogs/SaveInFileWindow.h"
#include "include/Menu/InstrumentsMenu.h"
#include "include/Styles/StyleLineCircuitLists.h"
#include "include/Styles/StyleEdgeCircuitLists.h"
#include "include/Styles/StyleJoinCircuitLists.h"
#include "include/Styles/StyleBrushLists.h"
#include "include/Buttons/OrderObjectButtons.h"
#include "include/Search/CollectAllActions.h"
#include "include/Settings/WindowThemeManager.h"


class QStatusBar;
class QToolBar;
class QLineEdit;
class QCompleter;
class QComboBox;
class QPushButton;
class QGraphicsView;
class QWidget;

class GridScene;
class CustomShapeItem;
class CommonSettingsMenu;
class FilesActionsMenu;
class ScaleMenu;
class InstrumentsMenu;
class ReferenceMenu;
class AccessibilityMenu;
class ObjectSettings;
class ObjectSettingsLists;
class GraphicsButtonLists;
class OrderObjectButtons;

class ApplicationWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit ApplicationWindow(QWidget* parent = nullptr);
    ~ApplicationWindow();

private slots:
    void onSearchActivated(const QString& name);
    void onObjectChanged(const QString& text);
    void onCircuitChanged(const QString& text);
    void onBrushChanged(const QString& text);
    void onColorWindowChanged(const QString& text);
    void onTextFontChanged(const QString& text);
    void onAddFigure();
    void onRemoveAllFigures();
    void onRemoveFigure();
    void onEndDrawing();
    void saveSettings();
private:
    void setupUi();
    void setupToolBar();
    void setupMenus();
    void setupGraphicsScene();
    void setupObjectSettings();
    void setupButtons();
    void setupOrderButtons();
    void setupSearch();
    void setupConnections();
    void setupAccessibilityMenu();
    void setupFilesMenu();
    void setupPdfMenu();
    void setupScaleMenu();
    void setupInstrumentsMenu();
    void setupCommonSettingsMenu();
    void setupReferenceMenu();
    bool isRunningInContainer() const;

    QWidget* centralWidget = nullptr;
    QToolBar* toolBar = nullptr;
    QStatusBar* status = nullptr;
    QLineEdit* searchField = nullptr;
    QCompleter* completer  = nullptr;

    QComboBox* configureObjectComboBox = nullptr;
    QComboBox* configureCircuitComboBox = nullptr;
    QComboBox* configureBrushComboBox  = nullptr;
    QComboBox* configureColorWindowComboBox = nullptr;
    QComboBox* configureTextFontComboBox = nullptr;

    QPushButton* addFigureButton = nullptr;
    QPushButton* removeButton = nullptr;
    QPushButton* removeAllFiguresButton = nullptr;
    QPushButton* endDrawingButton = nullptr;

    QGraphicsView*   graphicsView = nullptr;
    GridScene*       scene        = nullptr;
    CustomShapeItem* prototypeItem = nullptr;

    CommonSettingsMenu* csm = nullptr;
    FilesActionsMenu* fam = nullptr;
    ScaleMenu* sm  = nullptr;
    InstrumentsMenu* im  = nullptr;
    ReferenceMenu* rm  = nullptr;
    AccessibilityMenu* am  = nullptr;
    ObjectSettings* os  = nullptr;
    ObjectSettingsLists* osl = nullptr;
    GraphicsButtonLists* gbl = nullptr;
    OrderObjectButtons* oob = nullptr;

    QString objectName;
    QString circuitName;
    QString brushName;
    QString colorWindowName;
    QString textFontName;
    QString graphicsBackgroundColor;
    QString background_color;
    QString foreground_color;
    QString default_foreground_object_color;

    QFont original_font;
    QFont current_font;

    int font_size = 10;
    bool sound_enabled = true;
};

#endif // APPLICATIONWINDOW_H