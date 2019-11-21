#pragma once

#include <memory>

#include <QWidget>
#include <QMap>

#include <dataiface/iexhandler.h>
#include "domain/columnnode.h"

// zone of its work :: processing sqls and dmls

class ExcHolder
{
public:
    ExcHolder();
    ~ExcHolder();

    bool append(QWidget *wdg, const char* someStr, const char *select, const char *del, const char *upd, const char *insert);

    bool processSelect(QWidget *wdg, std::shared_ptr<QList<ColumnNode*>> dst, ColumnNode *nodePrm);
    bool processInsert(QWidget *wdg, std::shared_ptr<QList<ColumnNode *> > dst, ColumnNode *nodePrm);
    bool processUpdate(QWidget *wdg, std::shared_ptr<QList<ColumnNode *> > dst, ColumnNode *nodePrm);
    bool processDelete(QWidget *wdg, std::shared_ptr<QList<ColumnNode *> > dst, ColumnNode *nodePrm);

    QVariant unpack(std::shared_ptr<QList<ColumnNode *>> nodes, const QString &strColName, const int &irow);

private:
    // why not to hould executor pointers inside this map?
    // need to refactor !!!

    std::unique_ptr<QMap<QWidget*, QString>> m_mapExecutors;
    std::unique_ptr<IExHandler> m_exc_hndl;
    std::shared_ptr<IDataProvider> m_provider;
};


