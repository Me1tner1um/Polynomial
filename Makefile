CXX = g++

TARGET = build/polynomial_lab
SOURCES = src/main.cpp src/polynomial.cpp src/extended_polynomial.cpp src/polynomial_list.cpp src/polynomial_template.cpp src/polynomial_stl.cpp
HEADERS = include/polynomial.h include/extended_polynomial.h include/polynomial_list.h include/polynomial_template.h include/polynomial_stl.h
OBJECTS = build/main.o build/polynomial.o build/extended_polynomial.o build/polynomial_list.o build/polynomial_template.o build/polynomial_stl.o

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) -o $(TARGET) $(OBJECTS)

build/main.o: src/main.cpp $(HEADERS)
	$(CXX) -c src/main.cpp -o $@

build/polynomial.o: src/polynomial.cpp include/polynomial.h
	$(CXX) -c src/polynomial.cpp -o $@

build/extended_polynomial.o: src/extended_polynomial.cpp include/extended_polynomial.h include/polynomial.h
	$(CXX) -c src/extended_polynomial.cpp -o $@

build/polynomial_list.o: src/polynomial_list.cpp include/polynomial_list.h include/extended_polynomial.h include/polynomial.h
	$(CXX) -c src/polynomial_list.cpp -o $@

build/polynomial_template.o: src/polynomial_template.cpp include/polynomial_template.h
	$(CXX) -c src/polynomial_template.cpp -o $@

build/polynomial_stl.o: src/polynomial_stl.cpp include/polynomial_stl.h include/polynomial.h
	$(CXX) -c src/polynomial_stl.cpp -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)

distclean: clean
	rm -f $(TARGET)

rebuild: clean all

.PHONY: all debug clean distclean rebuild install help