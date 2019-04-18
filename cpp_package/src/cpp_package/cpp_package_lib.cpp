#include "../../include/cpp_class.hpp"
namespace cpp_package {

wrapper::wrapper()
: viewer("Simple Cloud Viewer") 
{

//    typedef message_filters::sync_policies::ApproximateTime<pointCloud, Ima> MySyncPolicy;
//    message_filters::Synchronizer<MySyncPolicy> sync(MySyncPolicy(10),*interface_.lidar_subscriber, *interface_.left_image_subscriber);
    message_filters::Subscriber<Ima> left_image_subscriber;
    message_filters::Subscriber<Ima> right_image_subscriber;
    message_filters::Subscriber<pointCloud> lidar_subscriber;
    typedef message_filters::sync_policies::ApproximateTime<Ima, Ima, pointCloud> MySyncPolicy;
    message_filters::Synchronizer<MySyncPolicy> sync(MySyncPolicy(10),left_image_subscriber
                                                                     ,right_image_subscriber
                                                                     ,lidar_subscriber
    );
    sync.registerCallback(boost::bind(& wrapper::callbackSubscriber, this, _1, _2, _3));

}
void wrapper::callbackSubscriber(const Ima::ConstPtr& Imageleft
                                           ,const Ima::ConstPtr& Imageright
                                           ,const sensor_msgs::PointCloud2ConstPtr& msginputcloud
                                          ){
    std::cout << "\nPreprocessing Started "   << std::endl;
    std::cout << "height:" << msginputcloud->height << std::endl;
    std::cout << "width:"  << msginputcloud->width  << std::endl;

    std::cout << "is_bigendian:"  << msginputcloud->is_bigendian  << std::endl;
    std::cout << "point_step:"    << msginputcloud->point_step    << std::endl;
    std::cout << "row_step:"      << msginputcloud->row_step      << std::endl;
    std::cout << "is_dense:"      << msginputcloud->is_dense      << std::endl;

    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZ>);
    pcl::fromROSMsg (*msginputcloud, *cloud);
//    viewer.showCloud (cloud);

    // do your stuff here...
//    Msg::Ptr newMsg = boost::make_shared<Msg>(*msg);
//    interface_.dummy_publisher.publish(newMsg);
}

} // namespace pcsskit_ros_tool
