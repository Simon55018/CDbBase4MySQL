#include "CDbBase4MySQL.h"
#include "CDbBase4MySQL_p.h"

namespace nsDb4MySQL
{
    CDbBase4MySQL::CDbBase4MySQL()
        : d_ptr(new CDbBase4MySQLPrivate)
    {
        d_ptr->q_ptr = NULL;
    }

    CDbBase4MySQL::~CDbBase4MySQL()
    {

    }

    bool CDbBase4MySQL::connectDB(DataBaseInfo stDataBaseInfo)
    {
        if( !stDataBaseInfo.isValid() )
        {
            return false;
        }

        return connectDB(stDataBaseInfo.sHostName, stDataBaseInfo.lPort, stDataBaseInfo.sDBName,
                         stDataBaseInfo.sUserName, stDataBaseInfo.sPassWord);
    }

    bool CDbBase4MySQL::connectDB(QString sHostName, int lPort, QString sDBName,
                                  QString sUserName, QString sPassWord)
    {
        Q_D(CDbBase4MySQL);
        if( d->m_sqlDataBase.isValid() &&
                d->m_sqlDataBase.isOpen() )
        {
            return true;
        }

        d->m_sqlDataBase = QSqlDatabase::addDatabase("QMYSQL");

        d->m_sqlDataBase.setHostName(sHostName);
        d->m_sqlDataBase.setPort(lPort);
        d->m_sqlDataBase.setDatabaseName(sDBName);
        d->m_sqlDataBase.setUserName(sUserName);
        d->m_sqlDataBase.setPassword(sPassWord);

        if( !d->m_sqlDataBase.open() )
        {
            return false;
        }

        return true;
    }

    void CDbBase4MySQL::disconnectDB()
    {
        Q_D(CDbBase4MySQL);
        if( d->m_sqlDataBase.isValid() &&
                d->m_sqlDataBase.isOpen() )
        {
            d->m_sqlDataBase.close();
        }
    }

    QSqlDatabase CDbBase4MySQL::getDatabase()
    {
        Q_D(CDbBase4MySQL);

        return d->m_sqlDataBase;
    }

    DataBaseInfo CDbBase4MySQL::getDataBaseInfo()
    {
        Q_D(CDbBase4MySQL);
        DataBaseInfo stDataBaseInfo;
        stDataBaseInfo.sHostName = d->m_sqlDataBase.hostName();
        stDataBaseInfo.lPort = d->m_sqlDataBase.port();
        stDataBaseInfo.sDBName = d->m_sqlDataBase.databaseName();
        stDataBaseInfo.sUserName = d->m_sqlDataBase.userName();
        stDataBaseInfo.sPassWord = d->m_sqlDataBase.password();

        return stDataBaseInfo;
    }

    bool CDbBase4MySQL::InsertQuery(QSqlQuery &query, const QString &sTableName, const QString &sValues, const QString &sFields)
    {
        Q_D(CDbBase4MySQL);
        if( sTableName.isEmpty() || sValues.isEmpty() )
        {
            return false;
        }

        QString sQuery;
        if (!sFields.isEmpty())
        {
            sQuery = QString("insert into %1(%2) values(%3);").arg(sTableName).arg(sFields).arg(sValues);
        }
        else
        {
            sQuery = QString("insert into %1 values(%2);").arg(sTableName).arg(sValues);
        }

        d->m_pMutex->lock();
        bool bRet = query.exec(sQuery);
        d->m_pMutex->unlock();

        return bRet;
    }

    QString CDbBase4MySQL::InsertQuery2String(const QString &sTableName, const QString &sValues, const QString &sFields)
    {
        if( sTableName.isEmpty() || sValues.isEmpty() )
        {
            return QString();
        }

        QString sQuery;
        if (!sFields.isEmpty())
        {
            sQuery = QString("insert into %1(%2) values(%3);").arg(sTableName).arg(sFields).arg(sValues);
        }
        else
        {
            sQuery = QString("insert into %1 values(%2);").arg(sTableName).arg(sValues);
        }

        return sQuery;
    }

