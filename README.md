#  LINEPASS
一款小型的交互式密码管理系统，需要部署服务器端和客户端。
支持多用户，网络远程存储。

**该项目处在试验阶段，问题多多**

## 客户端
语法列表:

show {all | title:xxx} 

put [title | company | account | passwd]

exit 退出客户端

### 安装
```
# make && make install
```
### 命令
客户端连接
```
linepass --line-port=8088 --line-host=127.0.0.1 --line-user=admin --line-passwd=admin
```
服务器端启动
```
linepassd --listen-port=8088 --pool-num=8 --mysql-port=3306 --mysql-host=127.0.0.1 
  --mysql-user=root --mysql-passwd=root --mysql-db=linepass
```
