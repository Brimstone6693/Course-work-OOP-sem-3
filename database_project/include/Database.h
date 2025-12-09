#ifndef DATABASE_H
#define DATABASE_H

#include "CustomContainer.h"
#include <QFile>
#include <QTextStream>
#include <QDataStream>
#include <QDir>
#include <QList>

class Database
{
public:
    Database();
    
    // Add a software package
    void addPackage(const SoftwarePackage& package);
    
    // Remove a software package by index
    void removePackage(int index);
    
    // Remove packages by condition
    template<typename Predicate>
    void removePackagesIf(Predicate pred)
    {
        m_container.remove_if(pred);
    }
    
    // Edit a software package by index
    void editPackage(int index, const SoftwarePackage& newPackage);
    
    // Find packages by condition
    template<typename Predicate>
    QList<SoftwarePackage> findPackages(Predicate pred)
    {
        return m_container.find(pred);
    }
    
    // Get all packages
    QVector<SoftwarePackage> getAllPackages() const;
    
    // Get number of packages
    int getPackageCount() const;
    
    // Merge with another database
    void mergeDatabase(const Database& other);
    
    // Save database to file
    bool saveToFile(const QString& filename) const;
    
    // Load database from file
    bool loadFromFile(const QString& filename);
    
    // Clear database
    void clear();

private:
    CustomContainer<SoftwarePackage> m_container;
};

#endif // DATABASE_H