#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QLabel>
#include <QListView>
#include <QMainWindow>
#include <QModelIndex>

#include "DataManager.h"
#include "ui_mainwindow.h"

class MainWindow : public QMainWindow, protected Ui::MainWindowClass
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
signals:
	void toggleCapture(bool toggle);
public slots:
	void setCapturing(bool toggle);
	void onRowsInserted(const QModelIndex&, int, int);
	void setStatus(const QString& status);
protected:
	QLabel* statusLabel;
};

#endif // MAINWINDOW_H
