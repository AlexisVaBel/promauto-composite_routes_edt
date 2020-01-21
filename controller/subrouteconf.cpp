#include "subrouteconf.h"

#include "../domain/sqlholder.h"
#include "../common/userinput.h"

#include <QCheckBox>
#include <QComboBox>
#include <QCompleter>
#include <QInputDialog>
#include <QSpinBox>
#include <QTextCodec>


static const int NUM_MAGIC_DUMMY = 0;



SubRouteConf::SubRouteConf(RoutesUI *ui, std::shared_ptr<IDataProvider> provider):UIToDBTable (ui,provider),m_completer(new QCompleter())
{
    configure_UI();
    configure_SIGSLOTS();
    m_lstCompleter  = std::make_shared<QStringList>();
    m_lstCompleted  = std::make_shared<QStringList>();

    m_lstAllSubs    = std::make_shared<QList<StructRoots *>>();
    m_lstDevsInSub  = std::make_shared<QList<StructRoots *>>();
    m_lstAllDevs    = std::make_shared<QList<StructRoots *>>();

}

void SubRouteConf::subs_cellClicked(int irow, int icol)
{
    if(irow >= m_lstAllSubs->length()) return;
    uint idRoute = m_lstAllSubs->at(irow)->id;
    sel_devs_inSub(idRoute);
}

void SubRouteConf::tab_idx_changed(int idx)
{
    if(idx == 1){
        sel_allSubs();
        sel_allDevs();
    }
}


void SubRouteConf::devs_cellClicked(int irow, int icol)
{
  std::cout << __PRETTY_FUNCTION__ << " | " << irow << " | " << icol << std::endl ;
  if(icol != 1) return;
}


void SubRouteConf::dev_cellChanged(const QString &str)
{
    std::cout << __PRETTY_FUNCTION__ << str.toStdString() << std::endl ;
    m_lstCompleted->append(str);
}

void SubRouteConf::dev_cellChanged(const QString &strOld, const QString &strNew)
{
    std::cout << __PRETTY_FUNCTION__ << strOld.toStdString() << " -- " << strNew.toStdString() << std::endl ;
    m_lstCompleter->append(strOld);
    m_lstCompleter->removeAll(strNew);

    m_lstCompleted->append(strNew);
    m_lstCompleted->removeAll(strOld);

    //

}

void SubRouteConf::add_device()
{    
    int irow = m_ui->tbl_SubRtsConf_DevsInSub->rowCount();
    m_ui->tbl_SubRtsConf_DevsInSub->insertRow(irow);



    SubrouteDevCombo *cmb = new SubrouteDevCombo();
    cmb->setCompleter(m_completer);
    connect(cmb, SIGNAL(textChangedSignal(const QString&, const QString&)), this, SLOT(dev_cellChanged(const QString&, const QString&)));

    cmb->addItems(*(m_lstCompleter.get()));
    cmb->setMaxVisibleItems(10); // magic number ooohhhh


    m_ui->tbl_SubRtsConf_DevsInSub->setCellWidget(irow, 1, std::move(cmb));
    //
    m_ui->tbl_SubRtsConf_DevsInSub->setItem(irow, 2, new QTableWidgetItem(""));
    m_ui->tbl_SubRtsConf_DevsInSub->setItem(irow, 3, new QTableWidgetItem(""));
    m_ui->tbl_SubRtsConf_DevsInSub->setItem(irow, 4, new QTableWidgetItem(""));
    m_ui->tbl_SubRtsConf_DevsInSub->setItem(irow, 5, new QTableWidgetItem(""));

    m_ui->tbl_SubRtsConf_DevsInSub->setItem(irow, 6, new QTableWidgetItem(""));
    m_ui->tbl_SubRtsConf_DevsInSub->setItem(irow, 7, new QTableWidgetItem(""));
    m_ui->tbl_SubRtsConf_DevsInSub->setItem(irow, 8, new QTableWidgetItem(""));
    m_ui->tbl_SubRtsConf_DevsInSub->setItem(irow, 9, new QTableWidgetItem(""));
    m_ui->tbl_SubRtsConf_DevsInSub->setItem(irow, 10,new QTableWidgetItem(""));
    //

    ((QComboBox *) m_ui->tbl_SubRtsConf_DevsInSub->cellWidget(irow, 1))->showPopup();

}

