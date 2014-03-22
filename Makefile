out: main.cc *.hh *.cc *.cpp
	g++ -g -std=c++0x -o out main_test.cc High_Calc.cc Img_Loader.cc Engine.cpp Camera.cpp Event.cpp Vector3d.cpp Cube.cpp -lglut -lGL -lGLU -lSDL -lSDL_image
