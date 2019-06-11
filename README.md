
繪圖技術設計與應用FinalProject
============
作業環境
===
Windows 10, visual studio 15 2017 Win64

方法說明
====

#### Requirement
1. cmake 
[install here](https://cmake.org/download/)
2. conan - package manager (windows)
[install here](https://conan.io/)

安裝完後開啟CMD
```bash
set PATH="C:\Program File\CMake\bin\";%PATH%
```
找**全英文**的路徑clone個
```bash
git clone https://github.com/genius92606/simple-3D-software.git
```
 #### 進入資料夾後
```bash
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

#### 執行
```bash
cd build
start bin\app.exe
```
程式如何運行
==

### File dialog
使用ImGui建立簡單的檔案總管系統，讓使用者可以很簡單的讀取檔案


### class
用來管理讀進來的Mesh以及Texture

### Struct
記錄所有物體的所有資訊

### 滾輪放大縮小以及改變視角
滑動滾輪可以ZOOM, 壓住滾輪移動可以改變視角


程式如何操作
==

1. 開啟執行檔後
```bash
cd build
start bin\app.exe
```
2. 按左邊的下拉選單後按"add"新增內建好的物件或是按右邊的"Load obj"來讀取物件
![](https://i.imgur.com/IhAxQ4V.png)
3. 如選擇"Load obj"則會跳出檔案總管
![](https://i.imgur.com/qK1QTp2.png)
右下角可以選擇想開啟的檔案格式
4. 新增好後原本的視窗會多出以下欄位
![](https://i.imgur.com/YrwHcA6.png)
可以更改物件的color, translate, rotation, scale
如不要內建的顏色，則可以按"Load Texture"讀取貼圖
5. 滑鼠滾輪按住後移動可以改變視角
6. 滑鼠滾輪可以ZOOM
7. 有添加基本的 abmient, diffuse, specular~



相關連結
==
[HackMD](https://hackmd.io/@u1E-qvfkRYmDU27hS1T6cA/HkI7sX2RE)
[GitHub](https://github.com/genius92606/simple-3D-software)
[PPT](https://github.com/genius92606/simple-3D-software/blob/master/Final%20project.pptx)
[PDF](https://github.com/genius92606/simple-3D-software/blob/master/Final%20project.pdf)
[Youtube]()


Thirdparty
==
1. GLFW3
2. ImGui


DEMO
==
![](https://i.imgur.com/cAVJojI.gif)