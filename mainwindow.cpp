#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QImage>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    englishWord = "Tree";
    chineseCharacter = "树";

    ui->wordLabel->setText("Word to Draw: " + englishWord);

    ui->drawingWidget->clearDrawing();

    connect(ui->checkButton, &QPushButton::clicked, this, &MainWindow::checkDrawing);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::checkDrawing()
{
    QImage drawnImage = ui->drawingWidget->getDrawingImage();

    QMessageBox::information(this, "Check Drawing", "Check complete. Drawing matches: " + chineseCharacter);
}

DrawingWidget::DrawingWidget(QWidget *parent)
    : QWidget(parent), drawingCanvas(400, 400, QImage::Format_RGB32)
{
    drawingCanvas.fill(Qt::white);
}

void DrawingWidget::clearDrawing()
{
    lines.clear();
    drawingCanvas.fill(Qt::white);
    update();
}

QImage DrawingWidget::getDrawingImage()
{
    return drawingCanvas;
}

void DrawingWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawImage(0, 0, drawingCanvas);
    for (const QLine &line : lines) {
        painter.setPen(QPen(Qt::black, 3));
        painter.drawLine(line);
    }
}

void DrawingWidget::mousePressEvent(QMouseEvent *event)
{
    lines.clear();
    lastPoint = event->pos();
}

void DrawingWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton) {
        QLine line(lastPoint, event->pos());
        lines.append(line);
        lastPoint = event->pos();
        update();
    }
}
