extends Node

func _on_4d_visualizer_pressed() -> void:
	get_tree().change_scene_to_file("res://Scenes/4DVisualizer.tscn")

func _on_3d_visualzer_pressed() -> void:
	get_tree().change_scene_to_file("res://Scenes/3DVisualizer.tscn")
