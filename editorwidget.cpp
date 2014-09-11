#include "editorwidget.h"

EditorWidget::EditorWidget(QWidget *parent) :
    QPlainTextEdit(parent)
{
    settings = new EditorSettings();
}

EditorSettings *EditorWidget::getSettings() const
{
    return settings;
}
void EditorWidget::setSettings(EditorSettings *value)
{
    settings = value;
}

