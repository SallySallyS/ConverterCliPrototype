#include <QCoreApplication>
#include <QCommandLineParser>
#include <QDebug>
#include <QFileInfo>
#include <QStringList>

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    app.setApplicationName("converter");
    app.setApplicationVersion("1.2");

    QCommandLineParser parser;
    parser.setApplicationDescription("CAD file converter");
    parser.addHelpOption();
    parser.addVersionOption();

    QCommandLineOption inputOption({"i", "input"}, "Input file (stp, obj, edc)", "file");
    QCommandLineOption outputOption({"o", "output"}, "Output file (stp, obj, edc)", "file");
    QCommandLineOption linearOption({"l", "linear"}, "Linear precision", "value", "0.1");
    QCommandLineOption angularOption({"a", "angular"}, "Angular precision", "value", "0.3");

    parser.addOption(inputOption);
    parser.addOption(outputOption);
    parser.addOption(linearOption);
    parser.addOption(angularOption);

    parser.addPositionalArgument("input", "Input file");
    parser.addPositionalArgument("output", "Output file");
    parser.addPositionalArgument("linear", "Linear precision [default: 0.1]");
    parser.addPositionalArgument("angular", "Angular precision [default: 0.3]");

    parser.process(app);

    const QStringList posArgs = parser.positionalArguments();

    QString inputPath = parser.value(inputOption);
    if (inputPath.isEmpty() && posArgs.size() > 0) inputPath = posArgs.at(0);

    QString outputPath = parser.value(outputOption);
    if (outputPath.isEmpty() && posArgs.size() > 1) outputPath = posArgs.at(1);

    if (inputPath.isEmpty() || outputPath.isEmpty()) {
        qCritical() << "Error: Input and output files are required!";
        parser.showHelp(1);
    }

    QFileInfo inputInfo(inputPath);
    QFileInfo outputInfo(outputPath);

    QString inputExt = inputInfo.suffix().toLower();
    QString outputExt = outputInfo.suffix().toLower();

    QStringList allowedFormats = {"stp", "obj", "edc"};

    if (!allowedFormats.contains(inputExt) || !allowedFormats.contains(outputExt)) {
        qCritical() << "Error: Unsupported format!";
        qCritical() << "Allowed formats: stp, obj, edc";
        return 1;
    }

    double linearPrecision = parser.isSet(linearOption) ? parser.value(linearOption).toDouble()
                                                        : (posArgs.size() > 2 ? posArgs.at(2).toDouble() : 0.1);

    double angularPrecision = parser.isSet(angularOption) ? parser.value(angularOption).toDouble()
                                                          : (posArgs.size() > 3 ? posArgs.at(3).toDouble() : 0.3);

    if (!inputInfo.exists()) {
        qCritical() << "Error: File" << inputPath << "not found.";
        return 1;
    }

    qInfo().noquote() << QString("Converting from %1 to %2").arg(inputExt.toUpper(), outputExt.toUpper());

    qInfo().noquote() << "Details:";
    qInfo().noquote() << "  Path: " << inputPath << "->" << outputPath;
    qInfo().noquote() << "  Params: Linear=" << linearPrecision << ", Angular=" << angularPrecision;

    // TODO: Здесь будет вызов реального конвертера

    qInfo() << "Success: Done.";
    return 0;
}
