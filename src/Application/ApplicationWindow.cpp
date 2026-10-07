#include "include/Application/ApplicationWindow.h"

ApplicationWindow::ApplicationWindow(QWidget* parent) : QMainWindow(parent) {
    QSettings settings;
    background_color = settings.value("window/background-color", "white").toString();
    foreground_color = settings.value("window/text-color", "black").toString();
    font_size = settings.value("window/font-size", 10).toInt();
    current_font = settings.value("window/font", QApplication::font()).value<QFont>();

    if (font_size > 2)
        current_font.setPointSize(font_size);

    original_font = QApplication::font();

    setWindowTitle("Графический редактор");
    setFixedSize(1200, 800);
    setMinimumSize(800, 600);
    setStyleSheet(QString("background-color: %1; color: %2;")
                      .arg(background_color, foreground_color));
    setWindowFlags(Qt::Window |
                   Qt::WindowMinimizeButtonHint |
                   Qt::WindowMaximizeButtonHint |
                   Qt::WindowCloseButtonHint);

    status = statusBar();

    setupUi();
    setupToolBar();
    setupMenus();
    setupGraphicsScene();
    setupObjectSettings();
    setupButtons();
    setupOrderButtons();
    setupSearch();
    setupConnections();

    const auto all_widgets = findChildren<QWidget*>();
    for (QWidget* w : all_widgets)
        w->setFont(current_font);
    setFont(current_font);
}

void ApplicationWindow::setupUi() {
    centralWidget = new QWidget(this);
    auto* main_layout = new QVBoxLayout(centralWidget);
    main_layout->setSpacing(10);

    setCentralWidget(centralWidget);

    os  = new ObjectSettings();
    osl = new ObjectSettingsLists();
    gbl = new GraphicsButtonLists();
    oob = new OrderObjectButtons();

    configureObjectComboBox = os->get_configure_object_combobox();
    configureCircuitComboBox = os->get_configure_circuit_combobox();
    configureBrushComboBox = os->get_configure_brush_combobox();
    configureColorWindowComboBox = os->get_configure_color_window_combobox();
    configureTextFontComboBox = os->get_configure_text_font_combobox();

    addFigureButton = gbl->get_figure_button();
    removeButton = gbl->get_remove_button();
    removeAllFiguresButton = gbl->get_remove_all_figures_button();
    endDrawingButton = gbl->get_end_drawing_button();

    auto* groups_layout = new QHBoxLayout(os->get_common_combobox_name());
    groups_layout->addWidget(os->get_configure_object_combobox_name());
    groups_layout->addWidget(os->get_configure_circuit_combobox_name());
    groups_layout->addWidget(os->get_configure_brush_combobox_name());
    groups_layout->addWidget(os->get_configure_color_window_name());
    groups_layout->addWidget(os->get_configure_text_font_name());

    auto* objectLayout = new QHBoxLayout(os->get_configure_object_combobox_name());
    auto* circuitLayout = new QHBoxLayout(os->get_configure_circuit_combobox_name());
    auto* brushLayout = new QHBoxLayout(os->get_configure_brush_combobox_name());
    auto* colorLayout = new QHBoxLayout(os->get_configure_color_window_name());
    auto* fontLayout = new QHBoxLayout(os->get_configure_text_font_name());

    objectLayout ->addWidget(configureObjectComboBox);
    objectLayout ->setAlignment(Qt::AlignCenter);

    circuitLayout->addWidget(configureCircuitComboBox);
    circuitLayout->setAlignment(Qt::AlignCenter);

    brushLayout->addWidget(configureBrushComboBox);
    brushLayout->setAlignment(Qt::AlignCenter);

    colorLayout->addWidget(configureColorWindowComboBox);
    colorLayout->setAlignment(Qt::AlignCenter);

    fontLayout->addWidget(configureTextFontComboBox);
    fontLayout->setAlignment(Qt::AlignCenter);

    auto* button_groups_layout = new QHBoxLayout(gbl->get_common_button_name());
    button_groups_layout->addWidget(addFigureButton);
    button_groups_layout->addWidget(removeButton);
    button_groups_layout->addWidget(removeAllFiguresButton);
    button_groups_layout->addWidget(endDrawingButton);

    main_layout->addWidget(os->get_common_combobox_name());
    main_layout->addWidget(oob->get_common_object_buttons_name());
    main_layout->addWidget(gbl->get_common_button_name());
}

