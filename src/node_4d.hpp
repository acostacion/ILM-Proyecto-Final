#pragma once

#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/classes/node.hpp>
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
        x = nx; y = ny;

        // XZ
        nx = x * cos(r.xz) - z * sin(r.xz);
        nz = x * sin(r.xz) + z * cos(r.xz);
        x = nx; z = nz;

        // XW
        nx = x * cos(r.xw) - w * sin(r.xw);
        nw = x * sin(r.xw) + w * cos(r.xw);
        x = nx; w = nw;

        // YZ
        ny = y * cos(r.yz) - z * sin(r.yz);
        nz = y * sin(r.yz) + z * cos(r.yz);
        y = ny; z = nz;

        // YW
        ny = y * cos(r.yw) - w * sin(r.yw);
        nw = y * sin(r.yw) + w * cos(r.yw);
        y = ny; w = nw;

        // ZW
        nz = z * cos(r.zw) - w * sin(r.zw);
        nw = z * sin(r.zw) + w * cos(r.zw);
        z = nz; w = nw;

        return Vector4(x, y, z, w);
    }
    class Node4D : public Node
    {
        GDCLASS(Node4D, Node);

    private:
    protected:
        Vector4 position;
        Rotation4D rotation;
        Vector4 scale;

        static void _bind_methods();

    public:
        Node4D();
        ~Node4D() = default;
        void _process(double delta) override;

        // GETTERS & SETTERS
        // Position
        virtual void set_position(Vector4 p_position) { position = p_position; }
        Vector4 get_position() const { return position; }
        // Rotation
        virtual void set_rotation(Rotation4D p_rotation) { rotation = p_rotation; }
        Rotation4D get_rotation() const { return rotation; }
        virtual void set_rot_xy(float p_xy) { rotation.xy = p_xy; }
        float get_rot_xy() const { return rotation.xy; }
        virtual void set_rot_xz(float p_xz) { rotation.xz = p_xz; }
        float get_rot_xz() const { return rotation.xz; }
        virtual void set_rot_xw(float p_xw) { rotation.xw = p_xw; }
        float get_rot_xw() const { return rotation.xw; }
        virtual void set_rot_yz(float p_yz) { rotation.yz = p_yz; }
        float get_rot_yz() const { return rotation.yz; }
        virtual void set_rot_yw(float p_yw) { rotation.yw = p_yw; }
        float get_rot_yw() const { return rotation.yw; }
        virtual void set_rot_zw(float p_zw) { rotation.zw = p_zw; }
        float get_rot_zw() const { return rotation.zw; }
        // Scale
        virtual void set_scale(Vector4 p_scale) { scale = p_scale; }
        Vector4 get_scale() const { return scale; }
    };
}