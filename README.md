# GUInity

GUInity is a 3D component-based game engine. It's a personal project started by myself, Guilherme Cunha.

My objectives with GUInity are:
- Study and practice C++ in a large project. It's also a way of learning new C++11 concepts.
- Get a better understanding about how game engines work under the hood
- Integrate several libraries into one software
- Develop with cross-platform in mind (currently GUInity works for both Windows and MacOS)

# Name

I chose the name GUInity because it summarizes well what I'm trying to do:
- GUI stands for Gui-lherme not for Graphical User Interface. It's mine! My precious!
- nity stands for Unity. It's the engine I have the most experience and the one that I'm using as a base for a lot of design decisions.

# Dependencies

Please note that even though I'm developing the engine from scratch, I'm also using a bunch of libraries to aid the development. For the purposes of this project, I've chosen to use, so far, the following libraries:

-PhysX (3.1.1)  Physics library developed by NVIDIA https://developer.nvidia.com/physx-sdk

-FreeType (2.4.0)  Free library for font handling fonts http://www.freetype.org/

-Boost(1.57.0)  I don't believe this set of libraries need any introduction http://www.boost.org/

-GLFW(3.0.4)  Cross-Platform library for handling window and basic OpenGL configuration http://www.glfw.org/

-libPNG  Library to handle .png files

-FBX SDK (2015.1)  Library to handle .fbx model files

-FMOD Studio (1.05.02)  Library to handle sound

Also, please note that due to possible licensing issues for the libraries, I'm not providing any of them in this repository. The benefit is that the repository is very compact.



# Goal

1 - Get to a point where it's easy to create a simple game using code, in an component-based engine that has built-in physics, graphics and audio systems.
2 - Have an editor to ease the development.

My goal is NOT to create a new and better Unity, but to understand how they were able to develop it. Unity has grown a lot over the last few years, they've been obviously been doing something right. This also supports some of my decisions, for example, I think it was very smart of them to use well tested and optimized libraries to handle critical portions of their engine, hence PhysX, FMOD, Beast, ...

# Considerations

-Creating a Game Engine is not a simple task. Instead of trying to create the most optimized engine ever, I'm just "doing" it, for now. Of course that does not mean that I'm throwing away memory and processing power, but I'm not scratching bits either. Most of the times, I aim for readability and try to experiment with new features of C++11. I've been learning a lot from this project and intend to carry it on as well as I can.
-I develop this project alongside my Master in Digital Media. This means that I don't have that much time to work on it.
