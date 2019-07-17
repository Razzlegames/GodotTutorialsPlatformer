extends Sprite

export(NodePath) var cameraPath
var currentCamera

func _ready():
	currentCamera = get_node(cameraPath)

func _process(delta):
	global_position = currentCamera.global_position