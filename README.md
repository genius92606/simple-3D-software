
ø�ϧ޳N�]�p�P����FinalProject
============
�@�~����
===
Windows 10, visual studio 15 2017 Win64

��k����
====

#### Requirement
1. cmake 
[install here](https://cmake.org/download/)
2. conan - package manager (windows)
[install here](https://conan.io/)

�w�˧���}��CMD
```bash
set PATH="C:\Program File\CMake\bin\";%PATH%
```
��**���^��**�����|clone��
```bash
git clone https://github.com/genius92606/simple-3D-software.git
```
 #### �i�J��Ƨ���
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

#### ����
```bash
cd build
start bin\app.exe
```
�{���p��B��
==

### File dialog
�ϥ�ImGui�إ�²�檺�ɮ��`�ިt�ΡA���ϥΪ̥i�H��²�檺Ū���ɮ�


### class
�ΨӺ޲zŪ�i�Ӫ�Mesh�H��Texture

### Struct
�O���Ҧ����骺�Ҧ���T

### �u����j�Y�p�H�Χ��ܵ���
�ưʺu���i�HZOOM, ����u�����ʥi�H���ܵ���


�{���p��ާ@
==

1. �}�Ұ����ɫ�
```bash
cd build
start bin\app.exe
```
2. �����䪺�U�Կ����"add"�s�W���ئn������άO���k�䪺"Load obj"��Ū������
![](https://i.imgur.com/IhAxQ4V.png)
3. �p���"Load obj"�h�|���X�ɮ��`��
![](https://i.imgur.com/qK1QTp2.png)
�k�U���i�H��ܷQ�}�Ҫ��ɮ׮榡
4. �s�W�n��쥻�������|�h�X�H�U���
![](https://i.imgur.com/YrwHcA6.png)
�i�H��磌��color, translate, rotation, scale
�p���n���ت��C��A�h�i�H��"Load Texture"Ū���K��
5. �ƹ��u������Ჾ�ʥi�H���ܵ���
6. �ƹ��u���i�HZOOM
7. ���K�[�򥻪� abmient, diffuse, specular~



�����s��
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