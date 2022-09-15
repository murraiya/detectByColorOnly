//later replace this with camera input stream

#include <ros/ros.h>
#include <sensor_msgs/image_encodings.h>
#include <sensor_msgs/Image.h>
#include <cv_bridge/cv_bridge.h>
#include <image_transport/image_transport.h>

#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;

Mat img;

int main(int argc, char** argv) {

    ros::init(argc, argv, "video_load_node");
    ros::NodeHandle nh;
	ros::Publisher raw_image_pub = nh.advertise<sensor_msgs::Image>("/raw_image", 1);

	VideoCapture cap("/media/autonav/SJ_SSD/forFeatureMatching.avi");
	if (!cap.isOpened())
		{ printf("Can't open the camera"); }

    while(ros::ok()){ //ctrl-c interrupt

		cap >> img;
		
		if (img.empty()==1)
		{
			cout<<"load finish"<<endl;
		}

		else{ //pub only when img is not empty, without this u get useless rosmsg

			sensor_msgs::Image ros_img_msg;
		
			std_msgs::Header header; // empty header
			header.seq = 1; // user defined counter
			header.stamp = ros::Time::now(); // time

			cv_bridge::CvImage cvImg = cv_bridge::CvImage(header, sensor_msgs::image_encodings::BGR8, img);
			cvImg.toImageMsg(ros_img_msg);
			
			raw_image_pub.publish(ros_img_msg);
			cout<<"published"<<endl;

		}

		
	}
    return 0;
}
