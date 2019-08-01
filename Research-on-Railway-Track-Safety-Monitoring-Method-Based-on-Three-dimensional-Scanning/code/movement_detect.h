#ifndef MOVEMENT_DETECT
#define MOVEMENT_DETECT
#pragma once
#include "pre_fliter.h"
#include <iostream>
#include <vector>
#include <fstream> 
#include "load.h"
#include <algorithm>
#include <pcl/io/pcd_io.h>  
#include <pcl/point_types.h>
#include <pcl/ModelCoefficients.h>
#include <pcl/point_types.h>
#include <pcl/filters/extract_indices.h>
#include <pcl/filters/voxel_grid.h>
#include <pcl/features/normal_3d.h>
#include <pcl/sample_consensus/method_types.h>
#include <pcl/sample_consensus/model_types.h>
#include <pcl/segmentation/sac_segmentation.h>
#include <pcl/segmentation/extract_clusters.h>

using namespace std;
using namespace pcl;

/*
��Movement_Detect ��Ҫ�����˶�������
��Ԫ����FrameDifferenceRoute���� ���������֡pcd�ļ�֮��Ĳ���
����MovementObject�������ڼ���Ƿ���Ŀ���˶�����
����frame_one frame_two frame_defference�ֱ�洢��һ֡���ڶ�֡�Ͳ���֡����
*/

class Movement_Detect 
{
	friend bool FrameDifferenceRoute(Movement_Detect target); 
public:
	Movement_Detect();
	Movement_Detect(PointCloud<PointXYZI>::Ptr &one, PointCloud<PointXYZI>::Ptr &two);
	~Movement_Detect() = default;
	bool MovementObject();
private:
	int roi_num = 0;
	int	not_roi_num = 0;
	// bool gaussian_fliter();
	bool euclidean_algorithm();
	PointCloud<PointXYZI>::Ptr frame_one;
	PointCloud<PointXYZI>::Ptr frame_difference;
};
#endif


