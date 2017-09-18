#include "ImageCatalog.h"

ImageCatalog::ImageCatalog(const QStringList &filter) : m_catalogIndex(), m_filter(filter)
{

}

void ImageCatalog::initialize(const QFile &imageFile)
{
    QFileInfo info(imageFile);
    QString filename = info.fileName();
    m_absoluteDir = info.absoluteDir().canonicalPath();
    initialize(info.absoluteDir());

    for (const QString& item : m_catalog)
    {
        if (item.compare(filename) == 0)
            break;
        ++m_catalogIndex;
    }
}

void ImageCatalog::initialize(const QDir &imageDir)
{
    m_absoluteDir = imageDir.canonicalPath();
    m_catalog = imageDir.entryList(m_filter, QDir::Filter::Files);
    m_catalogIndex.set(0, m_catalog.size());
}

uint64_t ImageCatalog::getCatalogSize()
{
    return m_catalog.size();
}

QString ImageCatalog::getCurrent()
{
    return getCatalogItem(m_catalogIndex);
}

QString ImageCatalog::getNext()
{
    return getCatalogItem(++m_catalogIndex);
}

QString ImageCatalog::getPrevious()
{
    return getCatalogItem(--m_catalogIndex);
}

QString ImageCatalog::getCatalogItem(const RotatingIndex<uint64_t>& catalogIndex)
{
    if (m_catalog.isEmpty())
        return QString();

    return m_absoluteDir + QDir::separator() + m_catalog.at(catalogIndex);
}
