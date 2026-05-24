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
            // Si es PrimitiveMesh, obtener su ArrayMesh
            if (p_mesh->get_class() == StringName("PrimitiveMesh"))
            {
                Ref<PrimitiveMesh> prim = p_mesh;
                Ref<ArrayMesh> arr_mesh = memnew(ArrayMesh);
                // Crear surface desde los datos de la primitiva
                arr_mesh->add_surface_from_arrays(
                    Mesh::PRIMITIVE_TRIANGLES,
                    prim->surface_get_arrays(0)
                );
                mesh = arr_mesh;
            }
            else
            {
                mesh = p_mesh;
            }
            
            if (mesh.is_valid())
            {
                _generate_vertices();
                _generate_faces();
            }
        }
        Ref<Mesh> get_mesh() { return mesh; }
    };

} // namespace godot