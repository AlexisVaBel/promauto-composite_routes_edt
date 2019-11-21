#include "ui_route_contain.h"

#include "domain/sqlholder.h"


UI_Route_Contain::UI_Route_Contain(RoutesUI *ui, std::shared_ptr<ExcHolder> exholder):UIToDBTable(ui, exholder)
{
    configure_UI();
    configure_SQL();
    configure_SIGSLOTS();
}

UI_Route_Contain::~UI_Route_Contain()
{
}

void UI_Route_Contain::configure_UI()
{
    m_ui->tbl_RtsEdt_SubsInRt->setColumnCount(1);
    m_ui->tbl_RtsEdt_SubsInRt->setShowGrid(true);
    m_ui->tbl_RtsEdt_SubsInRt->setSelectionMode(QAbstractItemView::SingleSelection);
    m_ui->tbl_RtsEdt_SubsInRt->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_ui->tbl_RtsEdt_SubsInRt->setHorizontalHeaderLabels(QStringList() << "Name");

    m_ui->tbl_RtsEdt_SubsAll->setColumnCount(1);
    m_ui->tbl_RtsEdt_SubsAll->setShowGrid(true);
    m_ui->tbl_RtsEdt_SubsAll->setSelectionMode(QAbstractItemView::SingleSelection);
    m_ui->tbl_RtsEdt_SubsAll->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_ui->tbl_RtsEdt_SubsAll->setHorizontalHeaderLabels(QStringList() << "Name");

    m_ui->tbl_RtsEdt_DevsInSub->setColumnCount(1);
    m_ui->tbl_RtsEdt_DevsInSub->setShowGrid(true);
    m_ui->tbl_RtsEdt_DevsInSub->setSelectionMode(QAbstractItemView::SingleSelection);
    m_ui->tbl_RtsEdt_DevsInSub->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_ui->tbl_RtsEdt_DevsInSub->setHorizontalHeaderLabels(QStringList() << "Name");

    m_ui->tbl_RtsEdt_DevsInRt->setColumnCount(3);
    m_ui->tbl_RtsEdt_DevsInRt->setShowGrid(true);
    m_ui->tbl_RtsEdt_DevsInRt->setSelectionMode(QAbstractItemView::SingleSelection);
    m_ui->tbl_RtsEdt_DevsInRt->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_ui->tbl_RtsEdt_DevsInRt->setHorizontalHeaderLabels(QStringList() << "Name" << "TimeStart" << "TimeStop");
}

void UI_Route_Contain::configure_SQL()
{
//bool ExcHolder::append(QWidget *wdg, const char* someStr, const char *select, const char *del, const char *upd, const char *insert)
    m_exholder->append(m_ui->tbl_RtsEdt_SubsAll,  "route_edt_subs_all",  CH_RTSEDT_SUBS_ALL,"","",CH_RTSEDT_SUBS_IN_RT_INS);
    m_exholder->append(m_ui->tbl_RtsEdt_SubsInRt, "route_edt_subs_inrt", CH_RTSEDT_SUBS_IN_RT,"","",CH_RTSEDT_SUBS_IN_RT_INS);

//;
//(%ROOT_ID%, %SUBROOT_ID%)

    m_exholder->append(m_ui->tbl_RtsEdt_DevsInRt, "route_edt_devs_inrt",      CH_RTSEDT_DEVS_IN_RT,"","","");
    m_exholder->append(m_ui->tbl_RtsEdt_DevsInSub, "route_edt_devs_insubs",   CH_RTSEDT_DEVS_IN_SUB,"","","");
}

void UI_Route_Contain::configure_SIGSLOTS()
{
}

