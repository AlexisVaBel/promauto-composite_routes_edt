#include "ui_routes.h"

#include "domain/sqlholder.h"

UI_Routes::UI_Routes(RoutesUI *ui, std::shared_ptr<ExcHolder> exholder):UIToDBTable(ui, exholder)
{
    configure_UI();
    configure_SQL();
    configure_SIGSLOTS();
}

UI_Routes::~UI_Routes()
{

}

void UI_Routes::configure_UI()
{
    m_ui->tbl_mnRts_AvlRts->setColumnCount(2);
    m_ui->tbl_mnRts_AvlRts->setShowGrid(true);
    m_ui->tbl_mnRts_AvlRts->setSelectionMode(QAbstractItemView::SingleSelection);
    m_ui->tbl_mnRts_AvlRts->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_ui->tbl_mnRts_AvlRts->hideColumn(0);
    m_ui->tbl_mnRts_AvlRts->setHorizontalHeaderLabels(QStringList() << "Id" <<"Name");

    // available subroutes
    m_ui->tbl_mnRts_SubsInRt->setColumnCount(1);
    m_ui->tbl_mnRts_SubsInRt->setShowGrid(true);
    m_ui->tbl_mnRts_SubsInRt->setSelectionMode(QAbstractItemView::SingleSelection);
    m_ui->tbl_mnRts_SubsInRt->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_ui->tbl_mnRts_SubsInRt->setHorizontalHeaderLabels(QStringList() << "Name");

    // available devices
    m_ui->tbl_mnRts_AllDevs->setColumnCount(1);
    m_ui->tbl_mnRts_AllDevs->setShowGrid(true);
    m_ui->tbl_mnRts_AllDevs->setSelectionMode(QAbstractItemView::SingleSelection);
    m_ui->tbl_mnRts_AllDevs->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_ui->tbl_mnRts_AllDevs->setHorizontalHeaderLabels(QStringList() << "Name");
}

void UI_Routes::configure_SQL()
{
    m_exholder->append(m_ui->tbl_mnRts_AvlRts,  "main_avl",      CH_MNEDT_ALL_RTS,   CH_MNEDT_ALL_RTS_DEL, CH_MNEDT_ALL_RTS_UPD, CH_MNEDT_ALL_RTS_INS);
    m_exholder->append(m_ui->tbl_mnRts_AllDevs, "main_devs",     CH_MNEDT_DEVS_IN_RT,CH_MNEDT_DEVS_IN_DEL,"","");
    m_exholder->append(m_ui->tbl_mnRts_SubsInRt,"main_subs",     CH_MNEDT_SUBS_IN_RT,CH_MNEDT_SUBS_IN_DEL,"","");

}



void UI_Routes::configure_SIGSLOTS()
{

}
