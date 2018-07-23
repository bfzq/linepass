#  LINEPASS
一款内部使用的密码管理工具，可以应用在家庭，公司以及个人场景。

## 客户端
语法列表:
show all 
show xxx 
put

```
./linepass --connect-port=8088 --connect-host=127.0.0.1 --connect-user=admin --connect-password=admin
```

```
./linepassd --listen-port=8088 --pool-num=8 --mysql-port=3306 --mysql-host=127.0.0.1 --mysql-user=root --mysql-passwd=root --mysql-db=linepass
```