    bool CDbBase4MySQL::DeleteQuery(QSqlQuery &query, const QString &sTableName, const QString &sWheCondition)
    {
        Q_D(CDbBase4MySQL);
        if( sTableName.isEmpty() )
        {
            return false;
        }

        QString sQuery;
        if (!sWheCondition.isEmpty())
        {
            sQuery = QString("delete from %1 where %2;").arg(sTableName).arg(sWheCondition);
        }
        else
        {
            sQuery = QString("delete from %1;").arg(sTableName);
        }

        d->m_pMutex->lock();
        bool bRet = query.exec(sQuery);
        d->m_pMutex->unlock();

        return bRet;
    }

    QString CDbBase4MySQL::DeleteQuery2String(const QString &sTableName, const QString &sWheCondition)
    {
        if( sTableName.isEmpty() )
        {
            return QString();
        }

        QString sQuery;
        if (!sWheCondition.isEmpty())
        {
            sQuery = QString("delete from %1 where %2;").arg(sTableName).arg(sWheCondition);
        }
        else
        {
            sQuery = QString("delete from %1;").arg(sTableName);
        }

        return sQuery;
    }

    bool CDbBase4MySQL::UpdateQuery(QSqlQuery &query, const QString &sTableName, const QString &sSetFields, const QString &sWheCondition)
    {
        Q_D(CDbBase4MySQL);
        if ( sTableName.isEmpty() || sSetFields.isEmpty() )
        {
            return false;
        }

        QString sQuery;
        if (!sWheCondition.isEmpty())
        {
            sQuery = QString("update %1 set %2 where %3;").arg(sTableName).arg(sSetFields).arg(sWheCondition);
        }
        else
        {
            sQuery = QString("update %1 set %2;").arg(sTableName).arg(sSetFields);
        }

        d->m_pMutex->lock();
        bool bRet = query.exec(sQuery);
        d->m_pMutex->unlock();

        return bRet;
    }

    QString CDbBase4MySQL::UpdateQuery2String(const QString &sTableName, const QString &sSetFields, const QString &sWheCondition)
    {
        if ( sTableName.isEmpty() || sSetFields.isEmpty() )
        {
            return QString();
        }

        QString sQuery;
        if (!sWheCondition.isEmpty())
        {
            sQuery = QString("update %1 set %2 where %3;").arg(sTableName).arg(sSetFields).arg(sWheCondition);
        }
        else
        {
            sQuery = QString("update %1 set %2;").arg(sTableName).arg(sSetFields);
        }

        return sQuery;
    }

    bool CDbBase4MySQL::SelectQuery(QSqlQuery &query, const QString &sFields, const QString &sTableName,
                                    const QString &sWheCondition, const QString &sGroupCondition,
                                    const QString &sOrderCondition, int nLimNum, int nOffNum)
    {
        Q_D(CDbBase4MySQL);
        if ( sTableName.isEmpty() || sFields.isEmpty() )
        {
            return false;
        }

        QString sQuery;
        if (!sWheCondition.isEmpty())
        {
            sQuery = QString("select %1 from %2 where %3").arg(sFields).arg(sTableName).arg(sWheCondition);
        }
        else
        {
            sQuery = QString("select %1 from %2").arg(sFields).arg(sTableName);
        }

        if( !sGroupCondition.isEmpty() )
        {
            sQuery.append(" ").append(QString("group by %1").arg(sGroupCondition));
        }
        if (!sOrderCondition.isEmpty())
        {
            sQuery.append(" ").append(QString("order by %1").arg(sOrderCondition));
        }

        if (nLimNum!=-1 && nOffNum != -1)
        {
            sQuery.append(" ").append(QString("limit %1, %2").arg(nLimNum).arg(nOffNum));
        }

        d->m_pMutex->lock();
        bool bRet = query.exec(sQuery);
        d->m_pMutex->unlock();

        return bRet;
    }

