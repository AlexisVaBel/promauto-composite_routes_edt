#ifndef ROUTESUI_H
#define ROUTESUI_H


#include "buttonpanel.h"

#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>
#include <QLineEdit>

#include <QLabel>

class RoutesUI: public QWidget
{
public:
    RoutesUI(QMainWindow *MainWindow);


    QWidget     *m_centralwidget;
    QTabWidget  *m_tabWidget;

    QLabel *m_tabRtsAll;
    QLabel *m_tabSubRtsConf;
    QLabel *m_tabRtsConf;

    QTableWidget  *tbl_RtsAll_AvlRts;
    QTableWidget  *tbl_RtsAll_SubsInRt;
    QTableWidget  *tbl_RtsAll_AllDevs;

    QTableWidget *tbl_SubRtsConf_DevsInSub;
    QTableWidget *tbl_SubRtsConf_SubsAll;

    QTableWidget *tbl_RtsConf_SubsAll;
    QTableWidget *tbl_RtsConf_SubsInRt;
    QTableWidget *tbl_RtsConf_DevsInRt;
    QTableWidget *tbl_RtsConf_DevsInSub;


    QLineEdit *m_edtRouteName;


    QStatusBar *statusbar;

    QLabel *lblCntrRtsAll;
    QLabel *lblCntrRtsAllDevs;
    ButtonPanel *m_pnlBtnsRtsAll;
    ButtonPanel *m_pnlBtnsRtsAllDevs;

    QLabel *lblSubsRtsConf;
    QLabel *lblGrpSubRtsConf_DevsInSub;
    ButtonPanel *m_pnlBtns_SubRtsConf;
    ButtonPanel *m_pnlBtns_SubRtsConf_DevsInSub;


    QGridLayout *gridLt_RtsAll;
    QGridLayout *gridLt_SubRtsConf;
    QGridLayout *gridLt_RtsConf;
};

#endif // ROUTESUI_H
