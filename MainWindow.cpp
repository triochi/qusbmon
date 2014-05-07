#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
	setupUi(this);

	packetsView->setModel(&DataManager::get().packets);
	packetsView->setColumnHidden(1, true);
	packetsView->setColumnHidden(6, true);

	statusLabel = new QLabel();
	statusLabel->setToolTip("Q: Queued D: Dropped");
	this->statusBar()->addWidget(statusLabel);

	QObject::connect(actionExit, SIGNAL(triggered()), qApp, SLOT(quit()));
	QObject::connect(actionStartStop, SIGNAL(toggled(bool)), this, SIGNAL(toggleCapture(bool)));
	QObject::connect(actionStartStop, SIGNAL(toggled(bool)), this, SLOT(setCapturing(bool)));
	QObject::connect(packetsView->model(), SIGNAL(rowsInserted(const QModelIndex&, int, int)),
					this, SLOT(onRowsInserted(const QModelIndex&, int, int)));
}

MainWindow::~MainWindow()
{}

void MainWindow::setStatus(const QString& status)
{
	statusLabel->setText(status);
}
void MainWindow::setCapturing(bool toggle)
{
	actionStartStop->setChecked(toggle);
	if(toggle == false)
	{
		for(int i=0; i<packetsView->model()->columnCount(); ++i)
			packetsView->resizeColumnToContents(i);
	}
}

void MainWindow::onRowsInserted(const QModelIndex& parent, int from, int to)
{
	packetsView->scrollToBottom();
}
