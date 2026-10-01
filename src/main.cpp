#include <cmath>
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <queue>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

using Id = long long;

struct Nodo {
    Id id;
    double latitud;
    double longitud;
};

struct Arco {
    int destino;
    double tiempo;
    double distancia;
    std::string calle;
};

class Grafo {
public:
    explicit Grafo(const std::string& nombre_archivo) {
        std::ifstream archivo(nombre_archivo);
        if (!archivo) {
            throw std::runtime_error("No se puede abrir " + nombre_archivo +
                                     ". Ejecuta primero: make descargar");
        }

        int cantidad_nodos;
        if (!(archivo >> cantidad_nodos) || cantidad_nodos <= 0) {
            throw std::runtime_error("El fichero no contiene un número válido de nodos.");
        }
        nodos_.reserve(cantidad_nodos);
        adyacencia_.resize(cantidad_nodos);

        for (int i = 0; i < cantidad_nodos; ++i) {
            Nodo nodo{};
            if (!(archivo >> nodo.id >> nodo.latitud >> nodo.longitud)) {
                throw std::runtime_error("No se pudo leer un nodo del fichero.");
            }
            indice_[nodo.id] = i;
            nodos_.push_back(nodo);
        }

        int cantidad_arcos;
        if (!(archivo >> cantidad_arcos) || cantidad_arcos < 0) {
            throw std::runtime_error("El fichero no contiene un número válido de arcos.");
        }
        for (int i = 0; i < cantidad_arcos; ++i) {
            Id origen, destino;
            double tiempo, distancia;
            if (!(archivo >> origen >> destino >> tiempo >> distancia)) {
                throw std::runtime_error("No se pudo leer un arco del fichero.");
            }
            std::string calle;
            std::getline(archivo, calle);
            if (!calle.empty() && calle[0] == '\t') calle.erase(0, 1);
            if (indice_.count(origen) && indice_.count(destino) && tiempo >= 0.0 &&
                distancia >= 0.0) {
                adyacencia_[indice_.at(origen)].push_back(
                    {indice_.at(destino), tiempo, distancia, calle});
            }
        }
    }

    std::pair<int, double> nodo_mas_cercano(double latitud, double longitud) const {
        int mejor = -1;
        double distancia_minima = std::numeric_limits<double>::infinity();
        for (int i = 0; i < static_cast<int>(nodos_.size()); ++i) {
            const double distancia = distancia_geografica(
                latitud, longitud, nodos_[i].latitud, nodos_[i].longitud);
            if (distancia < distancia_minima) {
                distancia_minima = distancia;
                mejor = i;
            }
        }
        return {mejor, distancia_minima};
    }

