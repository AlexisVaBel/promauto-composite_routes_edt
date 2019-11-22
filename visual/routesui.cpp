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


    gridLt_RtsAll     = new QGridLayout();
    gridLt_SubRtsConf = new QGridLayout();
    gridLt_RtsConf    = new QGridLayout();

    m_tabRtsAll         = new QLabel();
    m_tabSubRtsConf     = new QLabel();
    m_tabRtsConf        = new QLabel();


    lblCntrRtsAll       = new QLabel();
    lblCntrRtsAllDevs   = new QLabel();

    m_pnlBtnsRtsAll     = new ButtonPanel(lblCntrRtsAll);
    m_pnlBtnsRtsAllDevs = new ButtonPanel(lblCntrRtsAllDevs);


    lblSubsRtsConf              = new QLabel();
    lblGrpSubRtsConf_DevsInSub  = new QLabel();

    m_pnlBtns_SubRtsConf                    = new ButtonPanel(lblSubsRtsConf);
    m_pnlBtns_SubRtsConf_DevsInSub          = new ButtonPanel(lblGrpSubRtsConf_DevsInSub);

    m_tabRtsAll->setLayout(gridLt_RtsAll);
    m_tabSubRtsConf->setLayout(gridLt_SubRtsConf);
    m_tabRtsConf->setLayout(gridLt_RtsConf);

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



    gridLt_RtsAll->addWidget(lblCntrRtsAll, 0, 0);
    gridLt_RtsAll->addItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding), 0, 1, 1, 1);
    gridLt_RtsAll->addWidget(lblCntrRtsAllDevs, 0, 1);
    gridLt_RtsAll->addWidget(tbl_RtsAll_AvlRts, 1, 0);
    gridLt_RtsAll->addWidget(tbl_RtsAll_SubsInRt, 2, 0);
    gridLt_RtsAll->addWidget(tbl_RtsAll_AllDevs, 1, 1);

    gridLt_RtsAll->setColumnStretch(0,10);
    gridLt_RtsAll->setColumnStretch(1,20);
    gridLt_RtsAll->setRowStretch(0,0);
    gridLt_RtsAll->setRowStretch(1,3);
    gridLt_RtsAll->setRowStretch(2,2);



    gridLt_SubRtsConf->addWidget(lblSubsRtsConf, 0, 0);
    gridLt_SubRtsConf->addItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding), 0, 1, 1, 1);
    gridLt_SubRtsConf->addWidget(lblGrpSubRtsConf_DevsInSub, 0, 1);
    gridLt_SubRtsConf->addWidget(tbl_SubRtsConf_SubsAll, 1, 0);
    gridLt_SubRtsConf->addWidget(tbl_SubRtsConf_DevsInSub, 1, 1);
    gridLt_SubRtsConf->setRowStretch(0,0);
    gridLt_SubRtsConf->setRowStretch(1,3);




    gridLt_RtsConf->addWidget(m_edtRouteName, 0, 0, 1, 2, Qt::AlignLeft);
    gridLt_RtsConf->addWidget(tbl_RtsConf_SubsAll, 1, 0);
    gridLt_RtsConf->addWidget(tbl_RtsConf_DevsInSub, 2, 0);
    gridLt_RtsConf->addWidget(tbl_RtsConf_SubsInRt, 1, 1);
    gridLt_RtsConf->addWidget(tbl_RtsConf_DevsInRt, 2, 1);


    statusbar = new QStatusBar(MainWindow);
    statusbar->setObjectName(QStringLiteral("statusbar"));

    MainWindow->setCentralWidget(m_centralwidget);
    MainWindow->setStatusBar(statusbar);

    m_tabWidget->addTab(m_tabRtsAll,  QString("first"));
    m_tabWidget->addTab(m_tabSubRtsConf, QString("second"));
    m_tabWidget->addTab(m_tabRtsConf, QString("third"));


}
