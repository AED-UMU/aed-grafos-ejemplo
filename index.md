# Caminos mínimos por carretera en Murcia

Proyecto didáctico de la asignatura de Algoritmos y Estructuras de Datos: descarga la red de calles y carreteras de Murcia, la guarda en un fichero de texto y calcula la ruta más rápida entre dos puntos con el algoritmo de **Dijkstra**, implementado en C++ sobre listas de adyacencia.

[![Ver el código en GitHub](https://img.shields.io/badge/GitHub-repositorio-181717?logo=github)](https://github.com/AED-UMU/aed-grafos-ejemplo)

## ¿Qué hace?

- Descarga con Python (`osmnx`) la red de conducción de Murcia desde OpenStreetMap.
- Representa el callejero como un grafo dirigido y ponderado: cada nodo es un cruce y cada arco un tramo de calle con su tiempo de recorrido estimado.
- Busca los cruces más cercanos a las coordenadas de origen y destino.
- Calcula la ruta de menor tiempo con Dijkstra y muestra el tiempo estimado, las calles recorridas y la distancia total en kilómetros.

## Ejemplo de uso

```bash
./rutas data/murcia.graph 37.9922 -1.1307 37.9850 -1.1250
```

```text
Tiempo estimado: 6.4 min
Ruta de calles:
  Gran Vía Escultor Francisco Salzillo (0.5 km)
  Calle Acisclo Díaz (0.3 km)
  ...
Distancia total: 2.1 km
```

## Objetivo docente

El proyecto sirve para practicar:

- Representación de grafos mediante **listas de adyacencia**.
- El algoritmo de **Dijkstra** para caminos mínimos, en su versión clásica $O(n^2)$.
- Lectura y procesado de datos reales (OpenStreetMap) desde C++.

## Código fuente

El código completo, las instrucciones de instalación y la estructura del proyecto están en la rama `main` del repositorio:

**[github.com/AED-UMU/aed-grafos-ejemplo](https://github.com/AED-UMU/aed-grafos-ejemplo)**
