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
    // cv::imshow(" image", cv_ptr->image);  //CvImage class에서 멤버변수로 cv::Mat image 있음, ptr 형식 객체의 멤버에 접근할 때 -> 연산자 쓴다.
    // cv::waitKey(1);

    Mat img_hsv; 
    Mat roi;

    Mat yellow_mask, yellow_image;
    Mat channels[3];

    cvtColor(cv_ptr->image, img_hsv, COLOR_BGR2HSV);

    roi=img_hsv(Rect(300,300,20,20));

    if(!roi.empty())  cout<<"got my rect"<<endl;

    // imshow("roi", roi);
    ~roi;

	// Scalar lower_yellow(20, 20, 100);
	// Scalar upper_yellow(32, 255, 255);
    imshow("HSV before split", img_hsv);

    split(img_hsv, channels); //split to h,s,v
    
    imshow("HSV img after split", img_hsv); //original
    // imshow("Hue", channels[0]); //hue
    // // imshow("Saturate", channels[1]); //saturate
    // // imshow("Value", channels[2]); //value
    
    channels[2] = 255; //value to max
    // merge(channels, img_hsv); //merge h,s,v
    
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