void ApplicationWindow::setupToolBar() {
    toolBar = addToolBar("Инструменты");
    toolBar->setStyleSheet("background-color: black; color: white;");
    toolBar->setMovable(false);

    csm = new CommonSettingsMenu();
    fam = new FilesActionsMenu();
    sm = new ScaleMenu();
    im = new InstrumentsMenu();
    rm = new ReferenceMenu();
    am = new AccessibilityMenu();

    toolBar->addAction(fam->get_menu()->menuAction());
    toolBar->addAction(sm->get_menu()->menuAction());
    toolBar->addAction(csm->get_menu()->menuAction());
    toolBar->addAction(im->get_menu()->menuAction());
    toolBar->addAction(rm->get_menu()->menuAction());

    auto* spacer = new QWidget();
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    toolBar->addWidget(spacer);

    toolBar->addAction(am->get_menu()->menuAction());

    searchField = new QLineEdit();
    searchField->setPlaceholderText("Введите текст для поиска...");
    searchField->setMaximumWidth(200);
    searchField->setStyleSheet("background-color: black; color: white;");
    toolBar->addWidget(searchField);
}

void ApplicationWindow::setupSearch()
{
    auto* caa = new CollectAllActions();
    const QStringList all_actions = caa->collect_all_actions(toolBar);

    completer = new QCompleter(all_actions, searchField);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    completer->setFilterMode(Qt::MatchContains);
    completer->setCompletionMode(QCompleter::PopupCompletion);
    searchField->setCompleter(completer);

    connect(completer, QOverload<const QString&>::of(&QCompleter::activated),
            this, &ApplicationWindow::onSearchActivated);
}

void ApplicationWindow::onSearchActivated(const QString& name) {
    for (QAction* toolbar_action : toolBar->actions()) {
        QMenu* menu = toolbar_action->menu();
        if (!menu) continue;

        for (QAction* action : menu->actions()) {
            if (action->text() == name) {
                action->trigger();
                searchField->clear();
                return;
            }

            if (QMenu* sub_menu = action->menu()) {
                for (QAction* sub_action : sub_menu->actions()) {
                    if (sub_action->text() == name) {
                        sub_action->trigger();
                        searchField->clear();
                        return;
                    }
                    if (QMenu* sub_sub_menu = sub_action->menu()) {
                        for (QAction* ss_action : sub_sub_menu->actions()) {
                            if (ss_action->text() == name) {
                                ss_action->trigger();
                                searchField->clear();
                                return;
                            }
                        }
                    }
                }
            }
        }
    }
}

void ApplicationWindow::setupGraphicsScene() {
    prototypeItem = new CustomShapeItem();
    prototypeItem->setFocus();

    scene = new GridScene();
    scene->setSceneRect(0, 0, 800, 500);
    scene->addItem(prototypeItem);

    graphicsView = new QGraphicsView(scene);
}

void ApplicationWindow::setupMenus() {
    setupAccessibilityMenu();
    setupFilesMenu();
    setupPdfMenu();
    setupScaleMenu();
    setupInstrumentsMenu();
    setupCommonSettingsMenu();
    setupReferenceMenu();
}

void ApplicationWindow::setupAccessibilityMenu()
{
    for (QAction* special_action : am->get_menu()->actions()) {
        const QString text_action = special_action->text();

        connect(special_action, &QAction::toggled, this, [this, text_action](bool checked) {

            if (text_action == "Режим просмотра") {
                const auto graphics_items = scene->items();

                if (graphics_items.size() > 1) {
                    for (QGraphicsItem* item : graphics_items) {
                        if (auto* shape = qgraphicsitem_cast<CustomShapeItem*>(item)) {
                            shape->setFlag(QGraphicsItem::ItemIsMovable,checked);
                            shape->setFlag(QGraphicsItem::ItemIsFocusable,checked);
                            shape->setFlag(QGraphicsItem::ItemIsSelectable, checked);
                        }
                    }
                    return;
                }

                prototypeItem->setFlag(QGraphicsItem::ItemIsMovable,checked);
                prototypeItem->setFlag(QGraphicsItem::ItemIsFocusable,checked);
                prototypeItem->setFlag(QGraphicsItem::ItemIsSelectable,checked);

                QMap<bool, QPair<QColor, QColor>> configure_color;
                configure_color[true]  = qMakePair(QColor(background_color),
                                                  QColor(foreground_color));
                configure_color[false] = qMakePair(QColor(Qt::gray), QColor(Qt::white));

                const QColor bg = configure_color[checked].first;
                const QColor fg = configure_color[checked].second;

                QList<QWidget*> widgets = {
                    addFigureButton, removeButton,
                    removeAllFiguresButton, endDrawingButton,
                    configureObjectComboBox, configureCircuitComboBox,
                    configureBrushComboBox,  configureColorWindowComboBox,
                    configureTextFontComboBox
                };

                for (QPushButton* order_button : oob->get_order_buttons())
                    widgets.append(order_button);

                for (QWidget* widget : widgets) {
                    if (auto* button = qobject_cast<QPushButton*>(widget)) {
                        button->setEnabled(checked);
                        button->setStyleSheet(
                            QString("background-color: %1; color: %2")
                                .arg(bg.name(), fg.name()));
                    } else if (auto* combobox = qobject_cast<QComboBox*>(widget)) {
                        combobox->setEnabled(checked);
                        combobox->setStyleSheet(
                            QString("background-color: %1; color: %2;")
                                .arg(bg.name(), fg.name()));
                    }
                }

                QMenu* instruments_menu = im->get_menu();
                instruments_menu->setEnabled(checked);
                instruments_menu->setStyleSheet("background-color: black; color: white;");
                instruments_menu->addSeparator();

                am->get_moving_graphics_view_action()->setEnabled(checked);

            } else if (text_action == "Панорамирование сцены") {
                if (checked)
                    graphicsView->setDragMode(QGraphicsView::ScrollHandDrag);
                else
                    graphicsView->setDragMode(QGraphicsView::NoDrag);
            } else {
                sound_enabled = checked;
            }
        });
    }
}

