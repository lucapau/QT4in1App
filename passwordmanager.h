#ifndef PASSWORDMANAGER_H
#define PASSWORDMANAGER_H

#include <QObject>
#include <QString>
#include <QList>
#include <QFile>
#include <QCryptographicHash>
#include <QByteArray>

struct PasswordEntry {
    QString website;
    QString username;
    QString encryptedPassword;
    QString password; // Added for decrypted password
};

class PasswordManager : public QObject
{
    Q_OBJECT

public:
    explicit PasswordManager(QObject *parent = nullptr);
    bool addPassword(const QString &website, const QString &username, const QString &password);
    bool deletePassword(const QString &website, const QString &username);
    QList<PasswordEntry> viewPasswords() const;

private:
    QString storageFilePath = "passwords.dat";
    QByteArray m_encryptionKey;

    QList<PasswordEntry> loadPasswords() const;
    bool savePasswords(const QList<PasswordEntry> &passwords) const;
    QString encryptPassword(const QString &password) const;
    QString decryptPassword(const QString &encryptedPassword) const;
    void loadEncryptionKey();
};

#endif // PASSWORDMANAGER_H
