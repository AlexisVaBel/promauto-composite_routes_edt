#pragma once

#include "../dataiface/idataprovider.h"

#include <ibpp.h>

class IBPPDataProvider : public IDataProvider
{
public:
    virtual ~IBPPDataProvider() override;

    IBPPDataProvider(std::string &strHost, std::string &strPath, std::string &strUser, std::string &strPass);

    IBPPDataProvider(std::string &&strHost, std::string &&strPath, std::string &&strUser, std::string &&strPass);

    // IDataProvider interface

    bool proces_sql(const std::string &str, bool bDML = false, std::shared_ptr<QList<ColumnNode *>> m_lst = nullptr) override;

    bool connect() override;

    bool disconnect() override;

    IBPP::Database get_DB() const {return  m_db;}

private:
    IBPP::Database m_db;
};


