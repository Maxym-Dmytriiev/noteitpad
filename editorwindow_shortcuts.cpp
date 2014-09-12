#include "editorwindow.h"
#include "ui_editorwindow.h"

#include "aboutwindow.h"

// Help button click action
void EditorWindow::on_actionHelp_triggered()
{
    AboutWindow *about = new AboutWindow(this);
    about->show();
}