    QString CDbBase4MySQL::SelectQuery2String(const QString &sFields, const QString &sTableName,
                                              const QString &sWheCondition, const QString &sGroupCondition,
                                              const QString &sOrderCondition, int nLimNum, int nOffNum)
    {
        if ( sTableName.isEmpty() || sFields.isEmpty() )
        {
            return QString();
        }

        QString sQuery;
        if (!sWheCondition.isEmpty())
        {
            sQuery = QString("select %1 from %2 where %3").arg(sFields).arg(sTableName).arg(sWheCondition);
        }
        else
        {
            sQuery = QString("select %1 from %2").arg(sFields).arg(sTableName);
        }

        if( !sGroupCondition.isEmpty() )
        {
            sQuery.append(" ").append(QString("group by %1").arg(sGroupCondition));
        }
        if (!sOrderCondition.isEmpty())
        {
            sQuery.append(" ").append(QString("order by %1").arg(sOrderCondition));
        }

        if (nLimNum!=-1 && nOffNum != -1)
        {
            sQuery.append(" ").append(QString("limit %1, %2").arg(nLimNum).arg(nOffNum));
        }

        return sQuery;
    }

    bool CDbBase4MySQL::SelectJoinQuery(QSqlQuery &query, const QString &sJointType, const QString &sFields, const QString &sTableName,
                                        const QString &sJoinTableName, const QString &sEqualFields, const QString &sJoinEqualFields,
                                        const QString &sWhereCondition, const QString &sGroupCondition,
                                        const QString &sOrderCondition, int nLimNum, int nOffNum)
    {
        Q_D(CDbBase4MySQL);
        if ( sTableName.isEmpty() || sFields.isEmpty() ||
             sJoinTableName.isEmpty() || sEqualFields.isEmpty() )
        {
            return false;
        }

        QString sQuery;
        if( !sWhereCondition.isEmpty() )
        {
            sQuery = QString("select %1 from %2 %3 join %4 on %2.%5=%4.%6 where %7").arg(sFields).arg(sTableName).arg(sJointType)
                            .arg(sJoinTableName).arg(sEqualFields).arg(sJoinEqualFields).arg(sWhereCondition);
        }
        else
        {
            sQuery = QString("select %1 from %2 %3 join %4 on %2.%5=%4.%6").arg(sFields).arg(sTableName)
                            .arg(sJointType).arg(sJoinTableName).arg(sEqualFields).arg(sJoinEqualFields);
        }

        if( !sGroupCondition.isEmpty() )
        {
            sQuery.append(" ").append(QString("group by %1").arg(sGroupCondition));
        }
        if( !sOrderCondition.isEmpty() )
        {
            sQuery.append(" ").append(QString("order by %1").arg(sOrderCondition));
        }

        if ( nLimNum!=-1 && nOffNum != -1 )
        {
            sQuery.append(" ").append(QString("limit %1, %2").arg(nLimNum).arg(nOffNum));
        }

        d->m_pMutex->lock();
        bool bRet = query.exec(sQuery);
        d->m_pMutex->unlock();

        return bRet;
    }

