#include "MainWindow.h"
#include <QApplication>
#include <QMenuBar>
#include <QMessageBox>
#include <QInputDialog>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QContextMenuEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupUI();
    setupMenus();
    setupToolbar();
    setupStatusBar();
    populateTable();
    updateStatusBar();
}

MainWindow::~MainWindow()
{
}

void MainWindow::setupUI()
{
    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    
    mainLayout = new QVBoxLayout(centralWidget);
    
    // Create search bar
    searchLayout = new QHBoxLayout();
    searchLineEdit = new QLineEdit();
    searchLineEdit->setPlaceholderText("Search packages...");
    searchButton = new QPushButton("Search");
    clearSearchButton = new QPushButton("Clear");
    
    searchLayout->addWidget(searchLineEdit);
    searchLayout->addWidget(searchButton);
    searchLayout->addWidget(clearSearchButton);
    
    // Create table widget
    tableWidget = new QTableWidget();
    tableWidget->setColumnCount(5);
    tableWidget->setHorizontalHeaderLabels(QStringList() << "Name" << "Manufacturer" << "Size (MB)" << "Version" << "Year");
    tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    
    mainLayout->addLayout(searchLayout);
    mainLayout->addWidget(tableWidget);
    
    // Connect signals
    connect(searchButton, &QPushButton::clicked, this, &MainWindow::onSearchPackages);
    connect(clearSearchButton, &QPushButton::clicked, this, &MainWindow::onClearSearch);
    connect(tableWidget, &QTableWidget::customContextMenuRequested, 
            this, &MainWindow::onContextMenuRequested);
    
    setWindowTitle("Software Package Database");
    resize(800, 600);
}

void MainWindow::setupMenus()
{
    // File menu
    fileMenu = menuBar()->addMenu("File");
    
    loadAction = new QAction("Load Database", this);
    loadAction->setShortcut(QKeySequence("Ctrl+O"));
    loadAction->setStatusTip("Load database from file");
    connect(loadAction, &QAction::triggered, this, &MainWindow::onLoadDatabase);
    fileMenu->addAction(loadAction);
    
    saveAction = new QAction("Save Database", this);
    saveAction->setShortcut(QKeySequence("Ctrl+S"));
    saveAction->setStatusTip("Save database to file");
    connect(saveAction, &QAction::triggered, this, &MainWindow::onSaveDatabase);
    fileMenu->addAction(saveAction);
    
    mergeAction = new QAction("Merge Databases", this);
    mergeAction->setStatusTip("Merge with another database");
    connect(mergeAction, &QAction::triggered, this, &MainWindow::onMergeDatabases);
    fileMenu->addAction(mergeAction);
    
    fileMenu->addSeparator();
    
    quitAction = new QAction("Exit", this);
    quitAction->setShortcut(QKeySequence("Ctrl+Q"));
    quitAction->setStatusTip("Exit application");
    connect(quitAction, &QAction::triggered, this, &QApplication::quit);
    fileMenu->addAction(quitAction);
    
    // Edit menu
    editMenu = menuBar()->addMenu("Edit");
    
    addAction = new QAction("Add Package", this);
    addAction->setShortcut(QKeySequence("Ctrl+N"));
    addAction->setStatusTip("Add new software package");
    connect(addAction, &QAction::triggered, this, &MainWindow::onAddPackage);
    editMenu->addAction(addAction);
    
    editAction = new QAction("Edit Package", this);
    editAction->setShortcut(QKeySequence("Ctrl+E"));
    editAction->setStatusTip("Edit selected software package");
    connect(editAction, &QAction::triggered, this, &MainWindow::onEditPackage);
    editMenu->addAction(editAction);
    
    deleteAction = new QAction("Delete Package", this);
    deleteAction->setShortcut(QKeySequence("Del"));
    deleteAction->setStatusTip("Delete selected software package");
    connect(deleteAction, &QAction::triggered, this, &MainWindow::onDeletePackage);
    editMenu->addAction(deleteAction);
    
    // View menu
    viewMenu = menuBar()->addMenu("View");
    
    showAllAction = new QAction("Show All", this);
    showAllAction->setStatusTip("Show all packages in database");
    connect(showAllAction, &QAction::triggered, this, &MainWindow::onShowAllPackages);
    viewMenu->addAction(showAllAction);
    
    // Help menu
    helpMenu = menuBar()->addMenu("Help");
    
    aboutAction = new QAction("About", this);
    aboutAction->setStatusTip("About this application");
    connect(aboutAction, &QAction::triggered, this, &MainWindow::onAbout);
    helpMenu->addAction(aboutAction);
}