void SubRouteConf::del_device()
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
}

void SubRouteConf::add_subroute()
{
    QString strSubName = get_user_input("Новый маршрут");
    std::cout << __PRETTY_FUNCTION__  << " " << strSubName.toStdString()<< std::endl;
}

void SubRouteConf::del_subroute()
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
}

void SubRouteConf::refr_subroute()
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
}

void SubRouteConf::acc_subroute()
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
}


void SubRouteConf::configure_UI()
{
    QTextCodec *codec = QTextCodec::codecForName("CP1251");

    m_ui->tbl_SubRtsConf_SubsAll->setColumnCount(5);
    m_ui->tbl_SubRtsConf_SubsAll->setShowGrid(true);
    m_ui->tbl_SubRtsConf_SubsAll->setSelectionMode(QAbstractItemView::SingleSelection);
    m_ui->tbl_SubRtsConf_SubsAll->setSelectionBehavior(QAbstractItemView::SelectItems);
    m_ui->tbl_SubRtsConf_SubsAll->hideColumn(0);
    m_ui->tbl_SubRtsConf_SubsAll->setHorizontalHeaderLabels(QStringList() << "Id" << codec->toUnicode("Имя группы") << codec->toUnicode("Начало") << codec->toUnicode("Конец")  << codec->toUnicode("Цепочка") );

    m_ui->tbl_SubRtsConf_DevsInSub->setColumnCount(11);
    m_ui->tbl_SubRtsConf_DevsInSub->setShowGrid(true);
    m_ui->tbl_SubRtsConf_DevsInSub->setSelectionMode(QAbstractItemView::SingleSelection);
    m_ui->tbl_SubRtsConf_DevsInSub->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_ui->tbl_SubRtsConf_DevsInSub->hideColumn(0);
    m_ui->tbl_SubRtsConf_DevsInSub->setHorizontalHeaderLabels(QStringList() << "Id" << codec->toUnicode("Устройства") << codec->toUnicode("К") << codec->toUnicode("Н")
                                                       << codec->toUnicode("Кп") << codec->toUnicode("Пд") << codec->toUnicode("И")
                                                       << codec->toUnicode("Пр") << codec->toUnicode("ПдЗ")<< codec->toUnicode("Старт")<<codec->toUnicode("Стоп"));

    for(int i = 2; i < 9 ; ++i){

        if(i == 7)m_ui->tbl_SubRtsConf_DevsInSub->setColumnWidth(i,50);
        else
            m_ui->tbl_SubRtsConf_DevsInSub->setColumnWidth(i,40);
    }


}

void SubRouteConf::configure_SIGSLOTS()
{
    connect(m_ui->m_tabWidget,    &QTabWidget::currentChanged, this, &SubRouteConf::tab_idx_changed);

    connect(m_ui->tbl_SubRtsConf_SubsAll,    &QTableWidget::cellClicked, this, &SubRouteConf::subs_cellClicked );
    connect(m_ui->tbl_SubRtsConf_DevsInSub,    &QTableWidget::cellClicked, this, &SubRouteConf::devs_cellClicked );


    connect(m_ui->m_pnlBtns_SubRtsConf_DevsInSub->btnAdd,  &QPushButton::pressed     , this, &SubRouteConf::add_device);

    connect(m_ui->m_pnlBtns_SubRtsConf->btnAdd,  &QPushButton::pressed     , this, &SubRouteConf::add_subroute);
    connect(m_ui->m_pnlBtns_SubRtsConf->btnDell,  &QPushButton::pressed     , this, &SubRouteConf::del_subroute);
    connect(m_ui->m_pnlBtns_SubRtsConf->btnRefr,  &QPushButton::pressed     , this, &SubRouteConf::refr_subroute);
    connect(m_ui->m_pnlBtns_SubRtsConf->btnAccept,  &QPushButton::pressed     , this, &SubRouteConf::acc_subroute);
}

bool SubRouteConf::procsSelect()
{
    return false;
}

bool SubRouteConf::procsInsert()
{
    return false;
}

bool SubRouteConf::procsUpdate()
{
    return false;
}

bool SubRouteConf::procsDelete()
{
    return false;
}


