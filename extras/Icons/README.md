# StoneyDSP::Icons

This is primarily an internal project, designed to utilize a single set of binary resources as a CMake target, which can be shared around with the rest of the ```StoneyDSP``` library installation, providing a suite of graphical components and other objects to all of the other targets in the ```StoneyDSP``` installation. This target will also likely be exported into the form of a Napi Addon for the NodeJS runtime, allowing us to consume this library elsewhere, such as our webpages and other external projects.

It might also serve as a useful example project for resource-compiler targets and their uses.
