# Datasets reales y problemas de grafos

Este documento recopila **datasets reales** que pueden utilizarse para plantear ejercicios sobre grafos.  

---

## 1. Algoritmos y problemas tratados

| Algoritmo / técnica | Problema que resuelve |
|---|---|
| **DFS — Depth-First Search** | Recorrer un grafo; comprobar alcanzabilidad; detectar ciclos; obtener componentes conexas; base de otros algoritmos sobre grafos |
| **BFS — Breadth-First Search** | Recorrer un grafo por niveles; obtener componentes conexas; encontrar caminos con el menor número de aristas en grafos no ponderados |
| **DFS para detección de ciclos** | Determinar si un grafo dirigido o no dirigido contiene ciclos |
| **BFS / DFS para componentes conexas** | Determinar las componentes conexas de un grafo no dirigido |
| **BFS / DFS sobre la versión no dirigida** | Determinar las componentes débilmente conexas de un grafo dirigido |
| **Prim** | Encontrar un árbol de expansión mínimo de un grafo conexo, no dirigido y ponderado |
| **Kruskal** | Encontrar un árbol de expansión mínimo de un grafo conexo, no dirigido y ponderado |
| **Dijkstra** | Caminos mínimos desde un vértice origen hasta todos los demás en grafos con pesos positivos |
| **Floyd-Warshall** | Caminos mínimos entre todos los pares de vértices |
| **Kosaraju / Tarjan / Gabow** | Determinar las componentes fuertemente conexas de un grafo dirigido |
| **Algoritmo de Kahn** | Obtener una ordenación topológica de un DAG; también permite detectar que existe un ciclo si no puede completarse la ordenación |
| **Ordenación topológica basada en DFS** | Obtener una ordenación topológica de un DAG |
| **Tarjan para puntos de articulación** | Identificar vértices cuya eliminación desconecta parte de un grafo no dirigido |
| **Algoritmo para circuito de Euler** | Encontrar un circuito que visite todas las aristas exactamente una vez, cuando existe |
| **Ciclo hamiltoniano** | Determinar si existe un ciclo simple que visite todos los vértices exactamente una vez |
| **TSP — Traveling Salesman Problem** | Encontrar el ciclo de menor coste que visita todos los vértices |
| **Coloración de grafos** | Colorear un grafo con el mínimo número de colores de forma que dos vértices adyacentes no tengan el mismo color |
| **Isomorfismo de grafos** | Determinar si dos grafos tienen la misma estructura salvo un renombrado de sus vértices |

---

# 2. Datasets reales

## 2.1. OpenFlights — red mundial de rutas aéreas

