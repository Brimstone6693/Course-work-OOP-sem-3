#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>
#include <QAction>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QMessageBox>
#include <QFileDialog>
#include <QInputDialog>
#include <QHeaderView>
#include <QMenu>
#include <QContextMenuEvent>
#include <QToolTip>

#include "Database.h"
#include "SoftwarePackage.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onAddPackage();
    void onEditPackage();
    void onDeletePackage();
    void onSearchPackages();
    void onLoadDatabase();
    void onSaveDatabase();
    void onMergeDatabases();
    void onAbout();
    void onClearSearch();
    
    // Context menu actions
    void onContextMenuRequested(const QPoint &pos);
    void onShowAllPackages();

private:
    void setupUI();
    void setupMenus();
    void setupToolbar();
    void setupStatusBar();
    void populateTable();
    void updateStatusBar();
    void refreshTable();

    // Main widgets
    QWidget *centralWidget;
    QVBoxLayout *mainLayout;
    QHBoxLayout *searchLayout;
    QTableWidget *tableWidget;
    QLineEdit *searchLineEdit;
    QPushButton *searchButton;
    QPushButton *clearSearchButton;
    
    // Menu items
    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *viewMenu;
    QMenu *helpMenu;
    
    // Actions
    QAction *addAction;
    QAction *editAction;
    QAction *deleteAction;
    QAction *loadAction;
    QAction *saveAction;
    QAction *mergeAction;
    QAction *aboutAction;
    QAction *quitAction;
    QAction *showAllAction;
    
    // Toolbar actions
    QToolBar *mainToolBar;
    
    // Database
    Database database;
    
    // Context menu
    QMenu *contextMenu;
};

#endif // MAINWINDOW_H