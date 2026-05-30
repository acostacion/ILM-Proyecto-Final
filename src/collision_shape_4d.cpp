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

    // Filtrar duplicados con tolerancia y descartar NaN
    PackedVector3Array unique_points;
    const float tol = 0.01f;

    // print_verbose("[CollisionShape4D] recibidos: " + String::num(points.size()));
    for (int i = 0; i < points.size(); i++)
    {
        Vector3 p = points[i];

        if (Math::is_nan(p.x) || Math::is_nan(p.y) || Math::is_nan(p.z))
            continue;

        bool found = false;
        for (int j = 0; j < unique_points.size(); j++)
        {
            if (p.distance_to(unique_points[j]) < tol)
            {
                found = true;
                break;
            }
        }
        if (!found)
            unique_points.append(p);
    }
    // print_verbose("[CollisionShape4D] unicos: " + String::num(unique_points.size()));
    if (unique_points.size() >= 4)
        shape->set_points(unique_points);
    // Verificar que los puntos no tengan volumen para evitar error de convexidad
    Vector3 min_p = unique_points[0];
    Vector3 max_p = unique_points[0];
    for (int i = 1; i < unique_points.size(); i++)
    {
        min_p = min_p.min(unique_points[i]);
        max_p = max_p.max(unique_points[i]);
    }
    Vector3 extent = max_p - min_p;

    // Si alguna dimension es casi 0, los puntos son planos o lineales, lo que da error de convexidad. 
    // Evitar actualizar en ese caso.
    if (extent.x < tol || extent.y < tol || extent.z < tol)
        return;

    shape->set_points(unique_points);
}