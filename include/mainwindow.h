#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QKeyEvent>
#include <QString>

#include "../include/dialog.h"
#include "../include/scene.h"
#include "../include/marktable.h"
#include "../include/config.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Dialog* dialogWidget;
    Scene* scene;
    MarkTable* markTable;

    void setUpTableView();
    void resizeEvent(QResizeEvent*) override;
    void keyPressEvent(QKeyEvent*) override;

private slots:
    void toMark(const QModelIndex&);
};
#endif // MAINWINDOW_H
