#include "rigid_body_4d.h"
#include <godot_cpp/core/class_db.hpp>

using namespace godot;

void RigidBody4D::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("set_w_rotation_factor", "factor"), &RigidBody4D::set_w_rotation_factor);
    ClassDB::bind_method(D_METHOD("get_w_rotation_factor"), &RigidBody4D::get_w_rotation_factor);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "w_rotation_factor"), "set_w_rotation_factor", "get_w_rotation_factor");
}

void RigidBody4D::_physics_process(double delta)
{
    // Leer velocidad angular de la fisica 3D
    Vector3 ang_vel = get_angular_velocity();

    // Buscar hijos Node4D y empujarles rotacion W
    for (int i = 0; i < get_child_count(); i++)
    {
        Node4D *node4d = Object::cast_to<Node4D>(get_child(i));
        if (!node4d)
            continue;

        // Leer rotacion actual y sumar la generada por fisica
        Rotation4D rot = node4d->get_rotation();
        
        node4d->set_rot_xw(rot.xw + ang_vel.x * w_rotation_factor * delta);
        node4d->set_rot_yw(rot.yw + ang_vel.y * w_rotation_factor * delta);
        node4d->set_rot_zw(rot.zw + ang_vel.z * w_rotation_factor * delta);
    }
}