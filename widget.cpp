#include <QMessageBox>
#include <QPainter>
#include <QImage>
#include "widget.h"
#include "ui_widget.h"


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    qr = NULL;
    setString("amakuru yawe gakwa.");

}

Widget::~Widget()
{
    delete ui;
    if(qr != NULL)
       {
           QRcode_free(qr);
       }
}


//IMPLEMENT
void Widget::setString(QString str)
{
    string = str;
        if(qr != NULL)
        {
            QRcode_free(qr);
        }
        qr = QRcode_encodeString(string.toStdString().c_str(),
                                 1,
                                 QR_ECLEVEL_L,
                                 QR_MODE_8,
                                 1);
        update();
}
//IMPLEMENT
int Widget::getQRWidth() const
{
    if(qr != NULL)
        {
            return qr->width;
        }
        else
        {
            return 0;
        }
}

//IMPLEMENT
bool Widget::saveImage(QString fileName, int size)
{
    if(size != 0 && !fileName.isEmpty())
        {
            QImage image(size, size, QImage::Format_Mono);
            QPainter painter(&image);
            QColor background(Qt::white);
            painter.setBrush(background);
            painter.setPen(Qt::NoPen);
            painter.drawRect(0, 0, size, size);
            if(qr != NULL)
            {
                draw(painter, size, size);
            }
            return image.save(fileName);
        }
        else
        {
            return false;
        }
}

//IMPLEMENT
void Widget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
       QColor background(Qt::white);
       painter.setBrush(background);
       painter.setPen(Qt::NoPen);
       painter.drawRect(0, 0, width(), height());
       if(qr != NULL)
       {
           draw(painter, width(), height());
       }
}
//IMPLEMENT
QSize Widget::sizeHint() const
{
    QSize s;
        if(qr != NULL)
        {
            int qr_width = qr->width > 0 ? qr->width : 1;
            s = QSize(qr_width * 4, qr_width * 4);
        }
        else
        {
            s = QSize(50, 50);
        }
        return s;
}

//IMPLEMENT
QSize Widget::minimumSizeHint() const
{
    QSize s;
        if(qr != NULL)
        {
            int qr_width = qr->width > 0 ? qr->width : 1;
            s = QSize(qr_width, qr_width);
        }
        else
        {
            s = QSize(50, 50);
        }
        return s;
}



//IMPLEMENT
void Widget::draw(QPainter &painter, int width, int height)
{
    QColor foreground(Qt::black);
        painter.setBrush(foreground);
        const int qr_width = qr->width > 0 ? qr->width : 1;
        double scale_x = width / qr_width;
        double scale_y = height / qr_width;
        for( int y = 0; y < qr_width; y ++)
        {
            for(int x = 0; x < qr_width; x++)
            {
                unsigned char b = qr->data[y * qr_width + x];
                if(b & 0x01)
                {
                    QRectF r(x * scale_x, y * scale_y, scale_x, scale_y);
                    painter.drawRects(&r, 1);
                }
            }
        }
}
