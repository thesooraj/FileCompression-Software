#include "mainwindow.h"
#include "../huffman.h"
#include <fstream>
#include <sstream>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    setupUI();
    applyStyles();
    setAcceptDrops(true);
}

MainWindow::~MainWindow() {}

void MainWindow::setupUI() {
    setWindowTitle("Compressor");
    setMinimumSize(600, 500);

    QWidget* central = new QWidget(this);
    setCentralWidget(central);
    QVBoxLayout* mainLayout = new QVBoxLayout(central);
    mainLayout->setSpacing(15);
    mainLayout->setContentsMargins(30, 30, 30, 30);

    // Title
    titleLabel = new QLabel("🗜️ Compressor");
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setObjectName("titleLabel");
    mainLayout->addWidget(titleLabel);

    // Drop zone
    dropLabel = new QLabel("📁 Drag & Drop File Here\nor click Browse");
    dropLabel->setAlignment(Qt::AlignCenter);
    dropLabel->setObjectName("dropLabel");
    dropLabel->setMinimumHeight(80);
    mainLayout->addWidget(dropLabel);

    // Input file row
    QHBoxLayout* inputLayout = new QHBoxLayout();
    QLabel* inputLabel = new QLabel("Input File:");
    inputLabel->setFixedWidth(80);
    inputFileEdit = new QLineEdit();
    inputFileEdit->setPlaceholderText("Select input file...");
    browseInputBtn = new QPushButton("Browse");
    browseInputBtn->setObjectName("browseBtn");
    inputLayout->addWidget(inputLabel);
    inputLayout->addWidget(inputFileEdit);
    inputLayout->addWidget(browseInputBtn);
    mainLayout->addLayout(inputLayout);

    // Output file row
    QHBoxLayout* outputLayout = new QHBoxLayout();
    QLabel* outputLabel = new QLabel("Output File:");
    outputLabel->setFixedWidth(80);
    outputFileEdit = new QLineEdit();
    outputFileEdit->setPlaceholderText("Select output file...");
    browseOutputBtn = new QPushButton("Browse");
    browseOutputBtn->setObjectName("browseBtn");
    outputLayout->addWidget(outputLabel);
    outputLayout->addWidget(outputFileEdit);
    outputLayout->addWidget(browseOutputBtn);
    mainLayout->addLayout(outputLayout);

    // Progress bar
    progressBar = new QProgressBar();
    progressBar->setValue(0);
    progressBar->setTextVisible(true);
    mainLayout->addWidget(progressBar);

    // Stats row
    QHBoxLayout* statsLayout = new QHBoxLayout();
    originalSizeLabel = new QLabel("Original: 0 bytes");
    originalSizeLabel->setObjectName("statsLabel");
    compressedSizeLabel = new QLabel("Compressed: 0 bits");
    compressedSizeLabel->setObjectName("statsLabel");
    ratioLabel = new QLabel("Ratio: 0%");
    ratioLabel->setObjectName("statsLabel");
    statsLayout->addWidget(originalSizeLabel);
    statsLayout->addWidget(compressedSizeLabel);
    statsLayout->addWidget(ratioLabel);
    mainLayout->addLayout(statsLayout);

    // Buttons row
    QHBoxLayout* btnLayout = new QHBoxLayout();
    compressBtn = new QPushButton("🗜️ COMPRESS");
    compressBtn->setObjectName("compressBtn");
    compressBtn->setMinimumHeight(45);
    decompressBtn = new QPushButton("📂 DECOMPRESS");
    decompressBtn->setObjectName("decompressBtn");
    decompressBtn->setMinimumHeight(45);
    btnLayout->addWidget(compressBtn);
    btnLayout->addWidget(decompressBtn);
    mainLayout->addLayout(btnLayout);

    // Status label
    statusLabel = new QLabel("Ready");
    statusLabel->setAlignment(Qt::AlignCenter);
    statusLabel->setObjectName("statusLabel");
    mainLayout->addWidget(statusLabel);

    // Connect signals
    connect(browseInputBtn, &QPushButton::clicked, this, &MainWindow::browseInputFile);
    connect(browseOutputBtn, &QPushButton::clicked, this, &MainWindow::browseOutputFile);
    connect(compressBtn, &QPushButton::clicked, this, &MainWindow::compressFile);
    connect(decompressBtn, &QPushButton::clicked, this, &MainWindow::decompressFile);
}

