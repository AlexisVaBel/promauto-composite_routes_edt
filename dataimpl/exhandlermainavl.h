#pragma once

#include "../dataiface/iexhandler.h"

#include <QTextCodec>
#include <iostream>


struct ExHandlerMainAvl: public IExHandler{

    ExHandlerMainAvl(const char* someStr): IExHandler(someStr){}
    ~ExHandlerMainAvl() override {
        if(m_next)  delete m_next;
    }


    // IExHandler interface
public:
    virtual bool executeSelect(const std::string &strIdent, ColumnNode *nodePrm, std::shared_ptr<QList<ColumnNode *> > nodes, std::shared_ptr<IDataProvider> provider) override;
    virtual bool executeInsert(const std::string &strIdent, ColumnNode *nodePrm, std::shared_ptr<QList<ColumnNode *> > nodes, std::shared_ptr<IDataProvider> provider) override;
    virtual bool executeUpdate(const std::string &strIdent, ColumnNode *nodePrm, std::shared_ptr<QList<ColumnNode *> > nodes, std::shared_ptr<IDataProvider> provider) override;
    virtual bool executeDelete(const std::string &strIdent, ColumnNode *nodePrm, std::shared_ptr<QList<ColumnNode *> > nodes, std::shared_ptr<IDataProvider> provider) override;

private:
    QString prepareSQL(QString strSql, ColumnNode *nodePrm);
};



bool ExHandlerMainAvl::executeSelect(const std::string &strIdent, ColumnNode *nodePrm, std::shared_ptr<QList<ColumnNode *> > nodes, std::shared_ptr<IDataProvider> provider)
{    
    if(strIdent.compare(get_selfName()) == 0){        

        QString strSQL = prepareSQL(m_strSelect, nodePrm);
        std::cout << m_strSelect.toStdString()  << ": select sql is " << strSQL.toStdString() << std::endl;

        if(strSQL.isEmpty()) return false;

        return provider->proces_sql(strSQL.toStdString(), false, nodes);

    }
    return  IExHandler::executeSelect(strIdent, nodePrm, nodes, provider);
}

bool ExHandlerMainAvl::executeInsert(const std::string &strIdent, ColumnNode *nodePrm, std::shared_ptr<QList<ColumnNode *> > nodes, std::shared_ptr<IDataProvider> provider)
{
    if(strIdent.find(get_selfName()) == 0){                
        QString strSQL = prepareSQL(m_strInsert, nodePrm);
        std::cout << m_strInsert.toStdString()  << ": insert sql is " << strSQL.toStdString() << std::endl;
        if(strSQL.isEmpty()) return false;
        QTextCodec *codec = QTextCodec::codecForName("CP1251");
        return provider->proces_sql(codec->fromUnicode(strSQL).toStdString(), true, nodes);

    }
    return  IExHandler::executeInsert(strIdent, nodePrm, nodes, provider);
}

bool ExHandlerMainAvl::executeUpdate(const std::string &strIdent, ColumnNode *nodePrm, std::shared_ptr<QList<ColumnNode *> > nodes, std::shared_ptr<IDataProvider> provider)
{
    if(strIdent.find(get_selfName()) == 0){        
        QString strSQL = prepareSQL(m_strUpdate, nodePrm);
        if(strSQL.isEmpty()) return false;

        QTextCodec *codec = QTextCodec::codecForName("CP1251");

        return provider->proces_sql(codec->fromUnicode(strSQL).toStdString(), true, nodes);

    }
    return  IExHandler::executeUpdate(strIdent, nodePrm, nodes, provider);
}

bool ExHandlerMainAvl::executeDelete(const std::string &strIdent, ColumnNode *nodePrm, std::shared_ptr<QList<ColumnNode *> > nodes, std::shared_ptr<IDataProvider> provider)
{
    if(strIdent.find(get_selfName()) == 0){        
        QString strSQL = prepareSQL(m_strDelete, nodePrm);
        std::cout << __PRETTY_FUNCTION__ << " -- " <<strSQL.toStdString() << std::endl;
        if(strSQL.isEmpty()) return false;
        return provider->proces_sql(strSQL.toStdString(), true, nodes);

    }
    return  IExHandler::executeDelete(strIdent, nodePrm, nodes, provider);
}

QString ExHandlerMainAvl::prepareSQL(QString strSql, ColumnNode *nodePrm)
{

    QString strSqlNew = "", strTmp = strSql;

    ColumnNode *fstCol = nullptr;    

    do{

        std::cout << "to prepare " << strTmp.toStdString() << std::endl ;

        fstCol      = nodePrm;
        auto left   = strTmp.indexOf("%");
        auto right  = strTmp.indexOf("%",left+1);
        QString param1 = strTmp.midRef(left+1,right-left-1).toString();

        if(param1.isEmpty() || !strTmp.contains("%")) {
            return  strSql;
        }

        while (fstCol != nullptr) {
            if(fstCol->m_strColName.compare(param1, Qt::CaseInsensitive) == 0){
                strSqlNew += strTmp.left(left) + fstCol->m_varValue.toString();
                break;
            }
            fstCol = fstCol->nextNode;
        }
        // how to detect if parameter not found? -> simple, just test if fstCol is nullptr;

        if(fstCol == nullptr){
            //node doesn`t have need parameter, going out with empty sql ?? or maybe throw something ?
            return "";
        }
        // how to process such parameters as datetime and string? their need to be quoted, so quotes will be places in sql template
        strTmp = strTmp.rightRef(strTmp.length() - right - 1).toString();        

    }while(strTmp.contains("%"));

    strSqlNew+= strTmp;
    return strSqlNew;
}
