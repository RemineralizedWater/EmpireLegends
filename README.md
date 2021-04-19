# EmpireLegends
C++ remake of Eight-Minute Empire Legends game

https://medium.com/heuristics/c-application-development-part-1-project-structure-454b00f9eddc

Used this as project folder structure

    include/

By convention, include directory is for header files, but modern practice suggests that include directory must strictly contain headers that need to be exposed publicly. A thing to note here is the use of another directory inside the include directory. What is even more interesting is that it has a name same as that of your project. The reason to do this is to give a sense of specification when someone tries to use your library. Thus to use your library, one has to use the code

#include <Project_Name/public_header.h>

instead of

#include <public_header.h>

which basically makes it look kind of generalized.

Obviously the head file in this directory will be exposing those functions and classed that can be publicly called and used by someone using your library. 2. src/

This directory basically contains all the source code and the header files that are for internal use only. All the code that you library/project consists of must go in here. 3. libs/

This directory consists all the third party libraries that are need by your project. Usually if you look into any of the third party libraries present here, they would be following a similar structure that you are using for your project.

A point to note is there are two ways of using third party libraries in C++ — static and dynamic. This lib directory is only for static ones. We will discuss more on this later in a separate article ( Part 4 of this series). 4. test/

As the name suggests, code for unit testing is kept in this directory. 5. CMakeList.txt

This file is basically a configuration file that tells CMake what to do. We will talk in detail on CMakeList.txt in Part 2 of this series. Keep in mind that CMake is not a build system, but a build system generator. To understand this statement, you must know the difference between Make and CMake. We will get to this when we talk about CMake in the next article.
