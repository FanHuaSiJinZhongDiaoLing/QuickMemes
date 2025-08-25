#include "SearchBar.h"
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>

SearchBar::SearchBar(QWidget* parent) : QWidget(parent) {
    edit = new QLineEdit(this);
    button = new QPushButton("搜索", this);

    auto* layout = new QHBoxLayout(this);
    layout->addWidget(edit);
    layout->addWidget(button);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(5);

    connect(button, &QPushButton::clicked, this, &SearchBar::onButtonClicked);
}

void SearchBar::onButtonClicked() {
    emit searchTriggered(edit->text());
}
