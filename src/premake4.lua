#!lua

-- A solution contains projects, and defines the available configurations
solution "rae_render"
   configurations { "Debug", "Release" }
   platforms {"native", "x64", "x32"}

   -- A project defines one build target
   project "rae_render"
      kind "ConsoleApp"
      language "C++"
      targetdir "../bin/"
      files { "rae/**.hpp", "rae/**.cpp" }
      includedirs { "external/glew/include", "external/glfw/include", "external/nanovg/src", "external/glm", "external/glm/glm", "rae", "external/" }
      links {"glfw3", "glew", "nanovg", "assimp"}
      defines { "GLEW_STATIC", "NANOVG_GLEW" }

      configuration { "linux" }
         buildoptions { "-std=c++11" }
         links {"X11","Xrandr", "Xxf86vm", "Xinerama", "Xcursor", "rt", "GL", "GLU", "pthread"}
       
      configuration { "windows" }
         links {"glu32","opengl32", "gdi32", "winmm", "user32"}

      configuration { "macosx" }
         buildoptions { "-std=c++11 -stdlib=libc++" }
         linkoptions { "-stdlib=libc++", "-framework OpenGL", "-framework Cocoa", "-framework IOKit", "-framework CoreVideo" }

      configuration "Debug"
         defines { "DEBUG" }
         flags { "Symbols" }
         debugdir "../bin/"

      configuration "Release"
         defines { "NDEBUG" }
         flags { "Optimize" }
         debugdir "../bin/"

   -- GLFW Library
   project "glfw3"
      kind "StaticLib"
      language "C"
      targetdir "../lib"
      files { "external/glfw/lib/*.h", "external/glfw/lib/*.c", "external/glfw/include/GL/glfw.h" }
      includedirs { "external/glfw/lib", "external/glfw/include"}

      configuration {"linux"}
         files { "external/glfw/lib/x11/*.c", "external/glfw/x11/*.h" }
         includedirs { "external/glfw/lib/x11" }
         targetdir "../lib_linux"
         defines { "_GLFW_X11", "_GLFW_USE_LINUX_JOYSTICKS", "_GLFW_HAS_XRANDR", "_GLFW_HAS_PTHREAD" ,"_GLFW_HAS_SCHED_YIELD", "_GLFW_HAS_GLXGETPROCADDRESS" }
         buildoptions { "-pthread" }
       
      configuration {"windows"}
         files { "external/glfw/src/*.c", "external/glfw/src/*.h" }
         includedirs { "external/glfw/src" }
         defines { "_GLFW_EGL", "_GLFW_WIN32", "_GLFW_USE_OPENGL" }
       
      configuration {"Macosx"}
         files { "external/glfw/lib/cocoa/*.c", "external/glfw/lib/cocoa/*.h", "external/glfw/lib/cocoa/*.m" }
         includedirs { "external/glfw/lib/cocoa" }
         defines { "_GLFW_COCOA" }
         buildoptions { " -fno-common" }
         linkoptions { "-framework OpenGL", "-framework Cocoa", "-framework IOKit" }

      configuration "Debug"
         defines { "DEBUG" }
         flags { "Symbols", "ExtraWarnings" }

      configuration "Release"
         defines { "NDEBUG" }
         flags { "Optimize", "ExtraWarnings" }    

   -- GLEW Library         
   project "glew"
      kind "StaticLib"
      language "C"
      targetdir "../lib"
      files {"external/glew/*.c", "external/glew/*.h"}
      defines { "GLEW_STATIC" }

      configuration {"linux"}
         targetdir "../lib_linux"

      configuration "Debug"
         defines { "DEBUG" }
         flags { "Symbols", "ExtraWarnings" }

      configuration "Release"
         defines { "NDEBUG" }
         flags { "Optimize", "ExtraWarnings" }

   -- NanoVG Library
   project "nanovg"
      language "C"
      kind "StaticLib"
      includedirs { "external/nanovg/src" }
      files { "external/nanovg/src/*.c" }
      targetdir("../lib")
      defines { "_CRT_SECURE_NO_WARNINGS", "GLEW_STATIC" } --,"FONS_USE_FREETYPE" } Uncomment to compile with FreeType support

      configuration {"linux"}
         targetdir "../lib_linux"
      
      configuration "Debug"
         defines { "DEBUG" }
         flags { "Symbols", "ExtraWarnings"}

      configuration "Release"
         defines { "NDEBUG" }
         flags { "Optimize", "ExtraWarnings"}

   -- Assimp library
   project "assimp"
      kind "SharedLib"
      language "C"
      targetdir "../lib"
      files {"external/assimp/*.c", "external/assimp/*.h"}
      
      configuration {"linux"}
         targetdir "../lib_linux"

      configuration "Debug"
         defines { "DEBUG" }
         flags { "Symbols", "ExtraWarnings" }

      configuration "Release"
         defines { "NDEBUG" }
         flags { "Optimize", "ExtraWarnings" }

