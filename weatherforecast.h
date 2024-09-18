#ifndef WEATHERFORECAST_H
#define WEATHERFORECAST_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>

class WeatherForecast : public QObject
{
    Q_OBJECT

public:
    WeatherForecast(QObject *parent = nullptr);
    void getWeather(const QString &city);
    void fetchWeatherData(const QString &lat, const QString &lon);

signals:
    void weatherDataReady(const QString &temperature, const QString &windSpeed, const QString &humidity, const QString &description);
    void weatherDataFailed(const QString &errorString);

private slots:
    void handleWeatherReply(QNetworkReply *reply);
    void handleCoordinateReply(QNetworkReply *reply);

private:
    QNetworkAccessManager *networkManager;

    void fetchCoordinates(const QString &cityName);
};

#endif // WEATHERFORECAST_H
