extends Node

@export var _meshInstance4D : MeshInstance4D
@export var _tesseract : Mesh4D
@export var _pentachoron : Mesh4D

@export var _tesseractButton : Button
@export var _pentachoronButton : Button

func setTesseract() -> void: _meshInstance4D.mesh = _tesseract
	
func setPentachoron() -> void: _meshInstance4D.mesh = _pentachoron

func _ready() -> void:
	_tesseractButton.pressed.connect(setTesseract)
	_pentachoronButton.pressed.connect(setPentachoron)
	pass
