# BuzzBridge — OOP Business & Community Directory

BuzzBridge is a console-based C++ application developed as an Object-Oriented Programming semester project. It models a local-business discovery and promotion platform.

## Features

- business registration and login
- business categories and location-based discovery
- products and promotional offers
- customer ratings and written feedback
- profile-view, promotion-click and store-visit analytics
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

Using a C++17 compiler:

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

## Repository structure

```text
BuzzBridge-OOP/
├── src/
│   └── main.cpp
├── CMakeLists.txt
├── .gitignore
└── README.md
```

## Limitations

This is an academic console application. It uses file-based persistence and plain-text password storage, so it is not intended for production use.

## Skills demonstrated

C++ · Object-Oriented Programming · inheritance · polymorphism · STL · file handling · input validation · console application design
