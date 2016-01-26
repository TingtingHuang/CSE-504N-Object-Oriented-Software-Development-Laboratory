Name: Tingting Huang
Lab number: lab0

////////////////////////////////////////////////////////////////////////////
Error/warning Messages:
1. cannot open the test file
solution: after reading the treads on blackboard, I changed the directory of the test file to "Debug" file.
 
2. warning C4018: '<' : signed/unsigned mismatch at line: for (int j = 0; j < str.length(); j++)
solution: for (unsigned int j = 0; j < str.length(); j++)

////////////////////////////////////////////////////////////////////////////
Executable cases:
1. For regular .txt trails, the command line is:
	H:\My Documents\Visual Studio 2013\Projects\Debug>lab0.exe input_file.txt
The program prints all the strings with non-numeric characters and then all integers in different lines. 
The return code: 0

2. For nonexistent .txt trials, the command line is:
	H:\My Documents\Visual Studio 2013\Projects\Debug>lab0.exe noinput.txt
The program prints an error message: couldn't open: noinput.txt
The return code: -1

3. For more that one .txt arguments, the command line is:
	H:\My Documents\Visual Studio 2013\Projects\Debug>lab0.exe input_file.txt input.txt
The program prints: usage: lab0.exe <input_file_name>
The return code: -1

========================================================================
    CONSOLE APPLICATION : lab0 Project Overview
========================================================================

AppWizard has created this lab0 application for you.

This file contains a summary of what you will find in each of the files that
make up your lab0 application.


lab0.vcxproj
    This is the main project file for VC++ projects generated using an Application Wizard.
    It contains information about the version of Visual C++ that generated the file, and
    information about the platforms, configurations, and project features selected with the
    Application Wizard.

lab0.vcxproj.filters
    This is the filters file for VC++ projects generated using an Application Wizard. 
    It contains information about the association between the files in your project 
    and the filters. This association is used in the IDE to show grouping of files with
    similar extensions under a specific node (for e.g. ".cpp" files are associated with the
    "Source Files" filter).

lab0.cpp
    This is the main application source file.

/////////////////////////////////////////////////////////////////////////////
Other standard files:

StdAfx.h, StdAfx.cpp
    These files are used to build a precompiled header (PCH) file
    named lab0.pch and a precompiled types file named StdAfx.obj.

/////////////////////////////////////////////////////////////////////////////
Other notes:

AppWizard uses "TODO:" comments to indicate parts of the source code you
should add to or customize.

/////////////////////////////////////////////////////////////////////////////
