# BuzzBridge — OOP Business & Community Directory

BuzzBridge is a console-based C++ application that models a local-business discovery and promotion platform. It was developed as an Object-Oriented Programming semester project.

> **Academic context:** this was a university group project. The repository preserves the recovered project source and adds build/documentation files for easier review. The original team is credited in `docs/PROJECT_HISTORY.md`.

## Features

- business registration and login
- business categories and location-based discovery
- products and promotional offers
- customer ratings and written feedback
- profile-view / promotion-click / store-visit analytics
- file-based persistence
- input validation for interactive console workflows

## OOP concepts demonstrated

- abstract base class (`Profile`)
- inheritance (`Business : Profile`)
- encapsulation of profile, authentication and analytics data
- runtime polymorphism through an overridden `displayProfile()`
- composition using `Review` records and STL containers
- smart pointers and maps for object management
- file I/O for persistence

## Build

With a C++17 compiler:

```bash
g++ -std=c++17 -Wall -Wextra -pedantic src/main.cpp -o buzzbridge
./buzzbridge
```

Or with CMake:

```bash
cmake -S . -B build
cmake --build build
./build/buzzbridge
```

On Windows, the executable may be under `build/Debug/` depending on the generator.

## Repository structure

```text
src/main.cpp              recovered project implementation
CMakeLists.txt             portable build configuration
docs/PROJECT_HISTORY.md    academic provenance note
```

## Limitations

This is a coursework console application, not a production marketplace. Passwords are stored as plain text in the original design, persistence is file-based, and concurrency/security concerns were outside the project scope. Those limitations are retained/documented rather than hidden.

## Skills demonstrated

C++ · OOP · inheritance · polymorphism · STL · file handling · input validation · console application design
