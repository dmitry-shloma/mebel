#include "mainwindow.h"

#include <QApplication>
#include <QTextCodec>
#include <QMessageBox>

#include "settings.h"
#include "sqldatabasehelper.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
#ifdef Q_OS_WIN
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("IBM-866"));
#elif defined(Q_OS_LINUX)
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
#endif
    if (argc != 5) {
        QMessageBox::critical(
                    0,
                    "ВегаМебель",
                    "Ошибка. Укажите параметры командной строки");
        return EXIT_FAILURE;
    }

    const QString projectName = "Мебельщик";
    QString hostName = argv[1];
    QString databaseName = argv[2];
    QString userName = argv[3];
    QString password = argv[4];
    Settings::getInstance(
                projectName, hostName, databaseName, userName, password);

    SqlDatabaseHelper::getInstance(
                "QMYSQL",
                Settings::getInstance().getHostName(),
                Settings::getInstance().getDatabaseName(),
                Settings::getInstance().getUserName(),
                Settings::getInstance().getPassword());

    MainWindow w;
    w.show();

    return a.exec();
}
