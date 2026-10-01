# Caminos mínimos por carretera en Murcia

Proyecto didáctico pequeño: descarga la red de calles y carreteras de Murcia, la guarda en un fichero de texto y calcula una ruta con Dijkstra implementado en C++.

La red es un grafo dirigido y ponderado. Cada vértice representa un cruce (un nodo de OpenStreetMap); cada arco representa un tramo transitable y su peso es el tiempo estimado de recorrido (`travel_time`). La clase `Grafo` guarda los arcos en listas de adyacencia. Las coordenadas se usan solo para encontrar los cruces más cercanos al origen y al destino.

## Requisitos

- Linux, macOS o WSL con `g++` y `make`.
- Python 3 y `pip`.
- Conexión a Internet para descargar los datos de OpenStreetMap.

La descarga usa [OSMnx](https://osmnx.readthedocs.io/), que a su vez usa bibliotecas de Python como GeoPandas y consulta OpenStreetMap/Overpass. No hacen falta bibliotecas externas para compilar el programa C++.

## Instalación

Desde la carpeta del proyecto:

```bash
python3 -m venv .venv
source .venv/bin/activate
python -m pip install --upgrade pip
python -m pip install osmnx
make
```

En algunas distribuciones de Linux puede ser necesario instalar antes `python3-venv` y `build-essential` con el gestor de paquetes del sistema.

## Descargar el mapa

Con el entorno virtual activado:

```bash
make descargar
```

Esto ejecuta `scripts/descargar_mapa.py`, que obtiene la red de conducción con el equivalente a:

```python
ox.graph_from_place("Murcia, Spain", network_type="drive")
```

El script escribe `data/murcia.graph`, un formato de texto sencillo que lee el programa C++. La descarga depende de los datos disponibles en OpenStreetMap y puede tardar un poco. El fichero descargado no se incluye en Git porque ocupa espacio y puede regenerarse.

## Calcular una ruta

Indica las coordenadas de origen y destino (latitud y longitud):

```bash
./rutas data/murcia.graph 37.9922 -1.1307 37.9850 -1.1250
```

El programa busca el cruce más cercano a cada coordenada y calcula la ruta de menor tiempo estimado. Muestra el tiempo estimado, los nombres de las calles recorridas y la distancia total en kilómetros. Si una calle no tiene nombre en OpenStreetMap, aparece como «calle sin nombre».

También puedes consultar el uso:

```bash
./rutas --ayuda
```

## Reproducibilidad

Para repetir el proceso desde cero, activa `.venv`, ejecuta `make clean`, `make descargar` y `make`. Después usa el mismo comando de ruta. El código y las coordenadas de entrada son reproducibles; el mapa descargado puede cambiar con las actualizaciones de OpenStreetMap. Para conservar exactamente una ejecución, guarda una copia de `data/murcia.graph` junto con la fecha de descarga.

## Formato del fichero

El fichero contiene primero el número de nodos, después una línea por nodo (`id latitud longitud`), luego el número de arcos y una línea por arco (`origen destino travel_time_en_segundos longitud_en_metros` y el nombre de calle). Los identificadores son los de OpenStreetMap. Cada arco se escribe en la orientación que trae el grafo dirigido de OSMnx, por lo que las calles de sentido único no se pueden recorrer al revés. Dijkstra minimiza el tiempo; `length` se conserva para sumar y mostrar los kilómetros de la ruta resultante.

## Estructura

- `src/main.cpp`: clase `Grafo`, listas de adyacencia y algoritmo de Dijkstra.
- `scripts/descargar_mapa.py`: descarga y conversión del mapa.
- `Makefile`: compilación y tareas habituales.
