#ifndef MOVEMENT_DETECT_OCTREE
#define MOVEMENT_DETECT_OCTREE
#pragma once
#include "pch.h"
#include <QDebug>
#include <iostream>
#include <pcl/io/pcd_io.h>
#include <pcl/point_cloud.h>
#include <pcl/filters/statistical_outlier_removal.h>
#include <pcl/octree/octree.h>
#include <pcl/point_types.h>
#include <pcl/segmentation/extract_clusters.h>
#include <vector>

using namespace std;
using namespace pcl;

class MovementDetectOctree
{
public:
	MovementDetectOctree();
	MovementDetectOctree(PointCloud<PointXYZRGB>::Ptr &origin);
	~MovementDetectOctree() = default;
	bool detectMovement(PointCloud<PointXYZRGB>::Ptr &actual);
	bool detectMovement(PointCloud<PointXYZRGB>::Ptr &origin, PointCloud<PointXYZRGB>::Ptr &actual);
	PointCloud<PointXYZRGB>::Ptr getDifferCloud();
	PointCloud<PointXYZRGB>::Ptr getCloudClusterResult();
	//void clearCloudClusterResult();
	vector<int> getPointNum();
	void clearPointNum();
private:
	bool octree_algorithm();
	vector<int> newPointIdxVector; //�洢�������
	PointCloud<PointXYZRGB>::Ptr frame_origin;
	PointCloud<PointXYZRGB>::Ptr frame_actual;
	PointCloud<PointXYZRGB>::Ptr frame_differ;
	search::KdTree<PointXYZRGB>::Ptr tree;
	vector<PointIndices> cluster_indices; //���ָ�����ĵ����ţ���Ŷ��У�
	EuclideanClusterExtraction<PointXYZRGB> ec; //ŷʽ�ָ���
	PointCloud<PointXYZRGB>::Ptr cloud_cluster_result_tem;
	PointCloud<PointXYZRGB>::Ptr cloud_cluster_result; //�����ĸ���㼯��
};


#endif