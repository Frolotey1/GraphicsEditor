#include "QApplication"
#include "QStyleFactory"
#include "QSettings"
#include "QFont"
#include "include/Application/ApplicationWindow.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    QApplication::setStyle(QStyleFactory::create(QApplication::style()->objectName()));
    QApplication::setOrganizationName("GraphicsApplication");
    QApplication::setApplicationName("GraphicsEditor");

    QSettings settings;
    const int font_size = settings.value("window/font-size", 10).toInt();
    QFont f = settings.value("window/font", QApplication::font()).value<QFont>();
    if (font_size > 2) f.setPointSize(font_size);
    app.setFont(f);

    ApplicationWindow window;
    window.show();

    return app.exec();
}