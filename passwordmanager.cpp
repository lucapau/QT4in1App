#include "passwordmanager.h"
#include "qdatetime.h"
#include <QFile>
#include <QTextStream>
#include <QCryptographicHash>
#include <QDebug>
#include <QSettings>

PasswordManager::PasswordManager(QObject *parent)
    : QObject(parent)
{
    loadEncryptionKey();
}

bool PasswordManager::addPassword(const QString &website, const QString &username, const QString &password)
{
    QList<PasswordEntry> passwords = loadPasswords();
    QString encryptedPassword = encryptPassword(password);
    PasswordEntry newEntry{website, username, encryptedPassword};
    passwords.append(newEntry);
    return savePasswords(passwords);
}

bool PasswordManager::deletePassword(const QString &website, const QString &username)
{
    QList<PasswordEntry> passwords = loadPasswords();
    auto it = std::remove_if(passwords.begin(), passwords.end(),
                             [&](const PasswordEntry &entry) {
                                 return entry.website == website && entry.username == username;
                             });
    if (it != passwords.end()) {
        passwords.erase(it, passwords.end());
        return savePasswords(passwords);
    }
    return false;
}

QList<PasswordEntry> PasswordManager::viewPasswords() const
{
    QList<PasswordEntry> passwords = loadPasswords();
    for (PasswordEntry &entry : passwords) {
        entry.password = decryptPassword(entry.encryptedPassword);
    }
    return passwords;
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
    QByteArray data = password.toUtf8();
    QByteArray encrypted;
    for (int i = 0; i < data.size(); ++i) {
        encrypted.append(data[i] ^ m_encryptionKey[i % m_encryptionKey.size()]);
    }
    return QString(encrypted.toBase64());
}

QString PasswordManager::decryptPassword(const QString &encryptedPassword) const
{
    QByteArray data = QByteArray::fromBase64(encryptedPassword.toUtf8());
    QByteArray decrypted;
    for (int i = 0; i < data.size(); ++i) {
        decrypted.append(data[i] ^ m_encryptionKey[i % m_encryptionKey.size()]);
    }
    return QString::fromUtf8(decrypted);
}

void PasswordManager::loadEncryptionKey()
{
    QSettings settings("YourCompany", "YourApp");
    m_encryptionKey = settings.value("encryptionKey").toByteArray();
    if (m_encryptionKey.isEmpty()) {
        m_encryptionKey = QCryptographicHash::hash(QDateTime::currentDateTime().toString().toUtf8(), QCryptographicHash::Sha256);
        settings.setValue("encryptionKey", m_encryptionKey);
    }
}
