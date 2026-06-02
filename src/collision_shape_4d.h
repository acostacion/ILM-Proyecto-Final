#pragma once

#include <godot_cpp/classes/collision_shape3d.hpp>
#include <godot_cpp/classes/convex_polygon_shape3d.hpp>

namespace godot
{
    class MeshInstance4D; // Forward declaration

    // CollisionShape4D es un CollisionShape3D que actualiza su forma cada frame 
    // para representar la proyeccion de la mesh 4D en el mundo 3D.
    class CollisionShape4D : public CollisionShape3D
    {
        GDCLASS(CollisionShape4D, CollisionShape3D)

    protected:
        Ref<ConvexPolygonShape3D> shape;
        MeshInstance4D *target = nullptr;
        // Para evitar procesar geometria repetida
        uint64_t last_version = 0;

        static void _bind_methods();

    public:
        CollisionShape4D() = default;
        ~CollisionShape4D() = default;

        void _ready() override;
        void _process(double delta) override;
    };
}