#ifndef EDITORWIDGET_H
#define EDITORWIDGET_H

#include <QPlainTextEdit>

class EditorWidget : public QPlainTextEdit
{
    Q_OBJECT
public:
    explicit EditorWidget(QWidget *parent = 0);

signals:

public slots:

};

#endif // EDITORWIDGET_H
