#include "excholder.h"
#include "exhandlermainavl.h"
#include "ibppdataprovider.h"
#include "instead_c14.h"



ExcHolder::ExcHolder()
{
    m_exc_hndl     = custom_unique::make_unique<IExHandler>();
    m_mapExecutors = custom_unique::make_unique<QMap<QWidget*, QString>>();

//    m_provider     = std::make_shared<IBPPDataProvider> ("localhost","/work/cmn/db/trtovs/trtovs_mtr.fdb", "SYSDBA", "masterskey");
    m_provider     = std::make_shared<IBPPDataProvider> ("localhost","D:/promauto-src/VisScada/PrjTRTKR/trtkr_mtr.fdb","SYSDBA","masterkey");
    m_provider->connect();
}

ExcHolder::~ExcHolder()
{
    m_provider->disconnect();
}

bool ExcHolder::append(QWidget *wdg, const char* someStr, const char *select, const char *del, const char *upd, const char *insert)
{    
    if(m_mapExecutors->contains(wdg)) return false;

    IExHandler *tmp_hndl  = new ExHandlerMainAvl(someStr);
    tmp_hndl->m_strSelect = select;
    tmp_hndl->m_strDelete = del;
    tmp_hndl->m_strInsert = insert;
    tmp_hndl->m_strUpdate = upd;
    m_exc_hndl->add(tmp_hndl);

    m_mapExecutors->insert(wdg, someStr);
    return true;
}

bool ExcHolder::processSelect(QWidget *wdg, std::shared_ptr<QList<ColumnNode *> > dst, ColumnNode *nodePrm)
{
    auto it = m_mapExecutors->find(wdg);
    if(it == m_mapExecutors->end()) return false;
    QString strIdent = m_mapExecutors->value(wdg);
    dst->clear();
    return m_exc_hndl->executeSelect(strIdent.toStdString(), nodePrm, dst, m_provider);
}

bool ExcHolder::processInsert(QWidget *wdg, std::shared_ptr<QList<ColumnNode *> > dst, ColumnNode *nodePrm)
{
    if(nodePrm == nullptr) return false;
    auto it = m_mapExecutors->find(wdg);
    if(it == m_mapExecutors->end()) return false;
    QString strIdent = m_mapExecutors->value(wdg);
    return m_exc_hndl->executeInsert(strIdent.toStdString(), nodePrm, dst, m_provider);

}

bool ExcHolder::processUpdate(QWidget *wdg, std::shared_ptr<QList<ColumnNode *> > dst, ColumnNode *nodePrm)
{
    if(nodePrm == nullptr) return false;
    auto it = m_mapExecutors->find(wdg);
    if(it == m_mapExecutors->end()) return false;
    QString strIdent = m_mapExecutors->value(wdg);
    return m_exc_hndl->executeUpdate(strIdent.toStdString(), nodePrm, dst, m_provider);
}

bool ExcHolder::processDelete(QWidget *wdg, std::shared_ptr<QList<ColumnNode *> > dst, ColumnNode *nodePrm)
{
    if(nodePrm == nullptr) return false;
    auto it = m_mapExecutors->find(wdg);
    if(it == m_mapExecutors->end()) return false;
    QString strIdent = m_mapExecutors->value(wdg);
    return m_exc_hndl->executeDelete(strIdent.toStdString(), nodePrm, dst, m_provider);
}

QVariant ExcHolder::unpack(std::shared_ptr<QList<ColumnNode *> > nodes, const QString &strColName, const int &irow)
{
    return m_exc_hndl->unpack(nodes, strColName, irow);
}
