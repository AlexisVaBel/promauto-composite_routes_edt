#include "routesall.h"
#include "../domain/sqlholder.h"

#include <QCheckBox>
#include <QComboBox>
#include <QInputDialog>
#include <QPushButton>
#include <QSpinBox>
#include <QTextCodec>
#include <iostream>

struct STRCT_ALL_ROUTES{
    int id;
    QString str_name;
    QString str_descr;
    int code;
};

struct STRCT_SUBS_IN_ROUTE{
    int id;
    int root_id;
    QString str_name;
};

struct STRCT_DEVS_IN_ROUTE{
    // not editable
    int     id;
    int     root_id;
    int     device_id;
    QString str_name;
    //~not editable

    // editable
    int fl_transparent;     // FL_TRANSPARENT - Пр : 0 - , 1 - ПрЗ, 2 - ПрР , 3 - Пр
        // bitwise
    int fl_ctronly;
    int fl_armo;
    int fl_ctrlprod;
    int fl_prod;
    int fl_soleowner;
        //~ bitwise
    int dly_prodstop;
    int order;

    int time_start;
    int time_stop;
    // editable


    bool equal(STRCT_DEVS_IN_ROUTE & that){
        return (this->id == that.id) &&
                (this->fl_transparent == that.fl_transparent ) &&
                (this->fl_armo == that.fl_armo) &&
                (this->fl_prod == that.fl_prod) &&
                (this->fl_ctronly == that.fl_ctronly) &&
                (this->fl_ctrlprod == that.fl_ctrlprod) &&
                (this->fl_soleowner == that.fl_soleowner) &&
                (this->dly_prodstop == that.dly_prodstop) &&
                (this->time_start == that.time_start) &&
                (this->time_stop == that.time_stop) &&
                (this->order == that.order);
    }

    bool equal(STRCT_DEVS_IN_ROUTE * that){
        return (this->id == that->id) &&
                (this->fl_transparent == that->fl_transparent ) &&
                (this->fl_armo == that->fl_armo) &&
                (this->fl_prod == that->fl_prod) &&
                (this->fl_ctronly == that->fl_ctronly) &&
                (this->fl_ctrlprod == that->fl_ctrlprod) &&
                (this->fl_soleowner == that->fl_soleowner) &&
                (this->dly_prodstop == that->dly_prodstop) &&
                (this->time_start == that->time_start) &&
                (this->time_stop == that->time_stop) &&
                (this->order == that->order);
    }

};

// fl_armo - H
// FL_CTRLPROD - Кп
// FL_PROD - Пд
// DLY_PRODSTOP - ПдЗ
// FL_TRANSPARENT - Пр : 0 - , 1 - ПрЗ, 2 - ПрР , 3 - Пр
// FL_SOLEOWNER - И
// FL_CTRLONLY - К - Только контроль без управления
// << ("ПдЗ")<<("Пр")<< ("И")<<("Старт")<< ("Стоп"))

static const int FL_CTRONLY_COL      = 2;
static const int FL_ARMO_COL         = 3;
static const int FL_CTRLPROD_COL     = 4;
static const int FL_PROD_COL         = 5;
static const int FL_SOLEOWNER_COL    = 6;
static const int FL_TRANSPARENT_COL  = 7;
static const int FL_DLYPRODSTOP_COL  = 8;
static const int FL_TIMESTART_COL    = 9;
static const int FL_TIMESTOP_COL     = 10;

//


RoutesAll::RoutesAll(RoutesUI *ui, std::shared_ptr<IDataProvider> provider):UIToDBTable (ui, provider)
{
    configure_UI();
    configure_SIGSLOTS();
    m_lstAllRts     = std::make_shared<QList<STRCT_ALL_ROUTES*>>();
    m_lstSubsInRt   = std::make_shared<QList<STRCT_SUBS_IN_ROUTE*>>();;
    m_lstDevsInRt   = std::make_shared<QList<STRCT_DEVS_IN_ROUTE*>>();;
}

