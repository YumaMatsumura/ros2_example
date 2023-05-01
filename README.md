# ros2_example
![](https://img.shields.io/github/repo-size/YumaMatsumura/ros2_example)
![](https://img.shields.io/github/last-commit/YumaMatsumura/ros2_example)
[![BuildAndTest](https://img.shields.io/github/actions/workflow/status/YumaMatsumura/ros2_example/build.yml)](https://github.com/YumaMatsumura/ros2_example/actions/workflows/build.yml)

## dockerを使用する場合
1. `docker build -t ros2-example-image:v1 .`
2. `docker run --rm -it --name ros2-example-container --env ROS_DOMAIN_ID=1 ros2-example-image:v1`
3. `cd ~/ros2_ws && colcon build`
4. `source ~/.bashrc`

## example1
動的にパラメータを変更するサンプル。

### 解説
**dynamic_params_server**
- 設定されているパラメータ値をパブリッシュする。
- パラメータコールバック関数があるため、ノード起動中にパラメータを変更してもその値が反映される。

**dynamic_params_client**
- ターゲットノードのパラメータ値を動的に変更するためのサービスクライアント

### 実行手順
1. `ros2 run example1 dynamic_params_server`
2. `ros2 topic echo /params`
3. `ros2 run example1 dynamic_params_client`

## example2
メインノードの中でサブノードを作成するサンプル。  
メインにネームスペースをつけるとサブもネームスペースがつくことが確認できる。  

### 実行手順
1. `ros2 run example2 main_class --ros-args -r __ns:=/hoge`
2. `ros2 topic list`でトピック名確認
3. `ros2 node list`でノード名確認

## example3
プラグインをロードするサンプル。  
サンプルのプラグインでは、タイマー関数でstring型のデータをパブリッシュする。  

### 実行手順
1. `ros2 launch example3 load_plugin.launch.py`
2. `ros2 lifecycle set /load_plugins configure`
3. `ros2 lifecycle set /load_plugins activate`
4. `ros2 topic echo /sample`でサンプルプラグインからトピックが出ていることが確認できる。  

## example4
サブスクライブしたデータをros2 bagで保存するサンプル。  

## 実行手順
1. `ros2 run example4 bag_recorder`
2. `ros2 topic pub /sample std_msgs/msg/String "{data: 'sample'}"`
3. Ctrl+Cで保存を停止する。  
4. `cd ~/ros2_ws/src/ros2_example/example4/bag`
5. `ros2 bag play sample_bag/`
6. `ros2 topic echo /sample`でトピックが保存されていることを確認。  




