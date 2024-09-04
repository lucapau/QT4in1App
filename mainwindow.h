#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QCryptographicHash>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QTableWidgetItem>
#include <openssl/aes.h> // Ensure you have OpenSSL headers if used

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_convertButton_clicked();
    void on_addTaskButton_clicked();
    void on_removeTaskButton_clicked();
    void on_getWeatherButton_clicked();
    void on_addPasswordButton_clicked();
    void on_deletePasswordButton_clicked();
    void onNetworkReply(QNetworkReply *reply);
    void on_viewPasswordsButton_clicked();

private:
    void fetchExchangeRates();
    void fetchWeatherData(const QString &lat, const QString &lon);
    void fetchCoordinates(const QString &cityName);
    void loadPasswords();
    void savePasswords();
    void addPassword(const QString &website, const QString &username, const QString &password);
    bool appendToStorageFile(const QString &website, const QString &username, const QString &encryptedPassword);
    bool deletePassword(const QString &website, const QString &username);
    QString encryptPassword(const QString &password);
    QString decryptPassword(const QString &encryptedPassword);
    QString applyPadding(const QString &plaintext);
    QString removePadding(const QString &decryptedText);

    QByteArray aesEncrypt(const QString &plaintext, const QByteArray &key);
    QString aesDecrypt(const QByteArray &encrypted, const QByteArray &key);

    Ui::MainWindow *ui;
    QNetworkAccessManager *networkManager;

    double eurRate;
    double gbpRate;
    double jpyRate;
    double audRate;
    double cadRate;


    QString storageFile;
};
#endif // MAINWINDOW_H
