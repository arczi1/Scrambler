#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->LoadDataButton, SIGNAL(clicked(bool)), this, SLOT(onLoadButtonClicked()));
    connect(ui->ScrambleButton, SIGNAL(clicked(bool)), this, SLOT(onScrambleButtonClicked()));
    connect(ui->SendDataButton, SIGNAL(clicked(bool)), this, SLOT(onSendButtonClicked()));
    connect(ui->SaveDataButton, SIGNAL(clicked(bool)), this, SLOT(onSaveButtonClicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::printOnLog(QString text) {
    logText += ">";
    logText += text;
    logText += "\n";

    ui->plainTextEdit->ensureCursorVisible();
    ui->plainTextEdit->insertPlainText(">" + text + "\n");
    ui->plainTextEdit->ensureCursorVisible();

}

void MainWindow::onLoadButtonClicked() {
    printOnLog("Loading data");
    QString dataType{ getDataTypeFromUser() };
    loadData(dataType);
    printOnLog(dataType + " loaded");
    printOnLog("Data size: " + QString::fromStdString(std::to_string(data.size())));
}

QString MainWindow::getDataTypeFromUser() {
    QStringList dataTypes{{"MP3", "Only zeros", "Only ones"}};
    bool ok;
    QString dataType{QInputDialog::getItem(this, "Choose data type", tr("Types:"), dataTypes, 0, false, &ok)};

    if(ok && !dataType.isEmpty())
        return dataType;
    else
        return "invalid type";
}

void MainWindow::loadData(QString dataType) {
    if(dataType == "MP3")
        data = FileReader::readFile("file.mp3");
    else if (dataType == "Only zeros")
        data = SimpleBitDataGenerator::generateData(0, 1000);
    else if (dataType == "Only ones")
        data = SimpleBitDataGenerator::generateData(1, 1000);
}

void MainWindow::onScrambleButtonClicked() {
    printOnLog("Scrambling data");
    data = Scrambling::scrambleAdditive(data);
    printOnLog("Data scrambled");
}

void MainWindow::onSendButtonClicked(){
    printOnLog("Sending data");
    if(data.empty()) {
        printOnLog("No data provided");
        return;
    }
    startSimulation();
    printOnLog("Data sent");
}

void MainWindow::onSaveButtonClicked()
{
    printOnLog("Saving data");

    if(data.empty()) {
        printOnLog("No data provided");
        return;
    }
    FileReader::saveToFile(data, "saved.mp3");

    printOnLog("Data saved");
}

void MainWindow::startSimulation() {
    DataTransferSimulator simulation{};

    simulation.simulateSendingData(SimulationType::SimulationWithTheDataDisruptionDependedOnOccurrence, data);
    printOnLog("Number of lost bits: " + QString::fromStdString(std::to_string(simulation.getNumberOfRandomData())));
}

void MainWindow::on_HistogramButton_clicked()
{
    histogram = new Histogram(this, data);
    histogram->show();
}