void RoutesAll::routes_cellClicked(int irow, int icol)
{    
    if(irow >= m_lstAllRts->length()) return;
    int idRoute = m_lstAllRts->at(irow)->id;
    selectSubs(idRoute);
    selectDevs(idRoute);
}

void RoutesAll::main_cellChanged(int irow, int icol, int iprevRow, int iprevCol)
{

    routes_cellClicked(irow, icol);
}

void RoutesAll::main_cellDblClicked(int irow, int icol)
{

}

QString RoutesAll::get_user_input(QString str)
{
    bool ok;
    QString strUserInput = QInputDialog::getText(nullptr, tr("QInputDialog::getText()"), tr("Some input: "), QLineEdit::Normal, str, &ok);

    if(ok && !strUserInput.isEmpty()) return strUserInput;

    return "";
}

void RoutesAll::update_devs()
{
    //
    int root_id  = 0;
    bool bSucces = false;

    for(int i = 0; i < m_ui->tbl_RtsAll_AllDevs->rowCount(); ++i){

    // Manual mode "DELETE FROM  SUBROOTS WHERE  ID = :OLD_ID"

        STRCT_DEVS_IN_ROUTE *devs_in_route = new STRCT_DEVS_IN_ROUTE();
        STRCT_DEVS_IN_ROUTE *devs_in_route_to_cmp = nullptr;
        devs_in_route->id = m_ui->tbl_RtsAll_AllDevs->item(i,0)->text().toInt();

        for(int j = 0; j < m_lstDevsInRt->length(); ++j){
            if(devs_in_route->id == m_lstDevsInRt->at(j)->id){
                devs_in_route_to_cmp = m_lstDevsInRt->at(j);
                break;
            }
        }

        if(devs_in_route_to_cmp == nullptr) continue; // none found to update

        // fill struct from table
        devs_in_route->fl_armo       = ((QCheckBox*)  m_ui->tbl_RtsAll_AllDevs->cellWidget(i,FL_ARMO_COL))->isChecked() ? 1 : 0;
        devs_in_route->fl_prod       = ((QCheckBox*)  m_ui->tbl_RtsAll_AllDevs->cellWidget(i,FL_PROD_COL))->isChecked() ? 1 : 0;
        devs_in_route->fl_ctronly    = ((QCheckBox*)  m_ui->tbl_RtsAll_AllDevs->cellWidget(i,FL_CTRONLY_COL))->isChecked() ? 1 : 0;
        devs_in_route->fl_ctrlprod   = ((QCheckBox*)  m_ui->tbl_RtsAll_AllDevs->cellWidget(i,FL_CTRLPROD_COL))->isChecked() ? 1 : 0;
        devs_in_route->fl_soleowner  = ((QCheckBox*)  m_ui->tbl_RtsAll_AllDevs->cellWidget(i,FL_SOLEOWNER_COL))->isChecked() ? 1 : 0;
        devs_in_route->fl_transparent= ((QComboBox*)  m_ui->tbl_RtsAll_AllDevs->cellWidget(i,FL_TRANSPARENT_COL))->currentIndex();

        devs_in_route->dly_prodstop  = ((QSpinBox *) m_ui->tbl_RtsAll_AllDevs->cellWidget(i,FL_DLYPRODSTOP_COL))->value();
        devs_in_route->time_start    = ((QSpinBox *) m_ui->tbl_RtsAll_AllDevs->cellWidget(i,FL_TIMESTART_COL))->value();
        devs_in_route->time_stop     = ((QSpinBox *) m_ui->tbl_RtsAll_AllDevs->cellWidget(i,FL_TIMESTOP_COL))->value();

        if(!devs_in_route->equal(devs_in_route_to_cmp)){

            QString strDML = UPDATE_DEVS_IN_RT_ALL;
//" timestart = %1, timestop = %2 , ordernum = %3, FL_CTRLONLY = %4 , FL_ARMO =%5, FL_TRANSPARENT = %6, FL_CTRLPROD = %7, FL_PROD = %8, FL_SOLEOWNER = %9, DLY_PRODSTOP=%10 where id=%11"
            strDML = strDML.arg(devs_in_route->time_start).arg(devs_in_route->time_stop);
            strDML = strDML.arg(i).arg(devs_in_route->fl_ctronly);
            std::cout << "got DML " << strDML.toStdString() << std::endl;
            strDML = strDML.arg(devs_in_route->fl_armo).arg(devs_in_route->fl_transparent).arg(devs_in_route->fl_ctrlprod).arg(devs_in_route->fl_prod).arg(devs_in_route->fl_soleowner).arg(devs_in_route->dly_prodstop);
            strDML = strDML.arg(devs_in_route->id);

            if(!m_provider->proces_sql((strDML).toStdString(), true, nullptr)){
                std::cout << "no way it`s wrong";
                return ;
            }else{                
                bSucces = true;
                root_id = devs_in_route_to_cmp->root_id;
            }
        };


        delete devs_in_route;
    }    

    if(bSucces) selectDevs(root_id);
}

