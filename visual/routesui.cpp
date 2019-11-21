#include "routesui.h"

#include <QLabel>
#include <QLineEdit>


RoutesUI::RoutesUI(QMainWindow *MainWindow)
{
    if (MainWindow->objectName().isEmpty())
        MainWindow->setObjectName(QStringLiteral("MainWindow"));
    MainWindow->resize(890, 600);
    m_centralwidget = new QWidget(MainWindow);
    m_centralwidget->setObjectName(QStringLiteral("centralwidget"));
    m_tabWidget = new QTabWidget(m_centralwidget);
    m_tabWidget->setObjectName(QStringLiteral("tabWidget"));


    gridLt_MnRts  = new QGridLayout();
    gridLt_GrpEdt = new QGridLayout();
    gridLt_RtsEdt = new QGridLayout();

    m_tabMnRts   = new QLabel();
    m_tabGrpEdt  = new QLabel();
    m_tabRtsEdt  = new QLabel();


    lblCntrMnRts   = new QLabel();
    lblCntrMnDevs  = new QLabel();

    m_pnlBtnsMnRts  = new ButtonPanel(lblCntrMnRts);
    m_pnlBtnsMnDevs = new ButtonPanel(lblCntrMnDevs);


    lblGrpEdtSubs   = new QLabel();
    lblGrpEdtDevsInSub  = new QLabel();

    m_pnlBtnsEdtSubs  = new ButtonPanel(lblGrpEdtSubs);
    m_pnlBtnsDevsInSub = new ButtonPanel(lblGrpEdtDevsInSub);

    m_tabMnRts->setLayout(gridLt_MnRts);
    m_tabGrpEdt->setLayout(gridLt_GrpEdt);
    m_tabRtsEdt->setLayout(gridLt_RtsEdt);

    tbl_RtsAll_AvlRts    = new QTableWidget();
    tbl_RtsAll_SubsInRt  = new QTableWidget();
    tbl_RtsAll_AllDevs   = new QTableWidget();

    tbl_SubRtsConf_DevsInSub   = new QTableWidget();
    tbl_SubRtsConf_SubsAll     = new QTableWidget();

    tbl_RtsConf_SubsAll      = new QTableWidget();
    tbl_RtsConf_SubsInRt     = new QTableWidget();
    tbl_RtsConf_DevsInRt     = new QTableWidget();
    tbl_RtsConf_DevsInSub    = new QTableWidget();


    m_edtRouteName       = new QLineEdit();
    m_edtRouteName->setFixedSize(220, 28);



    gridLt_MnRts->addWidget(lblCntrMnRts, 0, 0);
    gridLt_MnRts->addItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding), 0, 1, 1, 1);
    gridLt_MnRts->addWidget(lblCntrMnDevs, 0, 1);
    gridLt_MnRts->addWidget(tbl_RtsAll_AvlRts, 1, 0);
    gridLt_MnRts->addWidget(tbl_RtsAll_SubsInRt, 2, 0);
    gridLt_MnRts->addWidget(tbl_RtsAll_AllDevs, 1, 1);

    gridLt_MnRts->setColumnStretch(0,10);
    gridLt_MnRts->setColumnStretch(1,20);
    gridLt_MnRts->setRowStretch(0,0);
    gridLt_MnRts->setRowStretch(1,3);
    gridLt_MnRts->setRowStretch(2,2);



    gridLt_GrpEdt->addWidget(lblGrpEdtSubs, 0, 0);
    gridLt_GrpEdt->addItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding), 0, 1, 1, 1);
    gridLt_GrpEdt->addWidget(lblGrpEdtDevsInSub, 0, 1);
    gridLt_GrpEdt->addWidget(tbl_SubRtsConf_SubsAll, 1, 0);
    gridLt_GrpEdt->addWidget(tbl_SubRtsConf_DevsInSub, 1, 1);
    gridLt_GrpEdt->setRowStretch(0,0);
    gridLt_GrpEdt->setRowStretch(1,3);




    gridLt_RtsEdt->addWidget(m_edtRouteName, 0, 0, 1, 2, Qt::AlignLeft);
    gridLt_RtsEdt->addWidget(tbl_RtsConf_SubsAll, 1, 0);
    gridLt_RtsEdt->addWidget(tbl_RtsConf_DevsInSub, 2, 0);
    gridLt_RtsEdt->addWidget(tbl_RtsConf_SubsInRt, 1, 1);
    gridLt_RtsEdt->addWidget(tbl_RtsConf_DevsInRt, 2, 1);


    statusbar = new QStatusBar(MainWindow);
    statusbar->setObjectName(QStringLiteral("statusbar"));

    MainWindow->setCentralWidget(m_centralwidget);
    MainWindow->setStatusBar(statusbar);

    m_tabWidget->addTab(m_tabMnRts,  QString("first"));
    m_tabWidget->addTab(m_tabGrpEdt, QString("second"));
    m_tabWidget->addTab(m_tabRtsEdt, QString("third"));


}
