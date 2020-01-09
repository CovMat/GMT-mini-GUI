# GMT-mini-GUI

## 下载地址

https://github.com/CovMat/GMT-mini-GUI/releases

## 注意事项

### GMT

使用本工具前请先在您的系统中安装好GMT，版本最低要求为5.4。
安装指南：https://docs.gmt-china.org/6.0/install/ （6.0版）、https://docs.gmt-china.org/5.4/install/ （5.4版）

### Ghostscript

为了保证GMT的psconvert正常运行，生成本工具需要的预览图片，用户需要安装Ghostscript。
一般来说，如果按照上面给出的GMT安装指南完整安装的话，用户的系统中已经安装好了Ghostscript。如果没安装Ghostscript，请参照GMT安装指南安装对应系统的Ghostscript。

## 运行方法

### windows

下载安装包，解压，直接双击运行exe即可。

### Linux

下载安装包，解压，打开终端进入文件夹，终端运行 `./GMT-GUI`。
如果不从终端运行的话（例如直接双击运行），无法继承环境变量PATH，会出现找不到GMT路径的错误。

### macOS

下载安装包并解压，打开终端，执行:

```
./GMT-GUI.app/Contents/MacOS/GMT-GUI
```
如果不从终端运行的话（例如直接双击运行），无法继承环境变量PATH，会出现找不到GMT路径的错误。

## 致谢

感谢[@SeisSpath](https://github.com/SeisSpath)协助编译了Linux版本，[@seisman](https://github.com/seisman)、[@core-man](https://github.com/core-man)、[@SeisPider](https://github.com/SeisPider)编译了MacOS版本，并进行了大量测试，给出了修改意见。感谢@yjmzj为软件修改提出的宝贵意见。
