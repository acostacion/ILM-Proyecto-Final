extends Node

func _on_physics_pressed() -> void:
	get_tree().change_scene_to_file("res://Scenes/PhysicsScene.tscn")
	
func _on_d_visualizer_pressed() -> void:
	get_tree().change_scene_to_file("res://Scenes/4DVisualizer.tscn")
