#ifndef CDBBASE4MYSQLPRIVATE_H
#define CDBBASE4MYSQLPRIVATE_H

#include "CDbBase4MySQL.h"

#include <QMutex>

namespace nsDb4MySQL
{
    class CDbBase4MySQLPrivate
    {
        Q_DECLARE_PUBLIC(CDbBase4MySQL)

    public:
        CDbBase4MySQLPrivate();

        virtual ~CDbBase4MySQLPrivate();

    private:
        CDbBase4MySQL   *q_ptr;
        QSqlDatabase    m_sqlDataBase;      // 当前默认数据库

        static QMutex   m_gMutexMain;
        QMutex          *m_pMutex;
        bool            m_bIsMutexlock;
    };
}

#endif // CDBBASE4MYSQLPRIVATE_H
