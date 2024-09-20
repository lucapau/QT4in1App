/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QTabWidget *tabWidget;
    QWidget *currencyConverter;
    QPushButton *convertButton;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QLineEdit *amountLineEdit;
    QLineEdit *resultLineEdit;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *verticalLayout_2;
    QComboBox *fromCurrencyComboBox;
    QComboBox *toCurrencyComboBox;
    QWidget *toDoList;
    QListWidget *taskListWidget;
    QLineEdit *taskLineEdit;
    QPushButton *addTaskButton;
    QPushButton *removeTaskButton;
    QWidget *passwords;
    QLineEdit *usernameLineEdit;
    QLineEdit *passwordLineEdit;
    QLineEdit *websiteLineEdit;
    QPushButton *addPasswordButton;
    QPushButton *viewPasswordsButton;
    QPushButton *removePasswordButton;
    QTableWidget *passwordTableWidget;
    QWidget *weatherForecast;
    QLineEdit *cityLineEdit;
    QPushButton *getWeatherButton;
    QLabel *label;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QLabel *humidityInfoLabel_3;
    QLabel *windInfoLabel_2;
    QLabel *temperatureInfoLabel;
    QWidget *gridLayoutWidget_2;
    QGridLayout *gridLayout_3;
    QLabel *windInfoLabel_4;
    QLabel *humidityInfoLabel_5;
    QLabel *temperatureInfoLabel_3;
    QLabel *iconInfoLabel_4;
    QMenuBar *menubar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        MainWindow->setStyleSheet(QString::fromUtf8("QTabWidget {\n"
"    background-color: #f0f0f0; /* Light gray background color */\n"
"    border: 2px solid #a0a0a0; /* Darker gray border */\n"
"    border-radius: 10px; /* Rounded corners for the tab widget */\n"
"    padding: 10px; /* Padding around the tabs */\n"
"}\n"
"\n"
"QTabBar::tab {\n"
"    background-color: #d0d0d0; /* Lighter gray background for tabs */\n"
"    border: 1px solid #a0a0a0; /* Darker border for tabs */\n"
"    border-radius: 5px; /* Rounded corners for the tabs */\n"
"    padding: 10px; /* Padding inside each tab */\n"
"    margin: 2px; /* Space between tabs */\n"
"}\n"
"\n"
"QTabBar::tab:selected {\n"
"    background-color: #ffffff; /* White background for selected tab */\n"
"    color: #000000; /* Black text color for selected tab */\n"
"}\n"
"\n"
"QTabBar::tab:hover {\n"
"    background-color: #e0e0e0; /* Slightly darker gray on hover */\n"
"}\n"
"\n"
"QTabBar::tab:!selected {\n"
"    background-color: #c0c0c0; /* Gray background for unselected tabs */\n"
"    color: #606060; /* D"
                        "arker text color for unselected tabs */\n"
"}\n"
"\n"
"QTabWidget::pane {\n"
"    border-top: 2px solid #a0a0a0; /* Border between the tabs and content */\n"
"    background-color: #ffffff; /* Background color of the content area */\n"
"    border-radius: 10px; /* Rounded corners for the content area */\n"
"    padding: 10px; /* Padding inside the content area */\n"
"}\n"
"\n"
""));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName("tabWidget");
        tabWidget->setGeometry(QRect(0, 0, 801, 581));
        tabWidget->setStyleSheet(QString::fromUtf8("QTabWidget {\n"
"    background-color: #f0f0f0;\n"
"    border: 2px solid #a0a0a0;\n"
"    border-radius: 10px;\n"
"    padding: 10px;\n"
"}\n"
"\n"
"QTabBar::tab {\n"
"    background-color: #d0d0d0;\n"
"    border: 1px solid #a0a0a0;\n"
"    border-radius: 5px;\n"
"    padding: 10px;\n"
"    margin: 2px;\n"
"}\n"
"\n"
"QTabBar::tab:selected {\n"
"    background-color: #3498db;\n"
"    color: #ffffff;\n"
"}\n"
"\n"
"QTabBar::tab:hover {\n"
"    background-color: #e0e0e0;\n"
"}\n"
"\n"
"QTabBar::tab:!selected {\n"
"    background-color: #c0c0c0;\n"
"    color: #606060;\n"
"}\n"
"\n"
"QTabWidget::pane {\n"
"    border-top: 2px solid #a0a0a0;\n"
"    background-color: #3498db;\n"
"    border-radius: 10px;\n"
"    padding: 10px;\n"
"}\n"
""));
        currencyConverter = new QWidget();
        currencyConverter->setObjectName("currencyConverter");
        convertButton = new QPushButton(currencyConverter);
        convertButton->setObjectName("convertButton");
        convertButton->setGeometry(QRect(230, 360, 80, 24));
        convertButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #d0d0d0;\n"
