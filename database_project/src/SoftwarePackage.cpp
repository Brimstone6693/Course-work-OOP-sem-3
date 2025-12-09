#include "SoftwarePackage.h"

SoftwarePackage::SoftwarePackage()
    : name(""), manufacturer(""), size(0.0), version(""), year(0)
{
}

SoftwarePackage::SoftwarePackage(const QString& name, const QString& manufacturer, double size, const QString& version, int year)
    : name(name), manufacturer(manufacturer), size(size), version(version), year(year)
{
}

bool SoftwarePackage::operator==(const SoftwarePackage& other) const
{
    return name == other.name && 
           manufacturer == other.manufacturer && 
           size == other.size && 
           version == other.version && 
           year == other.year;
}

bool SoftwarePackage::operator!=(const SoftwarePackage& other) const
{
    return !(*this == other);
}

QDataStream& operator<<(QDataStream& out, const SoftwarePackage& package)
{
    out << package.name << package.manufacturer << package.size << package.version << package.year;
    return out;
}

QDataStream& operator>>(QDataStream& in, SoftwarePackage& package)
{
    in >> package.name >> package.manufacturer >> package.size >> package.version >> package.year;
    return in;
}