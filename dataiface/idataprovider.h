#pragma once

#include <string>
#include <memory>
#include <iostream>

#include <QList>
#include "../domain/columnnode.h"

class IDataProvider{
public:
    IDataProvider(std::string &strHost, std::string &strPath, std::string &strUser, std::string &strPass):
        m_strHost(strHost), m_strPath(strPath), m_strUser(strUser), m_strPass(strPass){
        std::cout << " " << m_strHost << " | " << m_strPath << " | " << m_strUser << " | " << m_strPass <<  std::endl;
    }

    virtual ~IDataProvider(){}

    virtual bool proces_sql(const std::string &str, bool bDML = false, std::shared_ptr<QList<ColumnNode *>> m_lst = nullptr) = 0 ;
    virtual bool is_connected(){ return m_bConnected;}
    virtual bool connect()    = 0;
    virtual bool disconnect() = 0;

protected:
    std::string m_strHost;
    std::string m_strPath;
    std::string m_strUser;
    std::string m_strPass;

    bool    m_bConnected{false};
};
