#ifndef CURRENCYCONVERTER_H
#define CURRENCYCONVERTER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QString>
#include <QMap>

class CurrencyConverter : public QObject
{
    Q_OBJECT

public:
    CurrencyConverter(QObject *parent = nullptr);
    void convert(const QString &fromCurrency, const QString &toCurrency, double amount);
    void updateRates(const QMap<QString, double> &newRates);
    QMap<QString, double> exchangeRates;


signals:
    void conversionCompleted(double convertedAmount);
    void conversionFailed(const QString &errorString);

private slots:
    void handleNetworkReply(QNetworkReply *reply);

private:
    QNetworkAccessManager *networkManager;

    void fetchExchangeRates();
};

#endif // CURRENCYCONVERTER_H
