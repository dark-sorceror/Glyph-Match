#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QPainter>
#include <QMouseEvent>
#include <QImage>

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
    void checkDrawing();

private:
    Ui::MainWindow *ui;

    QString englishWord;
    QString chineseCharacter;

    QImage drawingImage;
};

class DrawingWidget : public QWidget
{
    Q_OBJECT

public:
    DrawingWidget(QWidget *parent = nullptr);
    void clearDrawing();
    QImage getDrawingImage();

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

private:
    QVector<QLine> lines;
    QImage drawingCanvas;
};

#endif // MAINWINDOW_H