    QString CDbBase4MySQL::SelectJoinQuery2String(const QString &sJointType, const QString &sFields, const QString &sTableName,
                                                  const QString &sJoinTableName, const QString &sEqualFields, const QString &sJoinEqualFields,
                                                  const QString &sWhereCondition, const QString &sGroupCondition,
                                                  const QString &sOrderCondition, int nLimNum, int nOffNum)
    {
        if ( sTableName.isEmpty() || sFields.isEmpty() ||
             sJoinTableName.isEmpty() || sEqualFields.isEmpty() )
        {
            return QString();
        }

        QString sQuery;
        if( !sWhereCondition.isEmpty() )
        {
            sQuery = QString("select %1 from %2 %3 join %4 on %2.%5=%4.%6 where %7").arg(sFields).arg(sTableName).arg(sJointType)
                            .arg(sJoinTableName).arg(sEqualFields).arg(sJoinEqualFields).arg(sWhereCondition);
        }
        else
        {
            sQuery = QString("select %1 from %2 %3 join %4 on %2.%5=%4.%6").arg(sFields).arg(sTableName)
                            .arg(sJointType).arg(sJoinTableName).arg(sEqualFields).arg(sJoinEqualFields);
        }

        if( !sGroupCondition.isEmpty() )
        {
            sQuery.append(" ").append(QString("group by %1").arg(sGroupCondition));
        }
        if( !sOrderCondition.isEmpty() )
        {
            sQuery.append(" ").append(QString("order by %1").arg(sOrderCondition));
        }

        if ( nLimNum!=-1 && nOffNum != -1 )
        {
            sQuery.append(" ").append(QString("limit %1, %2").arg(nLimNum).arg(nOffNum));
        }

        return sQuery;
    }

    bool CDbBase4MySQL::SelectJoin4SQLQuery(QSqlQuery &query, const QString &sJointType, const QString &sSelectSQL,
                                            const QString &sJoinSelectSQL, const QString &sTableName, const QString &sJoinTableName,
                                            const QString &sEqualFields, const QString &sJoinEqualFields,
                                            const QString &sWhereCondition, const QString &sGroupCondition,
                                            const QString &sOrderCondition, int nLimNum, int nOffNum)
    {
        Q_D(CDbBase4MySQL);

        if ( sTableName.isEmpty() || sSelectSQL.isEmpty() || sJoinSelectSQL.isEmpty() ||
             sJoinTableName.isEmpty() || sEqualFields.isEmpty() )
        {
            return false;
        }

        QString sQuery;
        if( !sWhereCondition.isEmpty() )
        {
            sQuery = QString("%1 %2 %3 join (%4) %5 on %2.%6=%5.%7 where %8").arg(sSelectSQL).arg(sTableName).arg(sJointType)
                            .arg(sJoinSelectSQL).arg(sJoinTableName).arg(sEqualFields).arg(sJoinEqualFields).arg(sWhereCondition);
        }
        else
        {
            sQuery = QString("%1 %2 %3 join (%4) %5 on %2.%6=%5.%7").arg(sSelectSQL).arg(sTableName).arg(sJointType)
                            .arg(sJoinSelectSQL).arg(sJoinTableName).arg(sEqualFields).arg(sJoinEqualFields);
        }

        if( !sGroupCondition.isEmpty() )
        {
            sQuery.append(" ").append(QString("group by %1").arg(sGroupCondition));
        }
        if( !sOrderCondition.isEmpty() )
        {
            sQuery.append(" ").append(QString("order by %1").arg(sOrderCondition));
        }

        if ( nLimNum!=-1 && nOffNum != -1 )
        {
            sQuery.append(" ").append(QString("limit %1, %2").arg(nLimNum).arg(nOffNum));
        }

        d->m_pMutex->lock();
        bool bRet = query.exec(sQuery);
        d->m_pMutex->unlock();

        return bRet;
    }

