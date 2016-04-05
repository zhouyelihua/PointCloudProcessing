#include <iostream>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/registration/icp.h>
#include <pcl/features/normal_3d.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <pcl/surface/mls.h>
#include <pcl/common/centroid.h>
#include <pcl/common/transforms.h>
#include <pcl/filters/statistical_outlier_removal.h>
//#include <pcl/filters/convolution_3d.h>
#include<iostream>
#include<fstream>
#include<vector>
typedef pcl::PointXYZRGB PointT;
typedef pcl::PointCloud<PointT> PointCloudT;
int
	main (int argc, char** argv)
{
	std::vector<double> X_vector;
	std::vector<double> Y_vector;
	std::vector<double> Z_vector;
	std::vector<double> R_vector;
	std::vector<double> G_vector;
	std::vector<double> B_vector;
	//X_vector.reserve(100000);
	//Y_vector.reserve(100000);
	//Z_vector.reserve(100000);
	//R_vector.reserve(100000);
	//G_vector.reserve(100000);
	//B_vector.reserve(100000);
	//X_vector.reserve(100000);
	double x_temp, y_temp, z_temp, r_temp, g_temp, b_temp,U,V;

	std::fstream in;
	char filename[30] = {0};
	sprintf(filename, "data%d.asc", 0);
	/*fstream in(filename);*/
	in.open(filename, fstream::in);
	//cout<<"process "<<filename<<endl;
	//in.open("Data0.txt", fstream::in);
	in.seekg(0);
	int NumPoint;
	//int nnnn=10000;
	int i=0;
	while (!in.eof())// while(nnnn--)
//	while(i<10)
	{
		//cout<<x_temp<<"\t";
		
		in >> x_temp >> y_temp >> z_temp >> r_temp >> g_temp >> b_temp>>U>>V;
		//cout<<i++<<"\t"<<U<<"\t"<<V<<endl;
		//cout<<x_temp<<"\t";
		X_vector.push_back(x_temp);
		Y_vector.push_back(y_temp);
		Z_vector.push_back(z_temp);
		R_vector.push_back(r_temp);
		G_vector.push_back(g_temp);
		B_vector.push_back(b_temp);

	}
	cout<<"read done"<<filename<<endl;
	NumPoint =X_vector.size();
	cout<<NumPoint<<endl;
	cout<<"begin!\n";
	// Load point cloud from disk
	pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud_in (new pcl::PointCloud<pcl::PointXYZRGB>);

	// Fill in the cloud data
	cloud_in->width  = NumPoint;
	cloud_in->height = 1;
	cloud_in->points.resize (cloud_in->width * cloud_in->height);
	cout<<"cloud_in->points.size ()"<<cloud_in->points.size ()<<endl;
	//for (size_t i = 0; i < cloud->points.size (); ++i)
	for (size_t i = 0; i < cloud_in->points.size (); ++i)
	{
		//cout<<i<<endl;
		cloud_in->points[i].x = X_vector.at(i) ;
		cloud_in->points[i].y = Y_vector.at(i) ;
		cloud_in->points[i].z = Z_vector.at(i) ;
		cloud_in->points[i].r = (int)(R_vector.at(i)*255 );
		cloud_in->points[i].g = (int)(G_vector.at(i)*255 );
		cloud_in->points[i].b = (int)(B_vector.at(i)*255 );
		//cout<<i<<endl;
	}
	X_vector.clear();
	Y_vector.clear();
	Z_vector.clear();
	R_vector.clear();
	G_vector.clear();
	B_vector.clear();

	pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud_out_filtered (new pcl::PointCloud<pcl::PointXYZRGB>);

	pcl::StatisticalOutlierRemoval<pcl::PointXYZRGB>sor;

	sor.setInputCloud(cloud_in);
	sor.setMeanK(100);
	sor.setStddevMulThresh(1.0);
	sor.filter(*cloud_out_filtered);
	//pcl::filters::GaussianKernelRGB<pcl::PointXYZRGB,pcl::PointXYZRGB> sor_in;
	//sor_in.setInputCloud (cloud_in);
	// sor_in.setSigma(0.1);
	//sor_in.setThreshold(1.0);

	// sor_in.setThresholdRelativeToSigma(0.1f);
	//sor_in.initCompute();
	//sor_in.(cloud_out_filtered);

	std::fstream out2;
	out2.open("data1out.txt", fstream::out);

	for (size_t i = 0; i < cloud_out_filtered->points.size (); ++i)
	{
		//cout<<i<<endl;
		out2<<cloud_out_filtered->points[i].x<<"\t"
			<<cloud_out_filtered->points[i].y<<"\t"
			<<cloud_out_filtered->points[i].z<<"\t"
			<<(int)cloud_out_filtered->points[i].r<<"\t"
			<<(int)cloud_out_filtered->points[i].g<<"\t"
			<<(int)cloud_out_filtered->points[i].b<<"\n";
		//cout<<i<<endl;
	}
	out2.close();
	return (0);
}
