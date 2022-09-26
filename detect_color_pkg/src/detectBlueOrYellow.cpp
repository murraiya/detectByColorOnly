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
using namespace cv;

void ImgSubCallback(const sensor_msgs::Image raw_img){
    cout<<"img_sub"<<endl;
    
    
    cv_bridge::CvImagePtr cv_ptr = cv_bridge::toCvCopy(raw_img, sensor_msgs::image_encodings::BGR8);

    Mat img_hsv; 
    Mat roi_hsv;
    Mat roi_h;

    Mat yellow_mask, yellow_image;
    Mat channels[3];

    cvtColor(cv_ptr->image, img_hsv, COLOR_BGR2HSV);

    roi_hsv=img_hsv(Rect(320,270,130,210));
    imshow("roi_hsv", roi_hsv);

    split(img_hsv, channels); //split to h,s,v
    
    // imshow("Hue", channels[0]); //hue

    roi_h=channels[0](Rect(320,270,130,210));
    imshow("roi_h", roi_h);
    
    waitKey(1);
    // cv::destroyAllWindows();
}

int main(int argc, char** argv) {

    ros::init(argc, argv, "detectBlueOrYellow_node");
    ros::NodeHandle nh;
    ros::Subscriber raw_image_sub = nh.subscribe<sensor_msgs::Image>("/raw_image", 10, ImgSubCallback);
    
    if(ros::ok())
        ros::spin();

    return 0;
}