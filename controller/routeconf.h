#ifndef SUBROUTESALL_H
#define SUBROUTESALL_H

#include "uitodbtable.h"

#include <QCompleter>

#include "domain/roots.h"




class RouteConf : public UIToDBTable
{
    Q_OBJECT
public:
    RouteConf(RoutesUI *ui = nullptr, std::shared_ptr<IDataProvider> provider = nullptr);
public slots:
    void        subs_cellClicked(int irow, int icol);    
    void        subs_cellDblClicked();    
    void        route_subs_cellDblClicked();

    void        add_subroute(int &idx);
    void        del_subroute(int &idx, int &root_id, int &subroot_id);

    void        tab_idx_changed(int idx);
public:
    // UIToDBTable interface
    virtual void configure_UI() override;
    virtual void configure_SIGSLOTS() override;
    virtual bool procsSelect() override;
    virtual bool procsInsert() override;
    virtual bool procsUpdate() override;
    virtual bool procsDelete() override;

private:
//    StructRoots

    std::shared_ptr<QList<StructRoots*>>    m_lstAllSubs;
    std::shared_ptr<QList<StructRoots*>>    m_lstSubsInRt;
    std::shared_ptr<QList<StructRoots*>>    m_lstDevsInRt;
    std::shared_ptr<QList<StructRoots*>>    m_lstDevsInSub;

    std::shared_ptr<QList<StructRoots*>>    m_lstRoutes;


    QCompleter      *m_completer;    


    void updateSubRoutesView() ;
    void updateSubInRouteView() ;
    void updateDevsInSubView();
    void updateDevsView() ;


    void selectDevsNSubs();
    void selectAllSubs();

    void selectDevsInSub(int id);

    void selectSubs(int id);
    void selectDevs(int id);


    bool can_add_sub_toRoute(); // devices in subroute couldn`t  intersect with devs in route;


    void selectRoutes(); // for autocompleter

    bool commonSelectProcedure(std::shared_ptr<QList<StructRoots*>> dataContainer, const QString &someScript, const uint &root_id = 0);
};


#endif // SUBROUTESALL_H
