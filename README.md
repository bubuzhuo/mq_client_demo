
# 编译方式


## 交叉编译

```
cmake -DCMAKE_TOOLCHAIN_FILE=./mtk_setup.cmake ..
```

## 容器编译

```
...
```

# 系统配置

## 开启 ntpd 网络时间同步

vi /etc/config/system

```
list server '0.lede.pool.ntp.org'
list server '1.lede.pool.ntp.org'
list server '2.lede.pool.ntp.org'
list server '3.lede.pool.ntp.org'
```



## 给rtc写入时间

```
 hwclock -w -f /dev/rtc1
 hwclock -r -f /dev/rtc1
 hwclock -s -f /dev/rtc1
```



