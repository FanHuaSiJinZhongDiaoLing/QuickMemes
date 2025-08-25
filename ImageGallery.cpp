#include "ImageGallery.h"
#include "SharedData.h"
#include <QDir>
#include <QRegularExpression>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMouseEvent>
#include <QClipboard>
#include <QDebug>
#include <QScreen>

// ====================== ImageGallery =========================

ImageGallery::ImageGallery(QWidget* parent)
    : QWidget(parent)
{
    scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);

    scrollWidget = new QWidget(scrollArea);
    scrollArea->setWidget(scrollWidget);

    mainLayout = new QVBoxLayout(scrollWidget);
    mainLayout->setAlignment(Qt::AlignTop);
    scrollWidget->setLayout(mainLayout);

    QVBoxLayout* outerLayout = new QVBoxLayout(this);
    outerLayout->addWidget(scrollArea);
    setLayout(outerLayout);

    reloadSettings();
}

void ImageGallery::reloadLayout()
{
    reloadImages(currentFolderPath);
}

void ImageGallery::reloadImages(const QString& folderPath)
{
    currentFolderPath = folderPath;
    clearImages();

    QString searchPattern = QString::fromStdString(SharedData::getInstance()->searchStr());
    QRegularExpression regex(searchPattern, QRegularExpression::CaseInsensitiveOption);

    QDir dir(folderPath);
    QStringList imageFiles = dir.entryList(QDir::Files);

    int numPerLine = SharedData::getInstance()->numPerLine();
    int gap = SharedData::getInstance()->picGap();
    int totalWidth = this->width();
    int imageSize = (totalWidth - (numPerLine - 1) * gap) / numPerLine;
    printf("Line= %d\n", numPerLine);
    printf("Gap= %d\n", gap);
    printf("TotalWidth= %d\n", totalWidth);
    printf("ImageSize= %d\n", imageSize);



    QHBoxLayout* currentRow = nullptr;
    int column = 0;

    for (const QString& file : imageFiles)
    {
        if (!regex.match(file).hasMatch()) continue;

        if (column % numPerLine == 0) {
            currentRow = new QHBoxLayout();
            currentRow->setSpacing(gap);
            mainLayout->addLayout(currentRow);
            rowLayouts.append(currentRow);
        }

        QWidget* imageWidget = createImageWidget(dir.absoluteFilePath(file), imageSize);
        currentRow->addWidget(imageWidget);
        column++;
    }
}

void ImageGallery::resizeEvent(QResizeEvent* event)
{
    QWidget::resizeEvent(event);
    reloadImages(currentFolderPath);
}

void ImageGallery::clearImages()
{
    while (QLayoutItem* child = mainLayout->takeAt(0)) {
        QLayout* rowLayout = child->layout();
        if (rowLayout) {
            // 清空每一行里的图片 widget
            while (QLayoutItem* item = rowLayout->takeAt(0)) {
                QWidget* widget = item->widget();
                if (widget) {
                    delete widget;
                }
                delete item;
            }
            delete rowLayout;
        }
        // 不要 delete child —— 因为我们只删除 rowLayout 和 item
    }
    rowLayouts.clear();
}


QWidget* ImageGallery::createImageWidget(const QString& filePath, int imageSize)
{
    return new ImageWidget(filePath, imageSize, this);
}

void ImageGallery::reloadSettings()
{
    setStyleSheet(QString("QWidget { background-color: %1; }")
        .arg(QString::fromStdString(SharedData::getInstance()->backgroundColor())));
    reloadImages(currentFolderPath);
}

// ====================== ImageWidget =========================

ImageWidget::ImageWidget(const QString& filePath, int imageSize, QWidget* parent)
    : QWidget(parent), imageLabel(new QLabel(this)), movie(nullptr),
    previewTimer(new QTimer(this)), filePath(filePath)
{
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(imageLabel);
    layout->setContentsMargins(0, 0, 0, 0);
    setLayout(layout);

    if (filePath.endsWith(".gif", Qt::CaseInsensitive)) {
        movie = new QMovie(filePath);
        imageLabel->setMovie(movie);
        movie->start();
    }
    else {
        QPixmap pix(filePath);
        originalPixmap = pix.scaled(imageSize, imageSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        imageLabel->setPixmap(originalPixmap);
    }

    previewTimer->setSingleShot(true);
    previewTimer->setInterval(500);
    connect(previewTimer, &QTimer::timeout, this, &ImageWidget::showPreview);
}

void ImageWidget::enterEvent(QEnterEvent*)
{
    previewTimer->start();
}

void ImageWidget::leaveEvent(QEvent*)
{
    previewTimer->stop();
    hidePreview();
}

void ImageWidget::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) {
        QClipboard* clipboard = QApplication::clipboard();
        clipboard->setText(filePath);
    }
}

void ImageWidget::showPreview()
{
    if (!previewPopup) {
        previewPopup = new ImagePreviewPopup(filePath);
    }

    QPoint globalPos = this->mapToGlobal(QPoint(width(), height() / 2));
    previewPopup->move(globalPos);
    previewPopup->show();
}

void ImageWidget::hidePreview()
{
    if (previewPopup) {
        previewPopup->close();
        previewPopup = nullptr;
    }
}

// ====================== ImagePreviewPopup =========================

ImagePreviewPopup::ImagePreviewPopup(const QString& filePath, QWidget* parent)
    : QWidget(parent), previewLabel(new QLabel(this)), movie(nullptr)
{
    setWindowFlags(Qt::Tool | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    setAttribute(Qt::WA_TranslucentBackground);
    setAttribute(Qt::WA_ShowWithoutActivating);
    setMouseTracking(true);

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setContentsMargins(2, 2, 2, 2);
    layout->addWidget(previewLabel);
    setLayout(layout);

    if (filePath.endsWith(".gif", Qt::CaseInsensitive)) {
        movie = new QMovie(filePath);
        previewLabel->setMovie(movie);
        movie->start();
    }
    else {
        QPixmap pix(filePath);
        QScreen* screen = QGuiApplication::primaryScreen();
        int previewSize = screen->availableGeometry().width() / 6;
        previewLabel->setPixmap(pix.scaled(previewSize, previewSize, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }

    adjustSize();
}

ImagePreviewPopup::~ImagePreviewPopup()
{
    if (movie) {
        movie->stop();
        delete movie;
    }
}

void ImagePreviewPopup::leaveEvent(QEvent*)
{
    close();
}
