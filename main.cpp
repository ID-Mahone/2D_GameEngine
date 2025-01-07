#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    MainWindow window;

    // Set the window title
    window.setWindowTitle("Shadows Call");

    window.show();

    return app.exec();
}
