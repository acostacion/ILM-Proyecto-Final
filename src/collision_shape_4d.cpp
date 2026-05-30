#include "collision_shape_4d.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/rigid_body3d.hpp>

#include "mesh_instance_4d.h"

using namespace godot;

void CollisionShape4D::_bind_methods()
{
}
void CollisionShape4D::_ready()
{

    shape.instantiate();
    set_shape(shape);
    // Buscar el MeshInstance4D entre los hermanos
    Node *parent = get_parent(); // RigidBody3D
    if (!parent)
    {
        print_error("[CollisionShape4D] Sin nodo padre");
        return;
    }

    // Iterar sobre los hijos del padre (mis hermanos)
    for (int i = 0; i < parent->get_child_count(); i++)
    {
        Node *sibling = parent->get_child(i);
        MeshInstance4D *mesh_inst = Object::cast_to<MeshInstance4D>(sibling);

        if (mesh_inst)
        {
            target = mesh_inst;
            print_verbose("[CollisionShape4D] MeshInstance4D encontrado");
            break;
        }
    }

    if (!target)
    {
        print_error("[CollisionShape4D] No se encontro MeshInstance4D hermano");
    }
}

void godot::CollisionShape4D::_process(double delta)
{
    if (!target)
    {
        print_error("[CollisionShape4D] target es nullptr");
        return;
    }

    // Leer geometria del observado
    const PackedVector3Array &points = target->get_projected_points();
    // Imposible formar un volumen con menos de 4 puntos
    if (points.size() < 4)
        return;

    // Validar NaN y calcular bounding box en una pasada
    Vector3 min_p, max_p;
    bool first = true;
    for (int i = 0; i < points.size(); i++)
    {
        Vector3 p = points[i];
        if (Math::is_nan(p.x) || Math::is_nan(p.y) || Math::is_nan(p.z))
            return;  // Punto roto => no actualizar este frame

        if (first) { min_p = max_p = p; first = false; }
        else { min_p = min_p.min(p); max_p = max_p.max(p); }
    }

    // Si es coplanar/colineal (alguna dimension cerca de 0), el hull falla y no se actualiza
    // mejor no actualizar que mostrar un hull roto
    Vector3 extent = max_p - min_p;
    if (extent.x < 0.01f || extent.y < 0.01f || extent.z < 0.01f)
        return;

    shape->set_points(points);
}