void ApplicationWindow::setupFilesMenu() {
    if (QMenu* create_menu = fam->get_create_menu()) {
        for (QAction* action : create_menu->actions()) {
            const QString type_image = action->text().toLower();

            connect(action, &QAction::triggered, this, [this, type_image]() {
                if (sound_enabled) QApplication::beep();

                CreateInFormatWindow cifw(this, type_image);
                if (cifw.exec() == QDialog::Accepted) {
                    status->showMessage(cifw.is_created()
                                        ? "Файл был успешно создан"
                                        : "Не удалось создать файл", 5000);
                } else {
                    status->showMessage("Действие отменено", 5000);
                }
            });
        }
    }

    connect(fam->get_open_action(), &QAction::triggered, this, [this]() {
        if (sound_enabled) QApplication::beep();

        OpenFileWindow ofw(this, scene);
        if (ofw.exec() == QDialog::Accepted) {
            const auto items = scene->items();
            for (QGraphicsItem* item : items) {
                scene->removeItem(item);
                delete item;
            }
            scene->addItem(ofw.get_pixmap_item());
        }
    });

    connect(fam->get_save_action(), &QAction::triggered, this, [this]() {
        if (sound_enabled) QApplication::beep();

        SaveInFileWindow sifw(this, scene, graphicsBackgroundColor);
        if (sifw.exec() == QDialog::Accepted) {
            if (sifw.is_saved())
                status->showMessage("Изображение было успешно сохранено", 5000);
        } else {
            status->showMessage("Действие отменено", 5000);
        }
    });
}

void ApplicationWindow::setupScaleMenu() {
    if (QMenu* scale_scene_menu = sm->get_scale_scene_menu()) {
        for (QAction* action : scale_scene_menu->actions()) {
            const QString configure_scene = action->text();

            connect(action, &QAction::triggered, this, [this, configure_scene]() {
                if (configure_scene == "Увеличить") {
                    graphicsView->scale(1.2, 1.2);
                } else if (configure_scene == "Уменьшить") {
                    graphicsView->scale(1 / 1.2, 1 / 1.2);
                } else {
                    graphicsView->resetTransform();
                }
            });
        }
    }

    if (QMenu* scale_font_menu = sm->get_scale_font_menu()) {
        for (QAction* action : scale_font_menu->actions()) {
            const QString configure_font = action->text();

            connect(action, &QAction::triggered, this, [this, configure_font]() {
                QFont font = QApplication::font();

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

                current_font = font;
                QApplication::setFont(font);

                const auto widgets = findChildren<QWidget*>();
                for (QWidget* widget : widgets)
                    widget->setFont(font);
                setFont(font);
            });
        }
    }
}

