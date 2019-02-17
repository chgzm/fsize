PROGRAM := fsize
OBJS := Main.o fs/FileStatsCollector.o fs/FileDescriptionLoader.o fs/LsColorsParser.o utils/Time.o utils/Color.o utils/Unit.o
INCLUDES := -I./utils -I./fs
CXX := g++
FLGS := -std=c++14
CXXFLAGS := -Wall -O2

.PHONY: all
$(PROGRAM): $(OBJS)
	$(CXX) $(FLGS) $(CXXFLAGS) -o $(PROGRAM) $(OBJS) -lmagic

.cpp.o:
	$(CXX) $(FLGS) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

.PHONY: clean
clean:
	$(RM) $(OBJS) $(PROGRAM)
