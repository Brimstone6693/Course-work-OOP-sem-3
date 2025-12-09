#ifndef SOFTWAREPACKAGE_H
#define SOFTWAREPACKAGE_H

#include <QString>
#include <QDataStream>
#include <QDebug>

class SoftwarePackage
{
public:
    SoftwarePackage();
    SoftwarePackage(const QString& name, const QString& manufacturer, double size, const QString& version = "", int year = 0);
    
    // Getters
    QString getName() const { return name; }
    QString getManufacturer() const { return manufacturer; }
    double getSize() const { return size; }
    QString getVersion() const { return version; }
    int getYear() const { return year; }
    
    // Setters
    void setName(const QString& newName) { name = newName; }
    void setManufacturer(const QString& newManufacturer) { manufacturer = newManufacturer; }
    void setSize(double newSize) { size = newSize; }
    void setVersion(const QString& newVersion) { version = newVersion; }
    void setYear(int newYear) { year = newYear; }
    
    // Comparison operators
    bool operator==(const SoftwarePackage& other) const;
    bool operator!=(const SoftwarePackage& other) const;
    
    // Stream operators for serialization
    friend QDataStream& operator<<(QDataStream& out, const SoftwarePackage& package);
    friend QDataStream& operator>>(QDataStream& in, SoftwarePackage& package);

private:
    QString name;
    QString manufacturer;
    double size;      // Size in MB
    QString version;
    int year;         // Release year
};

#endif // SOFTWAREPACKAGE_H