void ApplicationWindow::setupInstrumentsMenu() {
    QMenu* instruments_menu = im->get_menu();
    if (!instruments_menu) return;

    for (QAction* action : instruments_menu->actions()) {
        if (action->text() == "Сетка") {
            QMenu* grid_menu = action->menu();
            if (!grid_menu) continue;

            connect(grid_menu, &QMenu::triggered, this, [this](QAction* grid_action) {
                if (grid_action->text() == "Сбросить сетку") {
                    scene->set_grid_visible(false);
                    return;
                }

                bool converted = false;
                const int size = grid_action->text().left(2).toInt(&converted);
                if (!converted) {
                    status->showMessage("Ошибка считывания размера для сетки");
                    return;
                }
                scene->set_grid_size(size);
                scene->set_grid_visible(true);
            });
        } else if (action->text() == "Контур") {
            QMenu* circuit_menu = action->menu();
            if (!circuit_menu) continue;

            for (QAction* circuit_action : circuit_menu->actions()) {

                if (circuit_action->text() == "Стили линий") {
                    QMenu* circuit_line_menu = circuit_action->menu();
                    if (!circuit_line_menu) continue;

                    connect(circuit_line_menu, &QMenu::triggered, this,
                            [this](QAction* line_action) {
                                auto* slcl = new StyleLineCircuitLists(line_action->text());

                                const auto graphics_items = scene->items();
                                if (graphics_items.isEmpty()) {
                                    status->showMessage("Сцена пустая для настройки стилей линий");
                                    return;
                                }

                                bool found = false;
                                for (QGraphicsItem* item : graphics_items) {
                                    if (auto* shape = qgraphicsitem_cast<CustomShapeItem*>(item)) {
                                        shape->configure_pen_style(slcl->get_pen_style());
                                        found = true;
                                    }
                                }
                                if (!found)
                                    prototypeItem->configure_pen_style(slcl->get_pen_style());

                                delete slcl;
                            });

                } else if (circuit_action->text() == "Стили концов") {
                    QMenu* circuit_edge_menu = circuit_action->menu();
                    if (!circuit_edge_menu) continue;

                    connect(circuit_edge_menu, &QMenu::triggered, this,
                            [this](QAction* edge_action) {
                                auto* secl = new StyleEdgeCircuitLists(edge_action->text());

                                const auto graphics_items = scene->items();
                                if (graphics_items.isEmpty()) {
                                    status->showMessage("Сцена пустая для настройки стилей концов");
                                    return;
                                }

                                bool found = false;
                                for (QGraphicsItem* item : graphics_items) {
                                    if (auto* shape = qgraphicsitem_cast<CustomShapeItem*>(item)) {
                                        shape->configure_pen_cap_style(secl->get_pen_cap_style());
                                        found = true;
                                    }
                                }
                                if (!found)
                                    prototypeItem->configure_pen_cap_style(secl->get_pen_cap_style());

                                delete secl;
                            });

                } else if (circuit_action->text() == "Стили соединений") {
                    QMenu* join_menu = circuit_action->menu();
                    if (!join_menu) continue;

                    connect(join_menu, &QMenu::triggered, this,
                            [this](QAction* join_action) {
                                auto* sjcl = new StyleJoinCircuitLists(join_action->text());

                                const auto graphics_items = scene->items();
                                if (graphics_items.isEmpty()) {
                                    status->showMessage("Сцена пустая для настройки стилей соединений");
                                    return;
                                }

                                bool found = false;
                                for (QGraphicsItem* item : graphics_items) {
                                    if (auto* shape = qgraphicsitem_cast<CustomShapeItem*>(item)) {
                                        shape->configure_pen_join_style(sjcl->get_pen_join_style());
                                        found = true;
                                    }
                                }
                                if (!found)
                                    prototypeItem->configure_pen_join_style(sjcl->get_pen_join_style());

                                delete sjcl;
                            });

                } else if (circuit_action->text().contains("Сбросить", Qt::CaseInsensitive)) {
                    connect(circuit_action, &QAction::triggered, this, [this]() {
                        const auto graphics_items = scene->items();
                        bool found = false;

                        for (QGraphicsItem* item : graphics_items) {
                            if (auto* shape = qgraphicsitem_cast<CustomShapeItem*>(item)) {
                                shape->configure_pen_style(Qt::SolidLine);
                                shape->configure_pen_cap_style(Qt::SquareCap);
                                shape->configure_pen_join_style(Qt::BevelJoin);
                                found = true;
                            }
                        }
                        if (!found) {
                            prototypeItem->configure_pen_style(Qt::SolidLine);
                            prototypeItem->configure_pen_cap_style(Qt::SquareCap);
                            prototypeItem->configure_pen_join_style(Qt::BevelJoin);
                        }
                    });
                }
            }
        } else if (action->text() == "Заливка") {
            QMenu* brush_menu = action->menu();
            if (!brush_menu) continue;

            for (QAction* brush_action : brush_menu->actions()) {

                if (brush_action->text() == "Стили") {
                    QMenu* brush_style_menu = brush_action->menu();
                    if (!brush_style_menu) continue;

                    connect(brush_style_menu, &QMenu::triggered, this,
                            [this](QAction* brush_style_action) {
                                auto* sgbl = new StyleBrushLists(brush_style_action->text());

                                const auto graphics_items = scene->items();
                                if (graphics_items.isEmpty()) {
                                    status->showMessage("Сцена пустая для настройки стилей градиента");
                                    return;
                                }

                                bool found = false;
                                for (QGraphicsItem* item : graphics_items) {
                                    if (auto* shape = qgraphicsitem_cast<CustomShapeItem*>(item)) {
                                        shape->configure_brush_style(sgbl->get_brush_style());
                                        found = true;
                                    }
                                }
                                if (!found)
                                    prototypeItem->configure_brush_style(sgbl->get_brush_style());

                                delete sgbl;
                            });

                } else if (brush_action->text().contains("Сбросить", Qt::CaseInsensitive)) {
                    connect(brush_action, &QAction::triggered, this, [this]() {
                        const auto graphics_items = scene->items();
                        if (graphics_items.isEmpty()) {
                            status->showMessage("Сцена пустая для сброса стилей заливки");
                            return;
                        }

                        if (graphics_items.size() > 1) {
                            for (QGraphicsItem* item : graphics_items) {
                                if (auto* shape = qgraphicsitem_cast<CustomShapeItem*>(item))
                                    shape->configure_brush_style(Qt::SolidPattern);
                            }
                            return;
                        }

                        prototypeItem->configure_brush_style(Qt::SolidPattern);
                    });
                }
            }
        }
    }
}

