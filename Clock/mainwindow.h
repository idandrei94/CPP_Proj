#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QObject>
#include <QActionGroup>
#include <QPair>
#include <QMap>

#include "listener.h"
#include "documentwidget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

signals:

public slots:
    void onMenuShow();

protected:
    void addFileMenu();
    void addEditMenu();

protected:
    void addAction(QMenu* menuPtr, QString text,
                   const char* onSelectPtr,
                   QKeySequence acceleratorKey = 0,
                   QString iconName = QString(),
                   Listener enableListener = nullptr,
                   Listener checkListener = nullptr,
                   QActionGroup* groupPtr = nullptr);

    DEFINE_LISTENER(DocumentWidget, isSaveEnabled);
    DEFINE_LISTENER(DocumentWidget, isCutEnabled);
    DEFINE_LISTENER(DocumentWidget, isCopyEnabled);
    DEFINE_LISTENER(DocumentWidget, isPasteEnabled);
    DEFINE_LISTENER(DocumentWidget, isDeleteEnabled);

private:
    QMap<QAction*, QPair<QObject*, Listener>> m_enableMap, m_checkMap;
};

#endif // MAINWINDOW_H
