cmake_minimum_required(VERSION 3.16)

project(MiniGit VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(mgit
    src/main.cpp
    src/Repository.cpp
    src/Index.cpp
    src/RefManager.cpp
    src/WorkingDirectory.cpp
    src/CommitBuilder.cpp
    src/objects/Blob.cpp
    src/objects/Tree.cpp
    src/objects/Commit.cpp
    src/storage/ObjectDatabase.cpp
    src/hashing/SimpleHashStrategy.cpp
    src/commands/InitCommand.cpp
    src/commands/AddCommand.cpp
    src/commands/CommitCommand.cpp
    src/commands/LogCommand.cpp
    src/commands/StatusCommand.cpp
    src/commands/CatObjectCommand.cpp
    src/commands/CheckoutCommand.cpp
    src/commands/CommandParser.cpp
)

target_include_directories(mgit PRIVATE include)

if(MSVC)
    target_compile_options(mgit PRIVATE /W4 /permissive-)
else()
    target_compile_options(mgit PRIVATE -Wall -Wextra -Wpedantic)
endif()
