# ros2_example
[](https://img.shields.io/github/repo-size/YumaMatsumura/ros2_example)
[](https://img.shields.io/github/last-commit/YumaMatsumura/ros2_example)
[![BuildAndTest](https://github.com/YumaMatsumura/ros2_example/actions/workflows/build.yml)](https://img.shields.io/github/actions/workflow/status/YumaMatsumura/ros2_example/build.yml)

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