void ApplicationWindow::setupCommonSettingsMenu()
{
    QMenu* common_settings_menu = csm->get_menu();
    if (!common_settings_menu) return;

    for (QAction* action : common_settings_menu->actions()) {
        if (action->text() == "Вид приложения") {
            QMenu* style_menu = action->menu();
            if (!style_menu) continue;

            connect(style_menu, &QMenu::triggered, this, [this](QAction* style_action) {
                QStyle* style = QStyleFactory::create(style_action->text());
                if (!style) {
                    status->showMessage("Не удалось установить вид для приложения", 5000);
                    return;
                }
                QApplication::setStyle(style);
            });
        } else if (action->text() == "Оформление окна") {
            QMenu* design_window_menu = action->menu();
            if (!design_window_menu) continue;

            connect(design_window_menu, &QMenu::triggered, this, [this](QAction* design_window_action) {

                const auto theme_style_lists = csm->get_theme_style_lists();
                if (!theme_style_lists.contains(design_window_action->text())) return;

                const QPair<QString, QString> tool_bar_pair =
                    theme_style_lists[design_window_action->text()].at(0);
                const QPair<QString, QString> window_pair =
                    theme_style_lists[design_window_action->text()].at(1);

                toolBar->setStyleSheet(QString("background-color: %1; color: %2;")
                                           .arg(tool_bar_pair.first, tool_bar_pair.second));

                for (QAction* tb_action : toolBar->actions()) {
                    if (QMenu* type_menu = tb_action->menu()) {
                        type_menu->setStyleSheet(QString("background-color: %1; color: %2;")
                                                     .arg(tool_bar_pair.first,
                                                          tool_bar_pair.second));
                    } else {
                        searchField->setStyleSheet(QString("background-color: %1; color: %2;")
                                                       .arg(tool_bar_pair.first,
                                                            tool_bar_pair.second));
                    }
                }

                setStyleSheet(QString("background-color: %1; color: %2;")
                                  .arg(window_pair.first, window_pair.second));
            });
        } else if (action->text() == "Настройка шрифта") {
            connect(action, &QAction::triggered, this, [this]() {
                ConfigureFontWindow cfw;
                if (cfw.exec() == QDialog::Accepted) {
                    const QFont set_font = cfw.get_font();

                    const auto all_widgets = findChildren<QWidget*>();
                    for (QWidget* widget : all_widgets)
                        widget->setFont(set_font);
                    setFont(set_font);
                } else {
                    status->showMessage("Действие отменено", 5000);
                }
            });
        } else if (action->text() == "Возврат по умолчанию") {
            connect(action, &QAction::triggered, this, [this]() {
                toolBar->setStyleSheet("background-color: black; color: white;");
                setStyleSheet("background-color: white; color: black;");

                const auto all_widgets = findChildren<QWidget*>();
                for (QWidget* widget : all_widgets)
                    widget->setFont(original_font);
                setFont(original_font);
            });
        }
    }
}

