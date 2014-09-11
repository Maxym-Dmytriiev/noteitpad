#ifndef EDITORWIDGET_H
#define EDITORWIDGET_H

#include <QPlainTextEdit>
#include "editorsettings.h"

class EditorWidget : public QPlainTextEdit
{
    Q_OBJECT
public:
    explicit EditorWidget(QWidget *parent = 0);

    EditorSettings *getSettings() const;
    void setSettings(EditorSettings *value);

signals:

public slots:

private:
    EditorSettings *settings;

};

#endif // EDITORWIDGET_H
