#include "routeconf.h"
#include "../domain/sqlholder.h"

#include <QTextCodec>



RouteConf::RouteConf(RoutesUI *ui, std::shared_ptr<IDataProvider> provider):UIToDBTable (ui, provider)
{
    configure_UI();
    configure_SIGSLOTS();
    m_lstAllSubs    = std::make_shared<QList<StructRoots *>>();
    m_lstSubsInRt   = std::make_shared<QList<StructRoots *>>();
    m_lstDevsInRt   = std::make_shared<QList<StructRoots *>>();
    m_lstDevsInSub  = std::make_shared<QList< StructRoots*>>();

    m_lstRoutes     = std::make_shared<QList<StructRoots *>>();    
}

void RouteConf::subs_cellClicked(int irow, int icol)
{
    if(irow >= m_lstAllSubs->length()) return;
    int idRoute = m_lstAllSubs->at(irow)->id;
    selectDevsInSub(idRoute);
}


void RouteConf::subs_cellDblClicked()
{
    auto lstSelected = m_ui->tbl_RtsConf_SubsAll->selectionModel()->selectedRows();
    if(lstSelected.length() != 1)return;

    // take id for delete
    int id = m_lstAllSubs->at(lstSelected.at(0).row())->id;
    selectDevsInSub(id);
    if(can_add_sub_toRoute()) add_subroute(id);
    else {
        m_ui->tbl_RtsConf_SubsAll->item(lstSelected.at(0).row(),1)->setBackground(QBrush("#F4FA58"));
        std::cout << "Can`t append already existed device " << std::endl;
    }
}


void RouteConf::route_subs_cellDblClicked()
{
    auto lstSelected = m_ui->tbl_RtsConf_SubsInRt->selectionModel()->selectedRows();
    if(lstSelected.length() != 1)return;

    // take id for delete
    int id         = m_lstSubsInRt->at(lstSelected.at(0).row())->id;
    int subroot_id =m_lstSubsInRt->at(lstSelected.at(0).row())->subroot_id;
    int root_id    =m_lstSubsInRt->at(lstSelected.at(0).row())->root_id;
    del_subroute(id,root_id,subroot_id);
}

void RouteConf::add_subroute(int &idx)
{
    int iRouteIdx = -1;
    for(int i = 0; i < m_lstRoutes->length(); ++i){
        if(m_lstRoutes->at(i)->name.compare(m_ui->m_edtRouteName->text(), Qt::CaseInsensitive) == 0){
            iRouteIdx = m_lstRoutes->at(i)->id;
        }
    }
    if (iRouteIdx == -1 ) return;

    QString strDML = INSERT_SUB_TO_ROUTE ;
    strDML = strDML.arg(iRouteIdx).arg(idx);


    if(m_provider->proces_sql(strDML.toStdString(), true, nullptr)){        
        strDML = INSERT_DEVS_TO_ROOTDEVICES1;
        // need to insert devices ...
        //ROOT_ID, DEVICE_ID, TIMESTART, TIMESTOP, ORDERNUM, FL_CTRLONLY, FL_ARMO, FL_TRANSPARENT, FL_CTRLPROD, FL_PROD, FL_SOLEOWNER, DLY_PRODSTOP
        for(int i = 0; i < m_lstDevsInSub->length(); ++i){
            QString strDML2 = INSERT_DEVS_TO_ROOTDEVICES2;
            strDML2 = strDML2.arg(iRouteIdx).arg(m_lstDevsInSub->at(i)->device_id).arg(m_lstDevsInSub->at(i)->time_start).arg(m_lstDevsInSub->at(i)->time_stop).arg((m_lstDevsInSub->at(i)->order + 1000)).arg(m_lstDevsInSub->at(i)->fl_ctronly);
            strDML2 = strDML2.arg(m_lstDevsInSub->at(i)->fl_armo).arg(m_lstDevsInSub->at(i)->fl_transparent).arg(m_lstDevsInSub->at(i)->fl_ctrlprod).arg(m_lstDevsInSub->at(i)->fl_prod).arg(m_lstDevsInSub->at(i)->fl_soleowner).arg(m_lstDevsInSub->at(i)->dly_prodstop);
            strDML2 = strDML + strDML2;            

            if(! m_provider->proces_sql(strDML2.toStdString(), true, nullptr)){
                std::cout << "none insert made" << std::endl;
                std::cout << strDML2.toStdString() << std::endl;
            }
        }
        // ��� ������� ��� ��������
//        dsROOTDEVICES.Database.Execute('DELETE FROM ROOTDEVICES WHERE (ORDERNUM<1000) and (ROOT_ID='+inttostr(root_id)+')'); next to be made -- �����? ��������� ���� ���� ����� ������� �������������� �������� �� ���������� ������������
                                                                                                                             // ��������, ����� �� ������������ ����������? ��� ����� �� �������
//        dsROOTDEVICES.Database.Execute('UPDATE ROOTDEVICES SET ORDERNUM=ORDERNUM-1000 WHERE ORDERNUM>=1000');
        selectDevsNSubs();
    }
}

