#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>
#include <QJsonArray>
#include <QNetworkRequest>
#include <QUrl>
#include <openssl/rand.h>
#include <openssl/aes.h>




MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , networkManager(new QNetworkAccessManager(this))
{
    ui->setupUi(this);

    // UI components
    QStringList currencies = {"USD", "EUR", "GBP", "JPY", "AUD", "CAD"};
    for (const QString &currency : currencies){
        ui->fromCurrencyComboBox->addItem(currency);
        ui->toCurrencyComboBox->addItem(currency);
    }
    storageFile = "passwords.dat";

    ui->passwordTableWidget->setColumnCount(3);
    ui->passwordTableWidget->setHorizontalHeaderLabels(QStringList() << "Website" << "Username" << "Password");



    connect(ui->convertButton, &QPushButton::clicked, this, &MainWindow::on_convertButton_clicked);
    connect(networkManager, &QNetworkAccessManager::finished, this, &MainWindow::onNetworkReply);
    connect(ui->addTaskButton, &QPushButton::clicked, this, &MainWindow::on_addTaskButton_clicked);
    connect(ui->removeTaskButton, &QPushButton::clicked, this, &MainWindow::on_removeTaskButton_clicked);
    connect(ui->getWeatherButton, &QPushButton::clicked, this, &MainWindow::on_getWeatherButton_clicked);

    connect(ui->viewPasswordsButton, &QPushButton::clicked, this, &MainWindow::on_viewPasswordsButton_clicked);




    fetchExchangeRates();
    loadPasswords();
    qDebug() << "MainWindow constructor called.";

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::fetchExchangeRates()
{
    QString apiUrl = "https://v6.exchangerate-api.com/v6/f6b5ed25f71c239c219e3bde/latest/USD";
    QNetworkRequest request((QUrl(apiUrl)));
    networkManager->get(request);
}

void MainWindow::onNetworkReply(QNetworkReply *reply)
{
    QByteArray responseData = reply->readAll();
    QJsonDocument jsonDoc = QJsonDocument::fromJson(responseData);
    QJsonObject jsonObj = jsonDoc.object();

    if (reply->url().toString().contains("geocode")) {
        // Geocoding API response
        if (jsonObj.contains("results")) {
            QJsonArray results = jsonObj["results"].toArray();
            if (!results.isEmpty()) {
                QJsonObject firstResult = results[0].toObject();
                QJsonObject geometry = firstResult["geometry"].toObject();
                double lat = geometry["lat"].toDouble();
                double lon = geometry["lng"].toDouble();

                fetchWeatherData(QString::number(lat), QString::number(lon));
            }
        }
    } else if (reply->url().toString().contains("tomorrow")) {
        // Weather API response
        if (jsonObj.contains("data")) {
            QJsonObject data = jsonObj["data"].toObject();
            QJsonArray timelines = data["timelines"].toArray();
            if (!timelines.isEmpty()) {
                QJsonObject timeline = timelines[0].toObject();
                QJsonArray intervals = timeline["intervals"].toArray();
                if (!intervals.isEmpty()) {
                    QJsonObject interval = intervals[0].toObject();
                    QJsonObject values = interval["values"].toObject();
                    double temperature = values["temperature"].toDouble();

                    QString weatherText = QString("Temperature: %1 °C").arg(temperature);
                    ui->weatherInfoLabel->setText(weatherText);
                }
            }
        }
    } else if (reply->url().toString().contains("exchangerate-api")) {
        // Currency Exchange API response
        QJsonObject rates = jsonObj["conversion_rates"].toObject();

        // Store the exchange rates for various currencies
        eurRate = rates["EUR"].toDouble();
        gbpRate = rates["GBP"].toDouble();
        jpyRate = rates["JPY"].toDouble();
        audRate = rates["AUD"].toDouble();
        cadRate = rates["CAD"].toDouble();

        // Update the UI with the available rates (optional)
        qDebug() << "EUR Rate:" << eurRate;
        qDebug() << "GBP Rate:" << gbpRate;
        qDebug() << "JPY Rate:" << jpyRate;
        qDebug() << "AUD Rate:" << audRate;
        qDebug() << "CAD Rate:" << cadRate;

    } else {
        qDebug() << "Error:" << reply->errorString();
        ui->weatherInfoLabel->setText("Failed to retrieve data.");
    }

    reply->deleteLater();
}

void MainWindow::on_convertButton_clicked()
{
    double amount = ui->amountLineEdit->text().toDouble();
    QString fromCurrency = ui->fromCurrencyComboBox->currentText();
    QString toCurrency = ui->toCurrencyComboBox->currentText();

    // Mapping of currency pairs to conversion rates
    QMap<QString, double> rateMap {
        {"USD->EUR", eurRate},
        {"USD->GBP", gbpRate},
        {"USD->JPY", jpyRate},
        {"USD->AUD", audRate},
        {"USD->CAD", cadRate},
        {"EUR->USD", 1.0 / eurRate},
        {"GBP->USD", 1.0 / gbpRate},
        {"JPY->USD", 1.0 / jpyRate},
        {"AUD->USD", 1.0 / audRate},
        {"CAD->USD", 1.0 / cadRate},
        {"EUR->GBP", gbpRate / eurRate},
        {"GBP->EUR", eurRate / gbpRate},
        {"EUR->JPY", jpyRate / eurRate},
        {"AUD->EUR", 1.0 / audRate * eurRate},
        {"EUR->AUD", 1.0 / eurRate * audRate},
        {"AUD->GBP", 1.0 / audRate * gbpRate},
        {"GBP->AUD", 1.0 / gbpRate * audRate},
        {"AUD->JPY", 1.0 / audRate * jpyRate},
        {"JPY->AUD", 1.0 / jpyRate * audRate},
        {"AUD->CAD", 1.0 / audRate * cadRate},
        {"CAD->AUD", 1.0 / cadRate * audRate},
    };

    QString pairKey = fromCurrency + "->" + toCurrency;
    double conversionRate = rateMap.value(pairKey, 1.0);//defaults to 1 if a pair isnt found

    double convertedAmount = amount * conversionRate;
    ui->resultLineEdit->setText(QString::number(convertedAmount));
}


void MainWindow::on_addTaskButton_clicked()
{
    QString task = ui->taskLineEdit->text();
    if (!task.isEmpty()) {
        ui->taskListWidget->addItem(task);
        ui->taskLineEdit->clear();
    }
}

void MainWindow::on_removeTaskButton_clicked()
{
    QListWidgetItem *item = ui->taskListWidget->currentItem();
    if (item) {
        delete item;
    }
}

void MainWindow::on_getWeatherButton_clicked()
{
    QString cityName = ui->cityLineEdit->text();
    if (!cityName.isEmpty()) {
        fetchCoordinates(cityName);
    }
}

void MainWindow::fetchCoordinates(const QString &cityName)
{
    QString apiKey = "c33b902fbc25419a8273b30807166ceb";
    QString apiUrl = QString("https://api.opencagedata.com/geocode/v1/json?q=%1&key=%2").arg(cityName, apiKey);

    QNetworkRequest request((QUrl(apiUrl)));
    networkManager->get(request);
}

void MainWindow::fetchWeatherData(const QString &lat, const QString &lon)
{
    QString apiKey = "hyN6NgYkuuUPuD03Nm2gxFRIokmHj0Ut";
    QString apiUrl = QString("https://api.tomorrow.io/v4/timelines?location=%1,%2&fields=temperature&units=metric&timesteps=current&apikey=%3").arg(lat, lon, apiKey);

    QNetworkRequest request((QUrl(apiUrl)));
    networkManager->get(request);
}

void MainWindow::on_addPasswordButton_clicked()
{
    QString website = ui->websiteLineEdit->text();
    QString username = ui->usernameLineEdit->text();
    QString password = ui->passwordLineEdit->text();

    if (!website.isEmpty() && !username.isEmpty() && !password.isEmpty()) {
        addPassword(website, username, password);
        QMessageBox::information(this, "Success", "Password added successfully!");
    } else {
        QMessageBox::warning(this, "Input Error", "All fields must be filled out.");
    }
}

// Add Password Function (Handles encryption and updating UI and file)
void MainWindow::addPassword(const QString &website, const QString &username, const QString &password)
{
    QString encryptedPassword = encryptPassword(password);

    if (appendToStorageFile(website, username, encryptedPassword)) {
        // Update the table with the new password
        int row = ui->passwordTableWidget->rowCount();
        ui->passwordTableWidget->insertRow(row);
        ui->passwordTableWidget->setItem(row, 0, new QTableWidgetItem(website));
        ui->passwordTableWidget->setItem(row, 1, new QTableWidgetItem(username));
        ui->passwordTableWidget->setItem(row, 2, new QTableWidgetItem("********")); // Hide actual password
    }
}

// View Passwords Button Clicked
void MainWindow::on_viewPasswordsButton_clicked()
{
    // Load and display passwords (encrypted passwords not shown directly for security reasons)
    loadPasswords();
}

// Delete Password Button Clicked
void MainWindow::on_deletePasswordButton_clicked()
{
    QString website = ui->websiteLineEdit->text();
    QString username = ui->usernameLineEdit->text();

    if (!website.isEmpty() && !username.isEmpty()) {
        if (deletePassword(website, username)) {
            QMessageBox::information(this, "Success", "Password deleted successfully!");
        } else {
            QMessageBox::warning(this, "Delete Error", "No matching entry found.");
        }
    } else {
        QMessageBox::warning(this, "Input Error", "Please specify the website and username.");
    }
}

// Encryption Function
QString MainWindow::encryptPassword(const QString &password)
{
    QByteArray key = QByteArray::fromHex("00112233445566778899aabbccddeeff");
    QString paddedPassword = applyPadding(password);

    return aesEncrypt(paddedPassword, key).toHex();
}

// Decryption Function
QString MainWindow::decryptPassword(const QString &encryptedPassword)
{
    QByteArray key = QByteArray::fromHex("00112233445566778899aabbccddeeff");
    QByteArray encryptedData = QByteArray::fromHex(encryptedPassword.toUtf8());

    QString decryptedData = aesDecrypt(encryptedData, key);

    return removePadding(decryptedData);
}

// AES Encryption Helper Function
QByteArray MainWindow::aesEncrypt(const QString &plaintext, const QByteArray &key)
{
    AES_KEY aesKey;
    AES_set_encrypt_key(reinterpret_cast<const unsigned char*>(key.data()), key.size() * 8, &aesKey);

    QByteArray encrypted;
    QByteArray plaintextBytes = plaintext.toUtf8();

    int length = plaintextBytes.size();
    for (int i = 0; i < length; i += 16) {
        unsigned char encryptedBlock[16];
        AES_encrypt(reinterpret_cast<const unsigned char*>(plaintextBytes.constData() + i), encryptedBlock, &aesKey);
        encrypted.append(reinterpret_cast<char*>(encryptedBlock), 16);
    }

    return encrypted;
}

// AES Decryption Helper Function
QString MainWindow::aesDecrypt(const QByteArray &encrypted, const QByteArray &key)
{
    AES_KEY aesKey;
    AES_set_decrypt_key(reinterpret_cast<const unsigned char*>(key.data()), key.size() * 8, &aesKey);

    QByteArray decrypted;
    int length = encrypted.size();
    for (int i = 0; i < length; i += 16) {
        unsigned char decryptedBlock[16];
        AES_decrypt(reinterpret_cast<const unsigned char*>(encrypted.constData() + i), decryptedBlock, &aesKey);
        decrypted.append(reinterpret_cast<char*>(decryptedBlock), 16);
    }

    return QString::fromUtf8(decrypted);
}

// Add Padding to Plaintext
QString MainWindow::applyPadding(const QString &plaintext)
{
    int paddingLength = 16 - (plaintext.size() % 16);
    QString paddedText = plaintext;
    paddedText.append(QString(paddingLength, QChar(paddingLength)));
    return paddedText;
}

// Remove Padding from Decrypted Text
QString MainWindow::removePadding(const QString &decryptedText)
{
    int paddingLength = decryptedText.right(1).toInt();
    return decryptedText.left(decryptedText.size() - paddingLength);
}

// Load Passwords from Storage File
void MainWindow::loadPasswords()
{
    ui->passwordTableWidget->setRowCount(0); // Clear the table before loading
    QFile file(storageFile);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        while (!in.atEnd()) {
            QStringList line = in.readLine().split(",");
            if (line.size() == 3) {
                QString website = line[0];
                QString username = line[1];
                QString encryptedPassword = line[2];

                int row = ui->passwordTableWidget->rowCount();
                ui->passwordTableWidget->insertRow(row);
                ui->passwordTableWidget->setItem(row, 0, new QTableWidgetItem(website));
                ui->passwordTableWidget->setItem(row, 1, new QTableWidgetItem(username));
                ui->passwordTableWidget->setItem(row, 2, new QTableWidgetItem("********")); // Hide actual password
            }
        }
        file.close();
    }
}