"    color: white;\n"
"    border-radius: 5px;\n"
"    padding: 5px 10px;\n"
"    border: 1px solid #a0a0a0; \n"
"    font-size: 14px; \n"
"    font-weight: bold;/\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #b0b0b0\n"
"    border: 1px solid #8a8a8a; \n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #a0a0a0;  */\n"
"    border: 1px solid #707070; \n"
"}\n"
"\n"
"QPushButton:focus {\n"
"    outline: none; \n"
"    box-shadow: 0 0 5px #3498db;\n"
"}\n"
"\n"
"QPushButton:selected {\n"
"    background-color: rgb(170, 255, 255); \n"
"    color: black; /\n"
"}\n"
""));
        verticalLayoutWidget = new QWidget(currencyConverter);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(70, 110, 131, 221));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        amountLineEdit = new QLineEdit(verticalLayoutWidget);
        amountLineEdit->setObjectName("amountLineEdit");

        verticalLayout->addWidget(amountLineEdit);

        resultLineEdit = new QLineEdit(verticalLayoutWidget);
        resultLineEdit->setObjectName("resultLineEdit");

        verticalLayout->addWidget(resultLineEdit);

        verticalLayoutWidget_2 = new QWidget(currencyConverter);
        verticalLayoutWidget_2->setObjectName("verticalLayoutWidget_2");
        verticalLayoutWidget_2->setGeometry(QRect(220, 110, 131, 221));
        verticalLayout_2 = new QVBoxLayout(verticalLayoutWidget_2);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        fromCurrencyComboBox = new QComboBox(verticalLayoutWidget_2);
        fromCurrencyComboBox->setObjectName("fromCurrencyComboBox");

        verticalLayout_2->addWidget(fromCurrencyComboBox);

        toCurrencyComboBox = new QComboBox(verticalLayoutWidget_2);
        toCurrencyComboBox->setObjectName("toCurrencyComboBox");

        verticalLayout_2->addWidget(toCurrencyComboBox);

        tabWidget->addTab(currencyConverter, QString());
        toDoList = new QWidget();
        toDoList->setObjectName("toDoList");
        taskListWidget = new QListWidget(toDoList);
        taskListWidget->setObjectName("taskListWidget");
        taskListWidget->setGeometry(QRect(40, 80, 411, 381));
        taskLineEdit = new QLineEdit(toDoList);
        taskLineEdit->setObjectName("taskLineEdit");
        taskLineEdit->setGeometry(QRect(530, 220, 113, 24));
        addTaskButton = new QPushButton(toDoList);
        addTaskButton->setObjectName("addTaskButton");
        addTaskButton->setGeometry(QRect(500, 430, 80, 24));
        removeTaskButton = new QPushButton(toDoList);
        removeTaskButton->setObjectName("removeTaskButton");
        removeTaskButton->setGeometry(QRect(620, 430, 80, 24));
        tabWidget->addTab(toDoList, QString());
        passwords = new QWidget();
        passwords->setObjectName("passwords");
        usernameLineEdit = new QLineEdit(passwords);
        usernameLineEdit->setObjectName("usernameLineEdit");
        usernameLineEdit->setGeometry(QRect(280, 180, 113, 24));
        passwordLineEdit = new QLineEdit(passwords);
        passwordLineEdit->setObjectName("passwordLineEdit");
        passwordLineEdit->setGeometry(QRect(280, 240, 113, 24));
        websiteLineEdit = new QLineEdit(passwords);
        websiteLineEdit->setObjectName("websiteLineEdit");
        websiteLineEdit->setGeometry(QRect(280, 130, 113, 24));
        addPasswordButton = new QPushButton(passwords);
        addPasswordButton->setObjectName("addPasswordButton");
        addPasswordButton->setGeometry(QRect(410, 300, 91, 24));
        viewPasswordsButton = new QPushButton(passwords);
        viewPasswordsButton->setObjectName("viewPasswordsButton");
        viewPasswordsButton->setGeometry(QRect(300, 300, 101, 24));
        removePasswordButton = new QPushButton(passwords);
        removePasswordButton->setObjectName("removePasswordButton");
        removePasswordButton->setGeometry(QRect(189, 300, 101, 24));
        passwordTableWidget = new QTableWidget(passwords);
        passwordTableWidget->setObjectName("passwordTableWidget");
        passwordTableWidget->setGeometry(QRect(470, 90, 256, 192));
        tabWidget->addTab(passwords, QString());
        weatherForecast = new QWidget();
        weatherForecast->setObjectName("weatherForecast");
        cityLineEdit = new QLineEdit(weatherForecast);
        cityLineEdit->setObjectName("cityLineEdit");
        cityLineEdit->setGeometry(QRect(240, 20, 251, 24));
        getWeatherButton = new QPushButton(weatherForecast);
        getWeatherButton->setObjectName("getWeatherButton");
        getWeatherButton->setGeometry(QRect(560, 20, 80, 24));
        label = new QLabel(weatherForecast);
        label->setObjectName("label");
        label->setGeometry(QRect(140, 20, 101, 16));
        gridLayoutWidget = new QWidget(weatherForecast);
        gridLayoutWidget->setObjectName("gridLayoutWidget");
        gridLayoutWidget->setGeometry(QRect(340, 100, 251, 191));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(0, 0, 0, 0);
        humidityInfoLabel_3 = new QLabel(gridLayoutWidget);
        humidityInfoLabel_3->setObjectName("humidityInfoLabel_3");

        gridLayout->addWidget(humidityInfoLabel_3, 1, 0, 1, 1);

        windInfoLabel_2 = new QLabel(gridLayoutWidget);
        windInfoLabel_2->setObjectName("windInfoLabel_2");

        gridLayout->addWidget(windInfoLabel_2, 2, 0, 1, 1);

        temperatureInfoLabel = new QLabel(gridLayoutWidget);
        temperatureInfoLabel->setObjectName("temperatureInfoLabel");

        gridLayout->addWidget(temperatureInfoLabel, 0, 0, 1, 1);

        gridLayoutWidget_2 = new QWidget(weatherForecast);
        gridLayoutWidget_2->setObjectName("gridLayoutWidget_2");
        gridLayoutWidget_2->setGeometry(QRect(200, 100, 91, 191));
        gridLayout_3 = new QGridLayout(gridLayoutWidget_2);
        gridLayout_3->setObjectName("gridLayout_3");
        gridLayout_3->setContentsMargins(0, 0, 0, 0);
        windInfoLabel_4 = new QLabel(gridLayoutWidget_2);
        windInfoLabel_4->setObjectName("windInfoLabel_4");

        gridLayout_3->addWidget(windInfoLabel_4, 2, 0, 1, 1);

        humidityInfoLabel_5 = new QLabel(gridLayoutWidget_2);
        humidityInfoLabel_5->setObjectName("humidityInfoLabel_5");

        gridLayout_3->addWidget(humidityInfoLabel_5, 1, 0, 1, 1);

        temperatureInfoLabel_3 = new QLabel(gridLayoutWidget_2);
        temperatureInfoLabel_3->setObjectName("temperatureInfoLabel_3");

        gridLayout_3->addWidget(temperatureInfoLabel_3, 0, 0, 1, 1);

        iconInfoLabel_4 = new QLabel(weatherForecast);
        iconInfoLabel_4->setObjectName("iconInfoLabel_4");
        iconInfoLabel_4->setGeometry(QRect(320, 320, 111, 81));
        tabWidget->addTab(weatherForecast, QString());
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 21));
        MainWindow->setMenuBar(menubar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(3);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        convertButton->setText(QCoreApplication::translate("MainWindow", "Convert", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(currencyConverter), QCoreApplication::translate("MainWindow", "Currency Converter", nullptr));
        addTaskButton->setText(QCoreApplication::translate("MainWindow", "Add", nullptr));
        removeTaskButton->setText(QCoreApplication::translate("MainWindow", "Remove", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(toDoList), QCoreApplication::translate("MainWindow", "To-Do-List", nullptr));
        usernameLineEdit->setText(QCoreApplication::translate("MainWindow", "Username", nullptr));
        passwordLineEdit->setText(QCoreApplication::translate("MainWindow", "Password", nullptr));
        websiteLineEdit->setText(QCoreApplication::translate("MainWindow", "Website", nullptr));
        addPasswordButton->setText(QCoreApplication::translate("MainWindow", "Add Password", nullptr));
        viewPasswordsButton->setText(QCoreApplication::translate("MainWindow", "View Passwords", nullptr));
        removePasswordButton->setText(QCoreApplication::translate("MainWindow", "Delete Passwords", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(passwords), QCoreApplication::translate("MainWindow", "Passwords", nullptr));
        getWeatherButton->setText(QCoreApplication::translate("MainWindow", "Get Weather", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Enter City Name: ", nullptr));
        humidityInfoLabel_3->setText(QString());
        windInfoLabel_2->setText(QString());
        temperatureInfoLabel->setText(QString());
        windInfoLabel_4->setText(QCoreApplication::translate("MainWindow", "Wind:", nullptr));
        humidityInfoLabel_5->setText(QCoreApplication::translate("MainWindow", "Humidity:", nullptr));
        temperatureInfoLabel_3->setText(QCoreApplication::translate("MainWindow", "Temperature: ", nullptr));
        iconInfoLabel_4->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(weatherForecast), QCoreApplication::translate("MainWindow", "WeatherForecast", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
