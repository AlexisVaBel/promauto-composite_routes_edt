#ifndef SUBROUTECONF_H
#define SUBROUTECONF_H

#include "uitodbtable.h"
#include "domain/roots.h"



class SubRouteConf : public UIToDBTable
{
    Q_OBJECT
public:
    SubRouteConf(RoutesUI *ui = nullptr, std::shared_ptr<IDataProvider> provider = nullptr);


public slots:
    void    tab_idx_changed(int idx);


public:
    virtual void configure_UI() override;
    virtual void configure_SIGSLOTS() override;
    virtual bool procsSelect() override;
    virtual bool procsInsert() override;
    virtual bool procsUpdate() override;
    virtual bool procsDelete() override;

private:
    std::shared_ptr<QList<StructRoots*>>    m_lstAllSubs;
    std::shared_ptr<QList<StructRoots*>>    m_lstDevsInSub;

    std::shared_ptr<QList<StructRoots*>>    m_lstAllDevs;

    void selectAllSubs();
    void selectAllDevs();

    void updateSubRoutesView();


    bool commonSelectProcedure(std::shared_ptr<QList<StructRoots *> > dataContainer, const QString &someScript, const uint &root_id = 0);
};



#endif // SUBROUTECONF_H
