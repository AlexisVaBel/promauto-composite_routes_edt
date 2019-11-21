#ifndef UITODBTABLE_H
#define UITODBTABLE_H


#include <visual/routesui.h>
#include <dataiface/idataprovider.h>


class UIToDBTable: public QObject
{
Q_OBJECT
public:
    UIToDBTable(RoutesUI *ui = nullptr, std::shared_ptr<IDataProvider> provider = nullptr);
    virtual ~UIToDBTable(){ }

    virtual void configure_UI()  = 0;
    virtual void configure_SIGSLOTS() = 0;    

    virtual bool procsSelect() = 0;
    virtual bool procsInsert() = 0;
    virtual bool procsUpdate() = 0;
    virtual bool procsDelete() = 0;

protected:
    RoutesUI    *m_ui;    
    std::shared_ptr<IDataProvider> m_provider;
};

#endif // UITODBTABLE_H
