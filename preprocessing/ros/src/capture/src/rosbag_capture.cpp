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

class Capture_images{
public:
  void callback(const sensor_msgs::ImageConstPtr& left);
  void capture_image(Mat& imL, long sec, long nsec, std::string frame);
  std::string NumberToString(long long int Number);
  void setPath(std::string location);
private:
  std::string path;
};

void Capture_images::setPath(std::string location){
  path = location;
}

static long long int number = 0;
std::string Capture_images::NumberToString ( long long int Number )
  {
     std::ostringstream ss;
     ss << Number;
     return ss.str();
  }

void Capture_images::capture_image(Mat& imL, long sec, long nsec, std::string frame)
{
    //store images
    std::string t1, t2, tf1;
    std::string temp1, temp2;
    temp1 = NumberToString(sec);
    temp2 = NumberToString(nsec);
    //t1 = "/home/ashwath/PycharmProjects/deep_sort/preprocessing/images/";
    t1 = path;
    t2 = ".png";
    tf1 = t1 + frame + temp1 + temp2 + t2;
    number++;
    imwrite(tf1, imL);
}
 
void Capture_images::callback(const sensor_msgs::ImageConstPtr& left) {
  // conversion to rosmsgs::Image to cv::Mat using cv_bridge
  std_msgs::Header h = left->header;
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
  ROS_INFO("Enterd Callback");
  capture_image(cv_left->image, h.stamp.sec, h.stamp.nsec, h.frame_id);
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "image_listener");
  ros::NodeHandle nh("~");
  image_transport::ImageTransport it(nh);
  std::string input_topic, paths;
  nh.getParam("input_topic", input_topic);
  nh.getParam("save_dir",paths);
  Capture_images capture;
  capture.setPath(paths);
  image_transport::Subscriber sub = it.subscribe(input_topic, 1, &Capture_images::callback, &capture);
  ros::spin();
}
