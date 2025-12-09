#include <iostream>
#include "include/CustomContainer.h"
#include "include/SoftwarePackage.h"
#include "include/Database.h"
#include <string>

int main() {
    std::cout << "Testing Custom Container Implementation..." << std::endl;
    
    // Test SoftwarePackage
    std::cout << "\n1. Testing SoftwarePackage class:" << std::endl;
    SoftwarePackage package1("MyApp", "ACME Corp", 150.5, "1.2.0", 2023);
    std::cout << "Created package: " << package1.getName().toStdString() 
              << " by " << package1.getManufacturer().toStdString() 
              << ", size: " << package1.getSize() << " MB" << std::endl;
    
    // Test CustomContainer
    std::cout << "\n2. Testing CustomContainer class:" << std::endl;
    CustomContainer<SoftwarePackage> container;
    
    // Add some packages
    container.push_back(SoftwarePackage("Firefox", "Mozilla", 280.0, "102.0", 2022));
    container.push_back(SoftwarePackage("Chrome", "Google", 150.0, "110.0", 2023));
    container.push_back(SoftwarePackage("VSCode", "Microsoft", 100.0, "1.70", 2023));
    
    std::cout << "Container size: " << container.size() << std::endl;
    
    // Test iteration
    std::cout << "Iterating through container:" << std::endl;
    for (auto it = container.begin(); it != container.end(); ++it) {
        std::cout << "  - " << it->getName().toStdString() 
                  << " by " << it->getManufacturer().toStdString() << std::endl;
    }
    
    // Test find operation
    std::cout << "\n3. Testing find operation:" << std::endl;
    auto results = container.find([](const SoftwarePackage& p) {
        return p.getSize() > 120.0;
    });
    
    std::cout << "Packages larger than 120MB: " << results.size() << std::endl;
    for (const auto& pkg : results) {
        std::cout << "  - " << pkg.getName().toStdString() 
                  << " (" << pkg.getSize() << " MB)" << std::endl;
    }
    
    // Test Database
    std::cout << "\n4. Testing Database class:" << std::endl;
    Database db;
    
    // Add packages to database
    db.addPackage(SoftwarePackage("GIMP", "GNU", 300.0, "2.10", 2022));
    db.addPackage(SoftwarePackage("Inkscape", "OpenSource", 200.0, "1.2", 2023));
    db.addPackage(SoftwarePackage("Blender", "Blender Foundation", 500.0, "3.0", 2023));
    
    std::cout << "Database package count: " << db.getPackageCount() << std::endl;
    
    // Find packages by size
    auto largePackages = db.findPackages([](const SoftwarePackage& p) {
        return p.getSize() > 250.0;
    });
    
    std::cout << "Large packages (>250MB): " << largePackages.size() << std::endl;
    for (const auto& pkg : largePackages) {
        std::cout << "  - " << pkg.getName().toStdString() 
                  << " (" << pkg.getSize() << " MB)" << std::endl;
    }
    
    // Test save/load
    std::cout << "\n5. Testing save/load functionality:" << std::endl;
    bool saved = db.saveToFile("test.db");
    std::cout << "Save operation: " << (saved ? "SUCCESS" : "FAILED") << std::endl;
    
    Database db2;
    bool loaded = db2.loadFromFile("test.db");
    std::cout << "Load operation: " << (loaded ? "SUCCESS" : "FAILED") << std::endl;
    std::cout << "Loaded database package count: " << db2.getPackageCount() << std::endl;
    
    // Test merge
    std::cout << "\n6. Testing merge functionality:" << std::endl;
    Database db3;
    db3.addPackage(SoftwarePackage("LibreOffice", "The Document Foundation", 800.0, "7.4", 2023));
    std::cout << "Before merge - DB1: " << db.getPackageCount() 
              << ", DB3: " << db3.getPackageCount() << std::endl;
    
    db.mergeDatabase(db3);
    std::cout << "After merge - DB1: " << db.getPackageCount() << std::endl;
    
    std::cout << "\nAll tests completed successfully!" << std::endl;
    
    return 0;
}