void MainWindow::setupToolbar()
{
    mainToolBar = addToolBar("Main");
    
    mainToolBar->addAction(addAction);
    mainToolBar->addAction(editAction);
    mainToolBar->addAction(deleteAction);
    mainToolBar->addSeparator();
    mainToolBar->addAction(loadAction);
    mainToolBar->addAction(saveAction);
}

void MainWindow::setupStatusBar()
{
    statusBar()->showMessage("Ready");
}

void MainWindow::populateTable()
{
    QVector<SoftwarePackage> packages = database.getAllPackages();
    tableWidget->setRowCount(packages.size());
    
    for (int i = 0; i < packages.size(); ++i) {
        const SoftwarePackage& package = packages[i];
        
        QTableWidgetItem *nameItem = new QTableWidgetItem(package.getName());
        QTableWidgetItem *manufacturerItem = new QTableWidgetItem(package.getManufacturer());
        QTableWidgetItem *sizeItem = new QTableWidgetItem(QString::number(package.getSize()));
        QTableWidgetItem *versionItem = new QTableWidgetItem(package.getVersion());
        QTableWidgetItem *yearItem = new QTableWidgetItem(QString::number(package.getYear()));
        
        tableWidget->setItem(i, 0, nameItem);
        tableWidget->setItem(i, 1, manufacturerItem);
        tableWidget->setItem(i, 2, sizeItem);
        tableWidget->setItem(i, 3, versionItem);
        tableWidget->setItem(i, 4, yearItem);
    }
    
    tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    updateStatusBar();
}

void MainWindow::updateStatusBar()
{
    int count = database.getPackageCount();
    statusBar()->showMessage(QString("Total packages: %1").arg(count));
}

void MainWindow::refreshTable()
{
    populateTable();
    updateStatusBar();
}

void MainWindow::onAddPackage()
{
    bool ok;
    QString name = QInputDialog::getText(this, "Add Package", "Package Name:", QLineEdit::Normal, "", &ok);
    if (!ok || name.isEmpty()) return;
    
    QString manufacturer = QInputDialog::getText(this, "Add Package", "Manufacturer:", QLineEdit::Normal, "", &ok);
    if (!ok) return;
    
    QString sizeStr = QInputDialog::getText(this, "Add Package", "Size (MB):", QLineEdit::Normal, "0.0", &ok);
    if (!ok) return;
    double size = sizeStr.toDouble(&ok);
    if (!ok) {
        QMessageBox::warning(this, "Error", "Invalid size value!");
        return;
    }
    
    QString version = QInputDialog::getText(this, "Add Package", "Version:", QLineEdit::Normal, "", &ok);
    if (!ok) return;
    
    QString yearStr = QInputDialog::getText(this, "Add Package", "Release Year:", QLineEdit::Normal, "0", &ok);
    if (!ok) return;
    int year = yearStr.toInt(&ok);
    if (!ok) {
        QMessageBox::warning(this, "Error", "Invalid year value!");
        return;
    }
    
    SoftwarePackage package(name, manufacturer, size, version, year);
    database.addPackage(package);
    refreshTable();
}

void MainWindow::onEditPackage()
{
    int row = tableWidget->currentRow();
    if (row < 0) {
        QMessageBox::information(this, "Info", "Please select a package to edit.");
        return;
    }
    
    QVector<SoftwarePackage> packages = database.getAllPackages();
    if (row >= packages.size()) return;
    
    SoftwarePackage package = packages[row];
    
    bool ok;
    QString name = QInputDialog::getText(this, "Edit Package", "Package Name:", QLineEdit::Normal, package.getName(), &ok);
    if (!ok) return;
    
    QString manufacturer = QInputDialog::getText(this, "Edit Package", "Manufacturer:", QLineEdit::Normal, package.getManufacturer(), &ok);
    if (!ok) return;
    
    QString sizeStr = QInputDialog::getText(this, "Edit Package", "Size (MB):", QLineEdit::Normal, QString::number(package.getSize()), &ok);
    if (!ok) return;
    double size = sizeStr.toDouble(&ok);
    if (!ok) {
        QMessageBox::warning(this, "Error", "Invalid size value!");
        return;
    }
    
    QString version = QInputDialog::getText(this, "Edit Package", "Version:", QLineEdit::Normal, package.getVersion(), &ok);
    if (!ok) return;
    
    QString yearStr = QInputDialog::getText(this, "Edit Package", "Release Year:", QLineEdit::Normal, QString::number(package.getYear()), &ok);
    if (!ok) return;
    int year = yearStr.toInt(&ok);
    if (!ok) {
        QMessageBox::warning(this, "Error", "Invalid year value!");
        return;
    }
    
    SoftwarePackage newPackage(name, manufacturer, size, version, year);
    database.editPackage(row, newPackage);
    refreshTable();
}

