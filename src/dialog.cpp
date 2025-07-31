#include "../include/dialog.h"

void Dialog::showSaveMarkInFileDialog()
{
    QString filePath = QFileDialog::getSaveFileName(nullptr, "Сохранить файл",
                                                    QDir::homePath() + "/untitled.csv",
                                                    "Text files (*.csv);;All files (*.*)");

    if(!filePath.isEmpty())
    {
        emit saveFilePath(filePath);
    }

    emit setScrollHandDrag();
}

void Dialog::showLoadMarkFromFileDialog()
{
    QString filePath = QFileDialog::getOpenFileName(nullptr, "Выбрать файл",
                                                    QDir::homePath(),
                                                    "Text files (*.csv);;All files (*.*)");

    if(!filePath.isEmpty())
    {
        emit loadFilePath(filePath);
    }

    emit setScrollHandDrag();
}


