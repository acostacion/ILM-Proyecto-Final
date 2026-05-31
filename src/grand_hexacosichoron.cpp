#include "grand_hexacosichoron.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/memory.hpp>
#include <cstdint>

#include <godot_cpp/variant/vector4.hpp>
#include <godot_cpp/variant/vector3.hpp>
#include <godot_cpp/classes/standard_material3d.hpp>
#include <godot_cpp/variant/color.hpp>

using namespace godot;

void godot::GrandHexacosichoron::_bind_methods() {
    ClassDB::bind_method(D_METHOD("set_size", "size"), &GrandHexacosichoron::set_size);
    ClassDB::bind_method(D_METHOD("get_size"), &GrandHexacosichoron::get_size);
    // Propiedades
    ADD_PROPERTY(PropertyInfo(Variant::VECTOR4, "size"), "set_size", "get_size");
}

godot::GrandHexacosichoron::GrandHexacosichoron() : size(1, 1, 1, 1) {
    loadOffFile(_rutaCarmen + "Grand_Hexacosichoron.off");
}