#include "buttonpanel.h"

#include <QApplication>
#include <iostream>

ButtonPanel::ButtonPanel(QWidget *parent) : QWidget(parent)
{

    std::cout << __PRETTY_FUNCTION__ << std::endl;


    horizontalLayout = new QHBoxLayout(parent);
    horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));


    btnAdd = new QPushButton(parent);
    btnAdd->setObjectName(QStringLiteral("btnAdd"));



    btnDell = new QPushButton(parent);
    btnDell->setObjectName(QStringLiteral("btnDel"));



    btnRefr = new QPushButton(parent);
    btnRefr->setObjectName(QStringLiteral("btnRefr"));



    btnAccept = new QPushButton(parent);
    btnAccept->setObjectName(QStringLiteral("btnAccept"));



    horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);


    horizontalLayout->addWidget(btnAdd);
    horizontalLayout->addWidget(btnDell);
    horizontalLayout->addWidget(btnRefr);
    horizontalLayout->addWidget(btnAccept);
    horizontalLayout->addItem(horizontalSpacer);

    QMetaObject::connectSlotsByName(parent);
    btnAdd->setText(QApplication::translate("ButtonForm", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214", nullptr));
    btnDell->setText(QApplication::translate("ButtonForm", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214", nullptr));
    btnAccept->setText(QApplication::translate("ButtonForm", "\320\237\321\200\320\270\320\274\320\265\320\275\320\270\321\202\321\214", nullptr));
    btnRefr->setText(QApplication::translate("ButtonForm", "\320\236\320\261\320\275\320\276\320\262\320\270\321\202\321\214", nullptr));
}
