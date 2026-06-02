extends Node

@export var _meshes : Array[MeshDescriptor]

@export var _meshInstance4D : MeshInstance4D
@export var _optionButton : OptionButton

var _initScale : Vector4
func _ready() -> void:
	_initScale = _meshInstance4D.scale
	for i in range(0, len(_meshes)):
		_optionButton.add_item(_meshes[i].name, i)
	_optionButton.item_selected.connect(_on_item_selected)

func _on_item_selected(index: int) -> void:
	var id := _optionButton.get_selected_id()
	var meshdesc = _meshes[id]
	
	_meshInstance4D.mesh = meshdesc.mesh
	_meshInstance4D.scale = _initScale /  meshdesc.scale_divisor
