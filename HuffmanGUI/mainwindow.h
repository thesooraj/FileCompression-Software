#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QProgressBar>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFileDialog>
#include <QMessageBox>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

protected:
    void dragEnterEvent(QDragEnterEvent* event) override;
    void dropEvent(QDropEvent* event) override;

private slots:
    void browseInputFile();
    void browseOutputFile();
    void compressFile();
    void decompressFile();

private:
    // Input/Output fields
    QLineEdit* inputFileEdit;
    QLineEdit* outputFileEdit;

    // Buttons
    QPushButton* browseInputBtn;
    QPushButton* browseOutputBtn;
    QPushButton* compressBtn;
    QPushButton* decompressBtn;

    // Labels
    QLabel* titleLabel;
    QLabel* statusLabel;
    QLabel* originalSizeLabel;
    QLabel* compressedSizeLabel;
    QLabel* ratioLabel;
    QLabel* dropLabel;

    // Progress bar
    QProgressBar* progressBar;

    // Setup functions
    void setupUI();
    void applyStyles();
    void updateStats(int originalSize, int compressedSize);
};

#endif