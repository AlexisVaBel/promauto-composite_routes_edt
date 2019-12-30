#ifndef SUBROUTECONF_H
#define SUBROUTECONF_H

#include "uitodbtable.h"
#include "domain/roots.h"



class SubrouteDevsCompleter: public QAbstractListModel{
   Q_OBJECT
public:
    SubrouteDevsCompleter(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex() ) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

signals:
    void numberPopulated(int number);

public slots:
    void setItemSrc(const std::shared_ptr<QList<StructRoots*>> lstAllDevs);

    void setItemFilter(const std::shared_ptr<QList<StructRoots*>> lstExistDevs);

protected:
    bool canFetchMore(const QModelIndex &parent) const override;

    void fetchMore(const QModelIndex &parent) override;

private:
    QStringList m_lstDevs;
    int m_cntDevs;
};



class SubRouteConf : public UIToDBTable
{
    Q_OBJECT
public:
    SubRouteConf(RoutesUI *ui = nullptr, std::shared_ptr<IDataProvider> provider = nullptr);


public slots:
    void    subs_cellClicked(int irow, int icol);
    void    tab_idx_changed(int idx);


    void    add_device();

public:
    virtual void configure_UI() override;
    virtual void configure_SIGSLOTS() override;
    virtual bool procsSelect() override;
    virtual bool procsInsert() override;
    virtual bool procsUpdate() override;
    virtual bool procsDelete() override;

private:
    QCompleter                              *m_completer;
    std::shared_ptr<QStringList>            m_lstCompleter;
    std::shared_ptr<QList<StructRoots*>>    m_lstAllSubs;
    std::shared_ptr<QList<StructRoots*>>    m_lstDevsInSub;

    std::shared_ptr<QList<StructRoots*>>    m_lstAllDevs;


//    SubrouteDevsCompleter                   *m_modelDevs;
//    std::shared_ptr<QStringList>              m_modelDevs;


    void sel_allSubs();
    void sel_allDevs();

    void sel_devs_inSub(uint id);

    void upd_subRts_view();
    void upd_devsInSub_view();


    bool commonSelectProcedure(std::shared_ptr<QList<StructRoots *> > dataContainer, const QString &someScript, const uint &root_id = 0);
};



#endif // SUBROUTECONF_H