void SubRouteConf::sel_devs_inSub(uint id)
{
    QString strSQL(SELECT_ROUTE_DEVS_RTS);
    strSQL = strSQL.arg(id);


    if(commonSelectProcedure(m_lstDevsInSub,strSQL)){
        upd_devsInSub_view();
    }
}

void SubRouteConf::sel_allSubs()
{
    if(commonSelectProcedure(m_lstAllSubs,SELECT_SUBROUTES_RTS)){
        upd_subRts_view();
    }
}

void SubRouteConf::sel_allDevs()
{
    if(!commonSelectProcedure(m_lstAllDevs,SELECT_ALL_DEVS_MCHB)){ // select all devs
        std::cerr << "Impossible to get device list" << std::endl;
        return;
    }

    m_lstCompleter->clear();
    for(int i = 0; i < m_lstAllDevs->length(); ++i){
        m_lstCompleter->append(m_lstAllDevs->at(i)->name);
    }
    QCompleter *cmp = m_completer;
    delete cmp;
    m_completer = new QCompleter(*(m_lstCompleter.get()));

}

void SubRouteConf::upd_subRts_view()
{
    m_ui->tbl_SubRtsConf_SubsAll->blockSignals(true);
    try {
        while(m_ui->tbl_SubRtsConf_SubsAll->rowCount() > 0){
            m_ui->tbl_SubRtsConf_SubsAll->removeRow(0);
        }
        for(int i = 0; i < m_lstAllSubs->length(); ++i){
            m_ui->tbl_SubRtsConf_SubsAll->insertRow(i);
            m_ui->tbl_SubRtsConf_SubsAll->setItem(i, 0, new QTableWidgetItem(m_lstAllSubs->at(i)->id));
            m_ui->tbl_SubRtsConf_SubsAll->setItem(i, 1, new QTableWidgetItem(m_lstAllSubs->at(i)->name));
            //
            m_ui->tbl_SubRtsConf_SubsAll->setCellWidget(i, 2, new QCheckBox());
            m_ui->tbl_SubRtsConf_SubsAll->setCellWidget(i, 3, new QCheckBox());
            ((QCheckBox*) m_ui->tbl_SubRtsConf_SubsAll->cellWidget(i,2))->setChecked(m_lstAllSubs->at(i)->rootbegin == 1);
            ((QCheckBox*) m_ui->tbl_SubRtsConf_SubsAll->cellWidget(i,3))->setChecked(m_lstAllSubs->at(i)->rootend == 1);
            //
            m_ui->tbl_SubRtsConf_SubsAll->setItem(i, 4, new QTableWidgetItem(m_lstAllSubs->at(i)->descr));
            m_ui->tbl_SubRtsConf_SubsAll->item(i,1)->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        }
    } catch (std::exception &exc) {
        std::cerr << exc.what() << std::endl;
    }
    m_ui->tbl_SubRtsConf_SubsAll->blockSignals(false);
}

