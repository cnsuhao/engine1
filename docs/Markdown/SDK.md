Software Development Kit {#SDK}
========================

The Software Development Kit (SDK) is part of the code base and will be built along with the engine.
The engine is a set of static libraries you link into your application.
The SDK is a set of file you will need in order to develop software with the engine
-   Headers needed by applications integrating the engine
  - Located in the build/install/include directory
-   Library files to link your application against
  - Located in the build/install/lib directory

Along with these files, there is a seperate executable projet that provids examples of using the engine.
There are sample C++ methods as well as Java methods that can be compiled and executed to demonstrate how to use the API. 
To execute the C++ examples, simply run the HowTo project from the bin directory.
Each cpp and java file is well-commented and should help explain how and why one would exercise functionality.

The engine functionality is exposed via the @ref physeng.<br>
All data necessary to interact with the engine is via @ref CDM classes. 