void ApplicationWindow::setupReferenceMenu()
{
    QMenu* reference_menu = rm->get_menu();
    if (!reference_menu) return;

    QAction* about_program_action = rm->get_about_program_action();
    QToolButton* github_instructions_tool_button = rm->get_github_instructions_tool_button();

    if (about_program_action) {
        connect(about_program_action, &QAction::triggered, this, [this]() {
            QMessageBox::information(this,
                                     "Информация",
                                     "Приложение реализовано с помощью следующего стека технологий:\n"
                                     "1) Язык программирования С++17\n"
                                     "2) Qt Framework 6.11.2");
        });
    }

    if (github_instructions_tool_button) {
        connect(github_instructions_tool_button, &QToolButton::clicked, this, []() {
            QDesktopServices::openUrl(
                QUrl("https://github.com/Frolotey1/GraphicsEditor/tree/main/%D0%94%D0%BE%D0%BA%D1%83%D0%BC%D0%B5%D0%BD%D1%82%D0%B0%D1%86%D0%B8%D1%8F"));
        });

        if (QMenu* tool_button_menu = github_instructions_tool_button->menu()) {
            connect(tool_button_menu, &QMenu::triggered, this, [](QAction* tool_action) {
                const QString t = tool_action->text();
                if (t == "Панель окна") {
                    QDesktopServices::openUrl(QUrl(
                        "https://github.com/Frolotey1/GraphicsEditor/blob/main/%D0%94%D0%BE%D0%BA%D1%83%D0%BC%D0%B5%D0%BD%D1%82%D0%B0%D1%86%D0%B8%D1%8F/%D0%9F%D0%B0%D0%BD%D0%B5%D0%BB%D1%8C%20%D0%BE%D0%BA%D0%BD%D0%B0.md"));
                } else if (t == "Графическая сцена") {
                    QDesktopServices::openUrl(QUrl(
                        "https://github.com/Frolotey1/GraphicsEditor/blob/main/%D0%94%D0%BE%D0%BA%D1%83%D0%BC%D0%B5%D0%BD%D1%82%D0%B0%D1%86%D0%B8%D1%8F/%D0%93%D1%80%D0%B0%D1%84%D0%B8%D1%87%D0%B5%D1%81%D0%BA%D0%B0%D1%8F%20%D1%81%D1%86%D0%B5%D0%BD%D0%B0.md"));
                } else {
                    QDesktopServices::openUrl(QUrl(
                        "https://github.com/Frolotey1/GraphicsEditor/blob/main/%D0%94%D0%BE%D0%BA%D1%83%D0%BC%D0%B5%D0%BD%D1%82%D0%B0%D1%86%D0%B8%D1%8F/%D0%94%D0%B5%D0%B9%D1%81%D1%82%D0%B2%D0%B8%D1%8F%20%D0%BD%D0%B0%D0%B4%20%D0%BE%D0%B1%D1%8A%D0%B5%D0%BA%D1%82%D0%B0%D0%BC%D0%B8%20%D0%BD%D0%B0%20%D1%81%D1%86%D0%B5%D0%BD%D0%B5.md"));
                }
            });
        }
    }
}

void ApplicationWindow::setupPdfMenu()
{
    QMenu* pdf_menu = fam->get_pdf_menu();
    if (!pdf_menu) return;

    QToolButton* export_button = fam->get_tool_button();
    if (export_button) {
        connect(export_button, &QToolButton::clicked, this, [this]() {
            if (sound_enabled) QApplication::beep();

            PDFActionsWindow paw(this, "Экспорт", scene);
            if (paw.exec() == QDialog::Accepted) {
                status->showMessage(paw.is_exported()
                                    ? "Изображение было успешно экспортировано"
                                    : "Не удалось экспортировать изображение", 5000);
            } else {
                status->showMessage("Действие отменено", 5000);
            }
        });

        if (QMenu* export_button_sub_menu = export_button->menu()) {
            connect(export_button_sub_menu, &QMenu::triggered, this, [this](QAction* size_action) {

            PDFActionsWindow paw(this, "Экспорт", scene, size_action->text());
            if (paw.exec() == QDialog::Accepted) {
                status->showMessage(paw.is_exported()
                                    ? "Изображение было успешно экспортировано"
                                    : "Не удалось экспортировать изображение", 5000);
            } else {
                status->showMessage("Действие отменено", 5000);
            }
        });
        }
    }

    if (QAction* import_action = fam->get_import_action()) {
        connect(import_action, &QAction::triggered, this, [this]() {
            PDFActionsWindow paw(this, "Импорт", scene);
            if (paw.exec() == QDialog::Accepted) {
                status->showMessage(paw.is_imported()
                                    ? "Изображение было успешно импортировано"
                                    : "Не удалось импортировать изображение", 5000);
            } else {
                status->showMessage("Действие отменено", 5000);
            }
        });
    }
}

void ApplicationWindow::setupObjectSettings() {
    connect(configureObjectComboBox, &QComboBox::currentTextChanged,
            this, &ApplicationWindow::onObjectChanged);
    connect(configureCircuitComboBox, &QComboBox::currentTextChanged,
            this, &ApplicationWindow::onCircuitChanged);
    connect(configureBrushComboBox, &QComboBox::currentTextChanged,
            this, &ApplicationWindow::onBrushChanged);
    connect(configureColorWindowComboBox, &QComboBox::currentTextChanged,
            this, &ApplicationWindow::onColorWindowChanged);
    connect(configureTextFontComboBox, &QComboBox::currentTextChanged,
            this, &ApplicationWindow::onTextFontChanged);
}

