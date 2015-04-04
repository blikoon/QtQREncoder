#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

#include "qrencode/qrencode.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

    //This is where you pass the string to encode
    void setString(QString str);
    int getQRWidth() const;
    bool saveImage(QString name, int size);



signals:

protected:

    void paintEvent(QPaintEvent *);
    QSize sizeHint() const;
    QSize minimumSizeHint() const;



private:
    //This is where you paint on the widget
    //ZXing is doing all the heavy lifting here.
    void draw(QPainter &painter, int width, int height);
    QString string;
    QRcode *qr;


    Ui::Widget *ui;
};

#endif // WIDGET_H
