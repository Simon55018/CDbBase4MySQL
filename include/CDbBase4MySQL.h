#ifndef CDBBASE4MYSQL_H
#define CDBBASE4MYSQL_H

#include <QScopedPointer>
#include <QSqlDatabase>
#include <QtGlobal>
#include <QSqlQuery>

namespace nsDb4MySQL
{
    struct DataBaseInfo
    {
        QString         sHostName;      // 主机名
        int             lPort;          // 主机端口号
        QString         sDBName;        // 数据名字
        QString         sUserName;      // 用户名
        QString         sPassWord;      // 密码

        /*!
         * \brief isValid   判断结构数据是否有效
         * \return          正确/错误
         */
        bool isValid()
        {
            if( sHostName.isEmpty() || sDBName.isEmpty() ||
                    sUserName.isEmpty() || sPassWord.isEmpty() )
            {
                return false;
            }

            return true;
        }
    };

    class CDbBase4MySQLPrivate;
    class CDbBase4MySQL
    {
        Q_DISABLE_COPY(CDbBase4MySQL)
        Q_DECLARE_PRIVATE(CDbBase4MySQL)

    public:
        CDbBase4MySQL();

        virtual ~CDbBase4MySQL();

        /*!
         * \brief connectDB         连接数据库
         * \param stDataBaseInfo    [in]        数据库信息结构体
         * \return                  成功/失败
         */
        bool connectDB(DataBaseInfo stDataBaseInfo);
        /*!
         * \brief connectDB         连接数据库
         * \param sHostName         [in]        主机IP地址
         * \param lPort             [in]        主机端口号
         * \param sDBName           [in]        数据库名称
         * \param sUserName         [in]        用户名
         * \param sPassWord         [in]        密码
         * \return
         */
        bool connectDB(QString sHostName, int lPort, QString sDBName,
                       QString sUserName, QString sPassWord);

        /*!
         * \brief disconnectDB      断开数据连接
         */
        void disconnectDB();

        /*!
         * \brief getDatabase       获取当前Database对象,需自行判断对象是否有效
         * \return QSqlDatabase对象
         */
        QSqlDatabase getDatabase();

        /*!
         * \brief getDataBaseInfo   获取当前连接数据库的信息
         * \return                  数据库信息结构体
         */
        DataBaseInfo getDataBaseInfo();

        /*!
         * \brief InsertQuery       插入数据操作
         * \param query             [in&out]    数据库操作对象
         * \param sTableName        [in]        数据表名称
         * \param sValues           [in]        插入数据值
         * \param sFields           [in]        数据表元素名
         * \return 成功/失败
         */
        bool InsertQuery(QSqlQuery &query, const QString& sTableName,
                         const QString& sValues,  const QString& sFields = QString());
        /*!
         * \brief InsertQuery2String    插入数据操作字符串输出
         * \param 与InsertQuery参数一致
         * \return 插入操作字符串
         */
        static QString InsertQuery2String(const QString &sTableName,
                            const QString &sValues, const QString &sFields = QString());

        /*!
         * \brief DeleteQuery       删除数据操作
         * \param query             [in&out]    数据库操作对象
         * \param sTableName        [in]        数据表名称
         * \param sWheCondition     [in]        删除条件
         * \return 成功/失败
         */
        bool DeleteQuery(QSqlQuery &query, const QString& sTableName, const QString& sWheCondition = QString());
        /*!
         * \brief DeleteQuery2String    删除数据操作字符串输出
         * \param 与DeleteQuery参数一致
         * \return 删除操作字符串
         */
        static QString DeleteQuery2String(const QString &sTableName, const QString &sWheCondition = QString());

