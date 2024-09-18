#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QTableWidgetItem>
#include "currencyconverter.h"
#include "weatherforecast.h"
#include "passwordmanager.h"
#include "notetaking.h"

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
    void on_getWeatherButton_clicked();
    void on_convertButton_clicked();
    void on_addPasswordButton_clicked();
    void on_removeTaskButton_clicked();
    void on_addTaskButton_clicked();
    void onNetworkReply(QNetworkReply *reply);
    void onWeatherDataReady(const QString &temperature, const QString &windSpeed, const QString &humidity, const QString &description);
    void onWeatherDataFailed(const QString &errorString);
    void on_removePasswordButton_clicked();

private:
    Ui::MainWindow *ui;
    QNetworkAccessManager *networkManager;
    CurrencyConverter *currencyConverter;
    WeatherForecast *weatherForecast;
    PasswordManager *passwordManager;
    NoteTaking *noteTaking;

    void initializeComponents();
    void setupConnections();
    void fetchExchangeRates();
};

#endif // MAINWINDOW_H