void RouteConf::del_subroute(int &idx, int &root_id, int &subroot_id)
{
    QString strDML = DELETE_SUB_FROM_ROUTE ;
    strDML = strDML.arg(idx);

    if(m_provider->proces_sql(strDML.toStdString(), true, nullptr)){
        std::shared_ptr<QList<StructRoots*>>    lst_devsInSub = std::make_shared<QList<StructRoots *>>();
        QString strSQL = SELECT_ROUTE_DEVS_RTS;
        strSQL = strSQL.arg(root_id);
        if(commonSelectProcedure(lst_devsInSub,strSQL,root_id)){
            for(int i = 0; i < lst_devsInSub->length(); ++i){
                strDML = DELETE_SUB_DEVICES_FROM_ROUTE;
                strDML = strDML.arg(root_id);// root_id
                strDML = strDML.arg(lst_devsInSub->at(i)->device_id);// device_id

                if(m_provider->proces_sql(strDML.toStdString(), true, nullptr)){
                    continue;
                }else{
                    std::cout << __PRETTY_FUNCTION__ << " " << "Fatal error "<< std::endl;
                }
            }
        };

    }
    selectDevsNSubs();
}

void RouteConf::tab_idx_changed(int idx)
{
    // current tab selected
    if(idx == 2){
        selectRoutes();
        selectAllSubs();
    }
}

void RouteConf::configure_UI()
{
    QTextCodec *codec = QTextCodec::codecForName("CP1251");


    m_ui->tbl_RtsConf_SubsAll->setColumnCount(2);
    m_ui->tbl_RtsConf_SubsAll->setShowGrid(true);
    m_ui->tbl_RtsConf_SubsAll->setSelectionMode(QAbstractItemView::SingleSelection);
    m_ui->tbl_RtsConf_SubsAll->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_ui->tbl_RtsConf_SubsAll->hideColumn(0);
    m_ui->tbl_RtsConf_SubsAll->setHorizontalHeaderLabels(QStringList() << "Id" << codec->toUnicode("��������� ������ ��� ���. � �������"));

    m_ui->tbl_RtsConf_DevsInSub->setColumnCount(2);
    m_ui->tbl_RtsConf_DevsInSub->setShowGrid(true);
    m_ui->tbl_RtsConf_DevsInSub->setSelectionMode(QAbstractItemView::SingleSelection);
    m_ui->tbl_RtsConf_DevsInSub->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_ui->tbl_RtsConf_DevsInSub->hideColumn(0);
    m_ui->tbl_RtsConf_DevsInSub->setHorizontalHeaderLabels(QStringList() << "Id" << codec->toUnicode("����������"));

    m_ui->tbl_RtsConf_SubsInRt->setColumnCount(2);
    m_ui->tbl_RtsConf_SubsInRt->setShowGrid(true);
    m_ui->tbl_RtsConf_SubsInRt->setSelectionMode(QAbstractItemView::SingleSelection);
    m_ui->tbl_RtsConf_SubsInRt->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_ui->tbl_RtsConf_SubsInRt->hideColumn(0);
    m_ui->tbl_RtsConf_SubsInRt->setHorizontalHeaderLabels(QStringList() << "Id" << codec->toUnicode("������ � ������� ��������"));

    m_ui->tbl_RtsConf_DevsInRt->setColumnCount(5);
    m_ui->tbl_RtsConf_DevsInRt->setShowGrid(true);
    m_ui->tbl_RtsConf_DevsInRt->setSelectionMode(QAbstractItemView::SingleSelection);
    m_ui->tbl_RtsConf_DevsInRt->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_ui->tbl_RtsConf_DevsInRt->hideColumn(0);
    m_ui->tbl_RtsConf_DevsInRt->setHorizontalHeaderLabels(QStringList() << "Id" << codec->toUnicode("����������") << codec->toUnicode("�����") << codec->toUnicode("����") << codec->toUnicode("��������"));

}

