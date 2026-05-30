#include "collision_shape_4d.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/rigid_body3d.hpp>

#include "mesh_instance_4d.h"

using namespace godot;

void CollisionShape4D::_bind_methods()
{
}

CollisionShape4D::CollisionShape4D()
{
    shape.instantiate();
    set_shape(shape);
}

void CollisionShape4D::_ready()
{
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

    PackedVector3Array unique_points;

    for (int i = 0; i < points.size(); i++)
    {
        Vector3 p = points.get(i);
        bool found = false;
        for (int j = 0; j < unique_points.size(); j++)
        {
            if (unique_points.get(j) == p)
            {
                found = true;
                break;
            }
        }
        if (!found)
        {
            unique_points.append(p);
        }
    }

    if (unique_points.size() >= 4)
        shape->set_points(unique_points);
}