void ApplicationWindow::onObjectChanged(const QString& text) {
    objectName = text;
    if (objectName == "Прямоугольник") prototypeItem->set_shape(ShapeType::Rectangle);
    else if (objectName == "Линия") prototypeItem->set_shape(ShapeType::Line);
    else if (objectName == "Эллипс") prototypeItem->set_shape(ShapeType::Ellipse);
    else if (objectName == "Многоугольник") prototypeItem->set_shape(ShapeType::Polygon);
    else if (objectName == "Текст") {
        TextObject to;
        if (to.exec() == QDialog::Accepted) {
            const QString result = to.get_text();
            if (!result.isEmpty()) {
                prototypeItem->set_text(result);
                prototypeItem->set_pen_color("black");
                prototypeItem->set_shape(ShapeType::Text);
            }
        } else {
            status->showMessage("Действие отменено", 5000);
        }
    } else if (objectName == "Создать свой объект") {
        prototypeItem->set_shape(ShapeType::CustomPath);
        prototypeItem->start_custom_path();
    }
}

void ApplicationWindow::onCircuitChanged(const QString& text) {
    circuitName = osl->get_circuit(text);
    if (circuitName == "Создать свой цвет") {
        CircuitOwnColorWindow cocw;
        if (cocw.exec() == QDialog::Accepted)
            prototypeItem->set_pen_color(cocw.get_circuit_color());
        else
            status->showMessage("Не удалось задать цвет для контура", 5000);
        return;
    }
    prototypeItem->set_pen_color(circuitName);
}

void ApplicationWindow::onBrushChanged(const QString& text) {
    brushName = osl->get_brush(text);
    if (brushName == "Создать свой цвет") {
        BrushOwnColorWindow bocw;
        if (bocw.exec() == QDialog::Accepted)
            prototypeItem->set_brush_color(bocw.get_brush_color());
        return;
    }
    prototypeItem->set_brush_color(brushName);
}

void ApplicationWindow::onColorWindowChanged(const QString& text) {
    colorWindowName = osl->get_color_window(text);
    if (colorWindowName == "Создать свой цвет") {
        ConfigureGraphicsColorWindow cgcw;
        if (cgcw.exec() == QDialog::Accepted)
            graphicsView->setStyleSheet(QString("background-color: %1;")
                                            .arg(cgcw.get_graphics_background_color()));
        return;
    }
    graphicsBackgroundColor = colorWindowName;
    graphicsView->setStyleSheet(QString("background-color: %1;").arg(colorWindowName));
}

void ApplicationWindow::onTextFontChanged(const QString& text) {
    const auto items = scene->items();
    bool exist = true;
    for (QGraphicsItem* it : items) {
        if (auto* shape = qgraphicsitem_cast<CustomShapeItem*>(it)) {
            if (shape->get_current_shape() != ShapeType::Text) exist = false;
        }
    }
    if (!exist) {
        status->showMessage("Текст отсутствует для настройки шрифта", 5000);
        return;
    }

    textFontName = osl->get_text_font(text);
    if (textFontName == "Создать свой шрифт") {
        ConfigureFontWindow cfw;
        if (cfw.exec() == QDialog::Accepted) {
            const QFont f = cfw.get_font();
            for (QGraphicsItem* it : items)
                if (auto* shape = qgraphicsitem_cast<CustomShapeItem*>(it))
                    if (shape->get_current_shape() == ShapeType::Text)
                        shape->set_font_text_style(f);
            prototypeItem->set_font_text_style(f);
        } else {
            status->showMessage("Действие отменено", 5000);
        }
        return;
    }

    for (QGraphicsItem* it : items)
        if (auto* shape = qgraphicsitem_cast<CustomShapeItem*>(it))
            if (shape->get_current_shape() == ShapeType::Text)
                shape->set_font_text_style(QFont(textFontName));
    prototypeItem->set_font_text_style(QFont(textFontName));
}

void ApplicationWindow::setupButtons() {
    connect(addFigureButton, &QPushButton::clicked,
            this, &ApplicationWindow::onAddFigure);
    connect(removeButton, &QPushButton::clicked,
            this, &ApplicationWindow::onRemoveFigure);
    connect(removeAllFiguresButton, &QPushButton::clicked,
            this, &ApplicationWindow::onRemoveAllFigures);
    connect(endDrawingButton, &QPushButton::clicked,
            this, &ApplicationWindow::onEndDrawing);
}

void ApplicationWindow::onAddFigure() {
    auto* new_shape = new CustomShapeItem();

    new_shape->set_shape(prototypeItem->get_current_shape());
    new_shape->set_brush_color(prototypeItem->get_brush_color());
    new_shape->set_pen_color(prototypeItem->get_pen_color());
    new_shape->set_text(prototypeItem->get_text());

    const qreal x = QRandomGenerator::global()->bounded(0, 400);
    const qreal y = QRandomGenerator::global()->bounded(0, 300);

    new_shape->setPos(x, y);
    scene->addItem(new_shape);
}

