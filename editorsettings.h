#ifndef EDITORSETTINGS_H
#define EDITORSETTINGS_H

#include <QString>

class EditorSettings
{
public:
    EditorSettings();

    bool getMarkedListOn() const;
    void setMarkedListOn(bool value);

    bool getNumberedListOn() const;
    void setNumberedListOn(bool value);

    int getNumberedListIndex() const;
    void setNumberedListIndex(int value);

    bool getDocumentWasSaved() const;
    void setDocumentWasSaved(bool value);

    QString getCurrentFileName() const;
    void setCurrentFileName(const QString &value);

    void reset();

private:

    bool markedListOn;
    bool numberedListOn;
    int numberedListIndex;
    bool documentWasSaved;

    QString currentFileName;

};

#endif // EDITORSETTINGS_H
