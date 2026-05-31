#include "register_types.h"

#include "node_4d.hpp"
#include "mesh_4d.hpp"
#include "tesseract.h"
#include "pentachoron.h"
#include "hexadecachoron.h"
#include "icositetrachoron.h"
#include "off_file_reader.h"
#include "generic_mesh_4d.h"
#include "mesh_instance_4d.h"
#include "collision_shape_4d.h"
#include "rigid_body_4d.h"

#include <gdextension_interface.h>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/godot.hpp>

using namespace godot;

void initialize_example_module(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}

	GDREGISTER_CLASS(Node4D);
	GDREGISTER_CLASS(Mesh4D);
	GDREGISTER_CLASS(OffFileReader);
	GDREGISTER_CLASS(Tesseract);
	GDREGISTER_CLASS(Pentachoron);
	GDREGISTER_CLASS(Hexadecachoron);
	GDREGISTER_CLASS(Icositetrachoron);
	GDREGISTER_CLASS(GenericMesh4D);
	GDREGISTER_CLASS(MeshInstance4D);
	GDREGISTER_CLASS(CollisionShape4D);
	GDREGISTER_CLASS(RigidBody4D);
}

void uninitialize_example_module(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}
}

extern "C" {
// Initialization.
GDExtensionBool GDE_EXPORT example_library_init(GDExtensionInterfaceGetProcAddress p_get_proc_address, const GDExtensionClassLibraryPtr p_library, GDExtensionInitialization *r_initialization) {
	godot::GDExtensionBinding::InitObject init_obj(p_get_proc_address, p_library, r_initialization);

	init_obj.register_initializer(initialize_example_module);
	init_obj.register_terminator(uninitialize_example_module);
	init_obj.set_minimum_library_initialization_level(MODULE_INITIALIZATION_LEVEL_SCENE);

	return init_obj.init();
}
}