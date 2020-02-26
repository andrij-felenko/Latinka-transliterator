#include <QApplication>
#include "mainWindow.h"

int main(int argc, char** argv)
{
    qputenv("QT_AUTO_SCREEN_SCALE_FACTOR", "1");
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling); // DPI support
    QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps); //HiDPI pixmaps
    QApplication::setAttribute(Qt::AA_UseDesktopOpenGL);

    QApplication app(argc, argv);

    MainWindow w;
    w.show();

    return app.exec();
}
