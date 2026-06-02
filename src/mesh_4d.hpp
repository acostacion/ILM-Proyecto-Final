#pragma once
#include <vector>

#include <godot_cpp/variant/vector3.hpp>
#include <godot_cpp/variant/vector4.hpp>
#include <godot_cpp/core/math.hpp>
#include <godot_cpp/classes/resource.hpp>
#include <godot_cpp/core/memory.hpp>

namespace godot
{
    // Proyecta un Vector4 a Vector3 usando proyeccion perspectiva u ortografica
    inline Vector3 v4_to_v3(const Vector4 &v4, bool orthographic, float projection_distance, Vector4 p_scale = Vector4(1, 1, 1, 1))
    {
        float scale = 1.0f;
        if (!orthographic)
        {
            float denom = projection_distance - v4.w;
            if (Math::abs(denom) < 1e-6f)
                denom = 1e-6f;
            scale = projection_distance / denom;
        }

        return Vector3(v4.x * p_scale.x * scale, v4.y * p_scale.y * scale, v4.z * p_scale.z * scale);
    }

    // Cada vertice tiene un indice unico
    // Cada vertice es un Vector4 (x, y, z, w)
    struct Vertex
    {
        int index;
        Vector4 position;
        bool operator==(const Vertex &other) const
        {
            return position == other.position;
        }
    };
    // Cada cara es minimo un triangulo formado por 3 vertices, referenciados por sus indices
    struct Triangle
    {
        int v1, v2, v3; // Indices de los vertices que forman el triangulo
    };

    // Clase recurso que representa una malla 4D, con vertices y caras.
    // Es la clase base para objetos 4D como el Tesseract, offReader, GenericMesh4D, que generan su propia geometria.
    class Mesh4D : public Resource
    {
        GDCLASS(Mesh4D, Resource)
    protected:
        // vector de vertices que forman la mesh
        std::vector<Vertex> vertices;
        // vector de triangulos que forman las caras de la mesh
        std::vector<Triangle> faces;

        static void _bind_methods() {};
        // Generar los vertices de la mesh, implementado por clases hijas
        virtual void _generate_vertices() {};
        // Generar las caras de la mesh, implementado por clases hijas
        virtual void _generate_faces() {};

    public:
        Mesh4D() = default;
        ~Mesh4D() = default;

        // GETTERS Y SETTERS
        const std::vector<Vertex> &get_vertices() const { return vertices; }
        const std::vector<Triangle> &get_faces() const { return faces; }
    };
}