CXX = g++
CXXFLAGS = -std=c++17 -O2
HEADERS = Studentas.h Pagalbiniai.h Failai.h Meniu.h

programa: main.o Failai.o Pagalbiniai.o
	$(CXX) $(CXXFLAGS) main.o Failai.o Pagalbiniai.o -o programa

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f *.o programa
