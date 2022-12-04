# OpenGL

## Introduction

The aim of this project is to create a (textured) Digital Terrain Model (DTM). Then, a cube is being instantiated on top of the DTM, and make it move in a circular trajectory. Finally, The user has the possibility to move on the DTM (he will stay on the DTM, he can not fly away, or sink under it, or go out on a side of the DTM). The user will move using First person controls camera.
To move:
- forward: up key
- backward: down key
- right: right key
- left: left key

## To run on Windows 64bit

This project was run on Windows. Here are the following instructions in order for it to run:

### Visual Studio set up
The link for download is [here](https://visualstudio.microsoft.com/downloads/)

### Set up of vcpkg
The steps for the set up is [here](https://vcpkg.io/en/getting-started.html)
but here are all the steps to do at the root:

```
git clone https://github.com/Microsoft/vcpkg.git
.\vcpkg\bootstrap-vcpkg.bat
vcpkg install glm:x64-windows
vcpkg install glew:x64-windows
vcpkg install glfw3:x64-windows
vcpkg integrate install
```

## What was changed from the work done in class

To generate the DTM, a class mnt was created with all the needed functions to generate it in the openGL Window.

The Object class was change to include a function for the cube to move in a circular trajectory

The main.cpp
