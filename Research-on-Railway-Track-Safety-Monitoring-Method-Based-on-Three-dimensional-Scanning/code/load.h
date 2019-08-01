#pragma once
#include "pch.h"
#include <iostream>
#include <string>
#include <fstream>
#include <io.h>
#include <vector>
#include <algorithm>
#include <pcl/io/pcd_io.h>  
#include <pcl/point_types.h>

using namespace std;
using namespace pcl;

/*
��Get_Point_Cloud ��Ҫ���ڼ���pcdͼ��
��Ԫ����LoadPointCloud�������ڼ�����һ���ļ� ����next_file�����Ƿ������һ��
����GetPointCloudName()���ڻ�ȡ�ļ����е��ļ��б�
����in_path���������ļ�Ŀ¼
����point_cloud_name��¼�����ļ�����
����GetPointCloud()���ڻ�ȡ�б��洢��point_cloud_name��
*/

class PointCloudFile
{
	friend PointCloud<PointXYZRGB>::Ptr loadPointCloud(PointCloudFile target);
public:
	PointCloudFile();
	PointCloudFile(string file_path);  //�����Զ���·���Ĺ��캯��
	~PointCloudFile() = default;
	vector<string> getPointCloudName(); //����Ŀ¼���ļ��������б�
	//string getFileName();
private:
	string in_path;  //·����
	vector<string> point_cloud_name; //�ļ������б�
	bool getPointCloud(); //����·�����ļ��б�
	vector<_finddata_t> point_cloud_file; //�����ļ���Ϣ���У���������ʱ�����Ϣ
	struct _finddata_t fileinfo;
	string curr;  //��ǰ·��
	long long handle;
};

