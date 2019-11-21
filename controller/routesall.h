#ifndef ROUTESALL_H
#define ROUTESALL_H

#include "uitodbtable.h"


struct STRCT_ALL_ROUTES;
struct STRCT_SUBS_IN_ROUTE;
struct STRCT_DEVS_IN_ROUTE;


class RoutesAll : public UIToDBTable
{
Q_OBJECT
public:
    RoutesAll(RoutesUI *ui = nullptr, std::shared_ptr<IDataProvider> provider = nullptr);

    // UIToDBTable interface
public slots:
    void        routes_cellClicked(int irow, int icol);
    void        main_cellChanged(int irow, int icol, int iprevRow, int iprevCol);
    void        main_cellDblClicked(int irow, int icol);

    QString     get_user_input(QString str);

    void        update_devs();

    void        add_route();
    void        del_route();
    void        update_route();

    void        tab_idx_changed(int idx);

public:
    virtual void configure_UI() override;
    virtual void configure_SIGSLOTS() override;

    virtual bool procsSelect() override;
    virtual bool procsInsert() override;
    virtual bool procsUpdate() override;
    virtual bool procsDelete() override;


private:
    std::shared_ptr<QList<STRCT_ALL_ROUTES*>>    m_lstAllRts;
    std::shared_ptr<QList<STRCT_SUBS_IN_ROUTE*>> m_lstSubsInRt;
    std::shared_ptr<QList<STRCT_DEVS_IN_ROUTE*>> m_lstDevsInRt;

    void updateRoutesView() ;
    void updateSubsView() ;
    void updateDevsView() ;

    void selectSubs(int id);
    void selectDevs(int id);

};


#endif // ROUTESALL_H
