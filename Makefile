escalonador:*.cpp
	g++ -std=c++14 *.cpp -o escalonador

.PHONY: clean

clean:
	rm escalonador
