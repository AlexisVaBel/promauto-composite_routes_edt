#pragma once

#include <memory>

#include "idataprovider.h"
#include "../domain/columnnode.h"


struct IExHandler{
public:
    IExHandler(const std::string &selfName = ""):m_next(nullptr), m_strSelfName(selfName){}



    virtual ~IExHandler()
    {
        if(m_next)  delete m_next;
    }

    void add(IExHandler * n)
    {
        if(m_next != nullptr )m_next->add(n);
        else {
            m_next = n;
        }
    }

    virtual QVariant unpack(std::shared_ptr<QList<ColumnNode *>> nodes, const QString &strColName, const int &irow){
        QVariant varOut;
        if(irow >= nodes->size()) return varOut;
        auto nd = nodes->at(irow);
        while( nd->nextNode != nullptr ){
            if(nd->m_strColName.compare(strColName, Qt::CaseInsensitive) == 0){
                varOut = nd->m_varValue;
                break;
            }
            nd = nd->nextNode;
        };

        return varOut;
    }

    virtual QVariant unpack(std::shared_ptr<QList<ColumnNode *>> nodes, const int &icol, const int &irow){
        QVariant varOut;
        if(irow >= nodes->size()) return varOut;

        int lcl_idx = icol;

        auto nd = nodes->at(irow);
        while (nd->nextNode != nullptr && lcl_idx != 0) {
            --lcl_idx;
            nd = nd->nextNode;
        }

        if(lcl_idx == 0) varOut = nd->m_varValue;
        return  varOut;
    }



    virtual bool executeSelect(const std::string &strIdent, ColumnNode *nodePrm, std::shared_ptr<QList<ColumnNode *>> nodes, std::shared_ptr<IDataProvider> provider)
    {
        if(m_next) return m_next->executeSelect(strIdent, nodePrm, nodes, provider);
        return false;
    }

    virtual bool executeInsert(const std::string &strIdent, ColumnNode *nodePrm, std::shared_ptr<QList<ColumnNode *>> nodes, std::shared_ptr<IDataProvider> provider)
    {
        if(m_next) return m_next->executeInsert(strIdent, nodePrm, nodes, provider);
        return false;
    }

    virtual bool executeUpdate(const std::string &strIdent, ColumnNode *nodePrm, std::shared_ptr<QList<ColumnNode *>> nodes, std::shared_ptr<IDataProvider> provider)
    {
        if(m_next) return m_next->executeUpdate(strIdent, nodePrm, nodes, provider);
        return false;
    }

    virtual bool executeDelete(const std::string &strIdent, ColumnNode *nodePrm, std::shared_ptr<QList<ColumnNode *>> nodes, std::shared_ptr<IDataProvider> provider)
    {
        if(m_next) return m_next->executeDelete(strIdent, nodePrm, nodes, provider);
        return false;
    }


    virtual std::string get_selfName() const {return m_strSelfName;}

    IExHandler      * m_next;
    std::string     m_strSelfName;

    QString         m_strSelect;
    QString         m_strInsert;
    QString         m_strUpdate;
    QString         m_strDelete;
};








