# Extraido de: https://forum.godotengine.org/t/how-to-have-a-camera-zoom-in-and-out-in-3d-space/108313/2
extends Camera3D

func _process(delta):
	var mouse_input = 0.0
	
	# ponemos unos limites pa k no se vaya mu largo ni se acerque muxo

	if(Input.is_action_just_pressed("scrollUp")):
		if (fov > 40.0):
			mouse_input += 1.0
			
	if(Input.is_action_just_pressed("scrollDown")):
		if (fov < 120.0):
			mouse_input -= 1.0
		
	fov -= mouse_input
