#include "weatherforecast.h"
#include <QNetworkRequest>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>

WeatherForecast::WeatherForecast(QObject *parent)
    : QObject(parent), networkManager(new QNetworkAccessManager(this))
{
    connect(networkManager, &QNetworkAccessManager::finished, this, [this](QNetworkReply *reply) {
        if (reply->url().toString().contains("geocode")) {
            handleCoordinateReply(reply);
        } else if (reply->url().toString().contains("timelines")) {
            handleWeatherReply(reply);
        }
    });
}

void WeatherForecast::getWeather(const QString &cityName)
{
    fetchCoordinates(cityName);
}

void WeatherForecast::fetchCoordinates(const QString &cityName)
{
    QString apiKey = "c33b902fbc25419a8273b30807166ceb"; // Geocoding API key
    QString apiUrl = QString("https://api.opencagedata.com/geocode/v1/json?q=%1&key=%2").arg(cityName, apiKey);

    QNetworkRequest request((QUrl(apiUrl)));
    networkManager->get(request); // Send the network request for coordinates
}

void WeatherForecast::fetchWeatherData(const QString &lat, const QString &lon)
{
    QString apiKey = "TfNxwJddFVX13NkBah8XINiwlL6XL0jO"; // Weather API key
    QString apiUrl = QString("https://api.tomorrow.io/v4/timelines?location=%1,%2&fields=temperature,humidity,windSpeed,weatherCode&units=metric&timesteps=current&apikey=%3")
                         .arg(lat, lon, apiKey);

    QNetworkRequest request((QUrl(apiUrl)));
    networkManager->get(request); // Send the network request for weather data
}

void WeatherForecast::handleCoordinateReply(QNetworkReply *reply)
{
    if (reply->error() != QNetworkReply::NoError) {
        emit weatherDataFailed(reply->errorString());
        reply->deleteLater();
        return;
    }

    QByteArray responseData = reply->readAll();
    QJsonDocument jsonDoc = QJsonDocument::fromJson(responseData);
    QJsonObject jsonObj = jsonDoc.object();

    if (jsonObj.contains("results")) {
        QJsonArray results = jsonObj["results"].toArray();
        if (!results.isEmpty()) {
            QJsonObject firstResult = results[0].toObject();
            QJsonObject geometry = firstResult["geometry"].toObject();
            double lat = geometry["lat"].toDouble();
            double lon = geometry["lng"].toDouble();

            fetchWeatherData(QString::number(lat), QString::number(lon));
        } else {
            emit weatherDataFailed("No results found for the city.");
        }
    } else {
        emit weatherDataFailed("Invalid response format from geocoding API.");
    }

    reply->deleteLater();
}

void WeatherForecast::handleWeatherReply(QNetworkReply *reply)
{
    if (reply->error() != QNetworkReply::NoError) {
        emit weatherDataFailed(reply->errorString());
        reply->deleteLater();
        return;
    }

    QByteArray responseData = reply->readAll();
    QJsonDocument jsonDoc = QJsonDocument::fromJson(responseData);
    QJsonObject jsonObj = jsonDoc.object();

    qDebug() << "API response:" << jsonDoc.toJson(QJsonDocument::Indented);

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
                double humidity = values["humidity"].toDouble();
                double windSpeed = values["windSpeed"].toDouble();
                int weatherCode = values["weatherCode"].toInt(); // Use int for weatherCode

                qDebug() << "Raw weatherCode description:" << weatherCode;

                QString iconPath;
                switch (weatherCode) {
                case 1000:
                case 10001:
                    iconPath = ":/icons/sun.png";
                    break;
                case 1100:
                case 11001:
                case 1101:
                case 11011:
                case 1102:
                case 11021:
                    iconPath = ":/icons/partly_cloudy.png";
                    break;
                case 1001:
                    iconPath = ":/icons/cloudy.png";
                    break;
                case 4000:
                case 4200:
                case 4001:
                case 4201:
                    iconPath = ":/icons/rain-cloud.png";
                    break;
                case 8000:
                    iconPath = ":/icons/storm.png";
                    break;
                case 2100:
                case 2000:
                    iconPath = ":/icons/fog.png";
                    break;
                default:
                    iconPath = ":/icons/default.png";
                    break;
                }

                qDebug() << "Icon path: " << iconPath;

                QString temperatureText = QString("Temperature: %1 °C").arg(temperature);
                QString humidityText = QString("Humidity: %1%").arg(humidity);
                QString windSpeedText = QString("Wind Speed: %1 m/s").arg(windSpeed);

                emit weatherDataReady(temperatureText, windSpeedText, humidityText, QString::number(weatherCode));
            } else {
                emit weatherDataFailed("No intervals in weather data.");
            }
        } else {
            emit weatherDataFailed("No timelines in weather data.");
        }
    } else {
        emit weatherDataFailed("Invalid response format from weather API.");
    }

    reply->deleteLater();
}



