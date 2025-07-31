#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QPushButton>
#include <QMessageBox>
#include <QComboBox>
#include <QFileDialog>

class Dialog : public QDialog
{
    Q_OBJECT

private:
    QFileDialog saveMarkInFileDialog;
    QFileDialog loadMarkFromFileDialog;

signals:
    void saveFilePath(QString);
    void loadFilePath(QString);

    void setScrollHandDrag();

public slots:
    void showSaveMarkInFileDialog();
    void showLoadMarkFromFileDialog();
};

#endif // DIALOG_H
