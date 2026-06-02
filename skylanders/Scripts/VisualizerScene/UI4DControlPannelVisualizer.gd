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

# barras para parametros de visualizacion
@export var _sliderProjDist : HSlider
@export var _sliderWMax : HSlider
@export var _sliderWMin : HSlider

# para que se proyecte en ortografico
@export var _orthographicCheckbox : CheckBox

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
var _initPD : float
var _initWMax : float
var _initWMin : float

# metodos
func setXW(rot : float) -> void: _meshInstance4D.rot_xw = rot
func setYW(rot : float) -> void: _meshInstance4D.rot_yw = rot
func setZW(rot : float) -> void: _meshInstance4D.rot_zw = rot
func setPD(pd : float) -> void: _meshInstance4D.projection_distance = pd
func setWmax(w : float) -> void: _meshInstance4D.w_max = w
func setWMin(w : float) -> void: _meshInstance4D.w_min = w
func setWireframe(wireframe : bool) -> void: _meshInstance4D.wireframe = wireframe
func setOrthographic(orthographic : bool) -> void: _meshInstance4D.orthographic = orthographic
func setAutorotate(autorot : bool) -> void: _autoRotate = autorot

func saveInitialTransform() -> void:
	_initPos = _meshInstance4D.position
	_initRotXY = _meshInstance4D.rot_xy
	_initRotXZ = _meshInstance4D.rot_xz
	_initRotXW = _meshInstance4D.rot_xw
	_initRotYZ = _meshInstance4D.rot_yz
	_initRotYW = _meshInstance4D.rot_yw
	_initRotZW = _meshInstance4D.rot_zw
	_initPD = _meshInstance4D.projection_distance
	_initWMax = _meshInstance4D.w_max
	_initWMin = _meshInstance4D.w_min
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
	_meshInstance4D.projection_distance = _initPD
	_meshInstance4D.w_max = _initWMax
	_meshInstance4D.w_min = _initWMin
	#_meshInstance4D.scale = _initScale
	
	# pero tb la ui
	_sliderXW.value = _initRotXW
	_sliderYW.value = _initRotYW
	_sliderZW.value = _initRotZW
	_sliderProjDist.value = _initPD
	_sliderWMax.value = _initWMax
	_sliderWMin.value = _initWMin
	pass

# start()
func _ready() -> void:
	saveInitialTransform()
	_sliderXW.value_changed.connect(setXW)
	_sliderYW.value_changed.connect(setYW)
	_sliderZW.value_changed.connect(setZW)
	_sliderProjDist.value_changed.connect(setPD)
	_sliderWMax.value_changed.connect(setWmax)
	_sliderWMin.value_changed.connect(setWMin)
	_wireframeCheckbox.toggled.connect(setWireframe)
	_autoRotateCheckbox.toggled.connect(setAutorotate)
	_orthographicCheckbox.toggled.connect(setOrthographic)
	_resetButton.pressed.connect(resetTransform)
	pass

# update()
func _process(delta: float) -> void:
	if _autoRotate:
		_meshInstance4D.rot_xw += _speed * delta
		_meshInstance4D.rot_yw += _speed * delta
		_meshInstance4D.rot_zw += _speed * delta
	pass
