#!/usr/bin/env python3
#coding=utf-8

import rospy
from std_msgs.msg import String

# 接收到导航结果话题消息后的回调函数
def NavResultCallback(msg):
    rospy.logwarn(f"Navigation {msg.data}")


if __name__ == "__main__":
    # 初始化 ROS 节点
    rospy.init_node('wp_node')

    # 创建一个发布节点，将航标发布到 /waterplus/navi_waypoint 话题
    nav_pub = rospy.Publisher('/waterplus/navi_waypoint', String, queue_size=10)
    # 创建一个订阅节点，订阅来自 /waterplus/navi_result 话题的导航结果消息
    res_sub = rospy.Subscriber('/waterplus/navi_result', String, NavResultCallback, queue_size=10)

    rospy.sleep(1)

    # 创建一个航标对象
    nav_msg = String()
    nav_msg.data = '1'  # 设置航标
    # nav_msg.data = '2'
    # nav_msg.data = '3'
    # nav_msg.data = '4'
    nav_pub.publish(nav_msg)  # 发布 nav_msg 到 /waterplus/navi_waypoint 话题

    rospy.spin()  # 保持节点运行