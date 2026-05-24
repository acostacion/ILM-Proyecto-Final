#pragma once
#include <vector>

#include <godot_cpp/classes/resource.hpp>
#include <godot_cpp/core/memory.hpp>

namespace godot
{
    // Brian Kernighan's Algorithm para contar bits activos
    static int count_set_bits(int n)
    {
        int count = 0;
        while (n > 0)
        {
            n &= (n - 1);
            count += 1;
        }
        return count;
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
    struct Triangle
    {
        int v1, v2, v3; // Indices de los vertices que forman el triangulo
    };

    class Mesh4D : public Resource
    {
        GDCLASS(Mesh4D, Resource)
    protected:
        // vector de vertices que forman la mesh
        std::vector<Vertex> vertices;
        // vector de triangulos que forman las caras de la mesh
        std::vector<Triangle> faces;

        static void _bind_methods() {};

        virtual void _generate_vertices() {};
        virtual void _generate_faces() {};

    public:
        Mesh4D() = default;
        ~Mesh4D() = default;

        const std::vector<Vertex> &get_vertices() const { return vertices; }
        const std::vector<Triangle> &get_faces() const { return faces; }
    };
}