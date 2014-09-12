#include "editorwindow.h"
#include "ui_editorwindow.h"

#include <QDebug>
void EditorWindow::on_actionNew_triggered()
{
    createTab();
}

void EditorWindow::on_actionSave_triggered()
{
    qDebug() << "qq" << endl;

    EditorSettings *itsSettings = editor->getSettings();
    QString saveFileName = itsSettings->getCurrentFileName();

    // If this document was not already saved, open
    // a SaveFile dialog
    if (!itsSettings->getDocumentWasSaved()) {
        // Open dialog with user
        saveFileName = QFileDialog::getSaveFileName
                (this,
                 tr("Save notes..."),
                 "",
                 tr("Plain text file (*.txt);;All Files (*)"));

    }

    // If user deceided not to save file
    if (saveFileName.isEmpty()) {
            return;
    }

    QFile file(saveFileName);

    bool result = editor->save(&file);
    if (!result) return;

    // Change system variables
    itsSettings->setCurrentFileName(saveFileName);

    itsSettings->setDocumentWasSaved(true);
    itsSettings->setTextWasChanged(false);

    // Refresh supplemental text...
    QString shortName = QFileInfo(file).baseName();

    // Rename tab
    int index = ui->tabWidget->currentIndex();
    ui->tabWidget->setTabText(index, shortName);

    // StatusBar message
    ui->statusBar->showMessage(QTime::currentTime().toString() + " - Saved file \"" + shortName + "\"");

}
