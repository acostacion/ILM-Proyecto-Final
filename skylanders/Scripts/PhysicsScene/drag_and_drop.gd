extends Camera3D

# Cuerpo que estamos arrastrando actualmente
var dragging_body: RigidBody3D = null
# Distancia a la que se mantiene el objeto desde la cámara
var drag_distance: float = 0.0
# Fuerza con la que el objeto sigue al mouse
@export var drag_strength: float = 12.0

func _input(event):
	if event is InputEventMouseButton and event.button_index == MOUSE_BUTTON_LEFT:
		if event.pressed:
			_try_grab(event.position)
		else:
			_release()

func _try_grab(mouse_pos: Vector2):
	# Raycast
	var from = project_ray_origin(mouse_pos)
	var to = from + project_ray_normal(mouse_pos) * 1000.0
	
	var space_state = get_world_3d().direct_space_state
	var query = PhysicsRayQueryParameters3D.create(from, to)
	query.collision_mask = 1 # Solo detecta la capa 1
	var result = space_state.intersect_ray(query)
	
	# Agarramos solo si ha colisionado con un rigidbody
	if result and result.collider is RigidBody3D:
		dragging_body = result.collider
		# Mantiene un offset con el click
		drag_distance = from.distance_to(result.position)

func _release():
	dragging_body = null

func _physics_process(delta):
	if not dragging_body:
		return
	
	var mouse_pos = get_viewport().get_mouse_position()
	var from = project_ray_origin(mouse_pos)
	var dir = project_ray_normal(mouse_pos)
	var target = from + dir * drag_distance # Posicion objetivo
	
	# Mover el cuerpo hacia el target usando velocidad 
	# para respetar colisiones fisicas
	var to_target = target - dragging_body.global_position
	dragging_body.linear_velocity = to_target * drag_strength