**Dataset:** [OpenFlights Airport and Airline Data](https://openflights.org/data.php)

OpenFlights proporciona información de aeropuertos y rutas aéreas. Las rutas son **dirigidas**: una conexión `A -> B` no implica necesariamente que exista `B -> A`.

### Modelado

- **Vértice:** aeropuerto.
- **Arista:** vuelo/ruta directa entre dos aeropuertos.
- **Peso opcional:** distancia entre aeropuertos, calculada a partir de sus coordenadas.

Ejemplo:

```text
MAD -> LHR
MAD -> CDG
LHR -> JFK
CDG -> JFK
JFK -> SFO
```

### Problemas

#### Problema 1 — Aeropuertos alcanzables

> Dado un aeropuerto de origen, determinar todos los aeropuertos a los que se puede llegar mediante una secuencia de vuelos.

**Algoritmo:** DFS o BFS.

---

#### Problema 2 — Menor número de vuelos

> Dados dos aeropuertos, encontrar una ruta que utilice el menor número de vuelos posible.

**Algoritmo:** BFS.

Ejemplo:

```text
MAD -> CDG -> JFK
```

tiene dos aristas y, por tanto, requiere dos vuelos.

---

#### Problema 3 — Ruta de menor distancia

> Dados dos aeropuertos, encontrar la ruta cuya suma total de distancias sea mínima.

El peso de cada arista se obtiene de la distancia entre las coordenadas de los aeropuertos.

**Algoritmo:** Dijkstra.

---

#### Problema 4 — Distancias entre todos los aeropuertos

> Para un subconjunto reducido de aeropuertos, calcular la distancia mínima entre cada par de aeropuertos.

**Algoritmo:** Floyd-Warshall.

Es recomendable trabajar con un subconjunto pequeño del dataset, ya que Floyd-Warshall tiene coste cúbico respecto al número de vértices.

---

#### Problema 5 — Grupos de aeropuertos mutuamente alcanzables

> Encontrar grupos maximales de aeropuertos tales que desde cualquier aeropuerto del grupo se pueda llegar a cualquier otro y viceversa.

**Problema:** componentes fuertemente conexas.

**Algoritmos:** Kosaraju, Tarjan o Gabow.

---

## 2.2. Facebook — relaciones sociales

**Dataset:** [SNAP — Social circles: Facebook](https://snap.stanford.edu/data/ego-Facebook.html)

El dataset contiene una red social anonimizada de Facebook:

- **4.039 nodos**
- **88.234 aristas**

### Modelado

- **Vértice:** persona.
- **Arista no dirigida:** relación de amistad.

```text
persona_A --- persona_B
```

### Problemas

#### Problema 1 — Personas alcanzables

> Dada una persona, encontrar todas las personas que pertenecen a su misma componente social.

**Algoritmo:** DFS o BFS.

---

#### Problema 2 — Grados de separación

> Dados dos usuarios, calcular el número mínimo de relaciones de amistad necesarias para llegar de uno al otro.

**Algoritmo:** BFS.

---

#### Problema 3 — Grupos desconectados

> Determinar las componentes conexas de la red social.

**Algoritmo:** BFS o DFS.

---

#### Problema 4 — Ciclos de amistad

> Determinar si existe algún ciclo dentro de la red.

**Algoritmo:** DFS para detección de ciclos en grafos no dirigidos.

---

#### Problema 5 — Usuarios críticos

> Determinar qué usuarios, si desaparecieran de la red junto con sus relaciones, separarían una parte de la comunidad del resto.

**Problema:** puntos de articulación.

**Algoritmo:** Tarjan para puntos de articulación.

---

#### Problema 6 — Coloración

Supongamos que se quieren asignar recursos a usuarios conectados con la restricción de que dos usuarios relacionados no puedan recibir simultáneamente el mismo recurso.

> Encontrar el mínimo número de grupos necesarios para que dos usuarios conectados nunca pertenezcan al mismo grupo.

**Problema:** coloración de grafos.

---

## 2.3. Email-Eu-core — comunicaciones por correo electrónico

**Dataset:** [SNAP — email-Eu-core](https://snap.stanford.edu/data/email-Eu-core.html)

Dataset construido a partir de comunicaciones de correo electrónico de una institución europea.

- **1.005 personas**
- **25.571 aristas dirigidas**
- usuarios pertenecientes a **42 departamentos**

Existe una arista:

```text
u -> v
```

si `u` envió al menos un correo electrónico a `v`.

### Problemas

#### Problema 1 — Propagación de información

> Determinar si un mensaje podría llegar desde una persona `A` hasta una persona `B` pasando por una cadena de contactos.

**Algoritmo:** DFS o BFS.

---

#### Problema 2 — Cadena mínima de intermediarios

> Encontrar la cadena con el menor número de personas intermedias que conecta `A` con `B`.

**Algoritmo:** BFS.

---

#### Problema 3 — Ciclos de comunicación

> Determinar si existe una secuencia de comunicaciones que parte de una persona y vuelve a ella.

**Algoritmo:** DFS para detección de ciclos en grafos dirigidos.

---

#### Problema 4 — Comunidades mutuamente comunicadas

> Encontrar grupos en los que cada persona pueda alcanzar mediante comunicaciones a todas las demás personas del grupo.

**Problema:** componentes fuertemente conexas.

**Algoritmos:** Kosaraju, Tarjan o Gabow.

---

#### Problema 5 — Componentes débilmente conexas

> Ignorando la dirección de los correos, determinar qué grupos de personas están conectados entre sí.

**Algoritmo:** transformar el grafo en no dirigido y aplicar BFS o DFS.

---

## 2.4. Red de carreteras de California

**Dataset:** [SNAP — California road network](https://snap.stanford.edu/data/roadNet-CA.html)

Red real de carreteras de California.

- **1.965.206 nodos**
- **2.766.607 aristas**

### Modelado

- **Vértice:** intersección o extremo de una carretera.
- **Arista:** tramo de carretera.

El dataset de SNAP es **no ponderado**.

### Problemas

#### Problema 1 — Conectividad

> Determinar si es posible desplazarse entre dos intersecciones.

**Algoritmo:** BFS o DFS.

---

#### Problema 2 — Regiones desconectadas

> Determinar las componentes conexas de la red de carreteras.

**Algoritmo:** BFS o DFS.

---

#### Problema 3 — Intersecciones críticas

> Encontrar intersecciones cuya eliminación provoque que una parte de la red quede desconectada.

**Problema:** puntos de articulación.

**Algoritmo:** Tarjan para puntos de articulación.

---

#### Problema 4 — Escalabilidad

Ejecutar un mismo algoritmo sobre subconjuntos crecientes:

```text
1.000 vértices
10.000 vértices
100.000 vértices
1.000.000 vértices
```

y estudiar cómo evoluciona el tiempo de ejecución.

Es especialmente adecuado para estudiar experimentalmente la complejidad de **BFS y DFS**.

---

## 2.5. MATPOWER — redes eléctricas

**Proyecto:** [MATPOWER](https://matpower.org/)

**Repositorio:** [MATPOWER en GitHub](https://github.com/MATPOWER/matpower)

**Ejemplo IEEE de 14 buses:** [case14.m](https://github.com/MATPOWER/matpower/blob/master/data/case14.m)

MATPOWER contiene numerosos sistemas eléctricos reales o de referencia, entre ellos:

```text
case9
case14
case24_ieee_rts
case30
case57
case118
case300
...
```

### Modelado simplificado

- **Vértice:** bus/subestación.
- **Arista:** línea eléctrica.
- **Peso:** coste, longitud, impedancia u otra magnitud seleccionada para el ejercicio.

### Problemas

#### Problema 1 — Fallo de una línea

> Eliminar una línea eléctrica y comprobar si la red permanece conectada.

**Algoritmo:** BFS o DFS.

---

#### Problema 2 — Subestaciones aisladas

> Después de eliminar varias líneas, determinar qué grupos de subestaciones quedan desconectados.

**Problema:** componentes conexas.

**Algoritmo:** BFS o DFS.

---

#### Problema 3 — Subestaciones críticas

> Determinar qué buses, al ser eliminados, dividen la red en varias componentes.

**Problema:** puntos de articulación.

**Algoritmo:** Tarjan para puntos de articulación.

---

#### Problema 4 — Red de coste mínimo

En una abstracción del problema:

> Seleccionar un subconjunto de líneas que conecte todos los nodos con el menor coste total posible y sin formar ciclos.

**Problema:** árbol de expansión mínimo.

**Algoritmos:** Prim o Kruskal.

Este tipo de aplicación aparece explícitamente asociado a los árboles de expansión mínimos: redes eléctricas, fibra óptica y redes de tuberías.

---

## 2.6. DBLP — red de colaboración científica

**Dataset:** [SNAP — DBLP collaboration network](https://snap.stanford.edu/data/com-DBLP.html)

Red real de coautoría científica:

- **317.080 autores**
- **1.049.866 relaciones de coautoría**

### Modelado

- **Vértice:** investigador.
- **Arista:** dos investigadores han publicado al menos un artículo juntos.

```text
Autor A --- Autor B
```

### Problemas

#### Problema 1 — Distancia entre investigadores

> Dados dos investigadores, encontrar el número mínimo de colaboraciones necesarias para conectarlos.

**Algoritmo:** BFS.

Es una generalización del concepto de **número de Erdős**.

---

#### Problema 2 — Comunidad alcanzable

> Obtener todos los investigadores conectados directa o indirectamente con un investigador dado.

**Algoritmo:** DFS o BFS.

---

#### Problema 3 — Componentes de colaboración

> Determinar grupos de investigadores entre los que existe alguna cadena de colaboraciones.

**Algoritmo:** BFS o DFS para componentes conexas.

---

#### Problema 4 — Investigadores estructuralmente críticos

> Determinar investigadores cuya eliminación separaría una parte de la red de colaboración.

**Problema:** puntos de articulación.

**Algoritmo:** Tarjan para puntos de articulación.

---

## 2.7. ArXiv — colaboración científica en General Relativity

Si DBLP resulta demasiado grande, existe una alternativa mucho más manejable.

**Dataset:** [SNAP — ArXiv GR-QC collaboration network](https://snap.stanford.edu/data/ca-GrQc.html)

- **5.242 autores**
- **14.496 relaciones**

### Problemas

Se pueden plantear exactamente los mismos problemas que con DBLP:

- distancia entre dos autores → **BFS**
- investigadores alcanzables → **DFS / BFS**
- componentes conexas → **DFS / BFS**
- investigadores críticos → **puntos de articulación**

Es probablemente un dataset más adecuado que DBLP para una primera implementación.

---

## 2.8. Web de la Universidad de Notre Dame

**Dataset:** [SNAP — Notre Dame web graph](https://snap.stanford.edu/data/web-NotreDame.html)

- **325.729 páginas**
- **1.497.134 hipervínculos**

### Modelado

- **Vértice:** página web.
- **Arista dirigida:** hipervínculo.

```text
pagina_A -> pagina_B
```

### Problemas

#### Problema 1 — Navegabilidad

> Determinar si se puede llegar desde una página `A` hasta una página `B` siguiendo hipervínculos.

**Algoritmo:** BFS o DFS.

---

#### Problema 2 — Número mínimo de clics

> Encontrar el número mínimo de hipervínculos que es necesario seguir para llegar desde `A` hasta `B`.

**Algoritmo:** BFS.

---

#### Problema 3 — Ciclos de navegación

> Determinar si existe una secuencia de enlaces que permita volver a una página ya visitada.

**Algoritmo:** DFS para detección de ciclos.

---

#### Problema 4 — Grupos mutuamente navegables

> Encontrar grupos de páginas tales que desde cada una se pueda llegar a cualquiera de las demás.

**Problema:** componentes fuertemente conexas.

---

## 2.9. Internet — sistemas autónomos

**Dataset:** [SNAP — Autonomous Systems AS-733](https://snap.stanford.edu/data/as-733.html)

Los nodos representan **Autonomous Systems (AS)** de Internet y las aristas representan relaciones de conectividad entre ellos.

El dataset incluye **733 instantáneas temporales** de la red.

### Problemas

#### Problema 1 — Conectividad entre redes

> Comprobar si dos sistemas autónomos están conectados directa o indirectamente.

**Algoritmo:** BFS o DFS.

---

#### Problema 2 — Distancia entre sistemas

> Calcular el número mínimo de saltos necesarios para comunicar dos sistemas autónomos.

**Algoritmo:** BFS.

---

#### Problema 3 — Puntos críticos de Internet

> Determinar qué sistemas autónomos provocarían una desconexión de parte de la red si desapareciesen.

**Problema:** puntos de articulación.

---

## 2.10. Amazon — productos comprados conjuntamente

**Dataset:** [SNAP — Amazon co-purchasing network](https://snap.stanford.edu/data/com-Amazon.html)

- **334.863 productos**
- **925.872 relaciones**

Existe una arista entre dos productos cuando aparecen frecuentemente relacionados mediante la información de productos comprados conjuntamente.

### Modelado

- **Vértice:** producto.
- **Arista:** relación frecuente de compra conjunta.

### Problemas

#### Problema 1 — Productos relacionados

> Dado un producto, encontrar todos los productos situados como máximo a `k` relaciones de distancia.

**Algoritmo:** BFS limitada por niveles.

---

#### Problema 2 — Cadena mínima entre productos

> Encontrar la cadena más corta de relaciones de compra que conecta dos productos.

**Algoritmo:** BFS.

---

#### Problema 3 — Componentes

> Determinar grupos desconectados de productos.

**Algoritmo:** BFS o DFS.

---

## 2.11. OpenStreetMap — red de calles con tiempos de viaje reales

**Dataset:** [OpenStreetMap](https://www.openstreetmap.org/), descargado con la librería `osmnx`.

**Proyecto de ejemplo:** [aed-grafos-ejemplo](https://github.com/AED-UMU/aed-grafos-ejemplo), que descarga la red viaria de una ciudad (por ejemplo, Murcia) y calcula rutas con Dijkstra implementado en C++.

A diferencia de RoadNet-CA, este dataset se genera **ponderado**: cada arista lleva como peso el tiempo de viaje estimado (`travel_time`), calculado a partir de la velocidad máxima y la longitud del tramo.

### Modelado

- **Vértice:** cruce (nodo de OpenStreetMap), con latitud y longitud.
- **Arista dirigida:** tramo de calle transitable.
- **Peso:** tiempo estimado de recorrido (también puede usarse la distancia en metros).

```text
cruce_A -> cruce_B   [peso = tiempo de viaje]
```

### Por qué es un dataset especialmente bueno para caminos mínimos

- Es un grafo **real, dirigido y con pesos positivos genuinos** (no distancias en línea recta como en OpenFlights, ni un grafo sin pesos como RoadNet-CA): exactamente la entrada que necesita Dijkstra.
- Se puede generar a medida: una ciudad pequeña para prácticas rápidas, o una región entera para estudiar escalabilidad.
- El resultado se verifica de forma intuitiva: la ruta calculada debe coincidir con lo que mostraría un navegador GPS real.
- Permite comparar **tiempo mínimo** frente a **distancia mínima** usando dos pesos distintos sobre el mismo grafo.

### Problemas

#### Problema 1 — Ruta más rápida entre dos cruces

> Dadas las coordenadas de origen y destino, encontrar la ruta que minimiza el tiempo total de viaje.

**Algoritmo:** Dijkstra.

---

#### Problema 2 — Ruta más corta en distancia

> Repetir el problema anterior usando la distancia en metros como peso en lugar del tiempo.

**Algoritmo:** Dijkstra.

---

#### Problema 3 — Alcanzabilidad y componentes

> Comprobar si todos los cruces de la red son alcanzables entre sí, o si existen zonas aisladas (por ejemplo, calles peatonales o cortadas).

**Algoritmo:** BFS/DFS o componentes fuertemente conexas, al ser un grafo dirigido.

---

# 3. Problemas especialmente adecuados para cada algoritmo

## DFS

Datasets recomendados:

- Facebook
- Email-Eu-core
- RoadNet-CA
- DBLP
- Notre Dame Web

Ejemplos:

```text
¿Es B alcanzable desde A?
¿Qué nodos son alcanzables desde A?
¿Existen ciclos?
¿Cuáles son las componentes conexas?
```

---

## BFS

Datasets recomendados:

- Facebook
- OpenFlights
- Email-Eu-core
- DBLP
- Amazon
- Notre Dame Web

Ejemplos:

```text
¿Cuántos grados de separación existen entre dos personas?
¿Cuál es la ruta aérea que utiliza menos vuelos?
¿Cuál es la cadena más corta de colaboradores entre dos investigadores?
¿Cuál es el número mínimo de clics entre dos páginas?
```

---

## Prim y Kruskal

Datasets recomendados:

- MATPOWER
- cualquier red física ponderada obtenida a partir de carreteras, tuberías, fibra o electricidad.

Ejemplo:

```text
Queremos mantener conectadas todas las instalaciones
minimizando el coste total de las conexiones.
```

**Algoritmos:** Prim o Kruskal.

---

## Dijkstra

Datasets recomendados:

- **OpenStreetMap** (red de calles con tiempo de viaje real como peso): es el dataset más adecuado para Dijkstra, porque sus pesos son auténticos (tiempo o distancia reales) y no una aproximación como la distancia en línea recta entre aeropuertos.
- OpenFlights, con la distancia entre aeropuertos como peso: alternativa válida si se prefiere un grafo mucho más pequeño.

Ejemplo:

```text
¿Cuál es la ruta más rápida entre dos cruces
de la red de calles de una ciudad?
```

**Algoritmo:** Dijkstra.

---

## Floyd-Warshall

Dataset recomendado:

- subconjunto pequeño de OpenFlights.

Ejemplo:

```text
Calcular la matriz de distancias mínimas entre
todos los aeropuertos seleccionados.
```

**Algoritmo:** Floyd-Warshall.

---

## Componentes fuertemente conexas

Datasets recomendados:

- Email-Eu-core
- OpenFlights
- Notre Dame Web

Ejemplo:

```text
Encontrar grupos maximales de nodos donde todos
puedan alcanzar a todos siguiendo las direcciones
de las aristas.
```

**Algoritmos citados en las diapositivas:** Kosaraju, Tarjan o Gabow.

---

## Ordenación topológica

Para este problema el dataset debe representar **dependencias** y ser un DAG.

Ejemplo de modelado:

```text
Tarea A -> Tarea B
```

significa que `A` debe finalizar antes de comenzar `B`.

Problema:

```text
Encontrar un orden de ejecución que respete
todas las dependencias.
```

**Algoritmos:**

- Kahn.
- Ordenación topológica basada en DFS.

Una variante docente interesante consiste en construir el grafo a partir de las dependencias de paquetes de un proyecto software.

---

## Puntos de articulación

Datasets recomendados:

- red eléctrica de MATPOWER
- RoadNet-CA
- Facebook
- DBLP
- Autonomous Systems

Ejemplo:

```text
Si desaparece este nodo,
¿queda una parte de la red incomunicada?
```

**Algoritmo:** Tarjan para puntos de articulación.

---

## Circuito de Euler

Especialmente adecuado para redes de calles.

Ejemplo:

```text
Un vehículo debe recorrer todas las calles
exactamente una vez y regresar al punto inicial.
```

En un grafo no dirigido existe un circuito de Euler cuando el grafo es conexo y todos sus vértices tienen grado par.

Aplicaciones:

- barrido de calles;
- inspección de tramos;
- juegos de dibujar una figura sin levantar el lápiz.

---

# 4. Problemas NP tratados en las diapositivas

## Ciclo hamiltoniano

> Determinar si existe un ciclo simple que visite todos los vértices exactamente una vez.

Ejemplo con rutas:

```text
¿Existe una ruta circular que visite todas las ciudades
exactamente una vez?
```

---

## Traveling Salesman Problem — TSP

> En un grafo completo y ponderado, encontrar el ciclo de menor coste que pase por todos los nodos.

Ejemplo:

```text
Un repartidor debe visitar todas las localidades
y volver al origen.

¿Qué ruta minimiza la distancia total?
```

---

## Coloración de grafos

> Colorear los vértices utilizando el mínimo número de colores de forma que dos vértices adyacentes no tengan el mismo color.

Aplicaciones posibles:

```text
asignación de horarios
asignación de recursos incompatibles
coloración de mapas
```

---

## Isomorfismo de grafos

> Dados dos grafos, determinar si existe una biyección entre sus vértices que preserve las aristas.

Puede utilizarse como ejercicio para comparar distintas representaciones de una misma estructura.

---

# 5. Propuesta de secuencia de ejercicios

Una posible progresión para las prácticas sería:

| Nº | Dataset | Problema | Algoritmo |
|---:|---|---|---|
| 1 | Facebook | Recorrer la red desde un usuario | DFS |
| 2 | Facebook | Grados de separación | BFS |
| 3 | Facebook | Componentes sociales | BFS / DFS |
| 4 | Email-Eu-core | Detectar ciclos de comunicación | DFS |
| 5 | Email-Eu-core | Componentes fuertemente conexas | Kosaraju / Tarjan / Gabow |
| 6 | OpenFlights | Ruta con menor número de vuelos | BFS |
| 7 | OpenFlights | Ruta de menor distancia | Dijkstra |
| 8 | OpenFlights reducido | Caminos mínimos entre todos los aeropuertos | Floyd-Warshall |
| 9 | MATPOWER | Detectar nodos críticos de la red | Puntos de articulación |
| 10 | MATPOWER | Conectar toda la red con coste mínimo | Prim / Kruskal |
| 11 | Grafo de dependencias | Ordenar tareas | Kahn / DFS |
| 12 | Red de calles adecuada | Recorrer cada calle una vez | Circuito de Euler |
| 13 | Ciudades | Visitar todos los nodos una vez | Ciclo hamiltoniano |
| 14 | Ciudades ponderadas | Visitar todos los nodos minimizando el coste | TSP |
| 15 | Mapa / conflictos | Asignar el mínimo número de colores | Coloración |

---

# 6. Una opción especialmente buena: OpenFlights como hilo conductor

Un mismo dataset permite introducir varios problemas diferentes.

```text
                     OpenFlights
                          |
        +-----------------+------------------+
        |                 |                  |
  alcanzabilidad    menos vuelos      menor distancia
        |                 |                  |
     DFS/BFS             BFS              Dijkstra
                                              |
                                  todos contra todos
                                              |
                                       Floyd-Warshall
```

Ejercicios:

1. **¿Se puede llegar de `A` a `B`?**  
   DFS o BFS.

2. **¿Qué aeropuertos son alcanzables desde `A`?**  
   DFS o BFS.

3. **¿Qué ruta requiere menos vuelos entre `A` y `B`?**  
   BFS.

4. **¿Qué ruta tiene menor distancia total?**  
   Dijkstra.

5. **¿Cuáles son las distancias mínimas entre todos los aeropuertos de un subconjunto?**  
   Floyd-Warshall.

6. **¿Qué grupos de aeropuertos son mutuamente alcanzables?**  
   Componentes fuertemente conexas.

Esto permite mostrar que **el algoritmo se elige en función del problema que se quiere resolver y no simplemente en función del dataset**.

---

# 7. Enlaces

- [OpenStreetMap](https://www.openstreetmap.org/)
- [aed-grafos-ejemplo — GitHub](https://github.com/AED-UMU/aed-grafos-ejemplo)
- [OpenFlights — Airport and Airline Data](https://openflights.org/data.php)
- [SNAP — colección de datasets](https://snap.stanford.edu/data/)
- [SNAP — Facebook](https://snap.stanford.edu/data/ego-Facebook.html)
- [SNAP — Email-Eu-core](https://snap.stanford.edu/data/email-Eu-core.html)
- [SNAP — RoadNet California](https://snap.stanford.edu/data/roadNet-CA.html)
- [SNAP — DBLP](https://snap.stanford.edu/data/com-DBLP.html)
- [SNAP — ArXiv GR-QC](https://snap.stanford.edu/data/ca-GrQc.html)
- [SNAP — Notre Dame Web Graph](https://snap.stanford.edu/data/web-NotreDame.html)
- [SNAP — Autonomous Systems](https://snap.stanford.edu/data/as-733.html)
- [SNAP — Amazon](https://snap.stanford.edu/data/com-Amazon.html)
- [MATPOWER](https://matpower.org/)
- [MATPOWER — GitHub](https://github.com/MATPOWER/matpower)
- [MATPOWER — IEEE 14-bus case](https://github.com/MATPOWER/matpower/blob/master/data/case14.m)
