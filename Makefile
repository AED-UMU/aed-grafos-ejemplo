CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -pedantic -O2
PROGRAMA := rutas
FUENTE := src/main.cpp

.PHONY: all descargar clean

all: $(PROGRAMA)

$(PROGRAMA): $(FUENTE)
	$(CXX) $(CXXFLAGS) $(FUENTE) -o $(PROGRAMA)

descargar:
	python3 scripts/descargar_mapa.py

clean:
	rm -f $(PROGRAMA)
	rm -f data/murcia.graph
