#include "datasource.h"
DataSource::DataSource(){}

DataSource::DataOperation * DataSource::index()
{

    return indexer();

}
DataSource::DataOperation * DataSource::load(const QString &modelName)
{
    DataOperation * l_loader= m_indexed[modelName].loader;
    l_loader=(l_loader==0)?loader():l_loader;
    m_indexed[modelName].loader=l_loader;
    if(index()->result()==0)
        l_loader->setPreviousOperation(indexer());
    return l_loader;
}

DataSource::DataOperation * DataSource::loadAll()
{
}


DataSource::DataOperation * DataSource::DataOperation::previousOperation()
{
    return m_previousOperation;
}

void DataSource::DataOperation::setPreviousOperation(DataSource::DataOperation *operation)
{
    m_previousOperation=operation;
}


















