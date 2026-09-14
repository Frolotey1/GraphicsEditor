#include "QApplication"
#include "QMainWindow"
#include "QWidget"
#include "QPushButton"
#include "QVBoxLayout"
#include "QHBoxLayout"
#include "QGraphicsView"
#include "QGraphicsScene"
#include "QLabel"
#include "QMenu"
#include "QAction"
#include "QToolBar"
#include "QStatusBar"
#include "QFont"
#include "QMessageBox"
#include "QComboBox"
#include "QSettings"
#include "QRandomGenerator"
#include "GridScene.h"
#include "CommonSettingsMenu.h"
#include "FilesActionsMenu.h"
#include "PdfActionsWindow.h"
#include "ViewWindowMenu.h"
#include "ReferenceMenu.h"
#include "ConfigureColorWindow.h"
#include "ConfigureFontWindow.h"
#include "CircuitOwnColorWindow.h"
#include "BrushOwnColorWindow.h"
#include "ObjectSettings.h"
#include "ObjectSettingsLists.h"
#include "GraphicsActionLists.h"
#include "CustomShapeItem.h"
#include "ShapeType.h"
#include "TextObject.h"
#include "CreateInFormatWindow.h"
#include "OpenFileWindow.h"
#include "SaveInFileWindow.h"
#include "OwnGridSizeWindow.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    QApplication::setOrganizationName("GraphicsApplication");
    QApplication::setApplicationName("GraphicsEditor");

    QSettings settings;

    QString background_color = settings.value("window/background-color", "white").toString();
    QString foreground_color = settings.value("window/text-color", "white").toString();
    int font_size = settings.value("window/font-size", 12).toInt();
    QFont new_font = settings.value("window/font", QApplication::font()).value<QFont>();

    if (font_size > 2) {
        new_font.setPointSize(font_size);
    }

    app.setFont(new_font);

    QFont original_font = QApplication::font();

    QString default_settings = QString("background-color: %1; color: %2;")
                                   .arg(background_color)
                                   .arg(foreground_color);


    QMainWindow window;
    window.setWindowTitle("Графический редактор");
    window.setFixedSize(1000, 800);
    window.setStyleSheet(default_settings);

    QString object_name;
    QString circuit_name;
    QString brush_name;

    QLabel* graphics_field_name = new QLabel();
    graphics_field_name->setText("Графическое окно");
    graphics_field_name->setAlignment(Qt::AlignCenter);

    QString default_foreground_object_color;

    QStatusBar* status = window.statusBar();

    QWidget* central_widget = new QWidget();

    QVBoxLayout* main_layout = new QVBoxLayout(central_widget);
    main_layout->setSpacing(10);

    QToolBar* tool_bar = window.addToolBar("Инструменты");
    tool_bar->setStyleSheet("background-color: black; color: white;");

    CommonSettingsMenu* csm = new CommonSettingsMenu();
    FilesActionsMenu* fam = new FilesActionsMenu();
    ViewWindowMenu* vwm = new ViewWindowMenu();
    ReferenceMenu* rm = new ReferenceMenu();

    QMenu* files_menu = fam->get_menu();
    QMenu* settings_menu = csm->get_menu();
    QMenu* view_menu = vwm->get_menu();
    QMenu* reference_menu = rm->get_menu();

    tool_bar->addAction(files_menu->menuAction());
    tool_bar->addAction(view_menu->menuAction());
    tool_bar->addAction(settings_menu->menuAction());
    tool_bar->addAction(reference_menu->menuAction());

    ObjectSettings* os = new ObjectSettings();
    ObjectSettingsLists* osl = new ObjectSettingsLists();

    QHBoxLayout* groups_layout = new QHBoxLayout(os->get_common_combobox_name());

    QComboBox* object_combobox = os->get_object_combobox();
    QComboBox* circuit_combobox = os->get_circuit_combobox();
    QComboBox* brush_combobox = os->get_brush_combobox();

    QHBoxLayout* object_combobox_layout = new QHBoxLayout(os->get_object_combobox_name());
    QHBoxLayout* circuit_combobox_layout = new QHBoxLayout(os->get_circuit_combobox_name());
    QHBoxLayout* brush_combobox_layout = new QHBoxLayout(os->get_brush_combobox_name());

    object_combobox_layout->addWidget(object_combobox);
    object_combobox_layout->setAlignment(Qt::AlignCenter);

    circuit_combobox_layout->addWidget(circuit_combobox);
    circuit_combobox_layout->setAlignment(Qt::AlignCenter);

    brush_combobox_layout->addWidget(brush_combobox);
    brush_combobox_layout->setAlignment(Qt::AlignCenter);

    groups_layout->addWidget(os->get_object_combobox_name());
    groups_layout->addWidget(os->get_circuit_combobox_name());
    groups_layout->addWidget(os->get_brush_combobox_name());

    GraphicsActionLists* gal = new GraphicsActionLists();

    QHBoxLayout* button_groups_layout = new QHBoxLayout(gal->get_common_button_name());

    QPushButton* add_figure_button = gal->get_figure_button();
    QPushButton* reset_button = gal->get_reset_button();
    QPushButton* reset_all_figures_button = gal->get_reset_all_figures_button();
    QPushButton* end_drawing_button = gal->get_end_drawing_button();

    button_groups_layout->addWidget(add_figure_button);
    button_groups_layout->addWidget(end_drawing_button);
    button_groups_layout->addWidget(reset_button);
    button_groups_layout->addWidget(reset_all_figures_button);

    CustomShapeItem* csi = new CustomShapeItem();
    csi->setFocus();

    GridScene* set_model_scene = new GridScene();
    set_model_scene->setSceneRect(0, 0, 800, 500);
    set_model_scene->addItem(csi);

    QGraphicsView* set_graphics_view = new QGraphicsView(set_model_scene);

    //FileActionsMenu

    QMenu* create_menu = fam->get_create_menu();

    if (create_menu) {
        for (QAction* action : create_menu->actions()) {
            QString type_image = action->text().toLower();

            QObject::connect(action, &QAction::triggered, [&window, status, type_image]() {
                CreateInFormatWindow* cifw = new CreateInFormatWindow(&window, type_image);
                if (cifw->exec() == QDialog::Accepted) {
                    if (cifw->is_created()) {
                        status->showMessage("Файл был успешно создан", 5000);
                    } else {
                        status->showMessage("Не удалось создать файл", 5000);
                    }
                } else {
                    status->showMessage("Действие отменено", 5000);
                }
            });
        }
    }

    QObject::connect(fam->get_open_action(), &QAction::triggered, [&]() {
        OpenFileWindow* ofw = new OpenFileWindow(&window, set_model_scene);

        if (ofw->exec() == QDialog::Accepted) {
            QList<QGraphicsItem*> graphics_items = set_model_scene->items();

            if (graphics_items.size() > 0) {
                for (auto& item : graphics_items) {
                    set_model_scene->removeItem(item);
                    delete item;
                }
            }

            set_model_scene->addItem(ofw->get_pixmap_item());
        }
    });

    QObject::connect(fam->get_save_action(), &QAction::triggered, [&]() {
        SaveInFileWindow* sifw = new SaveInFileWindow(&window, set_model_scene);

        if (sifw->exec() == QDialog::Accepted) {
            if (sifw->is_saved()) {
                status->showMessage("Изображение было успешно сохранено", 5000);
            }
        } else {
            status->showMessage("Действие отменено", 5000);
        }
    });

    QMenu* pdf_menu = fam->get_pdf_menu();

    if (pdf_menu) {
        for (QAction* action : pdf_menu->actions()) {
            QString type_pdf_action = action->text();

            QObject::connect(action, &QAction::triggered, [&window, status, type_pdf_action, set_model_scene]() {
                PDFActionsWindow* paw = new PDFActionsWindow(&window, type_pdf_action, set_model_scene);

                if (paw->exec() == QDialog::Accepted) {
                    if (paw->is_exported()) {
                        status->showMessage("Изображение было успешно экспортировано", 5000);
                    } else if (paw->is_imported()) {
                        QList<QGraphicsItem*> graphics_items = set_model_scene->items();

                        for (auto& item : graphics_items) {
                            set_model_scene->removeItem(item);
                            delete item;
                        }

                        set_model_scene->addItem(paw->get_pixmap_item());
                        status->showMessage("Изображение было успешно импортировано", 5000);
                    } else {
                        status->showMessage("Действие не выполнено", 5000);
                    }
                } else {
                    status->showMessage("Действие отменено", 5000);
                }
            });
        }
    }

    //ViewWindowMenu

    QObject::connect(vwm->get_fullscreen_action(), &QAction::triggered, [&]() {
        window.showFullScreen();
    });
    QObject::connect(vwm->get_normalscreen_action(), &QAction::triggered, [&]() {
        window.showNormal();
    });

    QMenu* scale_scene_menu = vwm->get_scale_scene_menu();

    if (scale_scene_menu) {
        for (QAction* action : scale_scene_menu->actions()) {
            QString configure_scene = action->text();

            QObject::connect(action, &QAction::triggered, [configure_scene, set_graphics_view]() {
                if (configure_scene == "Увеличить") {
                    set_graphics_view->scale(1.2, 1.2);
                } else if (configure_scene == "Уменьшить") {
                    set_graphics_view->scale(1 / 1.2, 1 / 1.2);
                } else {
                    set_graphics_view->resetTransform();
                }
            });
        }
    }

    QMenu* scale_font_menu = vwm->get_scale_font_menu();

    if (scale_font_menu) {
        for (QAction* action : scale_font_menu->actions()) {
            QString configure_font = action->text();
            QObject::connect(action, &QAction::triggered,[&window, configure_font, &new_font, &font_size, original_font,&app]() {
                QFont font = app.font();

                 if (configure_font == "Увеличить") {
                     font_size = font.pointSize() + 2;
                     font.setPointSize(font_size);
                 } else if (configure_font == "Уменьшить") {
                     font_size = font.pointSize() - 2;
                     if (font_size < 2) font_size = 2;
                     font.setPointSize(font_size);
                 } else {
                     font = original_font;
                     font_size = original_font.pointSize();
                 }

                 new_font = font;
                 app.setFont(font);

                 QList<QWidget*> widgets = window.findChildren<QWidget*>();
                 for (QWidget* widget : widgets) {
                     widget->setFont(font);
                 }
                 window.setFont(font);
            });
        }
    }

    QMenu* grid_menu = vwm->get_grid_menu();

    if(grid_menu) {
        for(QAction* action : grid_menu->actions()) {
            QString type_grid_action = action->text();

            QObject::connect(action,&QAction::triggered,[type_grid_action,&window,set_model_scene,status](){
                if(type_grid_action == "Задать свой размер сетки") {
                    OwnGridSizeWindow* ogsw = new OwnGridSizeWindow();

                    if(ogsw->exec() == QDialog::Accepted) {
                        if(ogsw->is_accepted()) {
                            set_model_scene->set_grid_size(ogsw->get_own_grid_size());
                        } else {
                            status->showMessage("Не удалось задать собственный размер для сетки");
                        }
                    }
                } else {
                    bool converted = false;

                    int size = type_grid_action.left(2).toInt(&converted);

                    if(!converted) {
                        status->showMessage("Ошибка считывания размера для сетки");
                        return;
                    }

                    set_model_scene->set_grid_size(size);
                }

                set_model_scene->set_grid_visible(true);
            });
        }
    }
    QObject::connect(vwm->get_reset_grid_action(),&QAction::triggered,[set_model_scene](){
        set_model_scene->set_grid_visible(false);
    });

    // CommonSettingsMenu

    QObject::connect(csm->get_window_action(), &QAction::triggered, [&]() {
        ConfigureColorWindow* ccw = new ConfigureColorWindow();

        if (ccw->exec() == QDialog::Accepted) {
            background_color = ccw->get_background_color();
            foreground_color = ccw->get_foreground_color();

            default_settings = QString("background-color: %1; color: %2;")
                                   .arg(background_color)
                                   .arg(foreground_color);

            default_foreground_object_color = foreground_color;

            QList<QGraphicsItem*> graphics_items = set_model_scene->items();
            for (auto& item : graphics_items) {
                CustomShapeItem* shape_item = dynamic_cast<CustomShapeItem*>(item);
                if (shape_item) {
                    shape_item->set_brush_color(default_foreground_object_color);
                }
            }

            window.setStyleSheet(default_settings);
        }
    });

    QObject::connect(csm->get_font_action(), &QAction::triggered, [&]() {
        ConfigureFontWindow* cfw = new ConfigureFontWindow();

        if (cfw->exec() == QDialog::Accepted) {
            new_font = cfw->get_font();
            font_size = new_font.pointSize();
            app.setFont(new_font);

            QList<QWidget*> widgets = window.findChildren<QWidget*>();
            for (QWidget* widget : widgets) {
                widget->setFont(new_font);
            }
            window.setFont(new_font);
        }
    });

    QObject::connect(csm->get_reset_action(), &QAction::triggered, [&]() {
        background_color = "white";
        foreground_color = "black";

        window.setStyleSheet("background-color: white; color: black;");

        new_font = original_font;
        font_size = original_font.pointSize();
        app.setFont(original_font);

        QList<QWidget*> widgets = window.findChildren<QWidget*>();
        for (QWidget* widget : widgets) {
            widget->setFont(original_font);
        }
        window.setFont(original_font);
    });

    // ReferenceMenu

    QObject::connect(reference_menu->actions().at(0), &QAction::triggered, [&]() {
        QMessageBox::information(&window, "Информация",
                                 "Это приложение было написано на следующем стэке:\n"
                                 "1) Язык программирования: C++17\n"
                                 "2) Qt Framework 6.11.2");
    });

    // ObjectSettingsLists + ObjectSettings

    QObject::connect(object_combobox, &QComboBox::currentIndexChanged, [&]() {
        object_name = osl->get_object(object_combobox->currentIndex());

        if (object_name == "Прямоугольник") csi->set_shape(ShapeType::Rectangle);
        if (object_name == "Линия") csi->set_shape(ShapeType::Line);
        if (object_name == "Эллипс") csi->set_shape(ShapeType::Ellipse);
        if (object_name == "Многоугольник") csi->set_shape(ShapeType::Polygon);

        if (object_name == "Создать свой объект") {
            csi->set_shape(ShapeType::CustomPath);
            csi->start_custom_path();
        }

        if (object_name == "Текст") {
            TextObject* to = new TextObject();
            if (to->exec() == QDialog::Accepted) {
                QString result = to->get_text();

                if (result.isEmpty()) return;

                csi->set_text(result);
                csi->set_pen_color("black");
                csi->set_shape(ShapeType::Text);
            } else {
                status->showMessage("Действие отменено", 5000);
            }
        }
    });

    QObject::connect(circuit_combobox, &QComboBox::currentIndexChanged, [&]() {
        circuit_name = osl->get_circuit(circuit_combobox->currentIndex());

        if (circuit_name == "Создать свой цвет") {
            CircuitOwnColorWindow* cocw = new CircuitOwnColorWindow();
            if (cocw->exec() == QDialog::Accepted) {
                csi->set_pen_color(cocw->get_circuit_color());
            } else {
                status->showMessage("Не удалось задать цвет для контура", 5000);
            }
            return;
        }

        csi->set_pen_color(circuit_name);
    });

    QObject::connect(brush_combobox, &QComboBox::currentIndexChanged, [&]() {
        brush_name = osl->get_brush(brush_combobox->currentIndex());

        if (brush_name == "Создать свой цвет") {
            BrushOwnColorWindow* bocw = new BrushOwnColorWindow();
            if (bocw->exec() == QDialog::Accepted) {
                csi->set_brush_color(bocw->get_brush_color());
            }
            return;
        }

        csi->set_brush_color(brush_name);
    });

    // GraphicsActionLists

    QObject::connect(add_figure_button, &QPushButton::clicked, [&]() {
        CustomShapeItem* new_shape = new CustomShapeItem();

        new_shape->set_shape(csi->get_current_shape());
        new_shape->set_brush_color(csi->get_brush_color());
        new_shape->set_pen_color(csi->get_pen_color());

        qreal x = QRandomGenerator::global()->bounded(0, 400);
        qreal y = QRandomGenerator::global()->bounded(0, 300);

        new_shape->setPos(x, y);
        set_model_scene->addItem(new_shape);
    });
    QObject::connect(reset_all_figures_button, &QPushButton::clicked, [&]() {
        QList<QGraphicsItem*> graphics_items = set_model_scene->items();

        QMessageBox::StandardButton question = QMessageBox::question(&window,
                                                                     "Подтверждение",
                                                                     "Хотите ли сбросить все объекты на сцене?",
                                                                     QMessageBox::No | QMessageBox::Yes);

        if(question == QMessageBox::No) {
            status->showMessage("Сброс всех фигур отменен",5000);
            return;
        }

        if(graphics_items.size() == 0) {
            status->showMessage("Сцена пустая для удаления фигур",5000);
            return;
        }

        for (auto& item : graphics_items) {
            set_model_scene->removeItem(item);
            delete item;
        }

        csi = new CustomShapeItem();
        csi->set_shape(ShapeType::Rectangle);
        csi->set_pen_color(QColor(Qt::black).name());
        csi->set_brush_color(default_foreground_object_color);

        object_combobox->setCurrentIndex(0);
        circuit_combobox->setCurrentIndex(0);
        brush_combobox->setCurrentIndex(0);
    });
    QObject::connect(reset_button,&QPushButton::clicked,[&](){
        QList<QGraphicsItem*> graphics_items = set_model_scene->items();

        if(graphics_items.size() == 0) {
            status->showMessage("Сцена пустая для удаления фигуры",5000);
            return;
        }

        bool found = false;

        for(auto& item : graphics_items) {

            if(item == csi) continue;

            if(item->isSelected()) {
                set_model_scene->removeItem(item);
                delete item;
                found = true;
                break;
            }
        }

        if(found) {
            status->showMessage("Фигура была удалена успешно",5000);
        } else {
            status->showMessage("Не удалось удалить фигуру со сцены",5000);
        }
    });
    QObject::connect(end_drawing_button, &QPushButton::clicked, [&]() {
        if (csi->get_current_shape() != ShapeType::CustomPath) {
            status->showMessage("Действие применяется только к собственным объектам!", 5000);
            return;
        }
        csi->finish_custom_path();
    });

    main_layout->addWidget(os->get_common_combobox_name());
    main_layout->addWidget(graphics_field_name);
    main_layout->addWidget(set_graphics_view);
    main_layout->addWidget(gal->get_common_button_name());
    main_layout->addWidget(status);

    window.setCentralWidget(central_widget);

    QList<QWidget*> all_widgets = window.findChildren<QWidget*>();
    for (QWidget* widget : all_widgets) {
        widget->setFont(new_font);
    }
    window.setFont(new_font);

    QObject::connect(&window, &QMainWindow::destroyed, [&]() {
        QSettings settings;
        settings.setValue("window/background-color", background_color);
        settings.setValue("window/text-color", foreground_color);
        settings.setValue("window/font-size", app.font().pointSize());
        settings.setValue("window/font", app.font());
    });

    window.show();

    return app.exec();
}