void RoutesAll::add_route()
{
    QTextCodec *codec = QTextCodec::codecForName("CP1251");

    QString strSomeText = get_user_input(codec->toUnicode("Новый маршрут"));
    if(strSomeText.isEmpty()) return;

    for(int i = 0; i < m_lstAllRts->length(); ++i){
        if(m_lstAllRts->at(i)->str_name.compare(strSomeText, Qt::CaseInsensitive) == 0){
            std::cout << "already exists " << strSomeText.toStdString() << std::endl;
            return;
        }
    }

    QString strDML = INSERT_ROUTE_ALL;
    strDML = strDML.arg(strSomeText);

    if(m_provider->proces_sql(codec->fromUnicode(strDML).toStdString(), true, nullptr)){
        procsSelect();
    }
}

void RoutesAll::del_route()
{
    auto lstSelected = m_ui->tbl_RtsAll_AvlRts->selectionModel()->selectedRows();
    if(lstSelected.length() != 1)return;

    // take id for delete
    int id = m_lstAllRts->at(lstSelected.at(0).row())->id;
    QString strDML = DELETE_ROUTE_ALL;
    strDML = strDML.arg(id);

    if(m_provider->proces_sql(strDML.toStdString(), true, nullptr)){
        procsSelect();
    }
}

void RoutesAll::update_route()
{

    auto lstSelected = m_ui->tbl_RtsAll_AvlRts->selectionModel()->selectedRows();
    if(lstSelected.length() != 1)return;

    // take id for delete
    int id = m_lstAllRts->at(lstSelected.at(0).row())->id;

    QTextCodec *codec = QTextCodec::codecForName("CP1251");
    QString strSomeText = m_lstAllRts->at(lstSelected.at(0).row())->str_name;
    strSomeText = get_user_input(strSomeText);

    if(strSomeText.isEmpty()) return;   // empty input
    if(strSomeText.compare(m_lstAllRts->at(lstSelected.at(0).row())->str_name,Qt::CaseInsensitive) == 0) return; // nothing changed

    QString strDML = UPDATE_ROUTE_ALL;
    strDML = strDML.arg(strSomeText).arg(id);

    if(m_provider->proces_sql(codec->fromUnicode(strDML).toStdString(), true, nullptr)){
        procsSelect();
    }

}

void RoutesAll::tab_idx_changed(int idx)
{
    if(idx == 0){
        procsSelect();
    }
}


