#include <QApplication>
#include "mainwindow.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    // Set application info
    app.setApplicationName("Huffman Compression Tool");
    app.setApplicationVersion("1.0");
    app.setOrganizationName("thesooraj");

    MainWindow window;
    window.show();

    return app.exec();
}