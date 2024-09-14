#include "currencyconverter.h"
#include <QNetworkRequest>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>

CurrencyConverter::CurrencyConverter(QObject *parent)
    : QObject(parent), networkManager(new QNetworkAccessManager(this))
{
    fetchExchangeRates();
}

void CurrencyConverter::fetchExchangeRates()
{
    QString apiUrl = "https://v6.exchangerate-api.com/v6/f6b5ed25f71c239c219e3bde/latest/USD";
    QNetworkRequest request((QUrl(apiUrl)));
    connect(networkManager, &QNetworkAccessManager::finished, this, &CurrencyConverter::handleNetworkReply);
    networkManager->get(request);
}

void CurrencyConverter::handleNetworkReply(QNetworkReply *reply)
{
    if (reply->error() != QNetworkReply::NoError) {
        emit conversionFailed(reply->errorString());
        reply->deleteLater();
        return;
    }

    QByteArray responseData = reply->readAll();
    QJsonDocument jsonDoc = QJsonDocument::fromJson(responseData);
    QJsonObject jsonObj = jsonDoc.object();

    // Parse exchange rates
    QJsonObject rates = jsonObj["conversion_rates"].toObject();
    exchangeRates["EUR"] = rates["EUR"].toDouble();
    exchangeRates["GBP"] = rates["GBP"].toDouble();
    exchangeRates["JPY"] = rates["JPY"].toDouble();
    exchangeRates["AUD"] = rates["AUD"].toDouble();
    exchangeRates["CAD"] = rates["CAD"].toDouble();

    qDebug() << "Exchange rates updated.";
    reply->deleteLater();
}

void CurrencyConverter::updateRates(const QMap<QString, double> &newRates)
{
    exchangeRates = newRates;
}

void CurrencyConverter::convert(const QString &fromCurrency, const QString &toCurrency, double amount)
{
    if (fromCurrency == "USD") {
        // Converting from USD to another currency
        double conversionRate = exchangeRates.value(toCurrency, 1.0);
        double convertedAmount = amount * conversionRate;
        emit conversionCompleted(convertedAmount);
    } else if (toCurrency == "USD") {
        // Converting from another currency to USD
        double conversionRate = exchangeRates.value(fromCurrency, 1.0);
        double convertedAmount = amount / conversionRate;
        emit conversionCompleted(convertedAmount);
    } else {
        // Converting between two non-USD currencies (via USD)
        double fromRate = exchangeRates.value(fromCurrency, 1.0);
        double toRate = exchangeRates.value(toCurrency, 1.0);
        double convertedAmount = (amount / fromRate) * toRate;
        emit conversionCompleted(convertedAmount);
    }
}

