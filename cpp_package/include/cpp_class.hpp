// Messagefilter
#include <message_filters/subscriber.h>
#include <message_filters/synchronizer.h>
#include <message_filters/sync_policies/approximate_time.h>

// Messages
#include <sensor_msgs/PointCloud2.h>
#include <sensor_msgs/Image.h>

// PCL
#include <pcl_ros/point_cloud.h>
#include <pcl/visualization/cloud_viewer.h>


namespace cpp_package {

class wrapper {

    using pointCloud = sensor_msgs::PointCloud2;
    using Ima = sensor_msgs::Image;

private:
//    void callbackSubscriber(const sensor_msgs::PointCloud2ConstPtr& cloud, Ima::ConstPtr& Imagecolor);
    void callbackSubscriber(const Ima::ConstPtr& Imageleft
                           ,const Ima::ConstPtr& Imageright
                           ,const sensor_msgs::PointCloud2ConstPtr& cloud
                           );//


    pcl::visualization::CloudViewer viewer;

public:
    wrapper();

};
} 

