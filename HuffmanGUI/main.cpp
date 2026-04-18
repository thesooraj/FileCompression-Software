#include <QApplication>
#include "mainwindow.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    // Set application info
    app.setApplicationName("Compressor");
    app.setApplicationVersion("1.0");
    app.setOrganizationName("thesooraj");

    MainWindow window;
    window.show();

    return app.exec();
}