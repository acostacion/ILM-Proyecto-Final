#pragma once
#include <vector>
#include <unordered_map>

#include <godot_cpp/classes/primitive_mesh.hpp>
#include <godot_cpp/variant/vector4.hpp>

#include "mesh_4d.hpp"

namespace godot
{
    class Icositetrachoron : public Mesh4D
    {
        GDCLASS(Icositetrachoron, Mesh4D)
    protected:
        Vector4 size = {1, 1, 1, 1};

        static void _bind_methods();
        void _generate_vertices() override;
        void _generate_faces() override;

    public:
        Icositetrachoron();
        ~Icositetrachoron() = default;

        // SETTERS Y GETTERS
        void set_size(Vector4 p_size) { size = p_size; }
        Vector4 get_size() {return size;}
    };

} // namespace godot