void RoutesAll::configure_UI()
{
    QTextCodec *codec = QTextCodec::codecForName("CP1251");
    //main table
    m_ui->tbl_RtsAll_AvlRts->setColumnCount(2);
    m_ui->tbl_RtsAll_AvlRts->setShowGrid(true);
    m_ui->tbl_RtsAll_AvlRts->setSelectionMode(QAbstractItemView::SingleSelection);
    m_ui->tbl_RtsAll_AvlRts->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_ui->tbl_RtsAll_AvlRts->hideColumn(0);

    m_ui->tbl_RtsAll_AvlRts->setHorizontalHeaderLabels(QStringList() << "Id" << codec->toUnicode("Маршруты"));

    // available subroutes
    m_ui->tbl_RtsAll_SubsInRt->setColumnCount(1);
    m_ui->tbl_RtsAll_SubsInRt->setShowGrid(true);
    m_ui->tbl_RtsAll_SubsInRt->setSelectionMode(QAbstractItemView::SingleSelection);
    m_ui->tbl_RtsAll_SubsInRt->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_ui->tbl_RtsAll_SubsInRt->setHorizontalHeaderLabels(QStringList() << codec->toUnicode("Группы маршрута"));

    // available devices
    m_ui->tbl_RtsAll_AllDevs->setColumnCount(11);
    m_ui->tbl_RtsAll_AllDevs->setShowGrid(true);
    m_ui->tbl_RtsAll_AllDevs->setSelectionMode(QAbstractItemView::SingleSelection);
    m_ui->tbl_RtsAll_AllDevs->setSelectionBehavior(QAbstractItemView::SelectItems);
    m_ui->tbl_RtsAll_AllDevs->hideColumn(0);
    m_ui->tbl_RtsAll_AllDevs->setHorizontalHeaderLabels(QStringList() << "Id" << codec->toUnicode("Устройства") << codec->toUnicode("К") << codec->toUnicode("Н")
                                                       << codec->toUnicode("Кп") << codec->toUnicode("Пд") << codec->toUnicode("И")
                                                       << codec->toUnicode("Пр") << codec->toUnicode("ПдЗ")<< codec->toUnicode("Старт")<<codec->toUnicode("Стоп"));

    m_ui->m_pnlBtnsMnRts->btnAccept->setText(codec->toUnicode("Изменить"));

}

void RoutesAll::configure_SIGSLOTS()
{

    connect(m_ui->m_tabWidget,    &QTabWidget::currentChanged, this, &RoutesAll::tab_idx_changed);

    connect(m_ui->tbl_RtsAll_AvlRts, &QTableWidget::cellClicked        , this, &RoutesAll::routes_cellClicked );
    connect(m_ui->tbl_RtsAll_AvlRts, &QTableWidget::currentCellChanged , this, &RoutesAll::main_cellChanged );
    connect(m_ui->tbl_RtsAll_AvlRts, &QTableWidget::doubleClicked      , this, &RoutesAll::update_route );

    connect(m_ui->m_pnlBtnsMnDevs->btnAccept, &QPushButton::pressed, this, &RoutesAll::update_devs);


    connect(m_ui->m_pnlBtnsMnRts->btnAdd, &QPushButton::pressed, this, &RoutesAll::add_route);
    connect(m_ui->m_pnlBtnsMnRts->btnDell, &QPushButton::pressed, this, &RoutesAll::del_route);
    connect(m_ui->m_pnlBtnsMnRts->btnAccept, &QPushButton::pressed, this, &RoutesAll::update_route);

}


bool RoutesAll::procsInsert()
{
    return false;
}

bool RoutesAll::procsUpdate()
{
    return false;
}

bool RoutesAll::procsDelete()
{
    return false;
}


// view process
void RoutesAll::updateRoutesView()
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    m_ui->tbl_RtsAll_AvlRts->blockSignals(true);
    try {
        while(m_ui->tbl_RtsAll_AvlRts->rowCount() > 0){
            m_ui->tbl_RtsAll_AvlRts->removeRow(0);
        }
        for(int i = 0; i < m_lstAllRts->length(); ++i){
            m_ui->tbl_RtsAll_AvlRts->insertRow(i);
            m_ui->tbl_RtsAll_AvlRts->setItem(i, 0, new QTableWidgetItem(m_lstAllRts->at(i)->id));
            m_ui->tbl_RtsAll_AvlRts->setItem(i, 1, new QTableWidgetItem(m_lstAllRts->at(i)->str_name));
            m_ui->tbl_RtsAll_AvlRts->item(i,1)->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

        }
    } catch (std::exception &exc) {
        std::cerr << exc.what() << std::endl;
    }
    m_ui->tbl_RtsAll_AvlRts->blockSignals(false);
}

