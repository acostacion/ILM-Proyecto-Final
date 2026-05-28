extends Node3D

@export var _meshInstance4D : Node4D

# barras para las rotaciones
@export var _sliderXW : HSlider
@export var _sliderYW : HSlider
@export var _sliderZW : HSlider

# pa k se vea el wireframe o no #TODO hacer lo del wireframe public en la clase para poder acceder aki
@export var _wireframeCheckbox : CheckBox

# pa k rote solo o no
@export var _autoRotateCheckbox : CheckBox
var _autoRotate : bool = false

# parametros
var _speed : float = 0.5

# metodos
func setXW(rot : float) -> void: _meshInstance4D.rot_xw = rot
func setYW(rot : float) -> void: _meshInstance4D.rot_yw = rot
func setZW(rot : float) -> void: _meshInstance4D.rot_zw = rot
#func setWireframe(wireframe : bool) -> void: _meshInstance4D.
func setAutorotate(autorot : bool) -> void: _autoRotate = autorot

func _ready() -> void:
	_sliderXW.value_changed.connect(setXW)
	_sliderYW.value_changed.connect(setYW)
	_sliderZW.value_changed.connect(setZW)
	#_wireframeCheckbox.toggled.connect()
	_autoRotateCheckbox.toggled.connect(setAutorotate)
	pass
	
func _process(delta: float) -> void:
	if _autoRotate:
		_meshInstance4D.rot_xw += _speed * delta
		_meshInstance4D.rot_yw += _speed * delta
		_meshInstance4D.rot_zw += _speed * delta
	pass
		
		
		
