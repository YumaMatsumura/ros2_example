import os

from ament_index_python.packages import get_package_share_directory

from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, GroupAction
from launch.conditions import IfCondition
from launch.substitutions import LaunchConfiguration, PythonExpression
from launch_ros.actions import LoadComposableNodes, Node
from launch_ros.descriptions import ComposableNode

def generate_launch_description():
    container_name = LaunchConfiguration('container_name')
    use_composition = LaunchConfiguration('use_composition')
    declare_container_name_cmd = DeclareLaunchArgument(
        'container_name',
        default_value='example3_container',
        description='The name of container that nodes will load in if use composition')
    declare_use_composition_cmd = DeclareLaunchArgument(
        'use_composition',
        default_value='True',
        description='Use composed bringup if True')
        
    params_file = os.path.join(get_package_share_directory('example3'), 'params', 'params.yaml')
        
    load_nodes = GroupAction(
        condition=IfCondition(PythonExpression(['not ', use_composition])),
        actions=[
            Node(
                name='load_plugins',
                package='example3',
                executable='load_plugins',
                parameters=[params_file],
                output='screen')
            ])
            
    load_composable_nodes = GroupAction(
        condition=IfCondition(use_composition),
        actions=[
            Node(
                name=container_name,
                package='rclcpp_components',
                executable='component_container',
                output='screen'),
            
            LoadComposableNodes(
                target_container=container_name,
                composable_node_descriptions=[
                    ComposableNode(
                        name='load_plugins',
                        package='example3',
                        plugin='example3::LoadPlugins',
                        parameters=[params_file])
                    ]
                )
            ])
        
    return LaunchDescription([
        declare_container_name_cmd,
        declare_use_composition_cmd,
        load_nodes,
        load_composable_nodes])
