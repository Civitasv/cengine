# How to use ImGui

> Dear ImGui: Bloat-free Graphical User interface for C++ with minimal dependencies
> Source Link: <https://github.com/ocornut/imgui>

ImGui 是 C++ 的 GUI 库，本文对其基本使用进行总结。

## 设计哲学

ImGui 没有任何外部依赖，是面向 C++ 的轻量级 GUI 库，其主要用于原型设计、调试、可视化等工具的开发。

也正因此，它会缺少一些 GUI 库的常见功能。

## 使用

ImGui 的核心文件处在仓库的根目录 (imgui*.cpp, imgui*.h)。

ImGui 的后端处在 `backends` 目录。

### 一个简单的例子

```cpp
ImGui::Text("Hello, world %d", 123);
if (ImGui::Button("Save"))
    MySaveFunction();
ImGui::InputText("string", buf, IM_ARRAYSIZE(buf));
ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
```

![ImGui 例子](./images/2023-04-03-21-09-57.png)

## backends

<https://github.com/ocornut/imgui/blob/master/docs/BACKENDS.md>

在 Cazel 中，我们使用的是 OpenGL3 渲染后端，但在窗口管理、事件输出等方面，我们采用的是自定义 Platform 后端，特别的，我们的后端是对 GLFW 的封装。
