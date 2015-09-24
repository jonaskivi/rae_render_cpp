# rae_render_cpp
Small component based OpenGL renderer with NanoVG textures and Assimp model importing, and 3D picking shader

![ScreenShot](https://cloud.githubusercontent.com/assets/6566641/10071941/596eb9b4-62c6-11e5-8408-ef6ae295d3df.png)

# Features:

- Click on the object in the middle, and other objects will appear with an animation.
Clicking on the other objects will destroy them.
- Per pixel shading
- 3D picking via shader and glReadPixels.
- This time I tried making a component based system, instead of the more traditional object oriented.
There's just a base for a component system.
- Animatable textures with NanoVG, using frameBufferObjects.

- Move the camera with WASD and arrow keys.
- I-key will add objects, and O-key will destroy them.
- Esc to quit.

Source code is found under "src/rae". 

# Build instructions

	# on Linux (use premake4.4beta, not 4.3 which comes with Ubuntu 14.04):
    premake4 gmake
    # I had to install the GL headers:
    sudo apt-get install libgl1-mesa-dev libglu1-mesa-dev
    # I installed GLFW3 and GLEW from source, and copied the libs to the lib dir.
    # And finally:
    make
    # cd into the bin directory and run:
    ./rae_render

	# on OSX:
	premake4 xcode4
    # Open the project file and build it.
	
    # on Windows:
	premake4 vs2012
    # Open the project file and build it.
    # You may need to retarget it to vs2013 or vs2015 after opening it

Some known/TODO issues with the code:
- The component system is not very finished
- GLFW code should be separated into something like a Window class.

