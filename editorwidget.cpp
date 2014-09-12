#include "editorwidget.h"
#include <QMessageBox>

#include <QDebug>


EditorWidget::EditorWidget(QWidget *parent) :
    QPlainTextEdit(parent)
{
    settings = new EditorSettings();
    this->setFont(QFont("Lucida Console", 13));

    connect(this, SIGNAL(textChanged()), this, SLOT(on_textChanged()));
}

EditorSettings *EditorWidget::getSettings() const
{
    return settings;
}
void EditorWidget::setSettings(EditorSettings *value)
{
    settings = value;
}

void EditorWidget::on_textChanged()
{
    settings->setTextWasChanged(true);
}

bool EditorWidget::haveUnsavedChanges()
{
    // Detect if user has unsaved changes
    if (settings->textWasChanged) {

        QMessageBox::StandardButton reply;
        // Ask user for actions
        reply = QMessageBox::question(this,
                                      "Unsaved changes",
                                      "You have unsaved changes.\nSave them?",
                                      QMessageBox::Yes|QMessageBox::No|QMessageBox::Cancel);

        // Discard changes
        if (reply == QMessageBox::No) {
            return false;
        }

        // Save changes
        if (reply == QMessageBox::Yes) {
            return false;
        }

        return true;
    }

    return false;
}

bool EditorWidget::save(QFile * const file )
{
    // Try to open file in Write-only mode
    if (!file->open(QIODevice::WriteOnly)) {
        QMessageBox::information(this,
                                 tr("Unable to open file"),
                                 file->errorString());
        return false;
    }

    // Write contents to txt file:
    QTextStream out(file);
    out.setCodec("UTF-8");
    out << this->toPlainText();

    return true;
}



