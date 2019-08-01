#ifndef PRE_FLITER
#define PRE_FLITER

#pragma once
#include <vector>
#include <pcl/point_types.h>
#include <pcl/filters/statistical_outlier_removal.h>

using namespace std;
using namespace pcl;

/*
��Point_Cloud_Fliter����Ҫ�����˲�
����fliter()���ڷֱ����ֱ���˲��͸�˹�˲�
����get_point_cloud()�����˲���ĵ���
����point_cloud�����˲���ĵ���
����stright_fliter()��gaussian_fliter()�ֱ�ʵ��ֱ���˲��͸�˹�˲�
*/

class PointCloudFliter
{
public:
	PointCloudFliter();
	PointCloudFliter(PointCloud<PointXYZRGB>::Ptr &point_cloud_input);
	~PointCloudFliter() = default;
	bool fliterPointCloud();
	bool fliterPointCloud(PointCloud<PointXYZRGB>::Ptr &point_cloud_input);
	PointCloud<PointXYZRGB>::Ptr getPointCloud();
private:
	PointCloud<PointXYZRGB>::Ptr point_cloud;  //���ƶ���������ĵ��ƽ��г�ʼ��
	bool stright_fliter();
	bool gaussian_fliter();
};
#endif