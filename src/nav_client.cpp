#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>  // MoveBaseAction 的消息包格式
#include <actionlib/client/simple_action_client.h>  // 以简单的 Action 客户端为例

// Action 客户端的声明，并设置别名 MoveBaseClient
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

int main(int argc, char** argv){

    // 初始化 ROS 节点
    ros::init(argc, argv, "nav_client");

    // 使用别名创建 Action 客户端对象 action_client
    // 第一个参数是要连接的 Action Server 的名字
    // 当第二个参数为 true 时，会在通讯过程中自动阻塞，等待 Action Server 的返回结果
    MoveBaseClient action_client("move_base", true);

    // 等待 move_base 的导航服务启动
    // 使用 action_client.waitForServer() 函数查询服务的状态
    // ros::Duration() 函数的参数表示等待服务启动的时间，单位：秒
    while(!action_client.waitForServer(ros::Duration(5.0))){
        ROS_INFO("Waiting for the move_base action server to come up...");
    }

    move_base_msgs::MoveBaseGoal goal;  // 定义导航消息包对象 goal
    goal.target_pose.header.frame_id = "map";  // 导航点基准坐标系为 map，在某些应用中使用 base_link、base_footprint 坐标系会更加方便
                                               // 地图坐标系 map 是以机器人进行 SLAM 建图时，
                                               // 出发的位置为原点，机器人的初始坐标轴为地图坐标轴的坐标系
    goal.target_pose.header.stamp = ros::Time::now();  // 打上时间戳

    goal.target_pose.pose.position.x = -3.0;  // 导航点的 x 坐标数值
    goal.target_pose.pose.position.y = 2.0;  // 导航点的 y 坐标数值
    
    goal.target_pose.pose.orientation.w = 1.0;  // 导航点的目标姿态 w

    // 将消息包发送给 Action Server，此处为 move_base
    ROS_INFO("Sending goal...");
    action_client.sendGoal(goal);

    // 等待导航的结果
    ROS_INFO("Waiting for feedback...");
    action_client.waitForResult();

    // 收到结果之后使用 action_client.getStatus() 查询 move_base 返回的状态
    if (action_client.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
        // 成功到达导航点
        ROS_INFO("Mission complete!");
    else
        // 导航失败
        ROS_INFO("Mission failed...");

    return 0;
}