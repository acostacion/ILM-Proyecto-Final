#pragma once

#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/classes/node3d.hpp>
#include <godot_cpp/variant/vector4.hpp>
#include <cmath>

namespace godot
{
    struct Rotation4D
    {
        float xy, xz, xw, yz, yw, zw;

        Rotation4D(float p_xy, float p_xz, float p_xw, float p_yz, float p_yw, float p_zw) : xy(p_xy), xz(p_xz), xw(p_xw), yz(p_yz), yw(p_yw), zw(p_zw) {}

        bool operator==(const Rotation4D &other) const
        {
            return xy == other.xy && xz == other.xz && xw == other.xw &&
                   yz == other.yz && yw == other.yw && zw == other.zw;
        }
    };

    static inline Vector4 rotate4D(Vector4 v, Rotation4D r)
    {

        float x = v.x, y = v.y, z = v.z, w = v.w;
        float nx, ny, nz, nw;

        // XY
        nx = x * cos(r.xy) - y * sin(r.xy);
        ny = x * sin(r.xy) + y * cos(r.xy);
        x = nx;
        y = ny;

        // XZ
        nx = x * cos(r.xz) - z * sin(r.xz);
        nz = x * sin(r.xz) + z * cos(r.xz);
        x = nx;
        z = nz;

        // XW
        nx = x * cos(r.xw) - w * sin(r.xw);
        nw = x * sin(r.xw) + w * cos(r.xw);
        x = nx;
        w = nw;

        // YZ
        ny = y * cos(r.yz) - z * sin(r.yz);
        nz = y * sin(r.yz) + z * cos(r.yz);
        y = ny;
        z = nz;

        // YW
        ny = y * cos(r.yw) - w * sin(r.yw);
        nw = y * sin(r.yw) + w * cos(r.yw);
        y = ny;
        w = nw;

        // ZW
        nz = z * cos(r.zw) - w * sin(r.zw);
        nw = z * sin(r.zw) + w * cos(r.zw);
        z = nz;
        w = nw;

        return Vector4(x, y, z, w);
    }
    class Node4D : public Node3D
    {
        GDCLASS(Node4D, Node3D);

    private:
    protected:
        Vector4 position_4d = Vector4(0, 0, 0, 0);
        Rotation4D rotation_4d = Rotation4D(0, 0, 0, 0, 0, 0);
        Vector4 scale_4d = Vector4(1, 1, 1, 1);

        static void _bind_methods()
        {
            ClassDB::bind_method(D_METHOD("set_position"), &Node4D::set_position);
            ClassDB::bind_method(D_METHOD("get_position"), &Node4D::get_position);
            ClassDB::bind_method(D_METHOD("set_rot_xy"), &Node4D::set_rot_xy);
            ClassDB::bind_method(D_METHOD("get_rot_xy"), &Node4D::get_rot_xy);
            ClassDB::bind_method(D_METHOD("set_rot_xz"), &Node4D::set_rot_xz);
            ClassDB::bind_method(D_METHOD("get_rot_xz"), &Node4D::get_rot_xz);
            ClassDB::bind_method(D_METHOD("set_rot_xw"), &Node4D::set_rot_xw);
            ClassDB::bind_method(D_METHOD("get_rot_xw"), &Node4D::get_rot_xw);
            ClassDB::bind_method(D_METHOD("set_rot_yz"), &Node4D::set_rot_yz);
            ClassDB::bind_method(D_METHOD("get_rot_yz"), &Node4D::get_rot_yz);
            ClassDB::bind_method(D_METHOD("set_rot_yw"), &Node4D::set_rot_yw);
            ClassDB::bind_method(D_METHOD("get_rot_yw"), &Node4D::get_rot_yw);
            ClassDB::bind_method(D_METHOD("set_rot_zw"), &Node4D::set_rot_zw);
            ClassDB::bind_method(D_METHOD("get_rot_zw"), &Node4D::get_rot_zw);
            ClassDB::bind_method(D_METHOD("set_scale"), &Node4D::set_scale);
            ClassDB::bind_method(D_METHOD("get_scale"), &Node4D::get_scale);

            ADD_GROUP("4D Transform", "");
            ADD_PROPERTY(PropertyInfo(Variant::VECTOR4, "position"), "set_position", "get_position");
            ADD_GROUP("4D Rotation", "rot_");
            ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "rot_xy"), "set_rot_xy", "get_rot_xy");
            ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "rot_xz"), "set_rot_xz", "get_rot_xz");
            ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "rot_xw"), "set_rot_xw", "get_rot_xw");
            ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "rot_yz"), "set_rot_yz", "get_rot_yz");
            ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "rot_yw"), "set_rot_yw", "get_rot_yw");
            ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "rot_zw"), "set_rot_zw", "get_rot_zw");
            ADD_PROPERTY(PropertyInfo(Variant::VECTOR4, "scale"), "set_scale", "get_scale");
        }

    public:
        godot::Node4D::Node4D() : position_4d(0, 0, 0, 0), rotation_4d(0, 0, 0, 0, 0, 0), scale_4d(1, 1, 1, 1)
        {
        }
        ~Node4D() = default;

        // GETTERS & SETTERS
        // Position
        virtual void set_position(Vector4 p_position) { position_4d = p_position; }
        Vector4 get_position() const { return position_4d; }
        // Rotation
        virtual void set_rotation(Rotation4D p_rotation) { rotation_4d = p_rotation; }
        Rotation4D get_rotation() const { return rotation_4d; }
        virtual void set_rot_xy(float p_xy) { rotation_4d.xy = p_xy; }
        float get_rot_xy() const { return rotation_4d.xy; }
        virtual void set_rot_xz(float p_xz) { rotation_4d.xz = p_xz; }
        float get_rot_xz() const { return rotation_4d.xz; }
        virtual void set_rot_xw(float p_xw) { rotation_4d.xw = p_xw; }
        float get_rot_xw() const { return rotation_4d.xw; }
        virtual void set_rot_yz(float p_yz) { rotation_4d.yz = p_yz; }
        float get_rot_yz() const { return rotation_4d.yz; }
        virtual void set_rot_yw(float p_yw) { rotation_4d.yw = p_yw; }
        float get_rot_yw() const { return rotation_4d.yw; }
        virtual void set_rot_zw(float p_zw) { rotation_4d.zw = p_zw; }
        float get_rot_zw() const { return rotation_4d.zw; }
        // Scale
        virtual void set_scale(Vector4 p_scale) { scale_4d = p_scale; }
        Vector4 get_scale() const { return scale_4d; }
    };
}