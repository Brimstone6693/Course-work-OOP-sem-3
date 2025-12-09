#include "Database.h"

Database::Database()
{
}

void Database::addPackage(const SoftwarePackage& package)
{
    m_container.push_back(package);
}

void Database::removePackage(int index)
{
    if (index >= 0 && index < m_container.size()) {
        m_container.erase(index);
    }
}

void Database::editPackage(int index, const SoftwarePackage& newPackage)
{
    if (index >= 0 && index < m_container.size()) {
        m_container[index] = newPackage;
    }
}

QVector<SoftwarePackage> Database::getAllPackages() const
{
    return m_container.getAll();
}

int Database::getPackageCount() const
{
    return m_container.size();
}

void Database::mergeDatabase(const Database& other)
{
    m_container.merge(other.m_container);
}

bool Database::saveToFile(const QString& filename) const
{
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly)) {
        return false;
    }
    
    QDataStream out(&file);
    out.setVersion(QDataStream::Qt_5_15);
    
    QVector<SoftwarePackage> packages = getAllPackages();
    int count = packages.size();
    out << count;
    
    for (const auto& package : packages) {
        out << package;
    }
    
    file.close();
    return true;
}

bool Database::loadFromFile(const QString& filename)
{
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly)) {
        return false;
    }
    
    QDataStream in(&file);
    in.setVersion(QDataStream::Qt_5_15);
    
    clear();
    
    int count;
    in >> count;
    
    for (int i = 0; i < count; ++i) {
        SoftwarePackage package;
        in >> package;
        m_container.push_back(package);
    }
    
    file.close();
    return true;
}

void Database::clear()
{
    m_container.clear();
}

// Explicit template instantiation to avoid linker errors
template void Database::removePackagesIf<std::function<bool(const SoftwarePackage&)>>(
    std::function<bool(const SoftwarePackage&)> pred);
template QList<SoftwarePackage> Database::findPackages<std::function<bool(const SoftwarePackage&)>>(
    std::function<bool(const SoftwarePackage&)> pred);