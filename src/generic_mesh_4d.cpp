#include "generic_mesh_4d.h"

using namespace godot;

void GenericMesh4D::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("set_mesh", "mesh"), &GenericMesh4D::set_mesh);
    ClassDB::bind_method(D_METHOD("get_mesh"), &GenericMesh4D::get_mesh);    
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "mesh", PROPERTY_HINT_RESOURCE_TYPE, "Mesh"), "set_mesh", "get_mesh");
}

void GenericMesh4D::_generate_vertices()
{    
    vertices.clear();

    // Validar que la mesh exista y tenga surfaces
    if (!mesh.is_valid() || mesh->get_surface_count() == 0)
    {
        print_error("[MeshInstance4D] Mesh no valida o sin superficies");
        return;
    }

    // Obtener los arrays del primer surface
    Array surface_arrays = mesh->surface_get_arrays(0);

    // ARRAY_VERTEX contiene los vertices como Vector3
    PackedVector3Array vertices_3d = surface_arrays[Mesh::ARRAY_VERTEX];

    // Convertir cada vertice 3D a 4D (agregando W=0)
    for (int i = 0; i < vertices_3d.size(); i++)
    {
        Vector3 v3 = vertices_3d[i];
        Vector4 v4(v3.x, v3.y, v3.z, 0.0f); // W=0 por defecto
        vertices.push_back({i, v4});
    }
}

void GenericMesh4D::_generate_faces()
{    
    faces.clear();

    if (!mesh.is_valid() || mesh->get_surface_count() == 0)
    {
        print_error("[MeshInstance4D] Mesh no valida o sin superficies");
        return;
    }

    // Obtener los arrays del primer surface
    Array surface_arrays = mesh->surface_get_arrays(0);

    // ARRAY_INDEX contiene los indices como enteros
    PackedInt32Array indices = surface_arrays[Mesh::ARRAY_INDEX];

    // Los indices vienen en trio. (i0, i1, i2) forman un triangulo
    for (int i = 0; i < indices.size(); i += 3)
    {
        faces.push_back({indices[i], indices[i + 1], indices[i + 2]});
    }
}

GenericMesh4D::GenericMesh4D()
{}