void RoutesAll::updateSubsView()
{
    m_ui->tbl_RtsAll_SubsInRt->blockSignals(true);
    try {
        while(m_ui->tbl_RtsAll_SubsInRt->rowCount() > 0){
            m_ui->tbl_RtsAll_SubsInRt->removeRow(0);
        }

        for(int i = 0; i < m_lstSubsInRt->length(); ++i){
            m_ui->tbl_RtsAll_SubsInRt->insertRow(i);
            m_ui->tbl_RtsAll_SubsInRt->setItem(i, 0, new QTableWidgetItem(m_lstSubsInRt->at(i)->str_name));
        }
    } catch (std::exception &exc) {
        std::cerr << exc.what() << std::endl;
    }
    m_ui->tbl_RtsAll_SubsInRt->blockSignals(false);
}

void RoutesAll::updateDevsView()
{
    m_ui->tbl_RtsAll_AllDevs->blockSignals(true);

    try {
        QTextCodec *codec = QTextCodec::codecForName("CP1251");
        while(m_ui->tbl_RtsAll_AllDevs->rowCount() > 0){
            m_ui->tbl_RtsAll_AllDevs->removeRow(0);
        }

        for(int i = 0; i < m_lstDevsInRt->length(); ++i){
            m_ui->tbl_RtsAll_AllDevs->insertRow(i);

            m_ui->tbl_RtsAll_AllDevs->setItem(i, 0, new QTableWidgetItem(QString::number(m_lstDevsInRt->at(i)->id)));
            m_ui->tbl_RtsAll_AllDevs->setItem(i, 1, new QTableWidgetItem(m_lstDevsInRt->at(i)->str_name));

            for(int j = FL_CTRONLY_COL; j < FL_TRANSPARENT_COL ; ++j){
                m_ui->tbl_RtsAll_AllDevs->setCellWidget(i, j, new QCheckBox());
            }
            QComboBox *cmb = new QComboBox();
//            Пр : 0 - , 1 - ПрЗ, 2 - ПрР , 3 - Пр
            cmb->addItem(codec->toUnicode("Нет"));
            cmb->addItem(codec->toUnicode("ПрЗ"));
            cmb->addItem(codec->toUnicode("ПрР"));
            cmb->addItem(codec->toUnicode("Пр"));

            cmb->setCurrentIndex(m_lstDevsInRt->at(i)->fl_transparent);

            m_ui->tbl_RtsAll_AllDevs->setCellWidget(i, FL_TRANSPARENT_COL, std::move(cmb));



            ((QCheckBox*) m_ui->tbl_RtsAll_AllDevs->cellWidget(i,FL_CTRONLY_COL))->setChecked(m_lstDevsInRt->at(i)->fl_ctronly == 1);
            ((QCheckBox*) m_ui->tbl_RtsAll_AllDevs->cellWidget(i,FL_CTRLPROD_COL))->setChecked(m_lstDevsInRt->at(i)->fl_ctrlprod == 1);

            ((QCheckBox*) m_ui->tbl_RtsAll_AllDevs->cellWidget(i,FL_ARMO_COL))->setChecked(m_lstDevsInRt->at(i)->fl_armo == 1);
            ((QCheckBox*) m_ui->tbl_RtsAll_AllDevs->cellWidget(i,FL_PROD_COL))->setChecked(m_lstDevsInRt->at(i)->fl_prod == 1);

            ((QCheckBox*) m_ui->tbl_RtsAll_AllDevs->cellWidget(i,FL_SOLEOWNER_COL))->setChecked(m_lstDevsInRt->at(i)->fl_soleowner == 1);



            m_ui->tbl_RtsAll_AllDevs->setCellWidget(i, FL_DLYPRODSTOP_COL, new QSpinBox());
            m_ui->tbl_RtsAll_AllDevs->setCellWidget(i, FL_TIMESTART_COL, new QSpinBox());
            m_ui->tbl_RtsAll_AllDevs->setCellWidget(i, FL_TIMESTOP_COL, new QSpinBox());


            ((QSpinBox*) m_ui->tbl_RtsAll_AllDevs->cellWidget(i,FL_DLYPRODSTOP_COL))->setValue(m_lstDevsInRt->at(i)->dly_prodstop);
            ((QSpinBox*) m_ui->tbl_RtsAll_AllDevs->cellWidget(i,FL_TIMESTART_COL))->setValue(m_lstDevsInRt->at(i)->time_start);
            ((QSpinBox*) m_ui->tbl_RtsAll_AllDevs->cellWidget(i,FL_TIMESTOP_COL))->setValue(m_lstDevsInRt->at(i)->time_stop);



        }
    } catch (std::exception &exc) {
        std::cerr << exc.what() << std::endl;
    }
    m_ui->tbl_RtsAll_AllDevs->blockSignals(false);
}

