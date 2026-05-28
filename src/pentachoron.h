#pragma once
#include <vector>
#include <unordered_map>

#include <godot_cpp/classes/primitive_mesh.hpp>
#include <godot_cpp/variant/vector4.hpp>

#include "mesh_4d.hpp"

namespace godot
{
    class Pentachoron : public Mesh4D
    {
        GDCLASS(Pentachoron, Mesh4D)
    protected:
        // Size de los lados del hypercube
        Vector4 size = {1, 1, 1, 1};

        static void _bind_methods();
        // Generar los 16 vertices ( 8 vertices 1 cubo * 2 cubos)
        void _generate_vertices() override;
        // Generar los 24 cuadrados (6 caras * 4 cuadrados por cara)
        void _generate_faces() override;

    public:
        Pentachoron();
        ~Pentachoron() = default;

        // SETTERS Y GETTERS
        void set_size(Vector4 p_size) { size = p_size; }
        Vector4 get_size() {return size;}
    };

} // namespace godot