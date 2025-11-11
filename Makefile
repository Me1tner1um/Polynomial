CXX = g++

TARGET = polynomial_lab
SOURCES = main.cpp polynomial.cpp extended_polynomial.cpp polynomial_list.cpp polynomial_template.cpp polynomial_stl.cpp
HEADERS = polynomial.h extended_polynomial.h polynomial_list.h polynomial_template.h polynomial_stl.h
OBJECTS = $(SOURCES:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) -o $(TARGET) $(OBJECTS)

main.o: main.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c main.cpp

polynomial.o: polynomial.cpp polynomial.h
	$(CXX) $(CXXFLAGS) -c polynomial.cpp

extended_polynomial.o: extended_polynomial.cpp extended_polynomial.h polynomial.h
	$(CXX) $(CXXFLAGS) -c extended_polynomial.cpp

polynomial_list.o: polynomial_list.cpp polynomial_list.h extended_polynomial.h polynomial.h
	$(CXX) $(CXXFLAGS) -c polynomial_list.cpp

polynomial_template.o: polynomial_template.cpp polynomial_template.h
	$(CXX) $(CXXFLAGS) -c polynomial_template.cpp

polynomial_stl.o: polynomial_stl.cpp polynomial_stl.h polynomial.h
	$(CXX) $(CXXFLAGS) -c polynomial_stl.cpp

clean:
	rm -f $(OBJECTS) $(TARGET)

distclean: clean
	rm -f $(TARGET)

rebuild: clean all

.PHONY: all debug clean distclean rebuild install help