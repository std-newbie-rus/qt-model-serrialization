#ifndef DATASOURCE_H
#define DATASOURCE_H
#include <QAbstractItemModel>
#include <QThread>
#include <QMap>

/**
  \class DataSource класс источника данных моделей
*/
class DataSource
{
public:


    class Loader;
    class Saver;
    class DataTransfer;
    class DataOperation;
    DataOperation * loadAll();
    DataOperation * load(const QString & modelName);
    DataOperation * saver(QAbstractItemModel * model,const QString & name);
    DataOperation * index();
    DataOperation * flush();
protected:
    virtual DataOperation * loader() =0;
    virtual DataOperation * saver() =0;
    virtual DataOperation * flusher()=0;
    virtual DataOperation * indexer()=0;

private:
    struct DataToolSet
    {
        DataToolSet():loader(0),saver(0){}
        DataOperation * loader;
        DataOperation * saver;
    };
    QMap<QString,DataToolSet> m_indexed;



    DataSource();
    DataSource(const DataSource & ){}
};
/**
  \class DataSource::DataProgress класс представляющий собой прогресс текущей задачи по загрузке/сохранению данных

*/
class DataSource::DataOperation : public QThread
{
    Q_OBJECT
public:
    enum Error
    {
        ErrorNo,
        ErrorSourceUnreacheble,
        ErrorWrongFormat,
        ErrorNoSuchModel,
        ErrorSourceAcessDenided

    };
    explicit DataOperation(QObject * parent=0);
    virtual QAbstractItemModel * result() =0;
signals:
    void begin(int count);
    void end();
    void progress(int progress);
    void error(Error);
public:
    void setPreviousOperation(DataOperation * operation);


protected:
    DataOperation * previousOperation();

    virtual QAbstractItemModel * buildResult() =0;
    DataOperation * m_previousOperation;
};

/**
  @class DataSource::DataTransfer промежуточный базовый класс определяющий общий функционал между
функциями сохранения / загрузки данных
*/
class DataSource::DataTransfer :public QAbstractItemModel
{
    Q_OBJECT
public:

private:



};

/**
 @class DataSource::Loader класс отвечающий за загрузку модели из источника данных

*/
class DataSource::Loader : public DataSource::DataTransfer
{
    Q_OBJECT
public slots :
    virtual void load(const QString & model)=0;

};

/**
  \class   DataSource::Saver отвечает за сохранение модели в источник данных
*/
class DataSource::Saver : public DataSource::DataTransfer
{
    Q_OBJECT
public:
    void setModel(QAbstractItemModel * model);
    QAbstractItemModel * model();
public slots:
    virtual void save(const QString & model)=0;
private:



};

#endif // DATASOURCE_H
