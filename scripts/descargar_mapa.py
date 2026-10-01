#!/usr/bin/env python3
"""Descarga la red de conducción de Murcia y la convierte a formato de texto."""

from pathlib import Path

import osmnx as ox


ROOT = Path(__file__).resolve().parent.parent
OUTPUT = ROOT / "data" / "murcia.graph"


def main():
    print('Descargando la red de conducción de "Murcia, Spain"...')
    graph = ox.graph_from_place("Murcia, Spain", network_type="drive")
    graph = ox.routing.add_edge_speeds(graph)
    graph = ox.routing.add_edge_travel_times(graph)

    nodes = sorted(graph.nodes(data=True), key=lambda item: int(item[0]))
    # Conservamos la orientación de cada arco del grafo dirigido de OSMnx.
    edges = sorted(
        graph.edges(data=True),
        key=lambda item: (int(item[0]), int(item[1]), float(item[2].get("travel_time", 0))),
    )

    OUTPUT.parent.mkdir(parents=True, exist_ok=True)
    with OUTPUT.open("w", encoding="utf-8") as file:
        file.write(f"{len(nodes)}\n")
        for node_id, attributes in nodes:
            file.write(
                f"{int(node_id)} {attributes['y']:.8f} {attributes['x']:.8f}\n"
            )
        file.write(f"{len(edges)}\n")
        for origin, destination, attributes in edges:
            travel_time = float(attributes["travel_time"])
            street_name = attributes.get("name", "")
            if isinstance(street_name, list):
                street_name = ", ".join(str(name) for name in street_name)
            street_name = str(street_name).replace("\t", " ").replace("\n", " ")
            file.write(
                f"{int(origin)} {int(destination)} {travel_time:.3f} "
                f"{float(attributes['length']):.3f}\t{street_name}\n"
            )

    print(f"Guardados {len(nodes)} cruces y {len(edges)} tramos en {OUTPUT}")


if __name__ == "__main__":
    main()
