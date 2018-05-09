cmake_minimum_required(VERSION 3.7)
project(untitled1)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp MyMenu.h Line.cpp Line.h Circle.cpp Circle.h Filling.cpp Filling.h MyPoint.cpp MyPoint.h ShapeBuffer.cpp ShapeBuffer.h Clipping.cpp Clipping.h File.cpp File.h BezierCurve.cpp BezierCurve.h Shape.cpp Shape.h Poly.cpp Poly.h HermiteCurve.cpp HermiteCurve.h)
add_executable(untitled1 ${SOURCE_FILES})