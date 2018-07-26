#  LINEPASS
一款内部使用的密码管理工具，可以应用在家庭，公司以及个人场景。

## 客户端
语法列表:

show all 

show xxx 

put

exit 退出客户端

### 启动命令
```
./linepass --line-port=8088 --line-host=127.0.0.1 --line-user=admin --line-passwd=admin
```

```
./linepassd --listen-port=8088 --pool-num=8 --mysql-port=3306 --mysql-host=127.0.0.1 --mysql-user=root --mysql-passwd=root --mysql-db=linepass
```