void ApplicationWindow::onRemoveAllFigures() {
    if (sound_enabled) QApplication::beep();

    const auto answer = QMessageBox::question(
        this, "Подтверждение",
        "Хотите ли сбросить все объекты на сцене?",
        QMessageBox::No | QMessageBox::Yes);

    if (answer == QMessageBox::No) {
        status->showMessage("Сброс всех фигур отменен", 5000);
        return;
    }

    const auto items = scene->items();
    if (items.isEmpty()) {
        status->showMessage("Сцена пустая для удаления фигур", 5000);
        return;
    }

    for (QGraphicsItem* it : items) {
        scene->removeItem(it);
        delete it;
    }

    prototypeItem = new CustomShapeItem();
    prototypeItem->set_shape(ShapeType::Rectangle);
    prototypeItem->set_pen_color(QColor(Qt::black).name());
    prototypeItem->set_brush_color(default_foreground_object_color);

    configureObjectComboBox->setCurrentIndex(0);
    configureCircuitComboBox->setCurrentIndex(0);
    configureBrushComboBox->setCurrentIndex(0);
}

void ApplicationWindow::onRemoveFigure() {
    const auto items = scene->items();
    if (items.isEmpty()) {
        status->showMessage("Сцена пустая для удаления фигуры", 5000);
        return;
    }

    bool found = false;
    for (QGraphicsItem* it : items) {
        if (it == prototypeItem) continue;
        if (it->isSelected()) {
            scene->removeItem(it);
            delete it;
            found = true;
            break;
        }
    }

    status->showMessage(found ? "Фигура была удалена успешно"
                              : "Не удалось удалить фигуру со сцены", 5000);
}

void ApplicationWindow::onEndDrawing() {
    if (prototypeItem->get_current_shape() != ShapeType::CustomPath) {
        status->showMessage("Действие применяется только к собственным объектам!", 5000);
        return;
    }
    prototypeItem->finish_custom_path();
}

void ApplicationWindow::setupOrderButtons() {
    auto* order_graphics_imagination =
        new QHBoxLayout(oob->get_common_object_buttons_name());

    auto* order_buttons_layout  = new QVBoxLayout(oob->get_order_buttons_name());
    auto* graphics_scene_layout = new QHBoxLayout(oob->get_common_graphics_scene_name());

    for (QPushButton* b : oob->get_order_buttons())
        order_buttons_layout->addWidget(b);

    for (QPushButton* button : oob->get_order_buttons()) {
        const QString type_order_button = button->text();

        connect(button, &QPushButton::clicked, this, [this, type_order_button]() {
            QList<CustomShapeItem*> all_shapes;
            QList<CustomShapeItem*> selected_shapes;

            for (QGraphicsItem* item : scene->items()) {
                if (auto* shape = qgraphicsitem_cast<CustomShapeItem*>(item)) {
                    all_shapes.append(shape);
                    if (shape->isSelected()) selected_shapes.append(shape);
                }
            }

            if (all_shapes.isEmpty()) {
                status->showMessage("Сцена пустая для настройки порядка", 5000);
                return;
            }
            if (selected_shapes.isEmpty()) {
                status->showMessage("Нет выделенных фигур", 5000);
                return;
            }

            qreal min_z = 0, max_z = 0;
            for (CustomShapeItem* s : all_shapes) {
                min_z = qMin(min_z, s->zValue());
                max_z = qMax(max_z, s->zValue());
            }

            for (CustomShapeItem* s : selected_shapes) {
                const qreal r = s->rotation();
                if(type_order_button == "Поворот вправо на 90°")
                    s->setRotation(r + 90);
                else if (type_order_button == "Поворот влево на 90°")
                    s->setRotation(r - 90);
                else if (type_order_button == "Поворот на 45°")
                    s->setRotation(r + 45);
                else if (type_order_button == "Передний план") {
                    s->setZValue(max_z + 1);
                    max_z += 1;
                }
                else if (type_order_button == "Задний план") {
                    s->setZValue(min_z - 1);
                    min_z -= 1;
                }
                else if (type_order_button == "Выше на один")
                    s->setZValue(s->zValue() + 1);
                else if (type_order_button == "Ниже на один")
                    s->setZValue(s->zValue() - 1);

                s->update();
            }
        });
    }

    graphics_scene_layout->addWidget(graphicsView);

    order_graphics_imagination->addWidget(oob->get_order_buttons_name());
    order_graphics_imagination->addWidget(oob->get_common_graphics_scene_name());
}

void ApplicationWindow::saveSettings() {
    QSettings settings;
    settings.setValue("window/background-color",background_color);
    settings.setValue("window/text-color",foreground_color);
    settings.setValue("window/font-size",QApplication::font().pointSize());
    settings.setValue("window/font", QApplication::font());
}

void ApplicationWindow::setupConnections() {
    connect(qApp, &QCoreApplication::aboutToQuit, this, &ApplicationWindow::saveSettings);
}

ApplicationWindow::~ApplicationWindow() = default;
