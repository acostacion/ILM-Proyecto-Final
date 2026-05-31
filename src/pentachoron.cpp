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
    // https://polytope.miraheze.org/wiki/Pentachoron
    vertices.push_back({0, Vector4(1.0f/2.0f,  -sqrt(3.0f)/6.0f, -sqrt(6.0f)/12.0f, -sqrt(10.0f)/20.0f)});
    vertices.push_back({1, Vector4(-1.0f/2.0f, -sqrt(3.0f)/6.0f, -sqrt(6.0f)/12.0f, -sqrt(10.0f)/20.0f)});
    vertices.push_back({2, Vector4(0.0f,        sqrt(3.0f)/3.0f, -sqrt(6.0f)/12.0f, -sqrt(10.0f)/20.0f)});
    vertices.push_back({3, Vector4(0.0f,        0.0f,             sqrt(6.0f)/4.0f,  -sqrt(10.0f)/20.0f)});
    vertices.push_back({4, Vector4(0.0f,        0.0f,             0.0f,              sqrt(10.0f)/5.0f)});
}

void godot::Pentachoron::_generate_faces() {
    faces.clear();
    faces.reserve(10);

    // primero voy a hacer los triangulos de los de fuera
    faces.push_back({3, 0, 1});
    faces.push_back({3, 1, 2});
    faces.push_back({3, 2, 0});
    faces.push_back({0, 2, 1});

    // ahora los triangulos qeu forman con el de dentro
    faces.push_back({3, 4, 0});
    faces.push_back({3, 1, 4});
    faces.push_back({3, 4, 2});
    faces.push_back({4, 1, 8});
    faces.push_back({4, 2, 1});
    faces.push_back({4, 0, 2});
}

godot::Pentachoron::Pentachoron() : size(1, 1, 1, 1) {
    _generate_vertices();
    _generate_faces();
}
