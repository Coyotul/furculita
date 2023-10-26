#include "UiFileOpener.h"
#include <QtDesigner/QtDesigner>
#include <QtDesigner/QDesignerFormWindowManagerInterface>

UiFileOpener::UiFileOpener(QObject* parent) : QObject(parent) {}

void UiFileOpener::openUiFile(const QString& uiFilePath) {
    QDesignerFormWindowManagerInterface* manager = QDesignerFormWindowManagerInterface::instance();

    if (manager) {
        QDesignerFormWindowInterface* formWindow = manager->createFormWindow();
        if (formWindow) {
            formWindow->openUiFile(uiFilePath, true);
            formWindow->setVisible(true);
        }
    }
}