        /*!
         * \brief UpdateQuery       更新数据操作
         * \param query             [in&out]    数据库操作对象
         * \param sTableName        [in]        数据表名称
         * \param sSetFields        [in]        修改数据值
         * \param sWheCondition     [in]        更新条件
         * \return 成功/失败
         */
        bool UpdateQuery(QSqlQuery &query, const QString& sTableName,
                         const QString& sSetFields, const QString& sWheCondition = QString());
        /*!
         * \brief UpdateQuery2String    更新数据操作字符串输出
         * \param 与UpdateQuery参数一致
         * \return 更新操作字符串
         */
        static QString UpdateQuery2String(const QString &sTableName,
                            const QString &sSetFields, const QString &sWheCondition = QString());

        /*!
         * \brief SelectQuery       查询数据操作
         * \param query             [in&out]    数据库操作对象
         * \param sFields           [in]        数据表元素名
         * \param sTableName        [in]        数据表名称
         * \param sWheCondition     [in]        查询条件
         * \param sGroupCondition   [in]        分类聚合条件
         * \param sOrderCondition   [in]        排序条件
         * \param nLimNum           [in]        检索个数
         * \param nOffNum           [in]        偏移个数
         * \return 成功/失败
         */
        bool SelectQuery(QSqlQuery &query, const QString& sFields,
                         const QString& sTableName, const QString& sWheCondition = QString(), const QString& sGroupCondition = QString(),
                         const QString& sOrderCondition = QString(), int nLimNum = -1, int nOffNum = -1);
        /*!
         * \brief SelectQuery2String    查询数据操作字符串输出
         * \param 与SelectQuery参数一致
         * \return 查询操作字符串
         */
        static QString SelectQuery2String(const QString &sFields,
                            const QString &sTableName, const QString &sWheCondition = QString(), const QString &sGroupCondition = QString(),
                            const QString &sOrderCondition = QString(), int nLimNum = -1, int nOffNum = -1);


        /*!
         * \brief SelectLeftJoinQuery   左连接查询操作(包含所有的左边表中的记录甚至是右边表中没有和它匹配的记录)
         * \param query             [in&out]    数据库操作对象
         * \param sJoinType         [in]        连接操作("left", "right", "inner")
         * \param sFields           [in]        数据表元素名
         * \param sTableName        [in]        数据表名称
         * \param sJoinTableName    [in]        连接表名称
         * \param sEqualFields      [in]        数据表相等字段
         * \param sJoinEqualFields  [in]        连接表相等字段
         * \param sWheCondition     [in]        查询条件
         * \param sGroupCondition   [in]        分类聚合条件
         * \param sOrderCondition   [in]        排序条件
         * \param nLimNum           [in]        检索个数
         * \param nOffNum           [in]        偏移个数
         * \return 成功/失败
         */
        bool SelectJoinQuery(QSqlQuery &query, const QString &sJointType, const QString& sFields, const QString& sTableName,
                             const QString& sJoinTableName, const QString &sEqualFields, const QString &sJoinEqualFields,
                             const QString& sWhereCondition = QString(), const QString& sGroupCondition = QString(),
                             const QString& sOrderCondition = QString(),
                             int nLimNum = -1, int nOffNum = -1);

        /*!
         * \brief SelectLeftJoinQuery2String    左连接查询操作字符串输出
         * \param 与SelectLeftJoinQuery参数一致
         * \return 左连接查询操作字符串
         */
        static QString SelectJoinQuery2String(const QString& sJointType, const QString &sFields, const QString &sTableName,
                                              const QString& sJoinTableName, const QString &sEqualFields, const QString &sJoinEqualFields,
                                              const QString& sWhereCondition = QString(), const QString& sGroupCondition = QString(),
                                              const QString& sOrderCondition = QString(),
                                              int nLimNum = -1, int nOffNum = -1);

