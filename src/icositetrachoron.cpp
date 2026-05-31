#include "icositetrachoron.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/memory.hpp>
#include <cstdint>

#include <godot_cpp/variant/vector4.hpp>
#include <godot_cpp/variant/vector3.hpp>
#include <godot_cpp/classes/standard_material3d.hpp>
#include <godot_cpp/variant/color.hpp>

using namespace godot;

void godot::Icositetrachoron::_bind_methods() {
    ClassDB::bind_method(D_METHOD("set_size", "size"), &Icositetrachoron::set_size);
    ClassDB::bind_method(D_METHOD("get_size"), &Icositetrachoron::get_size);
    // Propiedades
    ADD_PROPERTY(PropertyInfo(Variant::VECTOR4, "size"), "set_size", "get_size");
}

void godot::Icositetrachoron::_generate_vertices() {
    vertices.push_back({0, Vector4(0.5f, 0.5f, 0.5f, 0.5f)});
    vertices.push_back({1, Vector4(0.5f, 0.5f, 0.5f, -0.5f)});
    vertices.push_back({2, Vector4(0.5f, 0.5f, -0.5f, 0.5f)});
    vertices.push_back({3, Vector4(0.5f, -0.5f, 0.5f, 0.5f)});
    vertices.push_back({4, Vector4(-0.5f, 0.5f, 0.5f, 0.5f)});
    vertices.push_back({5, Vector4(0.5f, 0.5f, -0.5f, -0.5f)});
    vertices.push_back({6, Vector4(0.5f, -0.5f, -0.5f, 0.5f)});
    vertices.push_back({7, Vector4(-0.5f, -0.5f, 0.5f, 0.5f)});
    vertices.push_back({8, Vector4(-0.5f, 0.5f, 0.5f, -0.5f)});
    vertices.push_back({9, Vector4(0.5f, -0.5f, 0.5f, -0.5f)});
    vertices.push_back({10, Vector4(-0.5f, 0.5f, -0.5f, 0.5f)});
    vertices.push_back({11, Vector4(0.5f, -0.5f, -0.5f, -0.5f)});
    vertices.push_back({12, Vector4(-0.5f, -0.5f, -0.5f, 0.5f)});
    vertices.push_back({13, Vector4(-0.5f, -0.5f, 0.5f, -0.5f)});
    vertices.push_back({14, Vector4(-0.5f, 0.5f, -0.5f, -0.5f)});
    vertices.push_back({15, Vector4(-0.5f, -0.5f, -0.5f, -0.5f)});
    vertices.push_back({16, Vector4(1.0f, 0.0f, 0.0f, 0.0f)});
    vertices.push_back({17, Vector4(0.0f, 0.0f, 0.0f, 1.0f)});
    vertices.push_back({18, Vector4(0.0f, 0.0f, 1.0f, 0.0f)});
    vertices.push_back({19, Vector4(0.0f, 1.0f, 0.0f, 0.0f)});
    vertices.push_back({20, Vector4(-1.0f, 0.0f, 0.0f, 0.0f)});
    vertices.push_back({21, Vector4(0.0f, 0.0f, 0.0f, -1.0f)});
    vertices.push_back({22, Vector4(0.0f, 0.0f, -1.0f, 0.0f)});
    vertices.push_back({23, Vector4(0.0f, -1.0f, 0.0f, 0.0f)});
}

