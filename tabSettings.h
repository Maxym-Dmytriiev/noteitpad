#ifndef TABSETTINGS_H
#define TABSETTINGS_H

#include <QMainWindow>
#include <QPlainTextEdit>
#include <QVector>
#include "editorwindow.h"

namespace Ui {
    class TabSettings;
}

class TabSettings{
public:
    TabSettings() {}

    Ui::EditorWindow *ui;

    QPlainTextEdit *txtEditor;
    QVector<QPlainTextEdit*> editors;

    bool documentWasSaved;
    bool markedListOn;
    bool numberedListOn;
    bool lectureNameEdit;
    int numberedListCounter;
    int tabIndex;

    bool textWasChanged;

    QString currentFileName;

    bool haveUnsavedChanges();
    bool eventFilter(QObject *obj, QEvent *e);

    void resetToBaseState();
};
#endif // TABSETTINGS_H
