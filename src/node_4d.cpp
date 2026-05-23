#include "node_4d.hpp"
using namespace godot;

void Node4D::_bind_methods()
{
    // ClassDB::bind_method(D_METHOD("nombre_en_editor"), &Clase::metodo_cpp);
    ClassDB::bind_method(D_METHOD("set_position"), &Node4D::set_position);
    ClassDB::bind_method(D_METHOD("get_position"), &Node4D::get_position);
    // ClassDB::bind_method(D_METHOD("set_rotation"), &Node4D::set_rotation);
    // ClassDB::bind_method(D_METHOD("get_rotation"), &Node4D::get_rotation);
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

    // ADD_PROPERTY(PropertyInfo(Variant::TIPO, "nombre_propiedad"), "set_nombre", "get_nombre");
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

godot::Node4D::Node4D() : position(0, 0, 0, 0), rotation(0, 0, 0, 0, 0, 0), scale(1, 1, 1, 1)
{
}

void godot::Node4D::_process(double delta)
{
}
