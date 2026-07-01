# videoCapture

基于 Qt Widgets、FFmpeg 和 OpenCV 的桌面视频录制软件。项目包含采集、解码、滤镜、编码、复用、渲染、事件队列和 UI 等模块，可作为学习 Qt + FFmpeg/OpenCV 音视频处理流程的示例工程。

## 项目来源

本项目基于 `liuhangAntonio/videoCapture` 修改而来。

- 原项目地址：https://gitee.com/liuhangantonio/videoCapture
- 原项目许可证：GPL-2.0
- 当前仓库用途：保存本人在原项目基础上的学习、适配和少量修改

本仓库保留原项目的 GPL-2.0 许可证要求。若你继续分发、修改或发布本项目，请继续遵守 GPL-2.0。

## 功能概览

- Qt Widgets 桌面界面
- FFmpeg 音视频采集、解码、编码、封装流程
- OpenGL 视频渲染
- OpenCV 视频帧处理能力
- 事件队列和多线程处理
- 录制控制、开始/暂停/停止等基础交互

## 目录结构

```text
videoCapture/
├─ capture/       采集上下文与工具
├─ clock/         全局时钟
├─ decoder/       音视频解码
├─ demuxer/       解复用
├─ encoder/       音视频编码
├─ event/         播放/录制事件
├─ filter/        音视频滤镜
├─ image/         界面图标资源
├─ muxer/         复用封装
├─ opencv/        OpenCV 处理模块
├─ opengl/        OpenGL 渲染控件
├─ player/        播放上下文
├─ queue/         包/帧/事件队列
├─ render/        音视频渲染
├─ resampler/     音视频重采样
├─ shaderSource/  OpenGL shader
├─ thread/        工作线程
├─ timer/         定时器
├─ ui/            Qt 界面
├─ image.qrc      Qt 资源文件
├─ videoCapture.pro
└─ main.cpp
```

## 依赖环境

推荐环境：

- Windows
- Qt 5.x Widgets
- MinGW 64-bit 工具链
- FFmpeg 开发库
- OpenCV 开发库

当前 `videoCapture.pro` 默认使用如下本地依赖目录：

```text
3rdparty/ffmpeg-amf/include
3rdparty/ffmpeg-amf/lib
3rdparty/opencv/include
3rdparty/opencv/lib
```

为了避免 GitHub 仓库过大，也避免提交本机二进制依赖，本仓库没有提交 `3rdparty/` 和 `include/` 目录。你 clone 后需要自己准备这些依赖。

## 准备第三方依赖

在项目根目录创建目录：

```text
3rdparty/
├─ ffmpeg-amf/
│  ├─ include/
│  └─ lib/
└─ opencv/
   ├─ include/
   └─ lib/
```

然后放入对应的 FFmpeg/OpenCV 头文件和 MinGW 可链接库。

如果你的依赖路径不同，修改 `videoCapture.pro` 里的这些配置：

```qmake
LIBS += -L$$PWD\3rdparty\ffmpeg-amf\lib
LIBS += $$PWD\3rdparty\opencv\lib\libopencv_*.a

INCLUDEPATH += $$PWD/3rdparty/opencv/include
INCLUDEPATH += $$PWD/3rdparty/ffmpeg-amf/include
```

运行时还需要确保相关 DLL 能被程序找到。常见做法：

- 将 FFmpeg/OpenCV DLL 放到生成的 `videoCapture.exe` 同目录；或
- 将 DLL 所在目录加入系统 `PATH`。

## 构建步骤

1. 安装 Qt Creator 和 Qt 5.x MinGW Kit。
2. 准备 FFmpeg/OpenCV 开发库，并按上面的目录结构放入 `3rdparty/`。
3. 使用 Qt Creator 打开 `videoCapture.pro`。
4. 选择 Desktop Qt MinGW 64-bit Kit。
5. 执行 qmake。
6. 构建项目。
7. 运行生成的 `videoCapture.exe`。

也可以在命令行中构建，路径按你的 Qt 安装位置调整：

```powershell
cd path\to\videoCapture
qmake videoCapture.pro
mingw32-make
```

## 使用说明

1. 启动程序。
2. 在界面中选择输入源或录制模式。
3. 点击开始按钮启动采集/录制。
4. 可通过暂停、停止按钮控制录制流程。
5. 输出文件位置和格式取决于程序当前配置与源码中的封装参数。

如果运行后没有画面或启动失败，优先检查：

- FFmpeg/OpenCV DLL 是否在 exe 同目录或 PATH 中；
- `videoCapture.pro` 中的 include/lib 路径是否正确；
- Qt Kit 是否和第三方库架构一致，比如都为 MinGW 64-bit；
- 摄像头/麦克风/桌面采集权限是否正常。

## GitHub 上传说明

本仓库通过 `.gitignore` 排除了本机文件和大体积依赖：

- `build/`
- `.qtcreator/`
- `*.pro.user`
- `*.exe`、`*.dll`、`*.o` 等构建产物
- 常见录屏输出视频文件
- `3rdparty/`
- `include/`

因此 GitHub 上保存的是项目源码和说明文档，不包含本机编译出来的程序，也不包含第三方 SDK 整包。

## 常见问题

### 1. 为什么 clone 后不能直接编译？

因为没有提交 `3rdparty/` 依赖目录。请先准备 FFmpeg/OpenCV 开发库，或修改 `videoCapture.pro` 指向你本机已有的依赖路径。

### 2. 为什么链接时报 `cannot find -lavcodec`？

说明 FFmpeg lib 路径不正确，或库文件名称/工具链不匹配。检查：

```qmake
LIBS += -L$$PWD\3rdparty\ffmpeg-amf\lib
```

并确认该目录下存在 MinGW 可链接的 `libavcodec` 等库。

### 3. 为什么运行时报 DLL 缺失？

编译能通过只代表链接库找到了。运行时还需要 DLL。把 FFmpeg/OpenCV 的 DLL 放到 exe 同目录，或加入 PATH。

### 4. 为什么不提交第三方库？

FFmpeg/OpenCV 依赖体积较大，且二进制发布涉及各自许可证和平台差异。公开仓库保留源码更清爽，也更适合 GitHub。

## License

本项目基于原 GPL-2.0 项目修改，继续遵循 GPL-2.0 许可证。详见 `LICENSE`。
