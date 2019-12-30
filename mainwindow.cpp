#include "mainwindow.h"



#include <QResizeEvent>


#include "dataimpl/ibppdataprovider.h"
#include "controller/routesall.h"
#include "controller/routeconf.h"

#include <controller/subrouteconf.h>



MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new RoutesUI(this))
{    

//    m_provider   = std::make_shared<IBPPDataProvider> ("localhost","/work/cmn/db/trtovs/trtovs_mtr.fdb", "SYSDBA", "masterskey");
    m_provider   = std::make_shared<IBPPDataProvider> ("localhost","/work/cmn/db/trtkr/trtkr_mtr.fdb", "SYSDBA", "masterskey");
    m_ui_all_rts = std::make_shared<RoutesAll>(ui, m_provider);
    m_ui_rt_conf = std::make_shared<RouteConf>(ui, m_provider);
    m_ui_subrt_conf = std::make_shared<SubRouteConf>(ui, m_provider);

    m_provider->connect();    
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    ui->m_tabWidget->resize(event->size());
}

void MainWindow::showEvent(QShowEvent *event)
{
    m_ui_all_rts->procsSelect();
}
//~some common staff
