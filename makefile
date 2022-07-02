apportioner: ./apportion/apportion.cpp
	g++ -std=c++17 -Wall -o apportioner ./apportion/apportion.cpp ./src/Apportionment.cpp ./src/methods.cpp ./src/State.cpp -I./src -I./src/tclap