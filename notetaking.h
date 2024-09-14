#ifndef NOTETAKING_H
#define NOTETAKING_H

#include <QObject>
#include <QStringList>
#include <QFile>
#include <QTextStream>

class NoteTaking : public QObject
{
    Q_OBJECT

public:
    explicit NoteTaking(QObject *parent = nullptr);
    QStringList loadTasks() const;
    bool addTask(const QString &task);
    bool removeTask(int index);

private:
    QString filePath = "tasks.txt";
    void saveTasks(const QStringList &tasks) const;
};

#endif // NOTETAKING_H
