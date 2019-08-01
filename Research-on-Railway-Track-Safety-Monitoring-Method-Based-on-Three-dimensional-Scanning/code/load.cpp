#include "pch.h"
#include "load.h"
#include <QDebug>

/*
struct _finddata_t {
 unsigned attrib;
 time_t time_create;
 time_t time_access;
 time_t time_write;
 _fsize_t size;
 char name[260];
};
unsigned atrrib�� �ļ����ԵĴ洢λ�á����洢һ��unsigned��Ԫ��
	���ڱ�ʾ�ļ������ԡ��ļ���������λ��ʾ�ģ���Ҫ������һЩ��
	_A_ARCH���浵���� _A_HIDDEN�����أ���_A_NORMAL����������
	_A_RDONLY��ֻ������_A_SUBDIR���ļ��У���_A_SYSTEM��ϵͳ����
	��Щ�������ж���ĺ꣬����ֱ��ʹ�ã��������������ʵ��һ
	���޷������ͣ�ֻ�����������Ӧ����2�ļ����ݣ��Ӷ���ֻ֤��
	һλΪ 1��������λΪ0������Ȼ��λ��ʾ����ô��һ���ļ��ж�
	������ʱ����������ͨ��λ��ķ�ʽ�����õ��������Ե��ۺϡ�
	����ֻ��+����+ϵͳ���ԣ�Ӧ��Ϊ��_A_HIDDEN | _A_RDONLY |
	_A_SYSTEM ��
time_t time_create�� �ļ�����ʱ�䡣
time_t time_access�� �ļ����һ�α����ʵ�ʱ�䡣
time_t time_write�� �ļ����һ�α��޸ĵ�ʱ�䡣
_fsize_t size�� �ļ��Ĵ�С��
char name [_MAX_FNAME ]���ļ����ļ����������_MAX_FNAME��һ��
	�����꣬����ͷ�ļ��б����壬��ʾ�����ļ�������󳤶ȡ�

1��_findfirst������long _findfirst(const char *, struct _finddata_t *);
	��һ������Ϊ�ļ�����������"*.*"�����������ļ���Ҳ������"*.cpp"����
	��.cpp�ļ����ڶ���������_finddata_t�ṹ��ָ�롣�����ҳɹ���������
	���������ʧ�ܣ�����-1��
2��_findnext������int _findnext(long, struct _finddata_t *);
	��һ������Ϊ�ļ�������ڶ�������ͬ��Ϊ_finddata_t�ṹ��ָ�롣������
	�ɹ�������0��ʧ�ܷ���-1��
3��_findclose()������int _findclose(long);
	ֻ��һ���������ļ���������رճɹ�����0��ʧ�ܷ���-1��
*/

PointCloudFile::PointCloudFile():in_path("D:\\2.Ԥ��") {}
//PointCloudFile::PointCloudFile() :in_path("C:\\Users\\mi\\OneDrive - mail.scut.edu.cn\\����\\����") {}
PointCloudFile::PointCloudFile(string file_path) :in_path(file_path) {}

//���رȽϺ������޸�Ϊ���ļ��Ĵ���ʱ�����У�ģ��������е����ɹ���
bool comp(const _finddata_t &a, const _finddata_t &b) {
	return a.time_create < b.time_create;
}

//private�����������ļ��б����
bool PointCloudFile::getPointCloud()
{
	curr = in_path + "\\*.pcd";
	if ((handle = _findfirst(curr.c_str(), &fileinfo)) == -1L) //��������ָ����չ���ļ�
	{
		cout << "û���ҵ�ƥ���ļ�!" << endl;
		return false;
	}
	else
	{
		point_cloud_file.push_back(fileinfo); //�����һ���ļ�
		while (!(_findnext(handle, &fileinfo)))
		{
			point_cloud_file.push_back(fileinfo);
		}
		_findclose(handle);
	}
	//���ļ�����˳�����к󣬽��ļ�����˳��push��point_cloud_name
	sort(point_cloud_file.begin(), point_cloud_file.end(), comp);
	for (auto it = point_cloud_file.begin(); it != point_cloud_file.end(); it++)
	{
		//qDebug() << (*it).name << endl;
		point_cloud_name.push_back((*it).name);
	}
	return true;
}

//public���������ڷ����ļ������б�
vector<string> PointCloudFile::getPointCloudName()
{
	if (getPointCloud()) return point_cloud_name;
}

PointCloud<PointXYZRGB>::Ptr loadPointCloud(PointCloudFile target)
{
	PointCloud<PointXYZRGB>::Ptr point_cloud(new PointCloud<PointXYZRGB>);
	//static int point_cloud_num = 0; //��¼��ȡ���˵ڼ��������ļ�
	static int point_cloud_num = 0;
	string point_cloud_target_name = target.in_path + "\\" + target.point_cloud_name[point_cloud_num];
	if (pcl::io::loadPCDFile<pcl::PointXYZRGB>(point_cloud_target_name, *point_cloud) == -1)
	{
		PCL_ERROR("Couldn't read file pcd\n");
	}
	point_cloud_num++;
	qDebug() << "num" << point_cloud_num << " load succeed!" << endl;
	
	//if (point_cloud_num % 10 == 0) point_cloud_num_th += 10;
	if (point_cloud_num == target.point_cloud_name.size()) point_cloud_num = 0;
	return point_cloud;
}

//string PointCloudFile::getFileName()
//{
	//return point_cloud_name[point_cloud_num];
//}