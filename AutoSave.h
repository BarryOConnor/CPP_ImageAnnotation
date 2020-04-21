#ifndef AUTOSAVE_H
#define AUTOSAVE_H
#include "Annotation.h"
#include <QThread>
#include <QTimer>

class AutoSave : public QObject
{
    Q_OBJECT

public:
    AutoSave();

public slots:
    void saveDataReady(QVector<QString> * uniqueImages, QVector<QPair<QString, QVector<Annotation *>>> *jsonData);

signals:
    void getSaveData();

private:
    QTimer *timer;
    QString filename;
    bool overwrite;
};
#endif // AUTOSAVE_H
