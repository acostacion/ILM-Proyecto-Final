# Extraido de: https://forum.godotengine.org/t/how-to-have-a-camera-zoom-in-and-out-in-3d-space/108313/2
extends Camera3D

@export var _zoomVel : float = 1.0
@export var _meshPos : Vector3 = Vector3.ZERO

func _ready() -> void:
	look_at(_meshPos)

func _process(delta):
	var mouse_input = 0.0
	# ponemos unos limites pa k no se vaya mu largo ni se acerque muxo
	if(Input.is_action_just_pressed("scrollUp")):
		if (fov > 40.0):
			mouse_input += _zoomVel * delta
			
	if(Input.is_action_just_pressed("scrollDown")):
		if (fov < 120.0):
			mouse_input -= _zoomVel * delta
		
	fov -= mouse_input
