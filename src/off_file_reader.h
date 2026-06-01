#pragma once
#include "mesh_4d.hpp"
#include <string>
#include <fstream>
#include <vector>

namespace godot
{
    class OffFileReader : public Mesh4D
    {
        GDCLASS(OffFileReader, Mesh4D)

    protected:
        static void _bind_methods();
        String _rutaCarmen = "C:/Users/Usuario/Music/ILM Proyecto Final/src/off_meshes/"; // TODO kitar luego cuando se solucione
        String off_path;
    public:
        OffFileReader() = default;
        ~OffFileReader() = default;

        void loadOffFile(String file);

        void OffFileReader::set_off_path(const String &p)
        {
            off_path = p;
            loadOffFile(off_path);
        }

        String OffFileReader::get_off_path() const
        {
            return off_path;
        }
    };
}