void MainWindow::applyStyles() {
    setStyleSheet(R"(
        QMainWindow {
            background-color: #1e1e2e;
        }
        QWidget {
            background-color: #1e1e2e;
            color: #cdd6f4;
            font-family: Arial;
            font-size: 14px;
        }
        #titleLabel {
            font-size: 22px;
            font-weight: bold;
            color: #89b4fa;
            padding: 10px;
        }
        #dropLabel {
            border: 2px dashed #89b4fa;
            border-radius: 10px;
            color: #89b4fa;
            font-size: 14px;
            padding: 20px;
        }
        QLineEdit {
            background-color: #313244;
            border: 1px solid #45475a;
            border-radius: 6px;
            padding: 8px;
            color: #cdd6f4;
        }
        QLineEdit:focus {
            border: 1px solid #89b4fa;
        }
        #browseBtn {
            background-color: #45475a;
            border: none;
            border-radius: 6px;
            padding: 8px 15px;
            color: #cdd6f4;
        }
        #browseBtn:hover {
            background-color: #585b70;
        }
        #compressBtn {
            background-color: #89b4fa;
            border: none;
            border-radius: 8px;
            padding: 10px;
            color: #1e1e2e;
            font-weight: bold;
            font-size: 15px;
        }
        #compressBtn:hover {
            background-color: #74c7ec;
        }
        #decompressBtn {
            background-color: #a6e3a1;
            border: none;
            border-radius: 8px;
            padding: 10px;
            color: #1e1e2e;
            font-weight: bold;
            font-size: 15px;
        }
        #decompressBtn:hover {
            background-color: #94e2d5;
        }
        QProgressBar {
            border: none;
            border-radius: 6px;
            background-color: #313244;
            height: 20px;
            text-align: center;
        }
        QProgressBar::chunk {
            background-color: #89b4fa;
            border-radius: 6px;
        }
        #statsLabel {
            background-color: #313244;
            border-radius: 8px;
            padding: 10px;
            text-align: center;
        }
        #statusLabel {
            color: #a6e3a1;
            font-size: 13px;
        }
    )");
}

void MainWindow::dragEnterEvent(QDragEnterEvent* event) {
    if (event->mimeData()->hasUrls()) {
        event->acceptProposedAction();
        dropLabel->setStyleSheet("border: 2px dashed #a6e3a1; border-radius: 10px; color: #a6e3a1; font-size: 14px; padding: 20px;");
    }
}

void MainWindow::dropEvent(QDropEvent* event) {
    QList<QUrl> urls = event->mimeData()->urls();
    if (!urls.isEmpty()) {
        inputFileEdit->setText(urls.first().toLocalFile());
        dropLabel->setStyleSheet("border: 2px dashed #89b4fa; border-radius: 10px; color: #89b4fa; font-size: 14px; padding: 20px;");
        statusLabel->setText("File loaded: " + urls.first().toLocalFile());
    }
}

void MainWindow::browseInputFile() {
    QString file = QFileDialog::getOpenFileName(this, "Select Input File");
    if (!file.isEmpty()) {
        inputFileEdit->setText(file);
    }
}

void MainWindow::browseOutputFile() {
    QString file = QFileDialog::getSaveFileName(this, "Select Output File");
    if (!file.isEmpty()) {
        outputFileEdit->setText(file);
    }
}

void MainWindow::updateStats(int originalSize, int compressedSize) {
    originalSizeLabel->setText("Original: " + QString::number(originalSize) + " bytes");
    compressedSizeLabel->setText("Compressed: " + QString::number(compressedSize) + " bits");
    float ratio = (float)compressedSize / (originalSize * 8) * 100;
    ratioLabel->setText("Ratio: " + QString::number(ratio, 'f', 1) + "%");
    progressBar->setValue((int)(100 - ratio));
}

void MainWindow::compressFile() {
    QString inputPath = inputFileEdit->text();
    QString outputPath = outputFileEdit->text();

    if (inputPath.isEmpty() || outputPath.isEmpty()) {
        statusLabel->setText("⚠️ Please select input and output files!");
        return;
    }

    std::ifstream inFile(inputPath.toStdString());
    if (!inFile.is_open()) {
        statusLabel->setText("❌ Cannot open input file!");
        return;
    }

    std::string text((std::istreambuf_iterator<char>(inFile)),
                      std::istreambuf_iterator<char>());
    inFile.close();

    std::unordered_map<char, int> freqMap;
    buildFrequencyMap(text, freqMap);
    Node* root = buildHuffmanTree(freqMap);

    std::unordered_map<char, std::string> codes;
    buildCodes(root, "", codes);

    std::string compressed = compress(text, codes);

    std::ofstream outFile(outputPath.toStdString());
    outFile << compressed;
    outFile.close();

    updateStats(text.size(), compressed.size());
    statusLabel->setText("✅ File compressed successfully!");
    deleteTree(root);
}

void MainWindow::decompressFile() {
    QString inputPath = inputFileEdit->text();
    QString outputPath = outputFileEdit->text();

    if (inputPath.isEmpty() || outputPath.isEmpty()) {
        statusLabel->setText("⚠️ Please select input and output files!");
        return;
    }

    statusLabel->setText("⚠️ Decompression requires original frequency data!");
}