void RouteConf::configure_SIGSLOTS()
{
    connect(m_ui->m_tabWidget,    &QTabWidget::currentChanged, this, &RouteConf::tab_idx_changed);


    connect(m_ui->m_edtRouteName, &QLineEdit::editingFinished, this, &RouteConf::selectDevsNSubs);

    connect(m_ui->tbl_RtsConf_SubsInRt, &QTableWidget::doubleClicked, this, &RouteConf::route_subs_cellDblClicked);

    connect(m_ui->tbl_RtsConf_SubsAll, &QTableWidget::cellClicked, this, &RouteConf::subs_cellClicked );
    connect(m_ui->tbl_RtsConf_SubsAll, &QTableWidget::doubleClicked, this, &RouteConf::subs_cellDblClicked );


}

bool RouteConf::procsSelect()
{
    return false;
}

bool RouteConf::procsInsert()
{
    return false;
}

bool RouteConf::procsUpdate()
{
    return false;
}

bool RouteConf::procsDelete()
{
    return false;
}

void RouteConf::updateSubRoutesView()
{    
    m_ui->tbl_RtsConf_SubsAll->blockSignals(true);
    try {
        while(m_ui->tbl_RtsConf_SubsAll->rowCount() > 0){
            m_ui->tbl_RtsConf_SubsAll->removeRow(0);
        }
        for(int i = 0; i < m_lstAllSubs->length(); ++i){
            m_ui->tbl_RtsConf_SubsAll->insertRow(i);
            m_ui->tbl_RtsConf_SubsAll->setItem(i, 0, new QTableWidgetItem(m_lstAllSubs->at(i)->id));
            m_ui->tbl_RtsConf_SubsAll->setItem(i, 1, new QTableWidgetItem(m_lstAllSubs->at(i)->name));
            m_ui->tbl_RtsConf_SubsAll->item(i,1)->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);




        }
    } catch (std::exception &exc) {
        std::cerr << exc.what() << std::endl;
    }
    m_ui->tbl_RtsConf_SubsAll->blockSignals(false);
}

void RouteConf::updateSubInRouteView()
{    
    m_ui->tbl_RtsConf_SubsInRt->blockSignals(true);
    try {
        while(m_ui->tbl_RtsConf_SubsInRt->rowCount() > 0){
            m_ui->tbl_RtsConf_SubsInRt->removeRow(0);
        }
        for(int i = 0; i < m_lstSubsInRt->length(); ++i){
            m_ui->tbl_RtsConf_SubsInRt->insertRow(i);
            m_ui->tbl_RtsConf_SubsInRt->setItem(i, 0, new QTableWidgetItem(m_lstSubsInRt->at(i)->id));
            m_ui->tbl_RtsConf_SubsInRt->setItem(i, 1, new QTableWidgetItem(m_lstSubsInRt->at(i)->name));
            m_ui->tbl_RtsConf_SubsInRt->item(i,1)->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

        }
    } catch (std::exception &exc) {
        std::cerr << exc.what() << std::endl;
    }
    m_ui->tbl_RtsConf_SubsInRt->blockSignals(false);
}

