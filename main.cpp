#include <QCoreApplication>
#include <QCommandLineParser>
#include <QDebug>
#include <QFileInfo>

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    app.setApplicationName("converter");
    app.setApplicationVersion("1.0");

    QCommandLineParser parser;
    parser.setApplicationDescription("CAD file converter");


    QCommandLineOption inputOption(QStringList() << "i" << "input", "Input file", "file");
    QCommandLineOption outputOption(QStringList() << "o" << "output", "Output file", "file");

    QCommandLineOption linearOption(QStringList() << "l" << "linear", "Linear precision", "value", "0.1");
    QCommandLineOption angularOption(QStringList() << "a" << "angular", "Angular precision", "value", "0.3");

    parser.addOption(inputOption);
    parser.addOption(outputOption);
    parser.addOption(linearOption);
    parser.addOption(angularOption);
    parser.addHelpOption();
    parser.addVersionOption();

    parser.process(app);

    // Проверка обязательных аргументов
    if (!parser.isSet(inputOption) || !parser.isSet(outputOption)) {
        qCritical() << "Error: Input and output files required";
        parser.showHelp(1);
    }

    QString inputFile = parser.value(inputOption);
    QString outputFile = parser.value(outputOption);
    double linearPrecision = parser.value(linearOption).toDouble();
    double angularPrecision = parser.value(angularOption).toDouble();

    // Проверка файлов
    if (!QFileInfo::exists(inputFile)) {
        qCritical() << "Error: Input file not found";
        return 1;
    }

    // Вывод параметров
    qInfo() << "Converting:" << inputFile << "->" << outputFile;
    qInfo() << "Linear precision:" << linearPrecision;
    qInfo() << "Angular precision:" << angularPrecision;

    // Здесь будет вызов конвертера
    // convert(inputFile, outputFile, linearPrecision, angularPrecision);

    qInfo() << "Conversion complete";
    return 0;
}
