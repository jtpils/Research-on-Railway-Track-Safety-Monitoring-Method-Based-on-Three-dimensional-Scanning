#include "button.h"

//inline ButtonThread::ButtonThread(){}

StartDetect::StartDetect(QWidget * window, PointCloudMain *point, QMenu *menu, QToolBar *tool)
{
	start_action = new QAction(QIcon(QApplication::style()->standardIcon(QStyle::SP_MediaPlay)), QStringLiteral("��ʼ"));
	start_action->setShortcut(tr("ctrl+s"));
	menu->addAction(start_action);
	tool->addAction(start_action);
	connect(start_action, &QAction::triggered, [=] {start_action->setDisabled(true);});
	connect(start_action, &QAction::triggered, point, &PointCloudMain::startDetect, Qt::UniqueConnection);
}

PauseDetect::PauseDetect(QWidget * window, PointCloudMain * point, QMenu * menu, QToolBar * tool)
{
	pause_action = new QAction(QIcon(QApplication::style()->standardIcon(QStyle::SP_MediaPause)), QStringLiteral("��ͣ"));
	pause_action->setShortcut(tr("ctrl+p"));
	menu->addAction(pause_action);
	tool->addAction(pause_action);
	connect(pause_action, &QAction::triggered, point, &PointCloudMain::pauseDetect, Qt::UniqueConnection);
}

KeepDetect::KeepDetect(QWidget * window, PointCloudMain * point, QMenu * menu, QToolBar * tool)
{
	keep_action = new QAction(QIcon(QApplication::style()->standardIcon(QStyle::SP_MediaSeekForward)), QStringLiteral("����"));
	keep_action->setShortcut(tr("ctrl+s"));
	menu->addAction(keep_action);
	tool->addAction(keep_action);
	connect(keep_action, &QAction::triggered, point, &PointCloudMain::keepDetect, Qt::UniqueConnection);
}

OpenPointFile::OpenPointFile(QWidget * window, QMenu * menu, QToolBar * tool)
{
	open_action = new QAction(QIcon(QApplication::style()->standardIcon(QStyle::SP_DialogOpenButton)), QStringLiteral("��"));
	open_action->setShortcut(tr("ctrl+o"));
	menu->addAction(open_action);
	tool->addAction(open_action);
	//connect(openAction, &QAction::triggered, window, &MainWindow::open_file);
}

SavePointFile::SavePointFile(QWidget * window, QMenu * menu, QToolBar * tool)
{
	save_action = new QAction(QIcon(QApplication::style()->standardIcon(QStyle::SP_DialogSaveButton)), QStringLiteral("����"));
	save_action->setShortcut(tr("ctrl+s"));
	menu->addAction(save_action);
	tool->addAction(save_action);
}

ShowDifferPoint::ShowDifferPoint(QWidget * window, PointCloudMain *point,QMenu * menu, QToolBar * tool)
{
	differ_action = new QAction(QIcon(QApplication::style()->standardIcon(QStyle::SP_DialogNoButton)), QStringLiteral("��ʾ�����"));
	differ_action->setShortcut(tr("ctrl+d"));
	menu->addAction(differ_action);
	tool->addAction(differ_action);
	connect(differ_action, &QAction::triggered, point, &PointCloudMain::showDiffer, Qt::UniqueConnection);
}

ShowClusterPoint::ShowClusterPoint(QWidget * window, PointCloudMain *point, QMenu * menu, QToolBar * tool)
{
	cluster_action = new QAction(QIcon(QApplication::style()->standardIcon(QStyle::QStyle::SP_DialogYesButton)), QStringLiteral("��ʾ������"));
	cluster_action->setShortcut(tr("ctrl+c"));
	menu->addAction(cluster_action);
	tool->addAction(cluster_action);
	connect(cluster_action, &QAction::triggered, point, &PointCloudMain::showCluster, Qt::UniqueConnection);

}

ResetView::ResetView(QWidget * window, PointCloudMain *point, QMenu *menu, QToolBar *tool)
{
	reset_action = new QAction(QIcon(QApplication::style()->standardIcon(QStyle::SP_BrowserReload)), QStringLiteral("�����ӽ�"));
	reset_action->setShortcut(tr("ctrl+r"));
	menu->addAction(reset_action);
	tool->addAction(reset_action);
	connect(reset_action, &QAction::triggered, point, &PointCloudMain::resetView, Qt::UniqueConnection);
}