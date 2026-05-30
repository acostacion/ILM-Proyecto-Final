@tool
extends EditorPlugin

func _enter_tree():
	# Registrar todos los iconos
	var mesh_instance_4d = preload("res://addons/godot_4d/icons/MeshInstance4D.svg")
	var node4d_icon = preload("res://addons/godot_4d/icons/Node4D.svg")
	
	var theme = get_editor_interface().get_editor_theme()
	theme.set_icon("MeshInstance4D", "EditorIcons", mesh_instance_4d)
	theme.set_icon("Node4D", "EditorIcons", node4d_icon)

func _exit_tree():
	pass
