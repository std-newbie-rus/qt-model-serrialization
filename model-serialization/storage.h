#ifndef STORAGE_H
#define STORAGE_H

#include <QString>
#include <QMap>
#include <QObject>

class DataSource;
class QAbstractItemModel;



class Storage:public QObject
{
public:

    typedef QMap<QString,DataSource*> DataSources;
    void registerDataSource(DataSource* s,const QString & name=QString());
    DataSource* dataSource(const QString & name=QString());
    void loadModel(QAbstractItemModel * model,const QString & name,const QString & dataSource=QString());
    void saveModel(QAbstractItemModel *model ,const QString & name,const QString & dataSource = QString());
    static Storage * globalInstance();

private:
    Storage();
    Storage(const Storage &s ){}
};

#endif // STORAGE_H
