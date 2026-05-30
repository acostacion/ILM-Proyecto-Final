# Extraido de un comentario de fieldtrip2178: https://www.youtube.com/watch?v=fMC9JWg4BMk
extends MeshInstance4D

var rotating = false

func _input(event):
	if event is InputEventMouseButton:
		if event.is_pressed():
			rotating = true
		
		if event.is_released():
			rotating = false
	
	if event is InputEventMouseMotion and rotating:
		var delta = get_process_delta_time()
		var rel = event.relative
		
		self.rotate_y(rel.x * .7 * delta)
		self.rotate_x(rel.y * .7 * delta)
	
