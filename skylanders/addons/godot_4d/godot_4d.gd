@tool
extends EditorPlugin
const NODE_4D = preload("res://addons/godot_4d/icons/Node4D.svg")
const MESH_INSTANCE_4D = preload("res://addons/godot_4d/icons/MeshInstance4D.svg")
const COLLISION_SHAPE_4D = preload("res://addons/godot_4d/icons/CollisionShape4D.svg")
const RIGIDBODY_4D = preload("res://addons/godot_4d/icons/Rigidbody4D.svg")

func _enter_tree():
	# Registrar todos los iconos
	var theme = get_editor_interface().get_editor_theme()
	theme.set_icon("Node4D", "EditorIcons", NODE_4D)
	theme.set_icon("MeshInstance4D", "EditorIcons", MESH_INSTANCE_4D)
	theme.set_icon("CollisionShape4D", "EditorIcons", COLLISION_SHAPE_4D)
	theme.set_icon("RigidBody4D", "EditorIcons", RIGIDBODY_4D)

func _exit_tree():
	pass
