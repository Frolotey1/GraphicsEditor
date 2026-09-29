#include "QApplication"
#include "QMainWindow"
#include "QStyleFactory"
#include "QDesktopServices"
#include "QWidget"
#include "QPushButton"
#include "QVBoxLayout"
#include "QHBoxLayout"
#include "QGraphicsView"
#include "QGraphicsScene"
#include "QLabel"
#include "QShortcut"
#include "QList"
#include "QMap"
#include "QPair"
#include "QMenu"
#include "QAction"
#include "QToolBar"
#include "QToolButton"
#include "QStatusBar"
#include "QLineEdit"
#include "QCompleter"
#include "QFont"
#include "QMessageBox"
#include "QComboBox"
#include "QSettings"
#include "QRandomGenerator"
#include "GridScene.h"
#include "CommonSettingsMenu.h"
#include "FilesActionsMenu.h"
#include "PdfActionsWindow.h"
#include "ScaleMenu.h"
#include "AccessibilityMenu.h"
#include "ReferenceMenu.h"
#include "ConfigureGraphicsColorWindow.h"
#include "ConfigureFontWindow.h"
#include "CircuitOwnColorWindow.h"
#include "BrushOwnColorWindow.h"
#include "ObjectSettings.h"
#include "ObjectSettingsLists.h"
#include "GraphicsButtonLists.h"
#include "CustomShapeItem.h"
#include "ShapeType.h"
#include "TextObject.h"
#include "CreateInFormatWindow.h"
#include "OpenFileWindow.h"
#include "SaveInFileWindow.h"
#include "InstrumentsMenu.h"
#include "StyleLineCircuitLists.h"
#include "StyleEdgeCircuitLists.h"
#include "StyleJoinCircuitLists.h"
#include "StyleBrushLists.h"
#include "OrderObjectButtons.h"
#include "CollectAllActions.h"
#include "WindowThemeManager.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    QApplication::setStyle(QStyleFactory::create(QApplication::style()->objectName()));
    QApplication::setOrganizationName("GraphicsApplication");
    QApplication::setApplicationName("GraphicsEditor");

    QSettings settings;

    QString background_color = settings.value("window/background-color", "white").toString();
    QString foreground_color = settings.value("window/text-color", "black").toString();
    int font_size = settings.value("window/font-size", 10).toInt();
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
    window.setFixedSize(1200, 800);
    window.setMinimumSize(800,600);
    window.setStyleSheet(default_settings);
    window.setWindowFlags(Qt::Window |
                          Qt::WindowMinimizeButtonHint |
                          Qt::WindowMaximizeButtonHint |
                          Qt::WindowCloseButtonHint);

    QString object_name;
    QString circuit_name;
    QString brush_name;
    QString color_window_name;
    QString text_font_name;
    QString graphics_background_color;

    QString default_foreground_object_color;
    bool sound_enabled = true;

    QStatusBar* status = window.statusBar();

    QWidget* central_widget = new QWidget();

    QVBoxLayout* main_layout = new QVBoxLayout(central_widget);
    main_layout->setSpacing(10);

    QToolBar* tool_bar = window.addToolBar("Инструменты");
    tool_bar->setStyleSheet("background-color: black; color: white;");
    tool_bar->setMovable(false);

    CommonSettingsMenu* csm = new CommonSettingsMenu();
    FilesActionsMenu* fam = new FilesActionsMenu();
    ScaleMenu* sm = new ScaleMenu();
    InstrumentsMenu* im = new InstrumentsMenu();
    ReferenceMenu* rm = new ReferenceMenu();
    AccessibilityMenu* am = new AccessibilityMenu();

    QMenu* files_menu = fam->get_menu();
    QMenu* settings_menu = csm->get_menu();
    QMenu* scale_menu = sm->get_menu();
    QMenu* instruments_menu = im->get_menu();
    QMenu* reference_menu = rm->get_menu();
    QMenu* accessibility_menu = am->get_menu();

    tool_bar->addAction(files_menu->menuAction());
    tool_bar->addAction(scale_menu->menuAction());
    tool_bar->addAction(settings_menu->menuAction());
    tool_bar->addAction(instruments_menu->menuAction());
    tool_bar->addAction(reference_menu->menuAction());

    QWidget* spacer = new QWidget();
    spacer->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Preferred);

    tool_bar->addWidget(spacer);

    tool_bar->addAction(accessibility_menu->menuAction());

    QLineEdit* search_field = new QLineEdit();
    search_field->setPlaceholderText("Введите текст для поиска...");
    search_field->setMaximumWidth(200);
    search_field->setStyleSheet("background-color: black; color: white;");

    CollectAllActions* caa = new CollectAllActions();
    QStringList all_actions = caa->collect_all_actions(tool_bar);

    QCompleter* completer = new QCompleter(all_actions,search_field);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    completer->setFilterMode(Qt::MatchContains);
    completer->setCompletionMode(QCompleter::PopupCompletion);

    search_field->setCompleter(completer);

    tool_bar->addWidget(search_field);

    ObjectSettings* os = new ObjectSettings();
    ObjectSettingsLists* osl = new ObjectSettingsLists();

    QHBoxLayout* groups_layout = new QHBoxLayout(os->get_common_combobox_name());

    QComboBox* configure_object_combobox = os->get_configure_object_combobox();
    QComboBox* configure_circuit_combobox = os->get_configure_circuit_combobox();
    QComboBox* configure_brush_combobox = os->get_configure_brush_combobox();
    QComboBox* configure_color_window_combobox = os->get_configure_color_window_combobox();
    QComboBox* configure_text_font_combobox = os->get_configure_text_font_combobox();

    QHBoxLayout* configure_object_combobox_layout = new QHBoxLayout(os->get_configure_object_combobox_name());
    QHBoxLayout* configure_circuit_combobox_layout = new QHBoxLayout(os->get_configure_circuit_combobox_name());
    QHBoxLayout* configure_brush_combobox_layout = new QHBoxLayout(os->get_configure_brush_combobox_name());
    QHBoxLayout* configure_color_window_layout = new QHBoxLayout(os->get_configure_color_window_name());
    QHBoxLayout* configure_text_font_layout = new QHBoxLayout(os->get_configure_text_font_name());

    configure_object_combobox_layout->addWidget(configure_object_combobox);
    configure_object_combobox_layout->setAlignment(Qt::AlignCenter);

    configure_circuit_combobox_layout->addWidget(configure_circuit_combobox);
    configure_circuit_combobox_layout->setAlignment(Qt::AlignCenter);

    configure_brush_combobox_layout->addWidget(configure_brush_combobox);
    configure_brush_combobox_layout->setAlignment(Qt::AlignCenter);

    configure_color_window_layout->addWidget(configure_color_window_combobox);
    configure_color_window_layout->setAlignment(Qt::AlignCenter);

    configure_text_font_layout->addWidget(configure_text_font_combobox);
    configure_text_font_layout->setAlignment(Qt::AlignCenter);

    groups_layout->addWidget(os->get_configure_object_combobox_name());
    groups_layout->addWidget(os->get_configure_circuit_combobox_name());
    groups_layout->addWidget(os->get_configure_brush_combobox_name());
    groups_layout->addWidget(os->get_configure_color_window_name());
    groups_layout->addWidget(os->get_configure_text_font_name());

    GraphicsButtonLists* gbl = new GraphicsButtonLists();

    QHBoxLayout* button_groups_layout = new QHBoxLayout(gbl->get_common_button_name());

    QPushButton* add_figure_button = gbl->get_figure_button();
    QPushButton* remove_button = gbl->get_remove_button();
    QPushButton* remove_all_figures_button = gbl->get_remove_all_figures_button();
    QPushButton* end_drawing_button = gbl->get_end_drawing_button();

    button_groups_layout->addWidget(add_figure_button);
    button_groups_layout->addWidget(remove_button);
    button_groups_layout->addWidget(remove_all_figures_button);
    button_groups_layout->addWidget(end_drawing_button);

    CustomShapeItem* csi = new CustomShapeItem();
    csi->setFocus();

    GridScene* set_model_scene = new GridScene();
    set_model_scene->setSceneRect(0, 0, 800, 500);
    set_model_scene->addItem(csi);

    QGraphicsView* set_graphics_view = new QGraphicsView(set_model_scene);

    OrderObjectButtons* oob = new OrderObjectButtons();

    QHBoxLayout* order_graphics_imagination = new QHBoxLayout(oob->get_common_object_buttons_name());

    QVBoxLayout* order_buttons_layout = new QVBoxLayout(oob->get_order_buttons_name());
    QHBoxLayout* graphics_scene_layout = new QHBoxLayout(oob->get_common_graphics_scene_name());

    for(QPushButton* button : oob->get_order_buttons()) {
        order_buttons_layout->addWidget(button);
    }

    for(QPushButton* button : oob->get_order_buttons()) {
        QString type_order_button = button->text();

        QObject::connect(button, &QPushButton::clicked,[type_order_button, &status, set_model_scene]() {

            QList<CustomShapeItem*> all_shapes;
            QList<CustomShapeItem*> selected_shapes;

            for(QGraphicsItem* item : set_model_scene->items()) {
                CustomShapeItem* shape = qgraphicsitem_cast<CustomShapeItem*>(item);

                if(shape) {
                    all_shapes.append(shape);

                    if(shape->isSelected()) {
                        selected_shapes.append(shape);
                    }
                }
             }

            if(all_shapes.isEmpty()) {
                status->showMessage("Сцена пустая для настройки порядка", 5000);
                return;
            }

            if(selected_shapes.isEmpty()) {
                status->showMessage("Нет выделенных фигур", 5000);
                return;
            }

            qreal min_z = 0;
            qreal max_z = 0;

            for(CustomShapeItem* shape : all_shapes) {
                if(shape->zValue() < min_z) min_z = shape->zValue();
                if(shape->zValue() > max_z) max_z = shape->zValue();
            }

            for(CustomShapeItem* shape_item : selected_shapes) {
                qreal current_rotation = shape_item->rotation();

                if(type_order_button == "Поворот вправо на 90°") {
                     shape_item->setRotation(current_rotation + 90);
                } else if(type_order_button == "Поворот влево на 90°") {
                     shape_item->setRotation(current_rotation - 90);
                } else if(type_order_button == "Поворот на 45°") {
                     shape_item->setRotation(current_rotation + 45);
                } else if(type_order_button == "Передний план") {
                     shape_item->setZValue(max_z + 1);
                     max_z += 1;
                } else if(type_order_button == "Задний план") {
                     shape_item->setZValue(min_z - 1);
                     min_z -= 1;
                } else if(type_order_button == "Выше на один") {
                     shape_item->setZValue(shape_item->zValue() + 1);
                } else if(type_order_button == "Ниже на один") {
                     shape_item->setZValue(shape_item->zValue() - 1);
                }

                shape_item->update();
            }
        });
    }

    graphics_scene_layout->addWidget(set_graphics_view);

    order_graphics_imagination->addWidget(oob->get_order_buttons_name());
    order_graphics_imagination->addWidget(oob->get_common_graphics_scene_name());

    //Completer

    QObject::connect(completer,QOverload<const QString&>::of(&QCompleter::activated),
                     [&, tool_bar]
                     (const QString& name) {

        for (QAction* toolbar_action : tool_bar->actions()) {
            QMenu* menu = toolbar_action->menu();
            if (!menu) continue;

            for (QAction* action : menu->actions()) {
                if (action->text() == name) {
                    action->trigger();
                    search_field->clear();
                    return;
                }

                QMenu* sub_menu = action->menu();
                if (sub_menu) {
                    for (QAction* sub_action : sub_menu->actions()) {
                        if (sub_action->text() == name) {
                            sub_action->trigger();
                            search_field->clear();
                            return;
                        }

                        QMenu* sub_sub_menu = sub_action->menu();
                        if (sub_sub_menu) {
                            for (QAction* ss_action : sub_sub_menu->actions()) {
                                if (ss_action->text() == name) {
                                    ss_action->trigger();
                                    search_field->clear();
                                    return;
                                }
                            }
                        }
                    }
                }
            }
        }
    });

    //AccessibilityMenu

    for(QAction* special_action : accessibility_menu->actions()) {
        QString text_action = special_action->text();
        QObject::connect(special_action,&QAction::toggled,[&,text_action](bool checked){

            if(text_action == "Режим просмотра") {

                QList<QGraphicsItem*> graphics_items = set_model_scene->items();

                if(graphics_items.size() > 1) {
                    for(auto& item : graphics_items) {
                        CustomShapeItem* shape_item = qgraphicsitem_cast<CustomShapeItem*>(item);

                        if(shape_item) {
                            shape_item->setFlag(QGraphicsItem::ItemIsMovable,checked);
                            shape_item->setFlag(QGraphicsItem::ItemIsFocusable,checked);
                            shape_item->setFlag(QGraphicsItem::ItemIsSelectable,checked);
                        }
                    }
                    return;
                }

                csi->setFlag(QGraphicsItem::ItemIsMovable,checked);
                csi->setFlag(QGraphicsItem::ItemIsFocusable,checked);
                csi->setFlag(QGraphicsItem::ItemIsSelectable,checked);

                QMap<bool,QPair<QColor,QColor>> configure_color;
                configure_color[true] = qMakePair(QColor(background_color),QColor(foreground_color));
                configure_color[false] = qMakePair(QColor(Qt::gray),QColor(Qt::white));

                QColor bg = configure_color[checked].first;
                QColor fg = configure_color[checked].second;

                QList<QWidget*> widgets =
                {   add_figure_button,remove_button,
                    remove_all_figures_button,end_drawing_button,
                    configure_object_combobox,configure_circuit_combobox,
                    configure_brush_combobox, configure_color_window_combobox,
                    configure_text_font_combobox
                };

                for(QPushButton* order_buttons : oob->get_order_buttons()) {
                    widgets.append(order_buttons);
                }

                for(QWidget* widget : widgets) {
                    QPushButton* button = qobject_cast<QPushButton*>(widget);

                    if(button) {
                        button->setEnabled(checked);
                        button->setStyleSheet(
                            QString("background-color: %1; color: %2").
                            arg(bg.name()).
                            arg(fg.name())
                        );
                    } else {
                        QComboBox* combobox = qobject_cast<QComboBox*>(widget);

                        if(combobox) {
                            combobox->setEnabled(checked);
                            combobox->setStyleSheet(
                                QString("background-color: %1; color: %2;").
                                arg(bg.name()).
                                arg(fg.name())
                            );
                        }
                    }
                }

                QColor black_background_color = Qt::black;
                QColor white_foreground_color = Qt::white;

                instruments_menu->setEnabled(checked);
                instruments_menu->setStyleSheet(
                    QString("background-color: %1; color: %2;").
                    arg(black_background_color.name()).
                    arg(white_foreground_color.name())
                );

                instruments_menu->addSeparator();

                QAction* panoraming_graphics_view_action = am->get_moving_graphics_view_action();
                panoraming_graphics_view_action->setEnabled(checked);

            } else if(text_action == "Панорамирование сцены") {
                if(checked) set_graphics_view->setDragMode(QGraphicsView::ScrollHandDrag);
                else set_graphics_view->setDragMode(QGraphicsView::NoDrag);
            } else
                sound_enabled = checked;
        });
    }

    //FileActionsMenu

    QMenu* create_menu = fam->get_create_menu();

    if (create_menu) {
        for (QAction* action : create_menu->actions()) {
            QString type_image = action->text().toLower();

            QObject::connect(action, &QAction::triggered, [&window, status, sound_enabled, type_image]() {
                if(sound_enabled) QApplication::beep();

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

        if(sound_enabled) QApplication::beep();

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
        if(sound_enabled) QApplication::beep();

        SaveInFileWindow* sifw = new SaveInFileWindow(&window, set_model_scene, graphics_background_color);

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
        QToolButton* export_button = fam->get_tool_button();

        QObject::connect(export_button,&QToolButton::clicked,[&,export_button](){

            if(sound_enabled) QApplication::beep();

            PDFActionsWindow* paw = new PDFActionsWindow(&window,"Экспорт",set_model_scene);

            if(paw->exec() == QDialog::Accepted) {
                if(paw->is_exported()) {
                    status->showMessage("Изображение было успешно импортировано",5000);
                } else {
                    status->showMessage("Не удалось экспортировать изображение",5000);
                }
            } else {
                status->showMessage("Действие отменено",5000);
            }
        });

        QMenu* export_button_sub_menu = export_button->menu();

        QObject::connect(export_button_sub_menu,&QMenu::triggered,[&](QAction* size_action){
            QString size_text = size_action->text();

            PDFActionsWindow* paw = new PDFActionsWindow(&window,"Экспорт",set_model_scene,size_text);

            if(paw->exec() == QDialog::Accepted) {
                if(paw->is_exported()) {
                    status->showMessage("Изображение было успешно экспортировано",5000);
                } else {
                    status->showMessage("Не удалось экспортировать изображение",5000);
                }
            } else {
                status->showMessage("Действие отменено",5000);
            }

        });

        QAction* import_action = fam->get_import_action();

        QObject::connect(import_action,&QAction::triggered,[&](){
            PDFActionsWindow* paw = new PDFActionsWindow(&window,"Импорт",set_model_scene);

            if(paw->exec() == QDialog::Accepted) {
                if(paw->is_imported()) {
                    status->showMessage("Изображение было успешно импортировано",5000);
                } else {
                    status->showMessage("Не удалось импортировать изображение",5000);
                }
            } else {
                status->showMessage("Действие отменено",5000);
            }
        });
    }

    //ScaleMenu

    QMenu* scale_scene_menu = sm->get_scale_scene_menu();

    if (scale_scene_menu) {
        for (QAction* action : scale_scene_menu->actions()) {
            QString configure_scene = action->text();

            QObject::connect(action, &QAction::triggered, [&status,configure_scene, set_graphics_view]() {
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

    QMenu* scale_font_menu = sm->get_scale_font_menu();

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

    //InstrumentsMenu

    if(instruments_menu) {
        for(QAction* action : instruments_menu->actions()) {
            if(action->text() == "Сетка") {

                QMenu* grid_menu = action->menu();

                QObject::connect(grid_menu,&QMenu::triggered,[status,sound_enabled,set_model_scene](QAction* grid_action){

                    if(grid_action->text() == "Сбросить сетку") {
                        set_model_scene->set_grid_visible(false);
                        return;
                    } else {
                        bool converted = false;

                        int size = grid_action->text().left(2).toInt(&converted);

                        if(!converted) {
                            status->showMessage("Ошибка считывания размера для сетки");
                            return;
                        }

                        set_model_scene->set_grid_size(size);
                    }

                    set_model_scene->set_grid_visible(true);
                });
            } else if (action->text() == "Контур") {
                QMenu* circuit_menu = action->menu();
                if (!circuit_menu) continue;

                for (QAction* circuit_action : circuit_menu->actions()) {
                    if (circuit_action->text() == "Стили линий") {
                        QMenu* circuit_line_menu = circuit_action->menu();
                        if (!circuit_line_menu) continue;

                        QObject::connect(circuit_line_menu, &QMenu::triggered, [csi,status,set_model_scene](QAction* line_action) {
                            StyleLineCircuitLists* slcl = new StyleLineCircuitLists(line_action->text());

                            QList<QGraphicsItem*> graphics_items = set_model_scene->items();

                            if(graphics_items.isEmpty()) {
                                status->showMessage("Сцена пустая для настройки стилей линий");
                                return;
                            }

                            bool found = false;

                            for(auto item : graphics_items) {

                                CustomShapeItem* shape_item = qgraphicsitem_cast<CustomShapeItem*>(item);
                                if(shape_item) {
                                    shape_item->configure_pen_style(slcl->get_pen_style());
                                    found = true;
                                }
                            }

                            if(!found) {
                                csi->configure_pen_style(slcl->get_pen_style());
                            }
                        });
                    } else if(circuit_action->text() == "Стили концов") {
                        QMenu* circuit_edge_menu = circuit_action->menu();
                        if (!circuit_edge_menu) continue;

                        QObject::connect(circuit_edge_menu, &QMenu::triggered, [csi,status,set_model_scene](QAction* edge_action) {
                            StyleEdgeCircuitLists* secl = new StyleEdgeCircuitLists(edge_action->text());

                            QList<QGraphicsItem*> graphics_items = set_model_scene->items();

                            if(graphics_items.isEmpty()) {
                                status->showMessage("Сцена пустая для настройки стилей концов");
                                return;
                            }

                            bool found = false;

                            for(auto item : graphics_items) {

                                CustomShapeItem* shape_item = qgraphicsitem_cast<CustomShapeItem*>(item);
                                if(shape_item) {
                                    shape_item->configure_pen_cap_style(secl->get_pen_cap_style());
                                    found = true;
                                }
                            }

                            if(!found) {
                                csi->configure_pen_cap_style(secl->get_pen_cap_style());
                            }
                        });
                    } else if(circuit_action->text() == "Стили соединений") {
                        QMenu* circuit_menu = action->menu();

                        if(!circuit_menu) continue;

                        QObject::connect(circuit_menu,&QMenu::triggered,[csi,status,set_model_scene](QAction* join_action){
                            StyleJoinCircuitLists* sjcl = new StyleJoinCircuitLists(join_action->text());

                            QList<QGraphicsItem*> graphics_items = set_model_scene->items();

                            if(graphics_items.isEmpty()) {
                                status->showMessage("Сцена пустая для настройки стилей соединений");
                                return;
                            }

                            bool found = false;

                            for(auto& item : graphics_items) {
                                CustomShapeItem* shape_item = qgraphicsitem_cast<CustomShapeItem*>(item);

                                if(shape_item) {
                                    shape_item->configure_pen_join_style(sjcl->get_pen_join_style());
                                    found = true;
                                }
                            }

                            if(!found) {
                                csi->configure_pen_join_style(sjcl->get_pen_join_style());
                            }
                        });
                    } else if(circuit_action->text().contains("Сбросить",Qt::CaseInsensitive)) {

                        QObject::connect(circuit_action,&QAction::triggered,[csi,set_model_scene](){
                            QList<QGraphicsItem*> graphics_item = set_model_scene->items();

                            bool found = false;

                            for(auto& item : graphics_item) {
                                CustomShapeItem* shape_item = qgraphicsitem_cast<CustomShapeItem*>(item);

                                if(shape_item) {
                                    shape_item->configure_pen_style(Qt::SolidLine);
                                    shape_item->configure_pen_cap_style(Qt::SquareCap);
                                    shape_item->configure_pen_join_style(Qt::BevelJoin);
                                    found = true;
                                }
                            }

                            if(!found) {
                                csi->configure_pen_style(Qt::SolidLine);
                                csi->configure_pen_cap_style(Qt::SquareCap);
                                csi->configure_pen_join_style(Qt::BevelJoin);
                            }
                        });
                    } else
                        continue;
                }
            } else if (action->text() == "Заливка"){

                QMenu* brush_menu = action->menu();

                if(!brush_menu) continue;

                for(QAction* action : brush_menu->actions()) {

                    if(action->text() == "Стили") {

                        QMenu* brush_style_menu = action->menu();

                        QObject::connect(brush_style_menu,&QMenu::triggered,[csi,status,set_model_scene](QAction* brush_style_action){
                            StyleBrushLists* sgbl = new StyleBrushLists(brush_style_action->text());

                            QList<QGraphicsItem*> graphics_items = set_model_scene->items();

                            if(graphics_items.isEmpty()) {
                                status->showMessage("Сцена пустая для настройки стилей градиента");
                                return;
                            }

                            bool found = false;

                            for(auto& item : graphics_items) {
                                CustomShapeItem* shape_item = qgraphicsitem_cast<CustomShapeItem*>(item);

                                if(shape_item) {
                                    shape_item->configure_brush_style(sgbl->get_brush_style());
                                    found = true;
                                }
                            }

                            if(!found) {
                                csi->configure_brush_style(sgbl->get_brush_style());
                            }
                        });
                    } else if(action->text().contains("Сбросить",Qt::CaseInsensitive)) {

                        QObject::connect(action,&QAction::triggered,[csi,set_model_scene,status](){

                            QList<QGraphicsItem*> graphics_items = set_model_scene->items();

                            if(graphics_items.isEmpty()) {
                                status->showMessage("Сцена пустая для сброса стилей заливки");
                                return;
                            }

                            if(graphics_items.size() > 1) {
                                for(auto& item : graphics_items) {
                                    CustomShapeItem* shape_item = qgraphicsitem_cast<CustomShapeItem*>(item);

                                    if(shape_item) {
                                        shape_item->configure_brush_style(Qt::SolidPattern);
                                    }

                                }

                                return;
                            }

                            csi->configure_brush_style(Qt::SolidPattern);
                        });
                    } else
                        continue;
                }
            } else
                continue;
        }
    }

    QMenu* common_settings_menu = csm->get_menu();

    if(common_settings_menu) {
        for(QAction* action : common_settings_menu->actions()) {

            if(action->text() == "Вид приложения") {
                QMenu* style_menu = action->menu();

                QObject::connect(style_menu,&QMenu::triggered,[&](QAction* style_action){
                    QStyle* style = QStyleFactory::create(style_action->text());

                    if(!style) {
                        status->showMessage("Не удалось установить вид для приложения",5000);
                        return;
                    }

                    QApplication::setStyle(style);
                });
            } else if(action->text() == "Оформление окна") {
                QMenu* design_window_menu = action->menu();

                QObject::connect(design_window_menu,&QMenu::triggered,[&](QAction* design_window_action){

                    QMap<QString,QList<QPair<QString,QString>>> theme_style_lists = csm->get_theme_style_lists();

                    QPair<QString,QString> tool_bar_pair = theme_style_lists[design_window_action->text()].at(0);
                    QPair<QString,QString> window_pair = theme_style_lists[design_window_action->text()].at(1);

                    tool_bar->setStyleSheet(QString("background-color: %1; color: %2;").
                                            arg(tool_bar_pair.first).
                                            arg(tool_bar_pair.second)
                    );

                    for(QAction* action : tool_bar->actions()) {
                        QMenu* type_menu = action->menu();

                        if(type_menu) {
                            type_menu->setStyleSheet(QString("background-color: %1; color: %2;").
                                                     arg(tool_bar_pair.first).
                                                     arg(tool_bar_pair.second));
                        } else {
                            search_field->setStyleSheet(QString("background-color: %1; color: %2;").
                                                        arg(tool_bar_pair.first).
                                                        arg(tool_bar_pair.second));
                        }
                    }

                    window.setStyleSheet(QString("background-color: %1; color: %2;").
                                         arg(window_pair.first).
                                         arg(window_pair.second)
                    );
                });
            } else if(action->text() == "Настройка шрифта") {
                QObject::connect(action,&QAction::triggered,[status,&window](){
                    ConfigureFontWindow* cfw = new ConfigureFontWindow();

                    if(cfw->exec() == QDialog::Accepted) {
                        QFont set_font = cfw->get_font();

                        QList<QWidget*> all_widgets = window.findChildren<QWidget*>();

                        for(QWidget* widget : all_widgets) {
                            widget->setFont(set_font);
                        }

                        window.setFont(set_font);
                    } else {
                        status->showMessage("Действие отменено",5000);
                    }
                });
            } else if(action->text() == "Возврат по умолчанию") {
                QObject::connect(action,&QAction::triggered,[tool_bar,&window,original_font](){
                    tool_bar->setStyleSheet("background-color: black; color: white;");
                    window.setStyleSheet("background-color: white; color: black;");

                    QList<QWidget*> all_widgets = window.findChildren<QWidget*>();

                    for(QWidget* widget : all_widgets) {
                        widget->setFont(original_font);
                    }

                    window.setFont(original_font);
                });
            } else
                continue;
        }
    }

    // ReferenceMenu

    if(reference_menu) {
        QAction* about_program_action = rm->get_about_program_action();
        QToolButton* github_instructions_tool_button = rm->get_github_instructions_tool_button();

        QObject::connect(about_program_action,&QAction::triggered,[&window](){
            QMessageBox::information(&window,"Информация","Приложение реализовано с помощью "
                                                            "следующего стека технологий:\n"
                                                            "1) Язык программирования С++17\n"
                                                            "2) Qt Framework 6.11.2");
        });

        QObject::connect(github_instructions_tool_button,&QToolButton::clicked,[](){
            QDesktopServices::openUrl(QUrl("https://github.com/Frolotey1/GraphicsEditor/tree/main/Documentation"));
        });

        QMenu* tool_button_menu = github_instructions_tool_button->menu();

        QObject::connect(tool_button_menu,&QMenu::triggered,[](QAction* tool_action){
            if(tool_action->text() == "Панель окна") {
                QDesktopServices::openUrl(QUrl("https://github.com/Frolotey1/GraphicsEditor/blob/main/Documentation/WindowPanelWiki.md"));
            } else if(tool_action->text() == "Графическая сцена") {
                QDesktopServices::openUrl(QUrl("https://github.com/Frolotey1/GraphicsEditor/blob/main/Documentation/GraphicsSceneWiki.md"));
            } else {
                QDesktopServices::openUrl(QUrl("https://github.com/Frolotey1/GraphicsEditor/blob/main/Documentation/GraphicsObjectActionsWiki.md"));
            }
        });
    }

    // ObjectSettings

    QObject::connect(configure_object_combobox, &QComboBox::currentTextChanged, [&]() {
        object_name = configure_object_combobox->currentText();

        if (object_name == "Прямоугольник") csi->set_shape(ShapeType::Rectangle);
        else if (object_name == "Линия") csi->set_shape(ShapeType::Line);
        else if (object_name == "Эллипс") csi->set_shape(ShapeType::Ellipse);
        else if (object_name == "Многоугольник") csi->set_shape(ShapeType::Polygon);
        else if (object_name == "Текст") {
            TextObject* to = new TextObject();
            if (to->exec() == QDialog::Accepted) {
                QString result = to->get_text();
                if (!result.isEmpty()) {
                    csi->set_text(result);
                    csi->set_pen_color("black");
                    csi->set_shape(ShapeType::Text);
                }
            } else {
                status->showMessage("Действие отменено", 5000);
            }
        } else if (object_name == "Создать свой объект") {
            csi->set_shape(ShapeType::CustomPath);
            csi->start_custom_path();
        }
    });

    QObject::connect(configure_circuit_combobox, &QComboBox::currentTextChanged, [&]() {
        circuit_name = osl->get_circuit(configure_circuit_combobox->currentText());

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
    QObject::connect(configure_brush_combobox, &QComboBox::currentTextChanged, [&]() {
        brush_name = osl->get_brush(configure_brush_combobox->currentText());

        if (brush_name == "Создать свой цвет") {
            BrushOwnColorWindow* bocw = new BrushOwnColorWindow();
            if (bocw->exec() == QDialog::Accepted) {
                csi->set_brush_color(bocw->get_brush_color());
            }
            return;
        }

        csi->set_brush_color(brush_name);
    });
    QObject::connect(configure_color_window_combobox, &QComboBox::currentTextChanged, [&](){
        color_window_name = osl->get_color_window(configure_color_window_combobox->currentText());

        if(color_window_name == "Создать свой цвет") {
            ConfigureGraphicsColorWindow* cgcw = new ConfigureGraphicsColorWindow();

            if (cgcw->exec() == QDialog::Accepted) {
                QString set_graphics_background_color = cgcw->get_graphics_background_color();

                set_graphics_view->setStyleSheet(QString("background-color: %1;").arg(set_graphics_background_color));
            }

            return;
        }

        graphics_background_color = color_window_name;

        set_graphics_view->setStyleSheet(QString("background-color: %1;").arg(color_window_name));
    });
    QObject::connect(configure_text_font_combobox,&QComboBox::currentTextChanged,[&](){
        QList<QGraphicsItem*> graphics_items = set_model_scene->items();

        bool exist = true;

        for(auto& item : graphics_items) {
            CustomShapeItem* shape_item = qgraphicsitem_cast<CustomShapeItem*>(item);

            if(shape_item->get_current_shape() != ShapeType::Text) {
                exist = false;
            }
        }

        if(!exist) {
            status->showMessage("Текст отсутствует для настройки шрифта",5000);
            return;
        }

        text_font_name = osl->get_text_font(configure_text_font_combobox->currentText());

        if(text_font_name == "Создать свой шрифт") {
            ConfigureFontWindow* cfw = new ConfigureFontWindow();

            if(cfw->exec() == QDialog::Accepted) {
                QFont set_font = cfw->get_font();

                for(auto& item : graphics_items) {
                    CustomShapeItem* shape_item = qgraphicsitem_cast<CustomShapeItem*>(item);

                    if(shape_item->get_current_shape() == ShapeType::Text) {
                        shape_item->set_font_text_style(set_font);
                    }
                }

                csi->set_font_text_style(set_font);
            } else {
                status->showMessage("Действие отменено",5000);
            }

            return;
        }

        for(auto& item : graphics_items) {
            CustomShapeItem* shape_item = qgraphicsitem_cast<CustomShapeItem*>(item);

            if(shape_item->get_current_shape() == ShapeType::Text) {
                shape_item->set_font_text_style(QFont(text_font_name));
            }
        }

        csi->set_font_text_style(QFont(text_font_name));

    });

    // GraphicsActionLists

    QObject::connect(add_figure_button, &QPushButton::clicked, [&]() {
        CustomShapeItem* new_shape = new CustomShapeItem();

        new_shape->set_shape(csi->get_current_shape());
        new_shape->set_brush_color(csi->get_brush_color());
        new_shape->set_pen_color(csi->get_pen_color());
        new_shape->set_text(csi->get_text());

        qreal x = QRandomGenerator::global()->bounded(0, 400);
        qreal y = QRandomGenerator::global()->bounded(0, 300);

        new_shape->setPos(x, y);
        set_model_scene->addItem(new_shape);
    });
    QObject::connect(remove_all_figures_button, &QPushButton::clicked, [&]() {
        QList<QGraphicsItem*> graphics_items = set_model_scene->items();

        if(sound_enabled) QApplication::beep();

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

        configure_object_combobox->setCurrentIndex(0);
        configure_circuit_combobox->setCurrentIndex(0);
        configure_brush_combobox->setCurrentIndex(0);
    });
    QObject::connect(remove_button,&QPushButton::clicked,[&](){
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
    main_layout->addWidget(oob->get_common_object_buttons_name());
    main_layout->addWidget(gbl->get_common_button_name());
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