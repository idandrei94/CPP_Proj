#ifndef CLOCK_H
#define CLOCK_H

#include <QWidget>
#include <QTimer>

namespace Ui {
class Clock;
}

class Clock : public QWidget
{
    Q_OBJECT

public:
    explicit Clock(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *eventPtr);
    ~Clock();

private:
    Ui::Clock *ui;
    QTimer m_timer;
};

#endif // CLOCK_H
