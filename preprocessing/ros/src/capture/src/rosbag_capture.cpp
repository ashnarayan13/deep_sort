#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>

#include <iostream>
#include <string>
#include <math.h>
#include <sstream>
#include <fstream>

using namespace cv;
using namespace std;

static long long int number = 0;
std::string NumberToString ( long long int Number )
  {
     std::ostringstream ss;
     ss << Number;
     return ss.str();
  }

void capture_image(Mat& imL)
{
    //store images
    std::string t1, t2, t3, tf1, tf2, punkt;
    std::ostringstream s1, s2;
    std::string temp1, temp2, dec1, dec2;
    temp1 = NumberToString(number);
    t1 = "/home/ashwath/PycharmProjects/deep_sort/preprocessing/images/";
    t3 = ".png";
    tf1 = t1 + temp1 + t3;
    number++;
    imwrite(tf1, imL);
}
 
void callback(const sensor_msgs::ImageConstPtr& left) {
  // conversion to rosmsgs::Image to cv::Mat using cv_bridge

  cv_bridge::CvImagePtr cv_left;
  try
    {
      cv_left = cv_bridge::toCvCopy(left);
    }
    catch (cv_bridge::Exception& e)
    {
      ROS_ERROR("cv_bridge exception: %s", e.what());
      return;
    }
  capture_image(cv_left->image);
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "image_listener");
  ros::NodeHandle nh;
  image_transport::ImageTransport it(nh);
  image_transport::Subscriber sub = it.subscribe("camera/image_raw", 1, callback);
  ros::spin();
  cv::destroyWindow("view");
}
