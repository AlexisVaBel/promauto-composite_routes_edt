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

    QLabel *m_tabMnRts;
    QLabel *m_tabGrpEdt;
    QLabel *m_tabRtsEdt;

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

    QLabel *lblCntrMnRts;
    QLabel *lblCntrMnDevs;
    ButtonPanel *m_pnlBtnsMnRts;
    ButtonPanel *m_pnlBtnsMnDevs;

    QLabel *lblGrpEdtSubs;
    QLabel *lblGrpEdtDevsInSub;
    ButtonPanel *m_pnlBtnsEdtSubs;
    ButtonPanel *m_pnlBtnsDevsInSub;


    QGridLayout *gridLt_MnRts;
    QGridLayout *gridLt_GrpEdt;
    QGridLayout *gridLt_RtsEdt;
};

#endif // ROUTESUI_H
