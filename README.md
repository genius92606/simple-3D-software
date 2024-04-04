
Final Project
============
Operating System
===
Windows 10, visual studio 15 2017 Win64

Instructions
====

#### Requirement
1. cmake 
[install here](https://cmake.org/download/)
2. conan - package manager (windows)
[install here](https://conan.io/)

Open command prompt
```bash
set PATH="C:\Program File\CMake\bin\";%PATH%
```
Clone the repository
```bash
git clone https://github.com/genius92606/simple-3D-software.git
```
Create "build" folder in the repository
```bash
cd simple-3D-software
mkdir build && cd build

conan remote add bincrafters https://api.bintray.com/conan/bincrafters/public-conan
conan install .. --build glad -sbuild_type=Debug
```
```bash
cd build
cmake .. -G "Visual Studio 15 2017 Win64"
```

#### Build
```bash
cd build
cmake --build .
```

#### Execution
```bash
cd build
start bin\app.exe
```
How do this work?
==

### File dialog
Using ImGui to build a simple file directory system, and let the user to load file easily.


### class
Manage loaded Mesh and Texture.

### Struct
Store all the information of the subject

### Zoom and change perspective
Scroll the wheel to zoom, and change the perspective by pressing and move the wheel at the same time.


Application Instruction
==

1. Execute the application
```bash
cd build
start bin\app.exe
```
2. Click the drop down menu at the left, and click "add" to add a built-in object or click "Load obj" to read objects.
![](https://i.imgur.com/IhAxQ4V.png)
3. If you choose "Load obj", it will pop up a file directory and you can choose files from the bottom right.
![](https://i.imgur.com/qK1QTp2.png)
4. After adding new objects, the windows will add an extra section like below, you can change color, translate, rotation, scale of the object. If you don't want the built-in color, you can further loading customize textures by clicking "Load Texture"
![](https://i.imgur.com/YrwHcA6.png)
5. Holding scrolling wheel and moving to change perspective.
6. Scroll the wheel to zoom.
7. This application includes abmient, diffuse, and specular lighting.



Relative Links
==

[GitHub](https://github.com/genius92606/simple-3D-software)

[PPT](https://github.com/genius92606/simple-3D-software/blob/master/Final%20project.pptx)

[PDF](https://github.com/genius92606/simple-3D-software/blob/master/Final%20project.pdf)

[Youtube](https://youtu.be/wzsEwaMZtxY)


Thirdparty
==
1. GLFW3
2. ImGui


DEMO
==
![](https://i.imgur.com/cAVJojI.gif)
