========================================================================
    STATIC LIBRARY : MyEngine Project Overview
========================================================================

MyEngine.vcxproj
    This is the main project file for VC++ projects generated using an Application Wizard.
    It contains information about the version of Visual C++ that generated the file, and
    information about the platforms, configurations, and project features selected with the
    Application Wizard.

MyEngine.vcxproj.filters
    This is the filters file for VC++ projects generated using an Application Wizard. 
    It contains information about the association between the files in your project 
    and the filters. This association is used in the IDE to show grouping of files with
    similar extensions under a specific node (for e.g. ".cpp" files are associated with the
    "Source Files" filter).

/////////////////////////////////////////////////////////////////////////////
Other notes:

Every module of this project is wrapped inside the "MyEngine" namespace.

Module included:
=>MyEngine

=>FatalErrors
=>GLSLProgram
=>ImageLoader
=>IOManager
=>picoPNG
=>Sprite
//A wrapper class that ONLY
=>ResourceManager
//This data structure loads and catches the texture files. It should NOT be used by itself.
//It is only included by Resource Manager to wrap the functionality.
=>TextureCache
//The data structure for each window
=>Window

*************************************************
*************************************************
*************************************************
*********Header File Only************************
*************************************************
*************************************************
*************************************************

=>GLTexture
//the data structure for each texture.
=>Vertex.h 
//the data structure for each vertice.
/////////////////////////////////////////////////////////////////////////////
