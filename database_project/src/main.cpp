#include <QApplication>
#include "MainWindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    
    // Set application information
    app.setApplicationName("Software Package Database");
    app.setApplicationVersion("1.0");
    app.setOrganizationName("Database Project");
    
    MainWindow window;
    window.show();
    
    return app.exec();
}