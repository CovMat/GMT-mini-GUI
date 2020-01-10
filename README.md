# GMT-mini-GUI

[![GitHub](https://img.shields.io/github/license/CovMat/GMT-mini-GUI)](https://github.com/CovMat/GMT-mini-GUI/blob/master/LICENSE)
[![Build Status](https://travis-ci.org/CovMat/GMT-mini-GUI.svg?branch=master)](https://travis-ci.org/CovMat/GMT-mini-GUI)
[![GitHub release (latest by date)](https://img.shields.io/github/v/release/CovMat/GMT-mini-GUI)](https://github.com/CovMat/GMT-mini-GUI/releases)

## 下载地址

https://github.com/CovMat/GMT-mini-GUI/releases

## 注意事项

### GMT

使用本工具前请先在您的系统中安装好GMT，版本最低要求为5.4。
安装指南：https://docs.gmt-china.org/6.0/install/ （6.0版）、https://docs.gmt-china.org/5.4/install/ （5.4版）

### Ghostscript

为了保证GMT的psconvert正常运行，生成本工具需要的预览图片，用户需要安装Ghostscript。

Windows平台的最新版Ghostscript下载地址为：https://www.ghostscript.com/download/gsdnld.html
Linux平台建议使用自带的软件仓库工具升级Ghostscript。
Mac用户请参考社区指南安装Ghostscript：https://docs.gmt-china.org/6.0/install/macOS/#homebrew

## 运行方法

### Windows

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

## 编译指南

### Windows

TBD。

注意：在windows下编译时，请使用MinGW作为Qt creator的编译工具。

### Linux

TBD。

注意：Linux下部分发行版的系统在使用Qt 5.14时会出现与QColor有关的编译错误，如果出现这种情况请卸载安装Qt 5.13。

### macOS

macOS下需要安装 Xcode Command Line Tools 和 Qt。

若你是Homebrew用户，则你已经安装了 Xcode Command Line Tools。执行如下命令以安装Qt:
```
brew install qt
```

安装完成后，向 `~/.bash_profile` 中加入如下语句将Qt添加到PATH路径中：
```
export PATH="/usr/local/opt/qt/bin:$PATH"
```

终端执行如下命令则会编译该项目：
```
make build
```
生成的可执行程序位于 `build/GMT-GUI.app/Contents/MacOS/GMT-GUI`.


## 致谢

感谢[@SeisSpath](https://github.com/SeisSpath)协助编译了Linux版本，[@seisman](https://github.com/seisman)、[@core-man](https://github.com/core-man)、[@SeisPider](https://github.com/SeisPider)、[@Seisboy](https://github.com/Seisboy)编译了MacOS版本，并进行了大量测试，给出了修改意见。感谢@yjmzj为软件修改提出的宝贵意见。

## 许可协议

本项目使用 [MIT license](LICENSE) 许可协议。