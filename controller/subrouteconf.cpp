#include "subrouteconf.h"

#include "../domain/sqlholder.h"

#include <QCheckBox>
#include <QTextCodec>


SubRouteConf::SubRouteConf(RoutesUI *ui, std::shared_ptr<IDataProvider> provider):UIToDBTable (ui,provider)
{
    configure_UI();
    configure_SIGSLOTS();

    m_lstAllSubs    = std::make_shared<QList<StructRoots *>>();
    m_lstDevsInSub  = std::make_shared<QList<StructRoots *>>();
    m_lstAllDevs    = std::make_shared<QList<StructRoots *>>();
}

void SubRouteConf::tab_idx_changed(int idx)
{
    if(idx == 1){
        selectAllSubs();
        selectAllDevs();
    }
}

void SubRouteConf::configure_UI()
{
    QTextCodec *codec = QTextCodec::codecForName("CP1251");

    m_ui->tbl_SubRtsConf_SubsAll->setColumnCount(5);
    m_ui->tbl_SubRtsConf_SubsAll->setShowGrid(true);
    m_ui->tbl_SubRtsConf_SubsAll->setSelectionMode(QAbstractItemView::SingleSelection);
    m_ui->tbl_SubRtsConf_SubsAll->setSelectionBehavior(QAbstractItemView::SelectItems);
    m_ui->tbl_SubRtsConf_SubsAll->hideColumn(0);
    m_ui->tbl_SubRtsConf_SubsAll->setHorizontalHeaderLabels(QStringList() << "Id" << codec->toUnicode("��� ������") << codec->toUnicode("������") << codec->toUnicode("�����")  << codec->toUnicode("�������") );

    m_ui->tbl_SubRtsConf_DevsInSub->setColumnCount(11);
    m_ui->tbl_SubRtsConf_DevsInSub->setShowGrid(true);
    m_ui->tbl_SubRtsConf_DevsInSub->setSelectionMode(QAbstractItemView::SingleSelection);
    m_ui->tbl_SubRtsConf_DevsInSub->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_ui->tbl_SubRtsConf_DevsInSub->hideColumn(0);
    m_ui->tbl_SubRtsConf_DevsInSub->setHorizontalHeaderLabels(QStringList() << "Id" << codec->toUnicode("����������") << codec->toUnicode("�") << codec->toUnicode("�")
                                                       << codec->toUnicode("��") << codec->toUnicode("��") << codec->toUnicode("�")
                                                       << codec->toUnicode("��") << codec->toUnicode("���")<< codec->toUnicode("�����")<<codec->toUnicode("����"));

}

void SubRouteConf::configure_SIGSLOTS()
{
    connect(m_ui->m_tabWidget,    &QTabWidget::currentChanged, this, &SubRouteConf::tab_idx_changed);
}

bool SubRouteConf::procsSelect()
{
}

bool SubRouteConf::procsInsert()
{
}

bool SubRouteConf::procsUpdate()
{
}

bool SubRouteConf::procsDelete()
{
}

void SubRouteConf::selectAllSubs()
{
    if(commonSelectProcedure(m_lstAllSubs,SELECT_SUBROUTES_RTS)){
        updateSubRoutesView();
    }
}

void SubRouteConf::selectAllDevs()
{

}

void SubRouteConf::updateSubRoutesView()
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
