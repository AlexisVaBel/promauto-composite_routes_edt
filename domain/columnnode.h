#pragma once

#include <iostream>
#include <type_traits>

#include <QDate>
#include <QString>
#include <QVariant>

#include <ibpp.h>

#include <QDebug>

struct ColumnNode{

    ColumnNode(){
        nextNode = nullptr;
    }
    ~ColumnNode(){
        delete nextNode;
    }

    void setTime(){

        qDebug() << QDate(m_tstampValue.Year(), m_tstampValue.Month(), m_tstampValue.Day());
//                    QDateTime(QDate(m_tstampValue.Year(), m_tstampValue.Month(), m_tstampValue.Day()),
//                              QTime(m_tstampValue.Hours(),m_tstampValue.Minutes(), m_tstampValue.Seconds())).toTime_t();
//        m_varValue = QVariant(QDateTime(QDate(m_tstampValue.Year(), m_tstampValue.Month(), m_tstampValue.Day()),
//                                        QTime(m_tstampValue.Hours(),m_tstampValue.Minutes(), m_tstampValue.Seconds())).toTime_t());
    }

    ColumnNode * get_by_name(QString str){
        auto tmp = this;
        while (tmp != nullptr) {
            if(tmp->m_strColName.compare(str, Qt::CaseInsensitive) == 0) break;            
            tmp = tmp->nextNode;
        }
        return tmp;
    }


    QString m_strColName{""};
    IBPP::SDT columnType{IBPP::sdSmallint};


    QString m_strValue{""};
    int     m_iValue{0};
    float   m_fValue{0};
    double  m_dValue{0};
    IBPP::Timestamp m_tstampValue{};

    int     m_iColCnt{0};
    QVariant m_varValue{};


    ColumnNode *nextNode;
};
