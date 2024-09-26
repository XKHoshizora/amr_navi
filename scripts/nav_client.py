#!/usr/bin/env python3
#coding=utf-8

import rospy
import actionlib
from move_base_msgs.msg import MoveBaseAction, MoveBaseGoal


if __name__ == "__main__":
    # 初始化 ROS 节点
    rospy.init_node('nav_client')

    # 创建 Action 客户端对象 action_client
    # 第一个参数是要连接的 Action Server 的名字
    # 当第二个参数为 true 时，会在通讯过程中自动阻塞，等待 Action Server 的返回结果
    action_client = actionlib.SimpleActionClient('move_base', MoveBaseAction)

    # 等待 move_base 的导航服务启动
    action_client.wait_for_server()

    goal = MoveBaseGoal()  # 定义导航消息包对象 goal
    goal.target_pose.header.frame_id = "map"  # 导航点基准坐标系为 map，在某些应用中使用 base_link、base_footprint 坐标系会更加方便
                                               # 地图坐标系 map 是以机器人进行 SLAM 建图时，
                                               # 出发的位置为原点，机器人的初始坐标轴为地图坐标轴的坐标系
    goal.target_pose.header.stamp = rospy.get_rostime()  # 打上时间戳

    goal.target_pose.pose.position.x = -3.0  # 导航点的 x 坐标数值
    goal.target_pose.pose.position.y = 2.0  # 导航点的 y 坐标数值
    goal.target_pose.pose.position.z = 0.0  # 导航点的 z 坐标数值
    
    goal.target_pose.pose.orientation.x = 0.0  # 导航点的目标姿态 x
    goal.target_pose.pose.orientation.y = 0.0  # 导航点的目标姿态 y
    goal.target_pose.pose.orientation.z = 0.0  # 导航点的目标姿态 z
    goal.target_pose.pose.orientation.w = 1.0  # 导航点的目标姿态 w

    # 将消息包发送给 Action Server，此处为 move_base
    rospy.loginfo("Sending goal...")
    action_client.send_goal(goal)

    # 等待导航的结果
    rospy.loginfo("Waiting for feedback...")
    action_client.wait_for_result()

    # 收到结果之后使用 action_client.get_state() 查询 move_base 返回的状态
    if action_client.get_state() == actionlib.GoalStatus.SUCCEEDED:
        # 成功到达导航点
        rospy.loginfo("Mission complete!")
    else:
        # 导航失败
        rospy.loginfo("Mission failed...")