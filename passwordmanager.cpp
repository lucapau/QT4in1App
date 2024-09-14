#include "passwordmanager.h"
#include <QFile>
#include <QTextStream>
#include <QCryptographicHash>
#include <QDebug>

PasswordManager::PasswordManager(QObject *parent)
    : QObject(parent)
{

}

bool PasswordManager::addPassword(const QString &website, const QString &username, const QString &password)
{
    QList<PasswordEntry> passwords = loadPasswords();

    // Encrypt password before saving
    QString encryptedPassword = encryptPassword(password);

    PasswordEntry newEntry{website, username, encryptedPassword};
    passwords.append(newEntry);

    return savePasswords(passwords);
}

bool PasswordManager::deletePassword(const QString &website, const QString &username)
{
    QList<PasswordEntry> passwords = loadPasswords();

    // Search and remove the password entry
    auto it = std::remove_if(passwords.begin(), passwords.end(),
                             [&](const PasswordEntry &entry) {
                                 return entry.website == website && entry.username == username;
                             });

    // Check if any matching entry was found and removed
    if (it != passwords.end()) {
        passwords.erase(it, passwords.end()); // Correctly erase the elements
        return savePasswords(passwords);
    }

    return false; // Return false if entry not found
}


QList<PasswordEntry> PasswordManager::viewPasswords() const
{
    return loadPasswords();
}

QList<PasswordEntry> PasswordManager::loadPasswords() const
{
    QList<PasswordEntry> passwords;
    QFile file(storageFilePath);

    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList fields = line.split(",");
            if (fields.size() == 3) {
                PasswordEntry entry;
                entry.website = fields[0];
                entry.username = fields[1];
                entry.encryptedPassword = fields[2];
                passwords.append(entry);
            }
        }
        file.close();
    }

    return passwords;
}

bool PasswordManager::savePasswords(const QList<PasswordEntry> &passwords) const
{
    QFile file(storageFilePath);

    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        for (const PasswordEntry &entry : passwords) {
            out << entry.website << "," << entry.username << "," << entry.encryptedPassword << "\n";
        }
        file.close();
        return true;
    }

    return false;
}

QString PasswordManager::encryptPassword(const QString &password) const
{
    QByteArray hash = QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256);
    return QString(hash.toHex());
}

QString PasswordManager::decryptPassword(const QString &encryptedPassword) const
{
    return QString(); // Placeholder
}
