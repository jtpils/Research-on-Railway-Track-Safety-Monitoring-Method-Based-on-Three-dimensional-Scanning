#include <iostream>
#include <pcl/io/pcd_io.h>
#include <pcl/point_cloud.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <pcl/io/io.h>
#include <pcl/keypoints/harris_3d.h>
#include <cstdlib>
#include <vector>
using namespace std;



int keypoint()
{
	pcl::PointCloud<pcl::PointXYZI>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZI>);
	pcl::io::loadPCDFile("C:\\Users\\mi\\OneDrive - mail.scut.edu.cn\\����\\20180125142128032.pcd", *cloud);
	//pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
	//pcl::copyPointCloud(*cloud, *cloud_xyzi);
	boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer(new pcl::visualization::PCLVisualizer);
	viewer->addPointCloud<pcl::PointXYZI>(cloud, "all_cloud");
	//ע��Harris��������Ʊ�������ǿ��(I)��Ϣ�ģ���Ϊ����ֵ������I������
	pcl::PointCloud<pcl::PointXYZI>::Ptr cloud_out(new pcl::PointCloud<pcl::PointXYZI>);
	pcl::HarrisKeypoint3D<pcl::PointXYZI, pcl::PointXYZI, pcl::Normal> harris;
	harris.setInputCloud(cloud);
	cout << "input successful" << endl;
	harris.setNonMaxSupression(true);
	harris.setRadius(0.04f);
	harris.setThreshold(0.02f);
	cout << "parameter set successful" << endl;
	//cout << cloud->at(0).x;
	//�½��ĵ��Ʊ����ʼ�������㣬����ָ���Խ��
	cloud_out->height = 1;
	cloud_out->width = 100;
	cloud_out->resize(cloud_out->height*cloud->width);
	cloud_out->clear();
	harris.compute(*cloud_out);
	int size = cloud_out->size();

	pcl::PointCloud<pcl::PointXYZI>::Ptr cloud_harris(new pcl::PointCloud<pcl::PointXYZI>);
	cloud_harris->height = 1;
	cloud_harris->width = 100;
	cloud_harris->resize(cloud_out->height*cloud->width);
	cloud_harris->clear();

	pcl::PointXYZI point;
	//���ӻ������֧��XYZI��ʽ���ƣ�������Ҫ����XYZ��ʽ��������
	for (int i = 0;i < size;i++)
	{
		cout << i << endl;
		point.x = cloud_out->at(i).x;
		point.y = cloud_out->at(i).y;
		point.z = cloud_out->at(i).z;
		point.intensity = cloud_out->at(i).intensity;
		cloud_harris->push_back(point);
	}



	pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZI> harris_color_handler(cloud_harris, 0, 255, 0);
	viewer->addPointCloud<pcl::PointXYZI>(cloud_harris, harris_color_handler, "harris");
	viewer->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 5, "harris");




	while (!viewer->wasStopped())
	{
		viewer->spinOnce(100);

	}

	system("pause");
}