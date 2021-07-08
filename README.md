# DirectX 11 c++ Engine
<p>
Visualization of 3D scenes through the DirectX graphics pipeline. <br>
The purpose of this project was for me to learn more about DirectX and computer graphics in general.
</p>

Implementation:
- Windows application implemented with the WINAPI interface
- The graphics pipeline is done with the DirectX 11 library
- GUI is implemented with the [ImGUI](https://github.com/ocornut/imgui) library

Functionality:
- Normal Map Shaders
- Specular Map Shaders
- Color Shaders
- Object transformations (translation, rotation, scale)
- Global light
- Importing simple predefined shapes


![Engine](https://user-images.githubusercontent.com/62693918/124922016-56bcda00-dff9-11eb-8f3e-678ab115d331.png)


Notes:
- The scene is rendered on a Texture Resource that is displayed in the ImGUI Scene window.
- Models are converted from .obj files to special .txt files that the program can read. Multiple models are included in the project itself.

Credits:
- Project setup is done with the help of [RasterTek](https://www.rastertek.com/tutdx11.html) tutorials
