extends Node

@export var _meshInstance4D : MeshInstance4D
@export var _tesseract : Mesh4D
@export var _pentachoron : Mesh4D
@export var _hexadecachoron : Mesh4D
@export var _icositetrachoron : Mesh4D

@export var _tesseractButton : Button
@export var _pentachoronButton : Button
@export var _hexadecachoronButton : Button
@export var _icositetrachoronButton : Button

var _initScale : Vector4

func setTesseract() -> void: 
	_meshInstance4D.mesh = _tesseract
	_meshInstance4D.scale = _initScale / 4.0
	pass
	
func setPentachoron() -> void: 
	_meshInstance4D.mesh = _pentachoron
	_meshInstance4D.scale = _initScale
	pass
	
func setHexadecachoron() -> void:
	_meshInstance4D.mesh = _hexadecachoron
	_meshInstance4D.scale = _initScale
	pass
	
func setIcositetrachoron() -> void:
	_meshInstance4D.mesh = _icositetrachoron
	_meshInstance4D.scale = _initScale / 2.0
	pass

func _ready() -> void:
	_initScale = _meshInstance4D.scale
	_tesseractButton.pressed.connect(setTesseract)
	_pentachoronButton.pressed.connect(setPentachoron)
	_hexadecachoronButton.pressed.connect(setHexadecachoron)
	_icositetrachoronButton.pressed.connect(setIcositetrachoron)
	pass
