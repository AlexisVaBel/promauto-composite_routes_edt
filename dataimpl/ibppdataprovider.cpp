#include "ibppdataprovider.h"

#include <QDate>
#include <QTextCodec>
#include <iostream>


IBPPDataProvider::IBPPDataProvider(std::string &strHost, std::string &strPath, std::string &strUser, std::string &strPass):
    IDataProvider (strHost, strPath, strUser, strPass)
{
    m_db = IBPP::DatabaseFactory(m_strHost, m_strPath, m_strUser, m_strPass);
}

IBPPDataProvider::IBPPDataProvider(std::string &&strHost, std::string &&strPath, std::string &&strUser, std::string &&strPass):
    IDataProvider (strHost, strPath, strUser, strPass)
{
    m_db = IBPP::DatabaseFactory(m_strHost, m_strPath, m_strUser, m_strPass);
}

IBPPDataProvider::~IBPPDataProvider()
{
    disconnect();
}

bool IBPPDataProvider::proces_sql(const std::string &str, bool bDML, std::shared_ptr<QList<ColumnNode *>> m_lst)
{
    IBPP::Transaction tr;
    if(! bDML)
        tr     = IBPP::TransactionFactory(m_db, IBPP::amRead, IBPP::ilReadCommitted, IBPP::lrNoWait, IBPP::tfNoAutoUndo);
    else {
        tr     = IBPP::TransactionFactory(m_db, IBPP::amWrite, IBPP::ilReadCommitted, IBPP::lrNoWait, IBPP::tfNoAutoUndo);        
    }

    auto iVal = 0;
    std::string strRes;

    try {
        IBPP::Statement   state  = IBPP::StatementFactory(m_db,tr);

        tr->Start();
        state->Execute(str);

        if(!bDML){
        QTextCodec *codec = QTextCodec::codecForName("CP1251");

        while (state->Fetch()) {
            iVal = state->Columns();

            ColumnNode *colNode  = new ColumnNode();
            ColumnNode *baseNode = colNode;

            for(auto i = 1 ; i <= iVal; ++ i){

                IBPP::SDT typeSDT = state->ColumnType(i);
                switch (typeSDT) {
                case IBPP::sdString:{
                    state->Get(state->ColumnNum(state->ColumnName(i)), strRes);
                    colNode->m_strValue = codec->toUnicode(strRes.data());
                    colNode->m_varValue = QVariant(codec->toUnicode(strRes.data()));
                    break;
                }
                case IBPP::sdSmallint:
                case IBPP::sdInteger:
                case IBPP::sdLargeint:{
                    state->Get(state->ColumnNum(state->ColumnName(i)), colNode->m_iValue);
                    colNode->m_varValue = QVariant(colNode->m_iValue);
                    break;
                }
                case IBPP::sdFloat:{
                    state->Get(state->ColumnNum(state->ColumnName(i)), colNode->m_fValue);
                    colNode->m_varValue = QVariant(colNode->m_fValue);
                    break;
                }
                case IBPP::sdDouble:{
                    state->Get(state->ColumnNum(state->ColumnName(i)), colNode->m_dValue);
                    colNode->m_varValue = QVariant(colNode->m_dValue);
                    break;
                }
                case IBPP::sdDate:
                case IBPP::sdTime:
                case IBPP::sdTimestamp:{
                    state->Get(state->ColumnNum(state->ColumnName(i)), colNode->m_tstampValue);
                    colNode->setTime();
                    break;
                }
                case IBPP::sdBlob:
                case IBPP::sdArray:
                    break;
                }
                colNode->m_strColName = QString::fromLocal8Bit(state->ColumnName(i));

                colNode->nextNode = new ColumnNode();
                colNode = colNode->nextNode;
                baseNode->m_iColCnt++;
            }
            m_lst->append(baseNode);
        }
        }


        tr->Commit();

    } catch (std::exception &exc) {
        std::cout << exc.what() << " :" << str << std::endl;
        tr->Rollback();        
        return false;
    }

    return  true;
}

bool IBPPDataProvider::connect()
{
    try {
        m_db->Connect();
        m_bConnected = m_db->Connected();
    } catch (std::exception &exc) {
        std::cout << exc.what() << std::endl;
    };
    return m_bConnected;
}

bool IBPPDataProvider::disconnect()
{
    if(m_bConnected){
        m_db->Disconnect();
    }
    m_bConnected = m_db->Connected();
    return !m_bConnected;
}