    QString CDbBase4MySQL::SelectJoin4SQLQuery2String(const QString &sJointType, const QString &sSelectSQL,
                                                      const QString &sJoinSelectSQL, const QString &sTableName,
                                                      const QString &sJoinTableName, const QString &sEqualFields,
                                                      const QString &sJoinEqualFields, const QString &sWhereCondition,
                                                      const QString &sGroupCondition, const QString &sOrderCondition,
                                                      int nLimNum, int nOffNum)
    {
        if ( sTableName.isEmpty() || sSelectSQL.isEmpty() || sJoinSelectSQL.isEmpty() ||
             sJoinTableName.isEmpty() || sEqualFields.isEmpty() )
        {
            return QString();
        }

        QString sQuery;
        if( !sWhereCondition.isEmpty() )
        {
            sQuery = QString("%1 %2 %3 join (%4) %5 on %2.%6=%5.%7 where %8").arg(sSelectSQL).arg(sTableName).arg(sJointType)
                            .arg(sJoinSelectSQL).arg(sJoinTableName).arg(sEqualFields).arg(sJoinEqualFields).arg(sWhereCondition);
        }
        else
        {
            sQuery = QString("%1 %2 %3 join (%4) %5 on %2.%6=%5.%7").arg(sSelectSQL).arg(sTableName).arg(sJointType)
                            .arg(sJoinSelectSQL).arg(sJoinTableName).arg(sEqualFields).arg(sJoinEqualFields);
        }

        if( !sGroupCondition.isEmpty() )
        {
            sQuery.append(" ").append(QString("group by %1").arg(sGroupCondition));
        }
        if( !sOrderCondition.isEmpty() )
        {
            sQuery.append(" ").append(QString("order by %1").arg(sOrderCondition));
        }

        if ( nLimNum!=-1 && nOffNum != -1 )
        {
            sQuery.append(" ").append(QString("limit %1, %2").arg(nLimNum).arg(nOffNum));
        }

        return sQuery;
    }

    bool CDbBase4MySQL::InsertOrReplaceQuery(QSqlQuery &query, const QString &sTableName, const QString &sValues, const QString &sFields)
    {
        Q_D(CDbBase4MySQL);
        if( sTableName.isEmpty() || sValues.isEmpty() )
        {
            return false;
        }

        QString sQuery;
        if (!sFields.isEmpty())
        {
            sQuery = QString("replace into %1(%2) values(%3);").arg(sTableName).arg(sFields).arg(sValues);
        }
        else
        {
            sQuery = QString("replace into %1 values(%2);").arg(sTableName).arg(sValues);
        }

        d->m_pMutex->lock();
        bool bRet = query.exec(sQuery);
        d->m_pMutex->unlock();

        return bRet;
    }

    QString CDbBase4MySQL::InsertOrReplaceQuery2String(const QString &sTableName, const QString &sValues, const QString &sFields)
    {
        if( sTableName.isEmpty() || sValues.isEmpty() )
        {
            return QString();
        }

        QString sQuery;
        if (!sFields.isEmpty())
        {
            sQuery = QString("replace into %1(%2) values(%3);").arg(sTableName).arg(sFields).arg(sValues);
        }
        else
        {
            sQuery = QString("replace into %1 values(%2);").arg(sTableName).arg(sValues);
        }

        return sQuery;
    }

    bool CDbBase4MySQL::beginTransaction()
    {
        Q_D(CDbBase4MySQL);
        bool bRet = false;
        if( !d->m_bIsMutexlock )
        {
            d->m_pMutex->lock();
            bRet = d->m_sqlDataBase.transaction();
            d->m_bIsMutexlock = true;
        }

        return bRet;
    }

    bool CDbBase4MySQL::commit()
    {
        Q_D(CDbBase4MySQL);
        bool bRet = false;
        if( d->m_bIsMutexlock )
        {
            bRet = d->m_sqlDataBase.commit();
        }

        return bRet;
    }

    bool CDbBase4MySQL::rollback()
    {
        Q_D(CDbBase4MySQL);
        bool bRet = false;
        if( d->m_bIsMutexlock )
        {
            bRet = d->m_sqlDataBase.rollback();
        }

        return bRet;
    }

    void CDbBase4MySQL::endTransaction()
    {
        Q_D(CDbBase4MySQL);
        d->m_pMutex->unlock();
        d->m_bIsMutexlock = false;
    }

    QMutex CDbBase4MySQLPrivate::m_gMutexMain(QMutex::Recursive);
    CDbBase4MySQLPrivate::CDbBase4MySQLPrivate()
    {
        q_ptr = NULL;
        m_bIsMutexlock = false;
        m_pMutex = &m_gMutexMain;
    }

    CDbBase4MySQLPrivate::~CDbBase4MySQLPrivate()
    {

    }
}

