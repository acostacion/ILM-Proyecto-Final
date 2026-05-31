#pragma once
#include <vector>
#include <unordered_map>

#include <godot_cpp/classes/primitive_mesh.hpp>
#include <godot_cpp/variant/vector4.hpp>

#include "mesh_4d.hpp"
#include "off_file_reader.h"

namespace godot
{
    class Hexadecachoron : public OffFileReader
    {
        GDCLASS(Hexadecachoron, OffFileReader)
    protected:
        Vector4 size = {1, 1, 1, 1};

        static void _bind_methods();

    public:
        Hexadecachoron();
        ~Hexadecachoron() = default;

        // SETTERS Y GETTERS
        void set_size(Vector4 p_size) { size = p_size; }
        Vector4 get_size() {return size;}
    };

} // namespace godot