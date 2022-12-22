# WaterMark Project

Used to put a watermark on image files.

## Description

This is a fun project to use my first passion programming, on my second drawing. 

## Getting Started

### Compiling and running

1. Get your terminal in the Watermark_Project folder
2. `cmake -B cmakebuild`
3. `cmake --build cmakebuild`
4. `.\cmakebuild\Debug\WatermarkProject.exe -h`

### Dependencies

* CMake
* OpenCV

## Authors

Pierre Maruejol

## Version History

* 0.1.0
    * Initial Release
    * The following functionnality are available:
        * Help (-h)
        * Input File Selector (-f)
        * Edit Input directory (-d \[path/To/Directory\])
        * Edit Output directory (-o \[path/To/Directory\])
        * Edit Text to watermark (-t \[text\])
        * Edit Text size (-fs \[size\])
        * Edit the wanted watermark position (-vAlign \[alignement\] || -hAlign \[alignement\])
