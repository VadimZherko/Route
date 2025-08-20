#include "../include/mainwindow.h"
#include "../ui/ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    dialogWidget(new Dialog),
    scene(new Scene),
    markTable(new MarkTable),
    actionTable(new ActionTable),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QPixmap pix(":/new/prefix1/axis.png");
    ui->image->setPixmap(pix);
    ui->image->setStyleSheet("background-color: rgba(255, 255, 255, 0);");
    ui->image->resize(pix.size());

    int windowWidth = this->width();
    int windowHeight = this->height();

    //markTable->resize(MARKTABLE_SIZE, windowHeight);
    markTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    actionTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //markTable->move(windowWidth - MARKTABLE_SIZE, 0);
    markTable->setParent(this);
    actionTable->setParent(this);

    ui->tabWidget->removeTab(1);
    ui->tabWidget->removeTab(0);

    ui->tabWidget->insertTab(0, markTable,"Marks");
    ui->tabWidget->insertTab(1, actionTable,"Actions");

    ui->tabWidget->resize(MARKTABLE_SIZE, windowHeight);
    ui->tabWidget->move(windowWidth - MARKTABLE_SIZE, 0);

    QObject::connect(ui->loadMarkButton, SIGNAL(clicked()), this->dialogWidget, SLOT(showLoadMarkFromFileDialog()));
    QObject::connect(ui->saveMarkButton, SIGNAL(clicked()), this->dialogWidget, SLOT(showSaveMarkInFileDialog()));

    QObject::connect(scene, &Scene::keyPressEvent_, this, &MainWindow::keyPressEvent);

    QObject::connect(scene, &Scene::setRubberBandDrag, this->ui->workArea,
                     [this]() { this->ui->workArea->setDragMode(QGraphicsView::RubberBandDrag); });
    QObject::connect(scene, &Scene::setScrollHandDrag, this->ui->workArea,
                     [this]() { this->ui->workArea->setDragMode(QGraphicsView::ScrollHandDrag); });
    QObject::connect(dialogWidget, &Dialog::setScrollHandDrag, this->ui->workArea,
                     [this]() {this->ui->workArea->setDragMode(QGraphicsView::ScrollHandDrag);});

    QObject::connect(scene, &Scene::markAdded, this->markTable, &MarkTable::addRow);
    QObject::connect(scene, &Scene::markCoordsUpdated, this->markTable, &MarkTable::updateCoordsRow);
    QObject::connect(scene, &Scene::markRemoved, this->markTable, &MarkTable::removeRow);
    QObject::connect(actionTable, &ActionTable::moveSignal, this->scene, &Scene::moveLineAdd);
    QObject::connect(actionTable, &ActionTable::delMoveSignal, this->scene, &Scene::moveLineDelete);

    QObject::connect(dialogWidget, &Dialog::saveFilePath, this->actionTable, &ActionTable::saveInFile);
    QObject::connect(dialogWidget, &Dialog::loadFilePath, this->scene, &Scene::loadTable);

    QObject::connect(markTable, &MarkTable::doubleClicked, this, &MainWindow::toMark);

    ui->workArea->setScene(scene);
    ui->workArea->centerOn(-GRID_SIZE * SCENE_X_COEF + 600, GRID_SIZE * SCENE_HEIGHT_COEF - 2250);

    QObject::connect(scene,&Scene::markAction,this->actionTable,&ActionTable::addRow);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent* event)
{
    QMainWindow::resizeEvent(event);

    int windowWidth = this->width();
    int windowHeight = this->height();

    int tableWidth = ui->tabWidget->width();

    ui->tabWidget->move(windowWidth - tableWidth, 0);
    ui->tabWidget->resize(MARKTABLE_SIZE, windowHeight);
    ui->workArea->resize(windowWidth - tableWidth, windowHeight);
    ui->image->move(20, windowHeight - 100);
}

void MainWindow::keyPressEvent(QKeyEvent* event)
{
    if(event->modifiers() == Qt::ControlModifier && event->key() == Qt::Key_S)
    {
        dialogWidget->showSaveMarkInFileDialog();
        ui->workArea->setDragMode(QGraphicsView::ScrollHandDrag);
    }
    else if(event->modifiers() == Qt::ControlModifier && event->key() == Qt::Key_L)
    {
        dialogWidget->showLoadMarkFromFileDialog();
        ui->workArea->setDragMode(QGraphicsView::ScrollHandDrag);
    }
}

//Not working
void MainWindow::toMark(const QModelIndex& index)
{
    auto coords = markTable->getCoords(index.row());
    ui->workArea->centerOn(coords.first, coords.second);
}