void SubRouteConf::upd_devsInSub_view()
{
    m_ui->tbl_SubRtsConf_DevsInSub->blockSignals(true);
    try {
        while(m_ui->tbl_SubRtsConf_DevsInSub->rowCount() > 0){
            m_ui->tbl_SubRtsConf_DevsInSub->removeRow(0);
        }
        for(int i = 0; i < m_lstDevsInSub->length(); ++i){
            m_ui->tbl_SubRtsConf_DevsInSub->insertRow(i);
            m_ui->tbl_SubRtsConf_DevsInSub->setItem(i, 0, new QTableWidgetItem(m_lstDevsInSub->at(i)->id));
            m_ui->tbl_SubRtsConf_DevsInSub->setItem(i, 1, new QTableWidgetItem(m_lstDevsInSub->at(i)->name));
            //
            m_ui->tbl_SubRtsConf_DevsInSub->setItem(i, 2, new QTableWidgetItem(""));
            m_ui->tbl_SubRtsConf_DevsInSub->setItem(i, 3, new QTableWidgetItem(""));
            m_ui->tbl_SubRtsConf_DevsInSub->setItem(i, 4, new QTableWidgetItem(""));
            m_ui->tbl_SubRtsConf_DevsInSub->setItem(i, 5, new QTableWidgetItem(""));

            m_ui->tbl_SubRtsConf_DevsInSub->setItem(i, 6, new QTableWidgetItem(""));
            m_ui->tbl_SubRtsConf_DevsInSub->setItem(i, 7, new QTableWidgetItem(""));
            m_ui->tbl_SubRtsConf_DevsInSub->setItem(i, 8, new QTableWidgetItem(""));
            m_ui->tbl_SubRtsConf_DevsInSub->setItem(i, 9, new QTableWidgetItem(""));
            m_ui->tbl_SubRtsConf_DevsInSub->setItem(i, 10, new QTableWidgetItem(""));
            //
        }
    } catch (std::exception &exc) {
        std::cerr << exc.what() << std::endl;
    }
    m_ui->tbl_SubRtsConf_DevsInSub->blockSignals(false);
    //***


    m_ui->tbl_SubRtsConf_DevsInSub->blockSignals(true);
    try {
        QTextCodec *codec = QTextCodec::codecForName("CP1251");
        while(m_ui->tbl_SubRtsConf_DevsInSub->rowCount() > 0){
            m_ui->tbl_SubRtsConf_DevsInSub->removeRow(0);
        }

        for(int i = 0; i < m_lstDevsInSub->length(); ++i){
            m_ui->tbl_SubRtsConf_DevsInSub->insertRow(i);

            m_ui->tbl_SubRtsConf_DevsInSub->setItem(i, 0, new QTableWidgetItem(QString::number(m_lstDevsInSub->at(i)->id)));
            m_ui->tbl_SubRtsConf_DevsInSub->setItem(i, 1, new QTableWidgetItem(m_lstDevsInSub->at(i)->name));

            for(int j = FL_CTRONLY_COL; j < FL_TRANSPARENT_COL ; ++j){
                m_ui->tbl_SubRtsConf_DevsInSub->setCellWidget(i, j, new QCheckBox());
            }
            QComboBox *cmb = new QComboBox();
//            Пр : 0 - , 1 - ПрЗ, 2 - ПрР , 3 - Пр
            cmb->addItem(codec->toUnicode("Нет"));
            cmb->addItem(codec->toUnicode("ПрЗ"));
            cmb->addItem(codec->toUnicode("ПрР"));
            cmb->addItem(codec->toUnicode("Пр"));


            cmb->setCurrentIndex(m_lstDevsInSub->at(i)->fl_transparent);

            m_ui->tbl_SubRtsConf_DevsInSub->setCellWidget(i, FL_TRANSPARENT_COL, std::move(cmb));



            ((QCheckBox*) m_ui->tbl_SubRtsConf_DevsInSub->cellWidget(i,FL_CTRONLY_COL))->setChecked(m_lstDevsInSub->at(i)->fl_ctronly == 1);
            ((QCheckBox*) m_ui->tbl_SubRtsConf_DevsInSub->cellWidget(i,FL_CTRLPROD_COL))->setChecked(m_lstDevsInSub->at(i)->fl_ctrlprod == 1);

            ((QCheckBox*) m_ui->tbl_SubRtsConf_DevsInSub->cellWidget(i,FL_ARMO_COL))->setChecked(m_lstDevsInSub->at(i)->fl_armo == 1);
            ((QCheckBox*) m_ui->tbl_SubRtsConf_DevsInSub->cellWidget(i,FL_PROD_COL))->setChecked(m_lstDevsInSub->at(i)->fl_prod == 1);

            ((QCheckBox*) m_ui->tbl_SubRtsConf_DevsInSub->cellWidget(i,FL_SOLEOWNER_COL))->setChecked(m_lstDevsInSub->at(i)->fl_soleowner == 1);



            m_ui->tbl_SubRtsConf_DevsInSub->setCellWidget(i, FL_DLYPRODSTOP_COL, new QSpinBox());
            m_ui->tbl_SubRtsConf_DevsInSub->setCellWidget(i, FL_TIMESTART_COL, new QSpinBox());
            m_ui->tbl_SubRtsConf_DevsInSub->setCellWidget(i, FL_TIMESTOP_COL, new QSpinBox());


            ((QSpinBox*) m_ui->tbl_SubRtsConf_DevsInSub->cellWidget(i,FL_DLYPRODSTOP_COL))->setValue(m_lstDevsInSub->at(i)->dly_prodstop);
            ((QSpinBox*) m_ui->tbl_SubRtsConf_DevsInSub->cellWidget(i,FL_TIMESTART_COL))->setValue(m_lstDevsInSub->at(i)->time_start);
            ((QSpinBox*) m_ui->tbl_SubRtsConf_DevsInSub->cellWidget(i,FL_TIMESTOP_COL))->setValue(m_lstDevsInSub->at(i)->time_stop);



        }
    } catch (std::exception &exc) {
        std::cerr << exc.what() << std::endl;
    }
    m_ui->tbl_SubRtsConf_DevsInSub->blockSignals(false);
    //***
}

