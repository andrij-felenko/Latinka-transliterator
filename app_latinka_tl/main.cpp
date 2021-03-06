#include <QApplication>
#include <QIcon>
#include "mainWindow.h"
#include "darkTheme.h"

int main(int argc, char** argv)
{
    qputenv("QT_AUTO_SCREEN_SCALE_FACTOR", "1");
    QApplication::setAttribute(Qt::AA_UseDesktopOpenGL);

    QApplication app(argc, argv);
    setDarkTheme();

    MainWindow w;
    w.setWindowTitle("Латинкова транслітерація");
    w.setWindowIcon(QIcon(":/latynka.svg"));
    w.show();

    return app.exec();
}
