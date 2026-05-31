#include "hexadecachoron.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/memory.hpp>
#include <cstdint>

#include <godot_cpp/variant/vector4.hpp>
#include <godot_cpp/variant/vector3.hpp>
#include <godot_cpp/classes/standard_material3d.hpp>
#include <godot_cpp/variant/color.hpp>

using namespace godot;

void godot::Hexadecachoron::_bind_methods() {
    ClassDB::bind_method(D_METHOD("set_size", "size"), &Hexadecachoron::set_size);
    ClassDB::bind_method(D_METHOD("get_size"), &Hexadecachoron::get_size);
    // Propiedades
    ADD_PROPERTY(PropertyInfo(Variant::VECTOR4, "size"), "set_size", "get_size");
}

void godot::Hexadecachoron::_generate_vertices() {
    vertices.push_back({0, Vector4(0.707106781186547f, 0.0f, 0.0f, 0.0f)});
    vertices.push_back({1, Vector4(0.0f, 0.0f, 0.0f, 0.707106781186547f)});
    vertices.push_back({2, Vector4(0.0f, 0.0f, 0.707106781186547f, 0.0f)});
    vertices.push_back({3, Vector4(0.0f, 0.707106781186547f, 0.0f, 0.0f)});
    vertices.push_back({4, Vector4(-0.707106781186547f, 0.0f, 0.0f, 0.0f)});
    vertices.push_back({5, Vector4(0.0f, 0.0f, 0.0f, -0.707106781186547f)});
    vertices.push_back({6, Vector4(0.0f, 0.0f, -0.707106781186547f, 0.0f)});
    vertices.push_back({7, Vector4(0.0f, -0.707106781186547f, 0.0f, 0.0f)});
}

void godot::Hexadecachoron::_generate_faces() {
    faces.clear();
    faces.reserve(32);

    faces.push_back({5, 6, 7});
    faces.push_back({4, 6, 7});
    faces.push_back({4, 5, 7});
    faces.push_back({4, 5, 6});
    faces.push_back({0, 6, 7});
    faces.push_back({0, 5, 7});
    faces.push_back({0, 5, 6});
    faces.push_back({1, 6, 7});
    faces.push_back({1, 4, 7});
    faces.push_back({1, 4, 6});
    faces.push_back({0, 1, 7});
    faces.push_back({0, 1, 6});
    faces.push_back({2, 5, 7});
    faces.push_back({0, 2, 7});
    faces.push_back({0, 2, 5});
    faces.push_back({2, 4, 7});
    faces.push_back({2, 4, 5});
    faces.push_back({1, 2, 7});
    faces.push_back({0, 1, 2});
    faces.push_back({1, 2, 4});
    faces.push_back({3, 5, 6});
    faces.push_back({3, 4, 6});
    faces.push_back({3, 4, 5});
    faces.push_back({0, 3, 6});
    faces.push_back({0, 3, 5});
    faces.push_back({1, 3, 6});
    faces.push_back({0, 1, 3});
    faces.push_back({1, 3, 4});
    faces.push_back({1, 2, 3});
    faces.push_back({2, 3, 4});
    faces.push_back({0, 2, 3});
    faces.push_back({2, 3, 5});
}

godot::Hexadecachoron::Hexadecachoron() : size(1, 1, 1, 1) {
    // https://polytope.miraheze.org/wiki/File:Hexadecachoron.off
    _generate_vertices();
    _generate_faces();
}