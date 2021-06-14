## 基于esp8266的超小型红外开机卡
## 简介
#### 使用esp8266ex芯片设计的一个远程开机卡，控制电脑开关机，并使用红外解码接入涂鸦智能，实现与其他智能家具的联动
- - -
## 板载资源介绍
#### 一颗LED，接线与ESP12模块一致
#### 一颗红外接收头，只能连ESP8266的IO14
#### 2p 2.54 排针，用于连接主板的PANEL接口
## 电路功能分析
### 「未完待续。。。」

## 注意事项：
#### PCIE板厚为1.6mm，注意不要打错厚度
#### 代码需要自行修改5行配置，有注释说明
#### 为了尽可能压缩空间，基本采用0402封装的阻容，焊接有一定难度
#### 目前暂未实现通过PCIE的#WAKE信号唤醒，查不到相关资料
- - -

#### 代码开源地址：[https://github.com/panyihang/power-card-esp8266](https://github.com/panyihang/power-card-esp8266)