#pragma once
#include <vector>
#include <unordered_map>

#include <godot_cpp/classes/primitive_mesh.hpp>
#include <godot_cpp/classes/array_mesh.hpp>
#include <godot_cpp/variant/vector4.hpp>

#include "mesh_4d.hpp"

namespace godot
{
    class GenericMesh4D : public Mesh4D
    {
        GDCLASS(GenericMesh4D, Mesh4D)
    protected:
        // Mesh 3D original
        Ref<Mesh> mesh;

        static void _bind_methods();
        // Generar los 16 vertices ( 8 vertices 1 cubo * 2 cubos)
        void _generate_vertices() override;
        // Generar los 24 cuadrados (6 caras * 4 cuadrados por cara)
        void _generate_faces() override;

    public:
        GenericMesh4D();
        ~GenericMesh4D() = default;

        // SETTERS Y GETTERS
        void set_mesh(Ref<Mesh> p_mesh)
        {
            print_verbose("[GENERIC] set_mesh() INICIO");

            if (!p_mesh.is_valid())
            {
                print_verbose("[GENERIC] mesh es nullptr");
                mesh = Ref<Mesh>(); // ← Cambiar nullptr por Ref<Mesh>()
                vertices.clear();
                faces.clear();
                return;
            }

            mesh = p_mesh;
            _generate_vertices();
            _generate_faces();

            print_verbose("[GENERIC] set_mesh() FIN");
        }
        Ref<Mesh> get_mesh() const
        {
            return mesh;
        }
    };

} // namespace godot