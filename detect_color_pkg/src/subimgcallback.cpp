//original sub code

#include <ros/ros.h>
#include <sensor_msgs/image_encodings.h>
#include <sensor_msgs/Image.h>
#include <cv_bridge/cv_bridge.h>
#include <image_transport/image_transport.h>

#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;

void ImgSubCallback(const sensor_msgs::Image raw_img){
    cout<<"img_sub"<<endl;
    //start here convert to cv img and imshow, check 
    cv_bridge::CvImagePtr cv_ptr = cv_bridge::toCvCopy(raw_img, sensor_msgs::image_encodings::BGR8);
    cv::imshow("image", cv_ptr->image);  //CvImage class에서 멤버변수로 cv::Mat image 있음, ptr 형식 객체의 멤버에 접근할 때 -> 연산자 쓴다.
    cv::waitKey(1);
}


int main(int argc, char** argv) {

    ros::init(argc, argv, "videoSubVisualNode");
    ros::NodeHandle nh;
    ros::Subscriber raw_image_sub = nh.subscribe<sensor_msgs::Image>("/raw_image", 10, ImgSubCallback);
    
    if(ros::ok())
        ros::spin();

    return 0;
}