    void dijkstra(int origen, int destino) const {
        const double infinito = std::numeric_limits<double>::infinity();
        std::vector<double> tiempos(nodos_.size(), infinito);
        std::vector<int> anterior(nodos_.size(), -1);
        std::vector<const Arco*> arco_anterior(nodos_.size(), nullptr);
        using Estado = std::pair<double, int>;
        std::priority_queue<Estado, std::vector<Estado>, std::greater<Estado>> cola;

        tiempos[origen] = 0.0;
        cola.push({0.0, origen});
        while (!cola.empty()) {
            const auto [tiempo_actual, actual] = cola.top();
            cola.pop();
            if (tiempo_actual > tiempos[actual]) continue;
            if (actual == destino) break;

            for (const Arco& arco : adyacencia_[actual]) {
                const double alternativa = tiempo_actual + arco.tiempo;
                if (alternativa < tiempos[arco.destino]) {
                    tiempos[arco.destino] = alternativa;
                    anterior[arco.destino] = actual;
                    arco_anterior[arco.destino] = &arco;
                    cola.push({alternativa, arco.destino});
                }
            }
        }

        if (!std::isfinite(tiempos[destino])) {
            std::cout << "No hay una ruta entre los cruces seleccionados.\n";
            return;
        }

        std::vector<int> ruta;
        for (int actual = destino; actual != -1; actual = anterior[actual]) {
            ruta.push_back(actual);
            if (actual == origen) break;
        }
        if (ruta.back() != origen) {
            std::cout << "No se pudo reconstruir la ruta.\n";
            return;
        }
        std::reverse(ruta.begin(), ruta.end());

        double distancia_total = 0.0;
        double distancia_calle = 0.0;
        std::cout << std::fixed << std::setprecision(1);
        std::cout << "Tiempo estimado: " << tiempos[destino] / 60.0 << " min\n";
        std::cout << "Ruta de calles:\n";
        std::string calle_anterior;
        bool primera_calle = true;
        for (std::size_t i = 1; i < ruta.size(); ++i) {
            const Arco* arco = arco_anterior[ruta[i]];
            if (arco == nullptr) continue;
            distancia_total += arco->distancia;
            const std::string nombre = arco->calle.empty() ? "calle sin nombre" : arco->calle;
            if (nombre != calle_anterior) {
                if (!primera_calle) {
                    std::cout << " (" << distancia_calle / 1000.0 << " km)\n";
                }
                std::cout << "  " << nombre;
                calle_anterior = nombre;
                distancia_calle = 0.0;
                primera_calle = false;
            }
            distancia_calle += arco->distancia;
        }
        if (!primera_calle) {
            std::cout << " (" << distancia_calle / 1000.0 << " km)\n";
        }
        std::cout << "Distancia total: " << distancia_total / 1000.0 << " km\n";
    }

private:
    static double distancia_geografica(double lat1, double lon1,
                                       double lat2, double lon2) {
        constexpr double radio_tierra = 6371000.0;
        constexpr double pi = 3.14159265358979323846;
        const double a1 = lat1 * pi / 180.0;
        const double a2 = lat2 * pi / 180.0;
        const double da = (lat2 - lat1) * pi / 180.0;
        const double dl = (lon2 - lon1) * pi / 180.0;
        const double h = std::sin(da / 2) * std::sin(da / 2) +
                         std::cos(a1) * std::cos(a2) *
                             std::sin(dl / 2) * std::sin(dl / 2);
        return 2 * radio_tierra * std::asin(std::sqrt(h));
    }

    std::vector<Nodo> nodos_;
    std::vector<std::vector<Arco>> adyacencia_;
    std::unordered_map<Id, int> indice_;
};

int main(int argc, char* argv[]) {
    if (argc == 2 && std::string(argv[1]) == "--ayuda") {
        std::cout << "Uso: ./rutas FICHERO lat_origen lon_origen lat_destino lon_destino\n"
                     "Ejemplo: ./rutas data/murcia.graph 37.9922 -1.1307 37.9850 -1.1250\n";
        return 0;
    }
    if (argc != 6) {
        std::cerr << "Uso: ./rutas FICHERO lat_origen lon_origen lat_destino lon_destino\n"
                     "Consulta ./rutas --ayuda para ver un ejemplo.\n";
        return 1;
    }

    try {
        const Grafo grafo(argv[1]);
        const double latitud_origen = std::stod(argv[2]);
        const double longitud_origen = std::stod(argv[3]);
        const double latitud_destino = std::stod(argv[4]);
        const double longitud_destino = std::stod(argv[5]);
        const auto origen = grafo.nodo_mas_cercano(latitud_origen, longitud_origen);
        const auto destino = grafo.nodo_mas_cercano(latitud_destino, longitud_destino);

        std::cout << std::fixed << std::setprecision(5);
        std::cout << "Origen: cruce " << origen.first << " (" << origen.second
                  << " m de las coordenadas indicadas)\n";
        std::cout << "Destino: cruce " << destino.first << " (" << destino.second
                  << " m de las coordenadas indicadas)\n";
        grafo.dijkstra(origen.first, destino.first);
    } catch (const std::exception& error) {
        std::cerr << "Error: " << error.what() << '\n';
        return 1;
    }
}
