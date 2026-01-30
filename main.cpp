#include <QCoreApplication>
#include <QCommandLineParser>
#include <QDebug>
#include <QFileInfo>


int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    app.setApplicationName("converter");
    app.setApplicationVersion("1.1");

    QCommandLineParser parser;
    parser.setApplicationDescription("CAD file converter. Supports both flags and positional arguments.");
    parser.addHelpOption();
    parser.addVersionOption();

    // 1. Описываем именованные ключи (Опции)
    QCommandLineOption inputOption({"i", "input"}, "Input STEP file", "file");
    QCommandLineOption outputOption({"o", "output"}, "Output OBJ file", "file");
    QCommandLineOption linearOption({"l", "linear"}, "Linear precision", "value", "0.1");
    QCommandLineOption angularOption({"a", "angular"}, "Angular precision", "value", "0.3");

    parser.addOption(inputOption);
    parser.addOption(outputOption);
    parser.addOption(linearOption);
    parser.addOption(angularOption);

    // 2. Описываем позиционные аргументы (для справки)
    parser.addPositionalArgument("input", "Input STEP file");
    parser.addPositionalArgument("output", "Output OBJ file");
    parser.addPositionalArgument("linear", "Linear precision [default: 0.1]");
    parser.addPositionalArgument("angular", "Angular precision [default: 0.3]");

    parser.process(app);

    const QStringList posArgs = parser.positionalArguments();

    // Входной файл
    QString inputFile = parser.value(inputOption);
    if (inputFile.isEmpty() && posArgs.size() > 0) {
        inputFile = posArgs.at(0);
    }

    // Выходной файл
    QString outputFile = parser.value(outputOption);
    if (outputFile.isEmpty() && posArgs.size() > 1) {
        outputFile = posArgs.at(1);
    }

    // Линейная точность
    double linearPrecision;
    if (parser.isSet(linearOption)) {
        linearPrecision = parser.value(linearOption).toDouble();
    } else if (posArgs.size() > 2) {
        linearPrecision = posArgs.at(2).toDouble();
    } else {
        linearPrecision = 0.1;
    }

    // Угловая точность
    double angularPrecision;
    if (parser.isSet(angularOption)) {
        angularPrecision = parser.value(angularOption).toDouble();
    } else if (posArgs.size() > 3) {
        angularPrecision = posArgs.at(3).toDouble();
    } else {
        angularPrecision = 0.3;
    }


    if (inputFile.isEmpty() || outputFile.isEmpty()) {
        qCritical() << "Error: Input and output files are required!";
        parser.showHelp(1);
    }

    if (!QFileInfo::exists(inputFile)) {
        qCritical() << "Error: File" << inputFile << "not found.";
        return 1;
    }

    // Вывод итоговых параметров для контроля
    qInfo().noquote() << "Status: Starting conversion...";
    qInfo().noquote() << "Input:  " << inputFile;
    qInfo().noquote() << "Output: " << outputFile;
    qInfo().noquote() << "Linear: " << linearPrecision;
    qInfo().noquote() << "Angular:" << angularPrecision;

    // TODO: Вызов вашего конвертера
    // convert(inputFile, outputFile, linearPrecision, angularPrecision);

    qInfo() << "Success: Done.";
    return 0;
}
