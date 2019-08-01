#ifndef POINT_CLOUD
#define POINT_CLOUD
#pragma once
#include <QDebug>
#include <QString>
#include <QObject>
#include "pch.h"
#include "pre_fliter.h"
#include <stdlib.h>
#include <iostream>
#include <vector>
#include "viewer.h"
#include <fstream> 
#include <windows.h>
#include "load.h"
#include <algorithm>
#include <pcl/io/pcd_io.h>  
#include <thread>
#include <string>
#include <pcl/point_types.h>
//#include <mutex>
#include <QEventLoop>
//#include "movement_detect.h"
//#include "movement_detect_gaussian.h"
#include "movement_detect_octree.h"

class PointCloudMain : public QObject
{
	Q_OBJECT
public:
	PointCloudMain();
	PointCloudMain(PointCloudViewer *viewer_main);
	~PointCloudMain();
	//void pause();
	void startThread();
	void sendFileNum() { emit FileNum(); }
	void sendOverFlag() { emit RunOver(); }
	void sendSafeFlag() { emit SafeFlag(); }
	void sendWarnFlag() { emit WarnFlag(); }
	void sendNewViewer() { emit NewViewer(point_cloud_actual, point_cloud_differ); }
public slots:
	void startDetect();
	void pauseDetect();
	void keepDetect();
	void showDiffer();
	void showCluster();
	void resetView();
	void keepShow();
signals:
	void FileNum();
	void RunOver();
	void SafeFlag();
	void WarnFlag();
	void NewViewer(const PointCloud<PointXYZRGB>::Ptr &point_cloud_actual, const PointCloud<PointXYZRGB>::Ptr &point_cloud_differ);
private:
	PointCloudViewer *viewer_main; //�Ӵ�1����ʾ��ǰ����
	//PointCloudViewer *viewer2; //�Ӵ�2����ʾ�������
	PointCloudFile point_cloud_file; //��ȡ�ļ��б���
	PointCloudFliter point_cloud_fliter; //���ƹ���Ԥ������
	MovementDetectOctree movement_detect_octree; //�˶������
	vector<string> point_cloud_list = point_cloud_file.getPointCloudName(); //�ļ��б�
	PointCloud<PointXYZRGB>::Ptr point_cloud_origin, point_cloud_actual, point_cloud_differ; //�������ƺ͵�ǰ����
	bool showtype; //������ʾ����㣨true�����ǵ����ţ�false��
	bool waitting;  //������ͣ������Ŀ���
	bool result; //���������
	bool viewshow;
};

#endif