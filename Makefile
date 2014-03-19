out: main.cc *.hh *.cc
	g++ -g -std=c++0x -o out main.cc High_Calc.cc Img_Loader.cc -lglut -lGL -lGLU -lSDL -lSDL_image
