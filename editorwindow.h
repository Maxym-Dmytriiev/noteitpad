#ifndef EDITORWINDOW_H
#define EDITORWINDOW_H

#include <QMainWindow>
#include <QVector>

#include "editorwidget.h"

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

    void on_actionNew_triggered();

    /*
    // Shortcuts functionality
    void on_actionList_triggered(bool condition);
    void on_actionNumberedList_triggered(bool condition);
    void on_actionLineTildas_triggered();
    void on_actionHeader_triggered();

    // Save/Load functionality
    void on_actionSave_triggered();
    void on_actionOpen_triggered();

    // Supplemental functionality

    void on_actionNew_triggered();
    void on_actionSaveAs_triggered();
    void on_actionHelp_triggered();
    void on_actionLecture_triggered();
    void on_searchButton_clicked();
    void on_searchRequest_textChanged(const QString &arg1);
    void on_searchRequest_returnPressed();
    void on_findLectureButton_clicked();
    void on_actionDefinition_triggered();
    void on_tabWidget_currentChanged(int index);
    */
protected:
    //void closeEvent(QCloseEvent *e);

private:
    Ui::EditorWindow *ui;
    EditorWidget *editor;

    //bool eventFilter(QObject *obj, QEvent *e);

    // State management
    void setStateToDefault();
    void setStateFromSettings(const EditorSettings *source);

    void StartSearch();
    void SetLetters(bool isCapital);

    void createTab(QString tabName = QString("Untitled"));
};

#endif // EDITORWINDOW_H
