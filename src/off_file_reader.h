#pragma once
#include "mesh_4d.hpp"
#include <string>
#include <fstream>
#include <vector>

namespace godot {
    class OffFileReader : public Mesh4D {
        GDCLASS(OffFileReader, Mesh4D)

    protected:
        static void _bind_methods();

    public:
        OffFileReader() = default;
        ~OffFileReader() = default;

        void loadOffFile(std::string file);
    };
}