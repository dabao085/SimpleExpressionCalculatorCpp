Test: Main.cc
	g++ -g -o Test Main.cc Node.cc -std=c++11
clean:
	rm -f Test	core.*