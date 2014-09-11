#include "editorwindow.h"
#include "ui_editorwindow.h"

#include "aboutwindow.h"


#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QTime>


EditorWindow::EditorWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::EditorWindow)
{
    ui->setupUi(this);

    txtEditor = CreateTab();

    txtEditor->installEventFilter(this);
    SetLetters(true);

    this->setFixedSize(width(), height());
    addAction(ui->actionSaveAs);

    resetToBaseState();

}

EditorWindow::~EditorWindow()
{
    delete ui;
}

QPlainTextEdit* EditorWindow::CreateTab(){
    QPlainTextEdit *newEditor = new QPlainTextEdit;
    newEditor->setFont(QFont("Lucida Console", 12));
    editors.append(newEditor);
    ui->tabWidget->addTab(newEditor, "untitled");
    return newEditor;
}

QPlainTextEdit* EditorWindow::CreateTab(QString tabName){
    QPlainTextEdit *newEditor = new QPlainTextEdit;
    newEditor->setFont(QFont("Lucida Console", 12));
    editors.append(newEditor);
    ui->tabWidget->addTab(newEditor, tabName);
    return newEditor;
}

// Shortcuts implementation
void EditorWindow::on_actionList_triggered(bool condition)
{
    // Switch button states
    ui->actionNumberedList->setEnabled(!condition);

    // Setup list states
    markedListOn = condition;

    if (condition) {
        txtEditor->appendPlainText(QString::fromUtf8("+ "));
        SetLetters(true);
    }
}

void EditorWindow::on_actionNumberedList_triggered(bool condition)
{
    // Switch button states
    ui->actionList->setEnabled(!condition);

    // Setup list states
    numberedListOn = condition;

    if (!numberedListOn) {
        numberedListCounter = 1;
    }

    if (condition) {
        txtEditor->appendPlainText(QString::fromUtf8("1. "));
        SetLetters(true);
    }
}

void EditorWindow::SetLetters(bool isCapital){
    //We set letters to capital

    QTextCharFormat capital2;
    if(isCapital){
        capital2.setFontCapitalization(QFont::Capitalize);
    }
    else{
        capital2.setFontCapitalization(QFont::MixedCase);
    }
    txtEditor->setCurrentCharFormat(capital2);
}

bool EditorWindow::eventFilter(QObject *obj, QEvent *e)
{
    if (obj == txtEditor && e->type() == QEvent::KeyRelease) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent*>(e);
        if (keyEvent->key() == Qt::Key_Return ||
            keyEvent->key() == Qt::Key_Enter)
        {
            if (markedListOn) {
                txtEditor->appendPlainText(QString::fromUtf8("+ "));
            }
            else if (numberedListOn) {
                txtEditor->insertPlainText(QString::number(++numberedListCounter) +
                                                    QString::fromUtf8(". "));
            }
            else if(lectureNameEdit){
                txtEditor->textCursor().deletePreviousChar();
                txtEditor->insertPlainText(" " + QDate::currentDate().toString() + "\n\n");
                this->lectureNameEdit = false;
            }

            /*
             * A little fix that prevents data appearing again
             * if enter was pressed after list (or smth else)
             */
            if(lectureNameEdit) this->lectureNameEdit = false;

            SetLetters(true);
            return true;
        }
        else if(keyEvent->key() == Qt::Key_Space){
            //Let's make letters capital after a dot!

            QTextCursor cursor = txtEditor->textCursor();
            cursor.movePosition(QTextCursor::PreviousCharacter);
            cursor.select(QTextCursor::WordUnderCursor);
            QString c = cursor.selectedText().right(1);
            if(c == "."){
                SetLetters(true);
            }
        }
        else {
            SetLetters(false);
            return QMainWindow::eventFilter(obj, e);
        }
    }
    else {
        return QMainWindow::eventFilter(obj, e);
    }

}

void EditorWindow::resetToBaseState()
{
    ui->actionList->setEnabled(true);
    ui->actionList->setChecked(false);
    markedListOn = false;

    ui->actionNumberedList->setEnabled(true);
    ui->actionNumberedList->setChecked(false);
    numberedListOn = false;
    numberedListCounter = 1;

    this->lectureNameEdit = false;

    textWasChanged = false;
    documentWasSaved = false;

    currentFileName = "Untitled";
    this->setWindowTitle("NoteIt Pad - " + currentFileName);
    ui->statusBar->showMessage(QTime::currentTime().toString() + " - Created new empty document");
}


