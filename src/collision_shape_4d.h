#pragma once

#include <godot_cpp/classes/collision_shape3d.hpp>
#include <godot_cpp/classes/convex_polygon_shape3d.hpp>

namespace godot
{
    class MeshInstance4D; // Forward declaration

    class CollisionShape4D : public CollisionShape3D
    {
        GDCLASS(CollisionShape4D, CollisionShape3D)

    protected:
        Ref<ConvexPolygonShape3D> shape;
        MeshInstance4D *target = nullptr;

        static void _bind_methods();

    public:
        CollisionShape4D();
        ~CollisionShape4D() = default;

        void _ready() override;
        void _process(double delta) override;
    };
}