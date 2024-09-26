#include <ros/ros.h>
#include <std_msgs/String.h>

// 接收到导航结果话题消息后的回调函数
void NavResultCallback(const std_msgs::String &msg) {
    ROS_WARN("[NavResultCallback] %s", msg.data.c_str());
}

int main(int argc, char** argv){
    // 初始化 ROS 节点
    ros::init(argc, argv, "wp_node");

    // 设置节点句柄
    ros::NodeHandle nh;

    // 创建一个发布节点，将航标发布到 /waterplus/navi_waypoint 话题
    ros::Publisher nav_pub = nh.advertise<std_msgs::String>("/waterplus/navi_waypoint", 10);
    // 创建一个订阅节点，订阅来自 /waterplus/navi_result 话题的导航结果消息
    ros::Subscriber res_sub = nh.subscribe("/waterplus/navi_result", 10,  NavResultCallback);

    sleep(1);  // sleep for 1 second

    // 创建一个航标对象
    std_msgs::String nav_msg;
    nav_msg.data = "1";  // 设置航标
    // nav_msg.data = "2";
    // nav_msg.data = "3";
    // nav_msg.data = "4";
    nav_pub.publish(nav_msg);  // 发布 nav_msg 到 /waterplus/navi_waypoint 话题

    ros::spin();  // 保持节点运行

    return 0;
}