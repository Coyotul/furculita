#ifndef UIFILEOPENER_H
#define UIFILEOPENER_H

#include <QObject>
#include <QString>

class UiFileOpener : public QObject {
    Q_OBJECT
public:
    UiFileOpener(QObject* parent = nullptr);

public slots:
    void openUiFile(const QString& uiFilePath);
};

#endif // UIFILEOPENER_H