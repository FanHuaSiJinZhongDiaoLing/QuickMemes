#ifndef SearchBar_H
#define SearchBar_H

#include <QWidget>

class QLineEdit;
class QPushButton;

class SearchBar : public QWidget {
    Q_OBJECT

public:
    explicit SearchBar(QWidget* parent = nullptr);

signals:
    void searchTriggered(const QString& text);

private slots:
    void onButtonClicked();

private:
    QLineEdit* edit;
    QPushButton* button;
};

#endif // SearchBar_H