void RouteConf::updateDevsInSubView()
{
    m_ui->tbl_RtsConf_DevsInSub->blockSignals(true);
    try {
        while(m_ui->tbl_RtsConf_DevsInSub->rowCount() > 0){
            m_ui->tbl_RtsConf_DevsInSub->removeRow(0);
        }
        for(int i = 0; i < m_lstDevsInSub->length(); ++i){
            m_ui->tbl_RtsConf_DevsInSub->insertRow(i);
            m_ui->tbl_RtsConf_DevsInSub->setItem(i, 0, new QTableWidgetItem(m_lstDevsInSub->at(i)->id));
            m_ui->tbl_RtsConf_DevsInSub->setItem(i, 1, new QTableWidgetItem(m_lstDevsInSub->at(i)->name));
            m_ui->tbl_RtsConf_DevsInSub->item(i,1)->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

        }
    } catch (std::exception &exc) {
        std::cerr << exc.what() << std::endl;
    }
    m_ui->tbl_RtsConf_DevsInSub->blockSignals(false);
}

void RouteConf::updateDevsView()
{ 
    m_ui->tbl_RtsConf_DevsInRt->blockSignals(true);
    try {
        while(m_ui->tbl_RtsConf_DevsInRt->rowCount() > 0){
            m_ui->tbl_RtsConf_DevsInRt->removeRow(0);
        }
        for(int i = 0; i < m_lstDevsInRt->length(); ++i){
            m_ui->tbl_RtsConf_DevsInRt->insertRow(i);
            m_ui->tbl_RtsConf_DevsInRt->setItem(i, 0, new QTableWidgetItem(m_lstDevsInRt->at(i)->id));
            m_ui->tbl_RtsConf_DevsInRt->setItem(i, 1, new QTableWidgetItem(m_lstDevsInRt->at(i)->name));
            m_ui->tbl_RtsConf_DevsInRt->item(i,1)->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

        }
    } catch (std::exception &exc) {
        std::cerr << exc.what() << std::endl;
    }
    m_ui->tbl_RtsConf_DevsInRt->blockSignals(false);
}

void RouteConf::selectDevsNSubs()
{
    for(int i = 0; i < m_lstRoutes->length(); ++i){
        if(m_lstRoutes->at(i)->name.compare(m_ui->m_edtRouteName->text(), Qt::CaseInsensitive) == 0){            
            selectSubs(m_lstRoutes->at(i)->id);
            selectDevs(m_lstRoutes->at(i)->id);
            break;
        }
    }
}


void RouteConf::selectAllSubs()
{
    if(commonSelectProcedure(m_lstAllSubs,SELECT_SUBROUTES_RTS)){
        updateSubRoutesView();
    }
}


void RouteConf::selectDevsInSub(int id)
{
    QString strSQL(SELECT_ROUTE_DEVS_RTS);
    strSQL = strSQL.arg(id);

    if(commonSelectProcedure(m_lstDevsInSub,strSQL,id)){
        updateDevsInSubView();
    }
}


void RouteConf::selectSubs(int id)
{
    QString strSQL(SELECT_SUBS_IN_RT_ALL);
    strSQL = strSQL.arg(id);

    if(commonSelectProcedure(m_lstSubsInRt,strSQL)){
        updateSubInRouteView();
    }
}


void RouteConf::selectDevs(int id)
{
    QString strSQL(SELECT_DEVS_IN_RT_ALL);
    strSQL = strSQL.arg(id);

    if(commonSelectProcedure(m_lstDevsInRt,strSQL,0)){
        updateDevsView();
    }
}

bool RouteConf::can_add_sub_toRoute()
{
    for(int isubs = 0; isubs < m_lstDevsInSub->length(); ++isubs){
        for(int idevs = 0; idevs < m_lstDevsInRt->length(); ++idevs){
            if(m_lstDevsInSub->at(isubs)->name.compare(m_lstDevsInRt->at(idevs)->name,Qt::CaseInsensitive)) return false; // use id, instead name - need to remake sql
        };
    };
    return true;
}



