# PlasmaInstabilityLoss
The modular design of CRPropa3 allows new functionalities to be easily integrated into the existing framework. This module is designed to study the impact of plasma instabilities on electromagnetic cascades.

The energy-loss calculation for electrons and positrons is implemented in the source file PlasmaInstabilityLoss.cpp based on the paper by Alawashra and Pohl 2022 ApJ 929 67, with the corresponding header file PlasmaInstabilityLoss.h, following the standard CRPropa 3 structure (see https://github.com/CRPropa/CRPropa3).

# - Steps to add the module in the preinstalled CRPropa3 -

The following steps describe how to add a custom interaction module — for example, a module called PlasmaInstabilityLoss — to the CRPropa framework:


# 1. Adding the Source File

Navigate to your CRPropa installation inside your virtual environment:

`CRPropa3/src/module`

Copy or move the PlasmaInstabilityLoss.cpp file into this directory.


# 2. Add the Header File

Go to:

`CRPropa3/include/crpropa/module`

Place the PlasmaInstabilityLoss.h file here.


# 3. Update the Python Interface

Go to:

`CRPropa3/python`

Open the file "2_headers.i" and add the following line once, where other interaction modules are listed:

`%include "crpropa/module/PlasmaInstabilityLoss.h"`


# 4. Update the Main Header File

Go to:

`CRPropa3/include`

Open "CRPropa.h" and add the following line once, where other interaction modules are included:

`#include "crpropa/module/PlasmaInstabilityLoss.h"`


# 5. Update the Build Configuration

Return to the main CRPropa directory and open "CMakeLists.txt".
Add the following line once, alongside other interaction modules:

`src/module/PlasmaInstabilityLoss.cpp`


# 6. Rebuild CRPropa

Navigate to the build directory and recompile CRPropa:

```>> make ``` 

```>> make install ```

After completing these steps, your new module will be successfully integrated into the CRPropa framework and accessible via the Python interface.
