#ifndef EDITORWINDOW_H
#define EDITORWINDOW_H

#include <QMainWindow>

namespace Ui {
class EditorWindow;
}

class EditorWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit EditorWindow(QWidget *parent = 0);
    ~EditorWindow();

private slots:

    // Shortcuts functionality
    void on_actionList_triggered(bool condition);
    void on_actionNumberedList_triggered(bool condition);
    void on_actionLineTildas_triggered();
    void on_actionHeader_triggered();

    // Save/Load functionality
    void on_actionSave_triggered();
    void on_actionOpen_triggered();

    // Supplemental functionality
    void on_txtEditorField_textChanged();

    void on_actionNew_triggered();

    void on_actionSaveAs_triggered();

    void on_actionHelp_triggered();

    void on_actionLecture_triggered();

protected:
    void closeEvent(QCloseEvent *e);

private:
    Ui::EditorWindow *ui;

    bool documentWasSaved;
    bool markedListOn;
    bool numberedListOn;
    bool lectureNameEdit;
    int numberedListCounter;

    bool textWasChanged;

    QString currentFileName;

    bool haveUnsavedChanges();
    bool eventFilter(QObject *obj, QEvent *e);

    void resetToBaseState();
};

#endif // EDITORWINDOW_H
