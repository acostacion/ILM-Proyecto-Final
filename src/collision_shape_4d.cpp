#include "collision_shape_4d.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/rigid_body3d.hpp>

#include "mesh_instance_4d.h"

using namespace godot;

void CollisionShape4D::_bind_methods()
{}

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
        return;

    uint64_t v = target->get_projection_version();
    if (v == last_version)
        return;
    last_version = v;

    // Leer geometria del observado
    const PackedVector3Array &points = target->get_projected_points();

    // print_verbose("[CollisionShape4D] recibidos: " + String::num(points.size()));
    // Filtrar NaN/infinitos
    PackedVector3Array clean;
    for (int i = 0; i < points.size(); i++)
        if (points[i].is_finite())
            clean.append(points[i]);

    if (clean.size() < 4) return;
    
    // Verificar que los puntos no tengan volumen para evitar error de convexidad
    Vector3 min_p = clean[0], max_p = clean[0];
    for (int i = 1; i < clean.size(); i++)
    {
        min_p = min_p.min(clean[i]);
        max_p = max_p.max(clean[i]);
    }
    Vector3 extent = max_p - min_p;

    // Si alguna dimension es casi 0, los puntos son planos o lineales, lo que da error de convexidad.
    // Evitar actualizar en ese caso.
    float tol = 0.01f;
    if (extent.x < tol || extent.y < tol || extent.z < tol)
        return;

    shape->set_points(clean);
}