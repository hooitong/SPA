##CS3202 15/16 Sem 1 Team 3 

Static Program Analyser (SPA)
###Description
This is a C++ project to develop a SPA tool to parse SIMPLE source code by any programmer which will populate the underlying PKB found within the system. After initialization, the programmer can provide queries via PQL language to retrieve the required information about the source program.

###Cloning the Project
This repository currently contains all the code to the entire solution.

Cloning will provide you with all the files needed to run the solution (Do not require to download the package from IVLE)
*Due to the whole solution being clone, there might be chances that the directory settings may not be correct.
If there is error such as 
>could not open source file "TNode.h"

Right click SPA > Properties > C/C++ > General > Additonal Include Directories > select the respective directory to the source folder.

###How to Build and Test
In VS2010, check whether you want to build in debug mode or release mode. After that, proceed to build the solution. You should find the .exe in the Debug/Release folder.

Ensure that you have sample_source.txt for unit testing and integration.txt for integration testing in the same folder before you run.
For the AutoTester, follow the guide provided to pass in the source and query file and specify the output file.
