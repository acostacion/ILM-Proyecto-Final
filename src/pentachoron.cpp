#include "pentachoron.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/memory.hpp>
#include <cstdint>

#include <godot_cpp/variant/vector4.hpp>
#include <godot_cpp/variant/vector3.hpp>
#include <godot_cpp/classes/standard_material3d.hpp>
#include <godot_cpp/variant/color.hpp>

using namespace godot;

void godot::Pentachoron::_bind_methods() {
    ClassDB::bind_method(D_METHOD("set_size", "size"), &Pentachoron::set_size);
    ClassDB::bind_method(D_METHOD("get_size"), &Pentachoron::get_size);
    // Propiedades
    ADD_PROPERTY(PropertyInfo(Variant::VECTOR4, "size"), "set_size", "get_size");
}

void godot::Pentachoron::_generate_vertices() {
    vertices.push_back({0, Vector4(0.158113883008419f, 0.204124145231932f, 0.288675134594813f, 0.5f)});
    vertices.push_back({1, Vector4(0.158113883008419f, 0.204124145231932f, 0.288675134594813f, -0.5f)});
    vertices.push_back({2, Vector4(0.158113883008419f, 0.204124145231932f, -0.577350269189626f, 0.0f)});
    vertices.push_back({3, Vector4(0.158113883008419f, -0.612372435695794f, 0.0f, 0.0f)});
    vertices.push_back({4, Vector4(-0.632455532033676f, 0.0f, 0.0f, 0.0f)});
}

void godot::Pentachoron::_generate_faces() {
    faces.clear();
    faces.reserve(10);

    faces.push_back({0, 3, 4});
    faces.push_back({0, 2, 4});
    faces.push_back({2, 3, 4});
    faces.push_back({0, 2, 3});
    faces.push_back({0, 1, 4});
    faces.push_back({1, 3, 4});
    faces.push_back({0, 1, 3});
    faces.push_back({1, 2, 4});
    faces.push_back({0, 1, 2});
    faces.push_back({1, 2, 3});
}

godot::Pentachoron::Pentachoron() : size(1, 1, 1, 1) {
    // https://polytope.miraheze.org/wiki/File:Pentachoron.off
    _generate_vertices();
    _generate_faces();
}
