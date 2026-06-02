extends Node

@export var _meshes : Array[MeshDescriptor]

@export var _meshInstance4D : MeshInstance4D
@export var _optionButton : OptionButton

var _initScale : Vector4
func _ready() -> void:
	_initScale = _meshInstance4D.scale
	for i in range(0, len(_meshes)):
		_optionButton.add_item(_meshes[i].name, i)
	#_optionButton.add_item("Pentacoro", 0)
	#_optionButton.add_item("Teseracto", 1)
	#_optionButton.add_item("Hexadecacoro", 2)
	#_optionButton.add_item("Icositetracoro", 3)
	#_optionButton.add_item("Hexacosicoro", 4)
	#_optionButton.add_item("Gran Hexacosicoro", 5)
	_optionButton.item_selected.connect(_on_item_selected)

func _on_item_selected(index: int) -> void:
	var id := _optionButton.get_selected_id()
	var meshdesc = _meshes[id]
	
	_meshInstance4D.mesh = meshdesc.mesh
	_meshInstance4D.scale = _initScale /  meshdesc.scale_divisor
#
#func setTesseract() -> void: 
	#_meshInstance4D.mesh = _tesseract
	#_meshInstance4D.scale = _initScale / 4.0
	#pass
	#
#func setPentachoron() -> void: 
	#_meshInstance4D.mesh = _pentachoron
	#_meshInstance4D.scale = _initScale
	#pass
	#
#func setHexadecachoron() -> void:
	#_meshInstance4D.mesh = _hexadecachoron
	#_meshInstance4D.scale = _initScale / 1.5
	#pass
	#
#func setIcositetrachoron() -> void:
	#_meshInstance4D.mesh = _icositetrachoron
	#_meshInstance4D.scale = _initScale / 2.0
	#pass
	#
#func setHexacosichoron() -> void:
	#_meshInstance4D.mesh = _hexacosichoron
	#_meshInstance4D.scale = _initScale / 3.5
	#pass
	#
#func setGrandHexacosichoron() -> void:
	#_meshInstance4D.mesh = _grandHexacosichoron
	#_meshInstance4D.scale = _initScale / 1.25
	#pass
