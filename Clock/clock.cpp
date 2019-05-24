#include "clock.h"
#include "ui_clock.h"

#include <QTime>
#include <QPainter>

Clock::Clock(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Clock)
{
    ui->setupUi(this);
    setWindowTitle("Clock");
    resize(600,600);
    m_timer.setParent(this);
    connect(&m_timer, SIGNAL(timeout()), this, SLOT(update()));
    m_timer.start(13);
}

void Clock::paintEvent(QPaintEvent *eventPtr)
{
    int side = qMin(width(), height());
    QTime time = QTime::currentTime();
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::TextAntialiasing);
    painter.translate(width()/2, height()/2);
    painter.scale(side / 200.0, side / 200.0);
    painter.save();
    for(int second = 0; second <= 60; ++ second) {
        if( (second % 5 ) == 0) {
            painter.drawLine(QPoint(0,81), QPoint(0,98));
        }
        else {
            painter.drawLine(QPoint(0, 90), QPoint(0,98));
        }
        painter.rotate(6);
    }
    painter.restore();
    double hours = time.hour(), minutes = time.minute(), seconds = time.second(), milliseconds = time.msec();
    painter.setPen(Qt::black);
    painter.setBrush(Qt::gray);
    static const QPoint hourHand[3] = {
        QPoint(8,8),
        QPoint(-8,8),
        QPoint(0,-60)
    };
    painter.save();
    double hour = hours + (minutes / 60.0) + (seconds / 3600.0) + (milliseconds / 3600000.0);
    painter.rotate(30.0 * hour);
    painter.drawConvexPolygon(hourHand, 3);
    painter.restore();

    static const QPoint minuteHand[3] = {
        QPoint(6,8),
        QPoint(-6, 8),
        QPoint(0, -70)
    };
    painter.save();
    double minute = minutes + (seconds / 60.0) + (milliseconds / 60000.0);
    painter.rotate(6.0 * minute);
    painter.drawPolygon(minuteHand, 3);
    painter.restore();

    static const QPoint secondHand[3] = {
        QPoint(4,8),
        QPoint(-4, 8),
        QPoint(0, -80)
    };
    painter.save();
    double second = seconds + (milliseconds / 1000.0);
    painter.rotate(6.0 * second);
    painter.drawPolygon(secondHand, 3);
    painter.restore();

    painter.save();
    painter.drawEllipse(QPoint(), 11, 11);
    painter.restore();
}

Clock::~Clock()
{
    delete ui;
}