void MainWindow::onDeletePackage()
{
    int row = tableWidget->currentRow();
    if (row < 0) {
        QMessageBox::information(this, "Info", "Please select a package to delete.");
        return;
    }
    
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirm Delete", "Are you sure you want to delete this package?",
                                  QMessageBox::Yes | QMessageBox::No);
    
    if (reply == QMessageBox::Yes) {
        database.removePackage(row);
        refreshTable();
    }
}

void MainWindow::onSearchPackages()
{
    QString searchTerm = searchLineEdit->text();
    if (searchTerm.isEmpty()) {
        populateTable();
        return;
    }
    
    auto predicate = [searchTerm](const SoftwarePackage& package) {
        return package.getName().contains(searchTerm, Qt::CaseInsensitive) ||
               package.getManufacturer().contains(searchTerm, Qt::CaseInsensitive) ||
               package.getVersion().contains(searchTerm, Qt::CaseInsensitive);
    };
    
    QList<SoftwarePackage> results = database.findPackages(predicate);
    
    tableWidget->setRowCount(results.size());
    
    for (int i = 0; i < results.size(); ++i) {
        const SoftwarePackage& package = results[i];
        
        QTableWidgetItem *nameItem = new QTableWidgetItem(package.getName());
        QTableWidgetItem *manufacturerItem = new QTableWidgetItem(package.getManufacturer());
        QTableWidgetItem *sizeItem = new QTableWidgetItem(QString::number(package.getSize()));
        QTableWidgetItem *versionItem = new QTableWidgetItem(package.getVersion());
        QTableWidgetItem *yearItem = new QTableWidgetItem(QString::number(package.getYear()));
        
        tableWidget->setItem(i, 0, nameItem);
        tableWidget->setItem(i, 1, manufacturerItem);
        tableWidget->setItem(i, 2, sizeItem);
        tableWidget->setItem(i, 3, versionItem);
        tableWidget->setItem(i, 4, yearItem);
    }
    
    tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    statusBar()->showMessage(QString("Search results: %1 packages found").arg(results.size()));
}

void MainWindow::onLoadDatabase()
{
    QString filename = QFileDialog::getOpenFileName(this, "Load Database", "", "Database Files (*.db);;All Files (*)");
    if (filename.isEmpty()) return;
    
    if (database.loadFromFile(filename)) {
        refreshTable();
        statusBar()->showMessage("Database loaded successfully: " + filename);
    } else {
        QMessageBox::critical(this, "Error", "Failed to load database file!");
    }
}

void MainWindow::onSaveDatabase()
{
    QString filename = QFileDialog::getSaveFileName(this, "Save Database", "", "Database Files (*.db);;All Files (*)");
    if (filename.isEmpty()) return;
    
    if (database.saveToFile(filename)) {
        statusBar()->showMessage("Database saved successfully: " + filename);
    } else {
        QMessageBox::critical(this, "Error", "Failed to save database file!");
    }
}

void MainWindow::onMergeDatabases()
{
    QString filename = QFileDialog::getOpenFileName(this, "Merge Database", "", "Database Files (*.db);;All Files (*)");
    if (filename.isEmpty()) return;
    
    Database tempDatabase;
    if (tempDatabase.loadFromFile(filename)) {
        database.mergeDatabase(tempDatabase);
        refreshTable();
        statusBar()->showMessage("Database merged successfully: " + filename);
    } else {
        QMessageBox::critical(this, "Error", "Failed to load database file for merging!");
    }
}

void MainWindow::onAbout()
{
    QMessageBox::about(this, "About", 
                      "Software Package Database\n\n"
                      "A database application for managing software packages.\n\n"
                      "Features:\n"
                      "- Add, edit, and delete software packages\n"
                      "- Search functionality\n"
                      "- Load and save databases\n"
                      "- Merge databases\n"
                      "- Custom container implementation\n\n"
                      "Developed using Qt5 and C++");
}

void MainWindow::onClearSearch()
{
    searchLineEdit->clear();
    populateTable();
}

void MainWindow::onContextMenuRequested(const QPoint &pos)
{
    if (!contextMenu) {
        contextMenu = new QMenu(this);
        contextMenu->addAction(addAction);
        contextMenu->addAction(editAction);
        contextMenu->addAction(deleteAction);
        contextMenu->addSeparator();
        contextMenu->addAction(showAllAction);
    }
    
    contextMenu->exec(tableWidget->mapToGlobal(pos));
}

void MainWindow::onShowAllPackages()
{
    populateTable();
}