void RouteConf::selectRoutes()
{
    QStringList lstCompleter;    

    if(commonSelectProcedure(m_lstRoutes,SELECT_ROUTES_ALL)){
        for(int i = 0; i < m_lstRoutes->length(); ++i){
            lstCompleter.push_back(m_lstRoutes->at(i)->name);
        }
    }
    m_completer     = new QCompleter(lstCompleter, this); // completer test
    m_ui->m_edtRouteName->setCompleter(m_completer);
}




bool RouteConf::commonSelectProcedure(std::shared_ptr<QList<StructRoots *> > dataContainer, const QString &someScript, const uint &root_id)
{
    std::shared_ptr<QList<ColumnNode *> > nodes = std::make_shared<QList<ColumnNode *> >(); // common node
    if(!m_provider->proces_sql(someScript.toStdString(), false, nodes)) return false;

    dataContainer->clear();
    for(int i = 0; i < nodes->length(); ++i){
        StructRoots *rts = new StructRoots();




        auto tmp = nodes->at(i)->get_by_name("id");
        if (tmp != nullptr){
            rts->id = tmp->m_varValue.toInt();
        }

        if(root_id != 0){ rts->root_id = root_id;}
        else {
            tmp = nodes->at(i)->get_by_name("root_id");
            if (tmp != nullptr){
                rts->root_id = tmp->m_varValue.toInt();
            }
        }


        tmp = nodes->at(i)->get_by_name("Name");
        if (tmp != nullptr){
            rts->name = tmp->m_varValue.toString();
        }

        tmp = nodes->at(i)->get_by_name("Descr");
        if (tmp != nullptr){
            rts->descr = tmp->m_varValue.toString();
        }


        tmp = nodes->at(i)->get_by_name("timestart");
        if (tmp != nullptr){
            rts->time_start = tmp->m_varValue.toInt();
        }


        tmp = nodes->at(i)->get_by_name("timestop");
        if (tmp != nullptr){
            rts->time_stop = tmp->m_varValue.toInt();
        }


        tmp = nodes->at(i)->get_by_name("FL_CTRLONLY");
        if (tmp != nullptr){
            rts->fl_ctronly = tmp->m_varValue.toInt();
        }


        tmp = nodes->at(i)->get_by_name("fl_armo");
        if (tmp != nullptr){
            rts->fl_armo = tmp->m_varValue.toInt();
        }


        tmp = nodes->at(i)->get_by_name("fl_transparent");
        if (tmp != nullptr){
            rts->fl_transparent = tmp->m_varValue.toInt();
        }


        tmp = nodes->at(i)->get_by_name("fl_ctrlprod");
        if (tmp != nullptr){
            rts->fl_ctrlprod = tmp->m_varValue.toInt();
        }


        tmp = nodes->at(i)->get_by_name("fl_prod");
        if (tmp != nullptr){
            rts->fl_prod = tmp->m_varValue.toInt();
        }



        tmp = nodes->at(i)->get_by_name("fl_soleowner");
        if (tmp != nullptr){
            rts->fl_soleowner = tmp->m_varValue.toInt();
        }


        tmp = nodes->at(i)->get_by_name("dly_prodstop");
        if (tmp != nullptr){
            rts->dly_prodstop = tmp->m_varValue.toInt();
        }

        tmp = nodes->at(i)->get_by_name("ordernum");
        if (tmp != nullptr){
            rts->order = tmp->m_varValue.toInt();
        }

        tmp = nodes->at(i)->get_by_name("device_id");
        if (tmp != nullptr){
            rts->device_id = tmp->m_varValue.toInt();
        }

        tmp = nodes->at(i)->get_by_name("subroot_id");
        if (tmp != nullptr){
            rts->subroot_id = tmp->m_varValue.toInt();
        }


        dataContainer->push_back(std::move(rts));
    }
    return true;

}

