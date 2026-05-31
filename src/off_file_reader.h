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
        String _rutaCarmen = "C:/Users/Usuario/Music/ILM Proyecto Final/src/off_meshes/"; // TODO kitar luego cuando se solucione

    public:
        OffFileReader() = default;
        ~OffFileReader() = default;

        void loadOffFile(String file);
    };
}