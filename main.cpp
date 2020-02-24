#include <QApplication>
#include "latinkaConverter.h"
#include "mainWindow.h"

int main(int argc, char** argv)
{
    QApplication app(argc, argv);

    MainWindow w;
    w.show();

    return app.exec();
}
