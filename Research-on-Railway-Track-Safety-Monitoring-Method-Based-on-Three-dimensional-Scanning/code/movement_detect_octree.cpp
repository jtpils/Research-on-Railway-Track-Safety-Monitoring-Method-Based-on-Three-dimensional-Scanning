#include "movement_detect_octree.h"
#include <pcl/segmentation/region_growing.h>

MovementDetectOctree::MovementDetectOctree() :
	frame_differ(new PointCloud<PointXYZRGB>) ,
	tree(new search::KdTree<PointXYZRGB>),
	cloud_cluster_result(new pcl::PointCloud<pcl::PointXYZRGB>)
{
	//tree->setInputCloud(cloud);
	//ec.setClusterTolerance(0.30); // 2cm
	//ec.setMinClusterSize(6);
	ec.setClusterTolerance(0.15); // 2cm
	ec.setMinClusterSize(6);
	ec.setMaxClusterSize(100);
	//ec.setMaxClusterSize(100);
	//����������
	ec.setSearchMethod(tree);
}

MovementDetectOctree::MovementDetectOctree(PointCloud<PointXYZRGB>::Ptr &origin)
	: frame_origin(frame_origin), 
	frame_differ(new PointCloud<PointXYZRGB>) ,
	tree(new search::KdTree<PointXYZRGB>),
	cloud_cluster_result(new pcl::PointCloud<pcl::PointXYZRGB>)
{
	//tree->setInputCloud(cloud);
	//ec.setClusterTolerance(0.10); // 2cm
	//ec.setMinClusterSize(6);

	//ec.setClusterTolerance(0.10); // 2cm
	ec.setClusterTolerance(0.060);
	ec.setMinClusterSize(8);
	ec.setMaxClusterSize(100);
	//����������
	ec.setSearchMethod(tree);
}


//public����������private�˶���⺯��
bool MovementDetectOctree::detectMovement(PointCloud<PointXYZRGB>::Ptr & actual)
{
	frame_actual = actual;
	return octree_algorithm();
}

bool MovementDetectOctree::detectMovement(PointCloud<PointXYZRGB>::Ptr & origin, PointCloud<PointXYZRGB>::Ptr & actual)
{
	frame_origin = origin;
	frame_actual = actual;
	return octree_algorithm();
}

//private�����������˶�������
bool MovementDetectOctree::octree_algorithm()
{
	srand((unsigned int)time(NULL));
	// �˲����ֱ��� �����صĴ�С
	//float resolution = 0.75f;
	float resolution = 0.65f;
	// ��ʼ���ռ�仯������
	pcl::octree::OctreePointCloudChangeDetector<pcl::PointXYZRGB>octree(resolution);
	octree.setInputCloud(frame_origin);
	octree.addPointsFromInputCloud();
	// �����˲������棬����cloudA��Ӧ�İ˲��������ڴ���
	octree.switchBuffers();

	octree.setInputCloud(frame_actual);
	octree.addPointsFromInputCloud();

	//��ȡǰһcloudA��Ӧ�İ˲�����cloudB��Ӧ�˲�����û�е�����
	octree.getPointIndicesFromNewVoxels(newPointIdxVector);
	//qDebug() << newPointIdxVector.size() << "&&&&&&&&&&&&&&&&&&&&&&&&" << endl;

	//frame_differ->resize(300);
	for (size_t i = 0; i < newPointIdxVector.size(); ++i)
	{
	//	frame_differ->at(i).x = frame_actual->points[newPointIdxVector[i]].x;
	//	frame_differ->at(i).y = frame_actual->points[newPointIdxVector[i]].y;
	//	frame_differ->at(i).z = frame_actual->points[newPointIdxVector[i]].z;
		frame_differ->points.push_back(frame_actual->points[newPointIdxVector[i]]);
		//frame_differ->points.push_back(frame_actual->points[newPointIdxVector[i]]);
		//frame_differ->at(i).r = 255;
		//frame_differ->at(i).g = 0;
		//frame_differ->at(i).b = 0;
	}
	//qDebug()<< frame_differ->size() << "&&&&&&&&&&&&&&&&&&&&&&&&" << endl;
	//newPointIdxVector.clear(); //���vector
	
	ec.setInputCloud(frame_differ);
	ec.extract(cluster_indices);
	//qDebug() << cluster_indices.size() << "&&&&&&&&&&&&&&&&&&&&&&&&" << endl;
	/*
	for (size_t i = 0;i < cloud_cluster_result_tem->size(); ++i)
	{
		cloud_cluster_result->at(i).x = cloud_cluster_result_tem->at(i).x;
		cloud_cluster_result->at(i).y = cloud_cluster_result_tem->at(i).y;
		cloud_cluster_result->at(i).z = cloud_cluster_result_tem->at(i).z;
	}
	cloud_cluster_result_tem->clear();
	
	pcl::RegionGrowing<pcl::PointXYZRGB, pcl::Normal> reg;
	//����ָ�Ŀ��
	PointCloud <pcl::Normal>::Ptr normals(new pcl::PointCloud <pcl::Normal>);
	reg.setSearchMethod(tree);
	reg.setNumberOfNeighbours(5);
	reg.setInputCloud(frame_differ);
	//reg.setIndices (indices);
	reg.setInputNormals(normals);

	//������������������֪ʶ
	reg.setMinClusterSize(7);
	reg.setMaxClusterSize(200);
	reg.setSmoothnessThreshold(3.0 / 180.0 * M_PI);
	reg.setCurvatureThreshold(1.0);
	reg.extract(cluster_indices);
	
	ofstream fout;
	fout.open("D:\\differ.txt", ios_base::app);
	static int i = 1;
	fout << i << ":" << newPointIdxVector.size() <<" "<< cluster_indices.size() << endl;
	i++;
	fout.close();
	*/

	if (0 == cluster_indices.size())
	{
		//newPointIdxVector.clear();
		//cluster_indices.clear();
		return true;
	}
	else if (1 <= cluster_indices.size())
	{
		//newPointIdxVector.clear();
		//cluster_indices.clear();
		return false;
	}
}

PointCloud<PointXYZRGB>::Ptr MovementDetectOctree::getCloudClusterResult()
{
	//cloud_cluster_result->resize(300);
	for (auto point = cluster_indices.begin(); point != cluster_indices.end(); point++)
	{
		for (std::vector<int>::const_iterator pit = point->indices.begin(); pit != point->indices.end(); ++pit)
			//frame_differ->points[*pit].r = 255;
			cloud_cluster_result->points.push_back(frame_differ->points[*pit]);
	}
	return cloud_cluster_result;
}

//public���������ص��Ƽ�Ĳ������
PointCloud<PointXYZRGB>::Ptr MovementDetectOctree::getDifferCloud()
{
	//newPointIdxVector.clear();
	//cluster_indices.clear();
	return frame_differ;
}

vector<int> MovementDetectOctree::getPointNum()
{
	//qDebug() << newPointIdxVector.size() << endl;
	return newPointIdxVector;
}

void MovementDetectOctree::clearPointNum()
{
	cluster_indices.clear();
	newPointIdxVector.clear();
	cloud_cluster_result->clear();
	frame_differ->clear();
}