void EditorWindow::on_actionLineTildas_triggered()
{
    txtEditor->appendPlainText("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
}

void EditorWindow::on_actionHeader_triggered()
{
    txtEditor->insertPlainText("------------");
    SetLetters(true);
}

void EditorWindow::on_actionDefinition_triggered()
{
    txtEditor->insertPlainText("\n-> ");
    SetLetters(true);
}

void EditorWindow::on_actionLecture_triggered()
{
    txtEditor->appendPlainText("\n===Lecture #");
    this->lectureNameEdit = true;
}


// Save/Load functionality implementation
void EditorWindow::on_actionSave_triggered()
{
    QString saveFileName = currentFileName;

    // If this document was not already saved, open
    // a SaveFile dialog
    if (!documentWasSaved) {
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
    else {
        QFile file(saveFileName);

        // Try to open file in Write-only mode
        if (!file.open(QIODevice::WriteOnly)) {
            QMessageBox::information(this,
                                     tr("Unable to open file"),
                                     file.errorString());
            return;
        }

        // Write contents to txt file:
        QTextStream out(&file);
        out.setCodec("UTF-8");
        out << txtEditor->toPlainText();

        // Change system variables
        currentFileName = saveFileName;
        documentWasSaved = true;
        textWasChanged = false;

        // Refresh supplemental text...
        QString shortName = QFileInfo(file).baseName();
        setWindowTitle("NoteIt Pad - " + shortName);
        ui->statusBar->showMessage(QTime::currentTime().toString() + " - Saved file \"" + shortName + "\"");
    }
}

void EditorWindow::on_actionSaveAs_triggered()
{
    documentWasSaved = false;
    on_actionSave_triggered();
}

void EditorWindow::on_actionOpen_triggered()
{
    bool decision = haveUnsavedChanges();

    // User deceided to wait
    if (decision == true) {
        return;
    }

    QString loadFileName = QFileDialog::getOpenFileName(this,
             tr("Open notes file..."), "",
             tr("Plain text files (*.txt);;All Files (*)"));

    if (loadFileName.isEmpty()) {
             return;
    }
    else {
        // Crate instance of file
        QFile file(loadFileName);

        // Try to open file for reading
        if (!file.open(QIODevice::ReadOnly)) {
            QMessageBox::information(this,
                                     tr("Unable to open file"),
                                     file.errorString());
            return;
        }

        // Read text file contents
        QTextStream in(&file);
        in.setCodec("UTF-8");
        QString contents = in.readAll();

        // Reset window
        resetToBaseState();

        txtEditor = CreateTab(QFileInfo(file).baseName());

        // Insert data into editor
        txtEditor->setPlainText(contents);
        currentFileName = loadFileName;

        documentWasSaved = true;
        textWasChanged = false;

        // Refresh supplemental text
        QString shortName = QFileInfo(file).baseName();
        setWindowTitle("NoteIt Pad - " + shortName);
        ui->statusBar->showMessage(QTime::currentTime().toString() + " - Loaded file \"" + shortName + "\"");
    }
}

void EditorWindow::closeEvent(QCloseEvent *e)
{
    bool decision = haveUnsavedChanges();

    // User deceided to wait
    if (decision == true) {
        e->ignore();
        return;
    }

    e->accept();
}

void EditorWindow::on_actionNew_triggered()
{
   /* bool decision = haveUnsavedChanges();

    if (decision) {
        return;
    }
    // Reset window
    txtEditor->clear();
    resetToBaseState();*/
    CreateTab();
}

// Supplemental functionality
void EditorWindow::on_txtEditorField_textChanged()
{
    textWasChanged = true;
}

bool EditorWindow::haveUnsavedChanges()
{
    // Detect if user has unsaved changes
    if (textWasChanged) {

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
            on_actionSave_triggered();
            return false;
        }

        return true;
    }

    return false;
}

void EditorWindow::on_actionHelp_triggered()
{
    AboutWindow *about = new AboutWindow(this);
    about->show();
}

void EditorWindow::on_searchButton_clicked()
{
    StartSearch();
}

void EditorWindow::on_searchRequest_textChanged(const QString &arg1)
{
    txtEditor->moveCursor(QTextCursor::Start);
    //Some improvements fore live search
    QString s = ui->searchRequest->text();
    if(!ui->searchRequest->text().isEmpty() && !txtEditor->find(s)){
        ui->searchRequest->setStyleSheet("QLineEdit{background: #FF3848;}");
    }
    else ui->searchRequest->setStyleSheet("QLineEdit{background: white;}");
}

void EditorWindow::on_searchRequest_returnPressed()
{
    StartSearch();
}

void EditorWindow::StartSearch(){
    QString s = ui->searchRequest->text();
    txtEditor->setFocus();
    if(!txtEditor->find(s)){
        QMessageBox::information(this,
                                              "Nothing found",
                                              "Find reached the starting point of the search",
                                              QMessageBox::Ok);
        txtEditor->setFocus();
        txtEditor->moveCursor(QTextCursor::Start);
        txtEditor->find(s);
    }
}

void EditorWindow::on_findLectureButton_clicked()
{
    txtEditor->setFocus();
    txtEditor->moveCursor(QTextCursor::Start);
    QString s = "===Lecture #" + ui->lectureNumberField->text();
    txtEditor->find(s);
}

void EditorWindow::on_tabWidget_currentChanged(int index)
{
    //txtEditor->
    txtEditor = editors.at(index);
    txtEditor->installEventFilter(this);
    //txtEditor = ui->tabWidget->currentWidget();
}
