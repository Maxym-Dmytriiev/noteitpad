#include "editorsettings.h"

EditorSettings::EditorSettings()
{
    reset();
}

bool EditorSettings::getMarkedListOn() const
{
    return markedListOn;
}
void EditorSettings::setMarkedListOn(bool value)
{
    markedListOn = value;
}

bool EditorSettings::getNumberedListOn() const
{
    return numberedListOn;
}
void EditorSettings::setNumberedListOn(bool value)
{
    numberedListOn = value;
}

int EditorSettings::getNumberedListIndex() const
{
    return numberedListIndex;
}
void EditorSettings::setNumberedListIndex(int value)
{
    numberedListIndex = value;
}

bool EditorSettings::getDocumentWasSaved() const
{
    return documentWasSaved;
}
void EditorSettings::setDocumentWasSaved(bool value)
{
    documentWasSaved = value;
}

QString EditorSettings::getCurrentFileName() const
{
    return currentFileName;
}
void EditorSettings::setCurrentFileName(const QString &value)
{
    currentFileName = value;
}

bool EditorSettings::getTextWasChanged() const
{
    return textWasChanged;
}
void EditorSettings::setTextWasChanged(bool value)
{
    textWasChanged = value;
}


void EditorSettings::reset()
{
    markedListOn = false;
    numberedListOn = false;
    numberedListIndex = 1;
    documentWasSaved = false;
    currentFileName = QString::fromStdString("Untitled");
}







