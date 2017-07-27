Software Development Kit {#SDK}
========================

The Software Development Kit (SDK) contains the following:
-   The tools provided in the @ref Toolkit
-   A collection of how-to cpp files demonstrating the use of the API
-   The headers needed by applications integrating the engine
-   32-bit debug and release libraries

The extracted file structure:
<img src="./Images/GUI/SDKDir.png" alt="Software Development Kit Directory">
<br>

The code base is C++11 compliant and we have 
provided cmake configuration files for various compilers.  We currently support
the following platforms, compilers:
-   Windows Visual Studio 2015 and later(MSVC)
-   GCC 4.8.1 and later
-   Clang 3.3 and later

The @ref SourceCode is available if you would like to customize
or build the project for a different platform.

We wrote executable sample C++ as well as Java methods that can be compiled and executed to demonstrate how to use the API. 
To execute the C++ examples, simply run cmake against the CMakeLists.txt file to create the project for your complier.
Each cpp and java file is well-commented and should help explain how and why one would exercise functionality.

The engine functionality is exposed via the @ref physeng.<br>
All data necessary to interact with the engine is via @ref CDM classes. 

