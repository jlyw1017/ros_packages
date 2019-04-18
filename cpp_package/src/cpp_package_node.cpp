#include "cpp_class.hpp"

int main(int argc, char* argv[]) {
    ros::init(argc, argv, "cpp_package_node");
    cpp_package::wrapper wrapper();
    ros::spin();
    return EXIT_SUCCESS;
}
