#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , networkManager(new QNetworkAccessManager(this))
    , currencyConverter(new CurrencyConverter(this))
    , weatherForecast(new WeatherForecast(this))
    , passwordManager(new PasswordManager(this))
    , noteTaking(new NoteTaking(this))
{
    ui->setupUi(this);
    initializeComponents();
    setupConnections();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initializeComponents() {
    QStringList currencies = {"USD", "EUR", "GBP", "JPY", "AUD", "CAD"};
    ui->fromCurrencyComboBox->addItems(currencies);
    ui->toCurrencyComboBox->addItems(currencies);

    ui->passwordTableWidget->setColumnCount(3);
    ui->passwordTableWidget->setHorizontalHeaderLabels({"Website", "Username", "Password"});

    ui->taskListWidget->setSortingEnabled(true);
}

void MainWindow::setupConnections() {
    connect(ui->convertButton, &QPushButton::clicked, this, &MainWindow::on_convertButton_clicked);
    connect(ui->getWeatherButton, &QPushButton::clicked, this, &MainWindow::on_getWeatherButton_clicked);
    connect(ui->removeTaskButton, &QPushButton::clicked, this, &MainWindow::on_removeTaskButton_clicked);
    connect(ui->addTaskButton, &QPushButton::clicked, this, &MainWindow::on_addTaskButton_clicked);
    connect(networkManager, &QNetworkAccessManager::finished, this, &MainWindow::onNetworkReply);
    connect(weatherForecast, &WeatherForecast::weatherDataReady, this, &MainWindow::onWeatherDataReady);
    connect(weatherForecast, &WeatherForecast::weatherDataFailed, this, &MainWindow::onWeatherDataFailed);
    connect(currencyConverter, &CurrencyConverter::conversionFailed, this, [](const QString &error) {
        QMessageBox::warning(nullptr, "Conversion Error", error);
    });
    connect(currencyConverter, &CurrencyConverter::conversionCompleted, this, [this](double result) {
        ui->resultLineEdit->setText(QString::number(result));
    });


}

void MainWindow::on_getWeatherButton_clicked() {
    QString cityName = ui->cityLineEdit->text();
    if (!cityName.isEmpty()) {
        weatherForecast->getWeather(cityName);
    }
}

void MainWindow::on_convertButton_clicked() {
    double amount = ui->amountLineEdit->text().toDouble();
    QString fromCurrency = ui->fromCurrencyComboBox->currentText();
    QString toCurrency = ui->toCurrencyComboBox->currentText();

    currencyConverter->convert(fromCurrency, toCurrency, amount);
}

void MainWindow::on_addPasswordButton_clicked() {
    QString website = ui->websiteLineEdit->text();
    QString username = ui->usernameLineEdit->text();
    QString password = ui->passwordLineEdit->text();

    if (!website.isEmpty() && !username.isEmpty() && !password.isEmpty()) {
        if (passwordManager->addPassword(website, username, password)) {
            QMessageBox::information(this, "Success", "Password added successfully!");
            ui->websiteLineEdit->clear();
            ui->usernameLineEdit->clear();
            ui->passwordLineEdit->clear();
            // Refresh password table
            ui->passwordTableWidget->setRowCount(0);
            for (const PasswordEntry &entry : passwordManager->viewPasswords()) {
                int row = ui->passwordTableWidget->rowCount();
                ui->passwordTableWidget->insertRow(row);
                ui->passwordTableWidget->setItem(row, 0, new QTableWidgetItem(entry.website));
                ui->passwordTableWidget->setItem(row, 1, new QTableWidgetItem(entry.username));
                ui->passwordTableWidget->setItem(row, 2, new QTableWidgetItem("********"));
            }
        } else {
            QMessageBox::warning(this, "Error", "Failed to add password.");
        }
    } else {
        QMessageBox::warning(this, "Input Error", "All fields must be filled out.");
    }
}

void MainWindow::on_removeTaskButton_clicked() {
    QListWidgetItem *item = ui->taskListWidget->currentItem();
    if (item) {
        delete item;
    }
}

void MainWindow::on_addTaskButton_clicked() {
    QString task = ui->taskLineEdit->text();
    if (!task.isEmpty()) {
        ui->taskListWidget->addItem(task);
        ui->taskLineEdit->clear();
    }
}

void MainWindow::onNetworkReply(QNetworkReply *reply) {
    QByteArray responseData = reply->readAll();
    QJsonDocument jsonDoc = QJsonDocument::fromJson(responseData);
    QJsonObject jsonObj = jsonDoc.object();

    if (reply->url().toString().contains("geocode")) {
        // Geocoding response
        if (jsonObj.contains("results")) {
            QJsonArray results = jsonObj["results"].toArray();
            if (!results.isEmpty()) {
                QJsonObject firstResult = results[0].toObject();
                QJsonObject geometry = firstResult["geometry"].toObject();
                QString lat = QString::number(geometry["lat"].toDouble());
                QString lon = QString::number(geometry["lng"].toDouble());
                weatherForecast->fetchWeatherData(lat, lon);
            }
        }
    } else if (reply->url().toString().contains("tomorrow")) {
    } else if (reply->url().toString().contains("exchangerate-api")) {
        // Currency exchange response
        QJsonObject rates = jsonObj["conversion_rates"].toObject();
        QMap<QString, double> newRates;
        newRates["EUR"] = rates["EUR"].toDouble();
        newRates["GBP"] = rates["GBP"].toDouble();
        newRates["JPY"] = rates["JPY"].toDouble();
        newRates["AUD"] = rates["AUD"].toDouble();
        newRates["CAD"] = rates["CAD"].toDouble();

        qDebug() << "Exchange rates updated.";
        currencyConverter->updateRates(newRates);
    } else {
        qDebug() << "Error:" << reply->errorString();
        ui->temperatureInfoLabel->setText("Failed to retrieve data.");
    }

    reply->deleteLater();
}

void MainWindow::onWeatherDataReady(const QString &temperature, const QString &windSpeed, const QString &humidity, const QString &weatherCode) {
    ui->temperatureInfoLabel->setText(temperature);
    ui->windInfoLabel_2->setText(windSpeed);
    ui->humidityInfoLabel_3->setText(humidity);

    QString iconPath;
    if (weatherCode == "1000" || weatherCode == "10001") {
        iconPath = "C:/Users/lucap/Documents/GitHub/QT4in1App/icons/sun.png";
    } else if (weatherCode == "1100" || weatherCode == "11001" || weatherCode == "1101" || weatherCode == "11011" || weatherCode == "1102" || weatherCode == "11021") { //partly cloudy
        iconPath = "C:/Users/lucap/Documents/GitHub/QT4in1App/icons/partly_cloudy.png";
    } else if (weatherCode == "1001") { //cloudy
        iconPath = "C:/Users/lucap/Documents/GitHub/QT4in1App/icons/cloudy.png";
    } else if (weatherCode == "4000" || weatherCode == "4200" || weatherCode == "4001" || weatherCode == "4201") { // rain
        iconPath = "C:/Users/lucap/Documents/GitHub/QT4in1App/icons/rain-cloud.png";
    } else if (weatherCode == "8000") { // storm
        iconPath = "C:/Users/lucap/Documents/GitHub/QT4in1App/icons/storm.png";
    } else if (weatherCode == "2100" || weatherCode == "2000") { // fog
        iconPath = "C:/Users/lucap/Documents/GitHub/QT4in1App/icons/fog.png";
    } else { // default
        iconPath = "C:/Users/lucap/Documents/GitHub/QT4in1App/icons/default.png";
    }

    qDebug() << "Icon path: " << iconPath;
    ui->iconInfoLabel_4->setScaledContents(true);

    QPixmap pixmap(iconPath);
    if (pixmap.isNull()) {
        qDebug() << "Failed to load the pixmap from" << iconPath;
    } else {
        ui->iconInfoLabel_4->setPixmap(pixmap);
    }
}



void MainWindow::onWeatherDataFailed(const QString &errorString) {
    ui->temperatureInfoLabel->setText("Error: " + errorString);
}

void MainWindow::on_removePasswordButton_clicked() {
    int currentRow = ui->passwordTableWidget->currentRow();
    if (currentRow >= 0) {
        QString website = ui->passwordTableWidget->item(currentRow, 0)->text();
        QString username = ui->passwordTableWidget->item(currentRow, 1)->text();

        if (passwordManager->deletePassword(website, username)) {
            QMessageBox::information(this, "Success", "Password removed successfully!");
            ui->passwordTableWidget->removeRow(currentRow);
        } else {
            QMessageBox::warning(this, "Error", "Failed to remove password.");
        }
    } else {
        QMessageBox::warning(this, "Error", "No password selected.");
    }
}