//~view process

void RoutesAll::selectSubs(int id)
{    
    std::shared_ptr<QList<ColumnNode *> > nodes = std::make_shared<QList<ColumnNode *> >();
    if(!m_provider->proces_sql(QString(SELECT_SUBS_IN_RT_ALL).arg(id).toStdString(), false, nodes)) return ;

    m_lstSubsInRt->clear();
    for(int i = 0; i < nodes->length(); ++i){
        auto tmp = nodes->at(i)->get_by_name("Id");
        STRCT_SUBS_IN_ROUTE *rts = new STRCT_SUBS_IN_ROUTE();
        if (tmp != nullptr){
            rts->id = tmp->m_varValue.toInt();
        }
        tmp = nodes->at(i)->get_by_name("Name");
        if (tmp != nullptr){
            rts->str_name = tmp->m_varValue.toString();
        }
        m_lstSubsInRt->push_back(std::move(rts));
    }
    updateSubsView();
}


void RoutesAll::selectDevs(int id)
{

    std::shared_ptr<QList<ColumnNode *> > nodes = std::make_shared<QList<ColumnNode *> >();

    if(!m_provider->proces_sql(QString(SELECT_DEVS_IN_RT_ALL).arg(id).toStdString(), false, nodes)) return ;

    m_lstDevsInRt->clear();
    for(int i = 0; i < nodes->length(); ++i){
        STRCT_DEVS_IN_ROUTE *rts = new STRCT_DEVS_IN_ROUTE();
        auto tmp = nodes->at(i)->get_by_name("id");
        rts->root_id = id;

        if (tmp != nullptr){
            rts->id = tmp->m_varValue.toInt();
        }
        tmp = nodes->at(i)->get_by_name("Name");
        if (tmp != nullptr){
            rts->str_name = tmp->m_varValue.toString();
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

        m_lstDevsInRt->push_back(std::move(rts));
    }

    updateDevsView();
}

bool RoutesAll::procsSelect()
{
    std::shared_ptr<QList<ColumnNode *> > nodes = std::make_shared<QList<ColumnNode *> >();
    if(!m_provider->proces_sql(SELECT_ROUTES_ALL, false, nodes)) return false;
    //
    m_lstAllRts->clear();
    for(int i = 0; i < nodes->length(); ++i){        
        STRCT_ALL_ROUTES *rts = new STRCT_ALL_ROUTES();

        auto tmp = nodes->at(i)->get_by_name("Id");
        if (tmp != nullptr){
            rts->id = tmp->m_varValue.toInt();            
        }
        tmp = nodes->at(i)->get_by_name("Name");
        if (tmp != nullptr){
            rts->str_name = tmp->m_varValue.toString();
        }
        m_lstAllRts->push_back(std::move(rts));
    }
    updateRoutesView();
    return true;
}
