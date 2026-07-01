# videoCapture

基于 Qt、FFmpeg 和 OpenCV 的视频录制软件。

## 项目来源

本项目基于 liuhangAntonio/videoCapture 修改而来。

- 原项目地址：https://gitee.com/liuhangantonio/videoCapture
- 原项目许可证：GPL-2.0
- 当前仓库用途：保存本人在原项目基础上的学习、适配和少量修改

本项目保留原项目许可证要求。若你继续分发或修改本项目，请遵守 GPL-2.0 许可证。

## 隐私与上传说明

仓库不应提交本机 IDE 配置、构建产物、可执行文件、录屏输出文件或本机依赖库二进制文件。

已通过 `.gitignore` 排除：

- `build/`
- `.qtcreator/`
- `*.pro.user`
- `*.exe`、`*.dll`、`*.o` 等构建产物
- 常见视频输出文件
- `3rdparty/**/bin/`、`3rdparty/**/lib/` 等本机第三方二进制库目录

## 依赖说明

项目源码引用 FFmpeg/OpenCV 相关头文件和库文件。由于第三方二进制依赖体积较大，且不同平台路径不同，上传到 GitHub 时不提交本机编译产物和二进制库。

如果需要在新机器上构建，请准备对应版本的 FFmpeg/OpenCV/Qt 环境，并按 `videoCapture.pro` 中的路径配置调整 `INCLUDEPATH` 和 `LIBS`。

## 构建方式

1. 使用 Qt Creator 打开 `videoCapture.pro`。
2. 配置 Qt 5.x MinGW 或兼容工具链。
3. 准备 FFmpeg/OpenCV 依赖。
4. 构建并运行。

## License

This project is distributed under the GNU General Public License v2.0. See `LICENSE` for details.
