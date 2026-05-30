extends Node

@export var _meshInstance4D : MeshInstance4D
@export var _tesseract : Mesh4D
@export var _pentachoron : Mesh4D

@export var _tesseractButton : Button
@export var _pentachoronButton : Button

var _initScale : Vector4

func setTesseract() -> void: 
	_meshInstance4D.mesh = _tesseract
	_meshInstance4D.scale = _initScale / 4.0
	
func setPentachoron() -> void: 
	_meshInstance4D.mesh = _pentachoron
	_meshInstance4D.scale = _initScale

func _ready() -> void:
	_initScale = _meshInstance4D.scale
	_tesseractButton.pressed.connect(setTesseract)
	_pentachoronButton.pressed.connect(setPentachoron)
	pass