//QString SubRouteConf::get_user_input(QString str)
//{

//    bool ok;
//    QTextCodec *codec = QTextCodec::codecForName("CP1251");
//    QString strUserInput = QInputDialog::getText(nullptr, tr("QInputDialog::getText()"), codec->toUnicode("Название маршрута: "), QLineEdit::Normal, str, &ok);


//    if(ok && !strUserInput.isEmpty()) return strUserInput;

//    return "";

//}



bool SubRouteConf::commonSelectProcedure(std::shared_ptr<QList<StructRoots *> > dataContainer, const QString &someScript, const uint &root_id)
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

        tmp = nodes->at(i)->get_by_name("rootbegin");
        if (tmp != nullptr){
            rts->rootbegin = tmp->m_varValue.toInt();
        }

        tmp = nodes->at(i)->get_by_name("rootend");
        if (tmp != nullptr){
            rts->rootend = tmp->m_varValue.toInt();
        }


        dataContainer->push_back(std::move(rts));
    }
    return true;

}




SubrouteDevsCompleter::SubrouteDevsCompleter(QObject *parent): QAbstractListModel(parent), m_cntDevs(0){    
}

int SubrouteDevsCompleter::rowCount(const QModelIndex &parent) const
{
    return parent.isValid() ? 0 : m_lstDevs.length()-1;
}

QVariant SubrouteDevsCompleter::data(const QModelIndex &index, int role) const{

    if(!index.isValid()) return QVariant();
    std::cout << __PRETTY_FUNCTION__ << std::endl;

    if (index.row() >= m_lstDevs.size() || index.row() < 0)
        return QVariant();

    if(role == Qt::DisplayRole){
        return m_lstDevs.at(index.row());
    }else
        if( role == Qt::BackgroundRole){
            int batch = (index.row() / 10) % 2;
            if(batch == 0)return QBrush(Qt::white);
            else return QBrush(Qt::gray);
        }
    return QVariant();
}

void SubrouteDevsCompleter::setItemSrc(const std::shared_ptr<QList<StructRoots *> > lstAllDevs)
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;

    beginResetModel();
    m_cntDevs = 0;
    for(int i = 0; i < lstAllDevs->length(); ++i){
        m_lstDevs << (lstAllDevs->at(i)->name);
    }
    m_cntDevs = 0;

    endResetModel();
    QModelIndex topLeft = createIndex(0,0);
    emit dataChanged(topLeft,topLeft);
}

void SubrouteDevsCompleter::setItemFilter(const std::shared_ptr<QList<StructRoots *> > lstExistDevs)
{
    beginResetModel();
    for(int i = 0; i < lstExistDevs->length(); ++i){
        auto idx = m_lstDevs.indexOf(lstExistDevs->at(i)->name);
        if(-1 != idx)
            m_lstDevs.removeAt(idx);
    }
    m_cntDevs = 0;
    endResetModel();
    QModelIndex topLeft = createIndex(0,0);
    emit dataChanged(topLeft,topLeft);
}

bool SubrouteDevsCompleter::canFetchMore(const QModelIndex &parent) const{
    if(!parent.isValid()) return false;
    std::cout << __PRETTY_FUNCTION__  << parent.row() << std::endl;
    return (m_cntDevs < m_lstDevs.length());
}

void SubrouteDevsCompleter::fetchMore(const QModelIndex &parent){
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    if(!parent.isValid()) return;

    int remainder = m_lstDevs.length() - m_cntDevs;
    int itemsToFetch = qMin(10, remainder);
    if(itemsToFetch <= 0) return;

    beginInsertRows(QModelIndex(), m_cntDevs, m_cntDevs + itemsToFetch - 1);
    m_cntDevs += itemsToFetch;
    endInsertRows();
    emit numberPopulated(itemsToFetch);
}
