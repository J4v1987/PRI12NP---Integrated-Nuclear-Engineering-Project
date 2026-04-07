# Install script for directory: /home/javier/Documents/C++/M1S2 projects/PRI12NP - 02 - Simulation of an experimental setup/TP GEANT4/B2a/B2a-3

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/usr/bin/objdump")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/exampleB2a" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/exampleB2a")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/exampleB2a"
         RPATH "")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "/home/javier/Documents/C++/M1S2 projects/PRI12NP - 02 - Simulation of an experimental setup/TP GEANT4/B2a/B2a-3/B2a-3-build/exampleB2a")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/exampleB2a" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/exampleB2a")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/exampleB2a"
         OLD_RPATH "/home/javier/spack/opt/spack/linux-sandybridge/root-6.36.00-lyqsqtfifo257mnwmsxlylvvlvcjubty/lib/root:/home/javier/spack/opt/spack/linux-sandybridge/geant4-11.3.2-7bzyo7zwespwru2nbtmajwt65xq5m3je/lib:/home/javier/spack/opt/spack/linux-sandybridge/qt-base-6.9.1-7pjs37gxvvtloe6tyalnq3abx3ij2rfo/lib:/home/javier/spack/opt/spack/linux-sandybridge/xerces-c-3.3.0-nxjasf26gyvn7qh4w3cklaklbrvqhhog/lib:/home/javier/spack/opt/spack/linux-sandybridge/zlib-ng-2.2.4-zso4svjbilbbp6xifn3ffl5xue4ert46/lib:/home/javier/spack/opt/spack/linux-sandybridge/expat-2.7.1-zejzr6ylal7q4rhm7acvnilrdxkmnsb6/lib:/home/javier/spack/opt/spack/linux-sandybridge/clhep-2.4.7.1-zlxzqgmvaf3plndrvmmmqgsvpiglrgwb/lib:"
         NEW_RPATH "")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/exampleB2a")
    endif()
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/home/javier/Documents/C++/M1S2 projects/PRI12NP - 02 - Simulation of an experimental setup/TP GEANT4/B2a/B2a-3/B2a-3-build/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