        /*!
         * \brief SelectInnerJoinQuery  SelectInnerJoinQuery  等值连接查询操作(两个表中联结字段相等的记录),用于两个由原表生成的表进行处理, 如下面语句
         *                              select a.serial_no,a.eq_type,a.eq_name from eq_info a inner join
         *                              (select serial_no from eq_info order by eq_primary_key limit 0, 10) b on a.serial_no = b.serial_no;
         * \param query                 [in&out]    数据库操作对象
         * \param sJoinType             [in]        连接操作("left", "right", "inner")
         * \param sSelectSQL            [in]        主查询语句
         * \param sJoinSelectSQL        [in]        副查询语句(主要用于获取连接表数据)
         * \param sTableName            [in]        主查询表别名
         * \param sJoinTableName        [in]        副查询表别名
         * \param sEqualFields          [in]        主查询相等字段
         * \param sJoinEqualFields      [in]        副查询相等字段
         * \param sWhereCondition       [in]        查询条件
         * \param sGroupCondition       [in]        分类聚合条件
         * \param sOrderCondition       [in]        排序条件
         * \param nLimNum               [in]        检索个数
         * \param nOffNum               [in]        偏移个数
         * \return 成功/失败
         */
        bool SelectJoin4SQLQuery(QSqlQuery &query, const QString &sJointType, const QString &sSelectSQL, const QString &sJoinSelectSQL,
                                 const QString& sTableName, const QString &sJoinTableName,
                                 const QString& sEqualFields, const QString &sJoinEqualFields,
                                 const QString& sWhereCondition = QString(), const QString& sGroupCondition = QString(),
                                 const QString& sOrderCondition = QString(), int nLimNum = -1, int nOffNum = -1);

        /*!
         * \brief SelectInnerJoinQuery2String   等值连接查询操作字符串输出
         * \param 与SelectInnerJoinQuery参数一致
         * \return 等值连接查询操作字符串
         */
        static QString SelectJoin4SQLQuery2String(const QString &sJointType, const QString &sSelectSQL, const QString &sJoinSelectSQL,
                                                  const QString& sTableName, const QString &sJoinTableName,
                                                  const QString& sEqualFields, const QString &sJoinEqualFields,
                                                  const QString& sWhereCondition = QString(), const QString& sGroupCondition = QString(),
                                                  const QString& sOrderCondition = QString(), int nLimNum = -1, int nOffNum = -1);

        /*!
         * \brief InsertOrReplaceQuery  插入或替换操作,当数据表中不存在数据则插入数据,当数据表存在数据则替换数据
         * \param query             [in&out]    数据库操作对象
         * \param sTableName        [in]        数据表名称
         * \param sValues           [in]        插入数据值
         * \param sFields           [in]        数据表元素名
         * \return 成功/失败
         */
        bool InsertOrReplaceQuery(QSqlQuery &query, const QString& sTableName,
                                  const QString& sValues,  const QString& sFields = QString());
        /*!
         * \brief InsertOrReplaceQuery2String   插入或替换操作字符串输出
         * \param 与InsertOrReplaceQuery参数一致
         * \return 插入或替换操作字符串
         */
        static QString InsertOrReplaceQuery2String(const QString &sTableName,
                                     const QString &sValues, const QString &sFields = QString());

        /// beginTransaction 与 endTransaction 必须成对调用,
        /// commit,rollback位于beginTransaction与endTransaction之间
        /// example
        /// beginTransaction();
        /// commit()/rollback();
        /// endTransaction();
        /*!
         * \brief   beginTransaction  开始数据库上事务(commit, rollback)
         * \return  成功/失败
         */
        bool beginTransaction();
        /*!
         * \brief commit    提交事务
         * \return 成功/失败
         */
        bool commit();
        /*!
         * \brief rollback  回滚事务
         * \return 成功/失败
         */
        bool rollback();
        /*!
         * \brief endTransaction    解决事务
         */
        void endTransaction();

    private:
        QScopedPointer<CDbBase4MySQLPrivate>    d_ptr;
        static CDbBase4MySQL   *m_pThis;
    };
}
#endif // CDBBASE4MYSQL_H
