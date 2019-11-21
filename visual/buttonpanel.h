#ifndef BUTTONPANEL_H
#define BUTTONPANEL_H

#include <QWidget>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>

class ButtonPanel : public QWidget
{
    Q_OBJECT
public:
    explicit ButtonPanel(QWidget *parent = nullptr);
    QHBoxLayout *horizontalLayout;
    QPushButton *btnAdd;
    QPushButton *btnDell;
    QPushButton *btnRefr;
    QPushButton *btnAccept;
    QSpacerItem *horizontalSpacer;

//signals:

//public slots:
};

#endif // BUTTONPANEL_H
