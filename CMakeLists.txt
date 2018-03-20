cmake_minimum_required(VERSION 3.7)

project(sortingVisualization)

add_executable(sortingVisualization main.cpp SDL_Plotter.h)
target_link_libraries(sortingVisualization /Library/Frameworks/SDL2_mixer.framework /Library/Frameworks/SDL2.framework)