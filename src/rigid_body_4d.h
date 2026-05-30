#pragma once
#include "node_4d.hpp"
#include <godot_cpp/classes/rigid_body3d.hpp>

namespace godot
{
    class RigidBody4D : public RigidBody3D
    {
        GDCLASS(RigidBody4D, RigidBody3D)

    protected:
        // Cuanto afecta la velocidad angular 3D a la rotacion W
        float w_rotation_factor = 1.0f;

        static void _bind_methods();

    public:
        RigidBody4D() = default;
        ~RigidBody4D() = default;

        void _physics_process(double delta) override;

        void set_w_rotation_factor(float p_factor) { w_rotation_factor = p_factor; }
        float get_w_rotation_factor() const { return w_rotation_factor; }
    };
}