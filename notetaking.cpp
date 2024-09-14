#include "notetaking.h"
#include <QFile>
#include <QTextStream>

NoteTaking::NoteTaking(QObject *parent)
    : QObject(parent)
{

}

QStringList NoteTaking::loadTasks() const
{
    QStringList tasks;
    QFile file(filePath);

    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine();
            tasks.append(line);
        }
        file.close();
    }

    return tasks;
}

bool NoteTaking::addTask(const QString &task)
{
    QStringList tasks = loadTasks();
    tasks.append(task);
    saveTasks(tasks);
    return true;
}

bool NoteTaking::removeTask(int index)
{
    QStringList tasks = loadTasks();

    if (index >= 0 && index < tasks.size()) {
        tasks.removeAt(index);
        saveTasks(tasks);
        return true;
    }

    return false;
}

void NoteTaking::saveTasks(const QStringList &tasks) const
{
    QFile file(filePath);

    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        for (const QString &task : tasks) {
            out << task << "\n";
        }
        file.close();
    }
}
