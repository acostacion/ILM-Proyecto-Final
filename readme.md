# Proyecto final ILM 25/26
## Autores
Carmen Becerra Gómez
Andrés García Navarro

## Descripción
Este proyecto consiste en el desarrollo de una extensión para el motor de desarrollo Godot que proporciona herramientas para crear nodos en 4 dimensiones asi como su renderizado.
Estamos aplicando esta extensión en un proyecto donde se mostrara el efecto del 4D a traves de un entorno en cuatro dimensiones del cual se podrá ver una unica seccion de esta cuarta dimensión, 

## Diagrama de clases

```mermaid
classDiagram

    class Node3D { Clase de Godot }

    class Node4D {
        + struct Rotation4D
        + static Vector4 rotate4D(Vector4 v, Rotation4D r)

        + Vector4 position
        + Vector4 scale
        + Rotation4D rot -> XY, XZ, XW, YZ, YW, ZW

        + getters y setters de pos, rot, scale... ()
    }

    class Resource { Clase de Godot }

    class Mesh4D {
        + static int count_set_bits(int n)
        + static Vector3 v4_to_v3(const Vector4 &v4, bool orthographic, float projection_distance, Vector4 p_scale)
        
        + struct Vertex
        + struct Triangle

        + vector~Vector4~ vertices
        + vector~Triangle~ faces

        + virtual void _generate_vertices()
        + virtual void _generate_faces()

        + getters y setters de vertices, faces... ()
    }

    class MeshInstance4D {
        + void draw_faces(const std::vector<Vector4> &transformed_vertex)
        + void draw_edges(const std::vector<Vector4> &transformed_vertex)

        + Ref~Mesh4D~ mesh
        + MeshInstance3D mesh_instance

        + bool show_edges
        + bool show_faces

        + float w_min
        + float w_max
        + float projection_distance
        + bool orthographic
        + PackedVector3Array projected_points

        + getters y setters de todos los parámetros de esta clase... ()
    }

    class RigidBody3D { Clase de Godot }

    class RigidBody4D {
        + float w_rotation_factor

        + _physics_process(double delta) override
        + getters y setters de w_rotation_factor... ()
    }

    class CollisionShape3D { Clase de Godot }

    class CollisionShape4D {
        + Ref~ConvexPolygonShape3D~ shape
        + MeshInstance4D target

        + _ready() override
        + _process(double delta) override
    }

    class GenericMesh4D {
        +Ref~Mesh~ mesh // mesh en 3D original

        + _generate_vertices() override
        + _generate_faces() override

        + getters y setters de mesh... ()
    }

    class Tesseract {
        + _generate_vertices() override
        + _generate_faces() override
    }

    class OffFileReader { + void loadOffFile(String file) }
    class Pentachoron {}
    class Hexadecachoron {}
    class Icositetrachoron {}
    class Hexacosichoron {}
    class GrandHexacosichoron {}

    Node3D <|-- Node4D
    Resource <|-- Mesh4D
    RigidBody3D <|-- RigidBody4D
    CollisionShape3D <|-- CollisionShape4D

    Node4D <|-- MeshInstance4D

    Mesh4D <|-- GenericMesh4D
    Mesh4D <|-- Tesseract
    Mesh4D <|-- OffFileReader

    OffFileReader <|-- Pentachoron
    OffFileReader <|-- Hexadecachoron
    OffFileReader <|-- Icositetrachoron
    OffFileReader <|-- Hexacosichoron
    OffFileReader <|-- GrandHexacosichoron
```