// Save Passwords to Storage File
void MainWindow::savePasswords()
{
    QFile file(storageFile);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        for (int row = 0; row < ui->passwordTableWidget->rowCount(); ++row) {
            QString website = ui->passwordTableWidget->item(row, 0)->text();
            QString username = ui->passwordTableWidget->item(row, 1)->text();
            QString password = ui->passwordTableWidget->item(row, 2)->text();  // Encrypted passwords should be saved

            QString encryptedPassword = encryptPassword(password);
            out << website << "," << username << "," << encryptedPassword << "\n";
        }
        file.close();
        QMessageBox::information(this, "Success", "Passwords saved successfully!");
    }
}

// Append a password entry to the storage file
bool MainWindow::appendToStorageFile(const QString &website, const QString &username, const QString &encryptedPassword)
{
    QFile file(storageFile);
    if (file.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&file);
        out << website << "," << username << "," << encryptedPassword << "\n";
        file.close();
        return true;
    }
    return false;
}

// Delete a password from the storage file
bool MainWindow::deletePassword(const QString &website, const QString &username)
{
    QFile file(storageFile);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QStringList lines;
        QTextStream in(&file);

        while (!in.atEnd()) {
            QString line = in.readLine();
            if (!line.startsWith(website + "," + username + ",")) {
                lines.append(line);
            }
        }
        file.close();

        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&file);
            for (const QString &line : lines) {
                out << line << "\n";
            }
            file.close();
            return true;
        }
    }
    return false;
}
