#ifndef IMAGEGALLERY_H
#define IMAGEGALLERY_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPixmap>
#include <QMovie>
#include <QTimer>
#include <QList>
#include <QScrollArea>
#include <QClipboard>
#include <QApplication>
#include <QPointer>

class ImagePreviewPopup;

class ImageWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ImageWidget(const QString& filePath, int imageSize, QWidget* parent = nullptr);

protected:
    void enterEvent(QEnterEvent* event) override;
    void leaveEvent(QEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;

private slots:
    void showPreview();
    void hidePreview();

private:
    QLabel* imageLabel;
    QPixmap originalPixmap;
    QMovie* movie;
    QTimer* previewTimer;
    QString filePath;
    QPointer<ImagePreviewPopup> previewPopup;
};

class ImageGallery : public QWidget
{
    Q_OBJECT
public:
    explicit ImageGallery(QWidget* parent = nullptr);

    void reloadLayout();
    void reloadImages(const QString& folderPath);
    void reloadSettings();

protected:
    void resizeEvent(QResizeEvent* event) override;

private:
    void updateLayout();
    void clearImages();
    QWidget* createImageWidget(const QString& filePath, int imageSize);

    QVBoxLayout* mainLayout;
    QList<QHBoxLayout*> rowLayouts;
    QScrollArea* scrollArea;
    QWidget* scrollWidget;

    QString currentFolderPath;
};

class ImagePreviewPopup : public QWidget
{
    Q_OBJECT
public:
    explicit ImagePreviewPopup(const QString& filePath, QWidget* parent = nullptr);
    ~ImagePreviewPopup();

protected:
    void leaveEvent(QEvent* event) override;

private:
    QLabel* previewLabel;
    QMovie* movie;
};

#endif // IMAGEGALLERY_H