void godot::Icositetrachoron::_generate_faces() {
    faces.clear();
    faces.reserve(96);

    faces.push_back({6, 12, 23});
    faces.push_back({12, 15, 23});
    faces.push_back({11, 15, 23});
    faces.push_back({6, 11, 23});
    faces.push_back({6, 11, 22});
    faces.push_back({11, 15, 22});
    faces.push_back({12, 15, 22});
    faces.push_back({6, 12, 22});
    faces.push_back({7, 12, 23});
    faces.push_back({3, 6, 23});
    faces.push_back({3, 7, 23});
    faces.push_back({7, 12, 17});
    faces.push_back({6, 12, 17});
    faces.push_back({3, 7, 17});
    faces.push_back({3, 6, 17});
    faces.push_back({13, 15, 23});
    faces.push_back({7, 13, 23});
    faces.push_back({7, 13, 20});
    faces.push_back({13, 15, 20});
    faces.push_back({7, 12, 20});
    faces.push_back({12, 15, 20});
    faces.push_back({9, 11, 23});
    faces.push_back({9, 13, 23});
    faces.push_back({9, 13, 21});
    faces.push_back({13, 15, 21});
    faces.push_back({9, 11, 21});
    faces.push_back({11, 15, 21});
    faces.push_back({3, 9, 23});
    faces.push_back({9, 11, 16});
    faces.push_back({6, 11, 16});
    faces.push_back({3, 9, 16});
    faces.push_back({3, 6, 16});
    faces.push_back({7, 13, 18});
    faces.push_back({9, 13, 18});
    faces.push_back({3, 9, 18});
    faces.push_back({3, 7, 18});
    faces.push_back({8, 13, 18});
    faces.push_back({8, 13, 20});
    faces.push_back({4, 7, 20});
    faces.push_back({4, 8, 20});
    faces.push_back({4, 7, 18});
    faces.push_back({4, 8, 18});
    faces.push_back({8, 13, 21});
    faces.push_back({1, 9, 21});
    faces.push_back({1, 8, 21});
    faces.push_back({1, 9, 18});
    faces.push_back({1, 8, 18});
    faces.push_back({14, 15, 21});
    faces.push_back({8, 14, 21});
    faces.push_back({14, 15, 20});
    faces.push_back({8, 14, 20});
    faces.push_back({5, 11, 16});
    faces.push_back({5, 11, 21});
    faces.push_back({1, 5, 21});
    faces.push_back({1, 5, 16});
    faces.push_back({1, 9, 16});
    faces.push_back({5, 11, 22});
    faces.push_back({2, 5, 22});
    faces.push_back({2, 6, 22});
    faces.push_back({2, 5, 16});
    faces.push_back({2, 6, 16});
    faces.push_back({5, 14, 21});
    faces.push_back({5, 14, 22});
    faces.push_back({14, 15, 22});
    faces.push_back({5, 14, 19});
    faces.push_back({8, 14, 19});
    faces.push_back({1, 5, 19});
    faces.push_back({1, 8, 19});
    faces.push_back({10, 12, 20});
    faces.push_back({10, 12, 17});
    faces.push_back({4, 10, 20});
    faces.push_back({4, 10, 17});
    faces.push_back({4, 7, 17});
    faces.push_back({10, 14, 22});
    faces.push_back({2, 10, 22});
    faces.push_back({10, 14, 19});
    faces.push_back({2, 5, 19});
    faces.push_back({2, 10, 19});
    faces.push_back({10, 12, 22});
    faces.push_back({10, 14, 20});
    faces.push_back({2, 10, 17});
    faces.push_back({2, 6, 17});
    faces.push_back({4, 10, 19});
    faces.push_back({4, 8, 19});
    faces.push_back({0, 1, 16});
    faces.push_back({0, 2, 19});
    faces.push_back({0, 2, 16});
    faces.push_back({0, 1, 19});
    faces.push_back({0, 3, 18});
    faces.push_back({0, 3, 16});
    faces.push_back({0, 1, 18});
    faces.push_back({0, 4, 17});
    faces.push_back({0, 2, 17});
    faces.push_back({0, 4, 19});
    faces.push_back({0, 3, 17});
    faces.push_back({0, 4, 18});
}

godot::Icositetrachoron::Icositetrachoron() : size(1, 1, 1, 1) {
    // https://polytope.miraheze.org/wiki/File:Icositetrachoron.off
    _generate_vertices();
    _generate_faces();
}
