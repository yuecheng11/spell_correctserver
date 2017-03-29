INC_DIR:= ./inc/ ./inc/net/ ./inc/threadpool/ ./inc/timer/
SRC_DIR:= ./src ./src/net ./src/threadpool ./src/timer
SRCS:=$(wildcard ./src/*.cpp) $(wildcard ./src/net/*.cpp) $(wildcard ./src/net/*.c) $(wildcard ./src/threadpool/*.cpp) $(wildcard ./src/timer/*.cpp)
OBJS:= $(patsubst %.cpp, %.o, $(SRCS))
LIBS:= -lpthread

CXX:=g++

CXXFLAGS:= -w -g -std=c++11 $(addprefix -I, $(INC_DIR)) $(LIBS) -Wno-deprecated

EXE:=./bin/main

$(EXE):$(OBJS)
	$(CXX) -o $(EXE) $(SRCS) $(CXXFLAGS)
#$(SRC_DIR)/%.o:$(SRC_DIR)/%.cc
	#$(CXX)  -c $^ -o $@ $(CXXFLAGS)

clean:
	rm -rf $(EXE)
	rm -rf $(OBJS)
