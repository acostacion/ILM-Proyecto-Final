extends Node3D

@export var _meshInstance4D : MeshInstance4D

# barras para las rotaciones
@export var _sliderXW : HSlider
@export var _sliderYW : HSlider
@export var _sliderZW : HSlider

# pa k se vea el wireframe o no 
@export var _wireframeCheckbox : CheckBox

# pa k rote solo o no
@export var _autoRotateCheckbox : CheckBox
var _autoRotate : bool = false

# parametros
var _speed : float = 0.5

# relativo al reset
@export var _resetButton : Button
var _initPos : Vector4
var _initRotXY : float
var _initRotXZ : float
var _initRotXW : float
var _initRotYZ : float
var _initRotYW : float
var _initRotZW : float

# metodos
func setXW(rot : float) -> void: _meshInstance4D.rot_xw = rot
func setYW(rot : float) -> void: _meshInstance4D.rot_yw = rot
func setZW(rot : float) -> void: _meshInstance4D.rot_zw = rot
func setWireframe(wireframe : bool) -> void: _meshInstance4D.wireframe = wireframe
func setAutorotate(autorot : bool) -> void: _autoRotate = autorot

func saveInitialTransform() -> void:
	_initPos = _meshInstance4D.position
	_initRotXY = _meshInstance4D.rot_xy
	_initRotXZ = _meshInstance4D.rot_xz
	_initRotXW = _meshInstance4D.rot_xw
	_initRotYZ = _meshInstance4D.rot_yz
	_initRotYW = _meshInstance4D.rot_yw
	_initRotZW = _meshInstance4D.rot_zw
#	_initScale = _meshInstance4D.scale
	pass

func resetTransform() -> void:
	# reseteamos valores
	_meshInstance4D.position = _initPos
	_meshInstance4D.rot_xy = _initRotXY
	_meshInstance4D.rot_xz = _initRotXZ
	_meshInstance4D.rot_xw = _initRotXW
	_meshInstance4D.rot_yz = _initRotYZ
	_meshInstance4D.rot_yw = _initRotYW
	_meshInstance4D.rot_zw = _initRotZW
	#_meshInstance4D.scale = _initScale
	
	# pero tb la ui
	_sliderXW.value = _initRotXW
	_sliderYW.value = _initRotYW
	_sliderZW.value = _initRotZW
	pass

# start()
func _ready() -> void:
	saveInitialTransform()
	_sliderXW.value_changed.connect(setXW)
	_sliderYW.value_changed.connect(setYW)
	_sliderZW.value_changed.connect(setZW)
	_wireframeCheckbox.toggled.connect(setWireframe)
	_autoRotateCheckbox.toggled.connect(setAutorotate)
	_resetButton.pressed.connect(resetTransform)
	pass

# update()
func _process(delta: float) -> void:
	if _autoRotate:
		_meshInstance4D.rot_xw += _speed * delta
		_meshInstance4D.rot_yw += _speed * delta
		_meshInstance4D.rot_zw += _speed * delta
	pass
