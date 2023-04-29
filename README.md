# ros2_example
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
