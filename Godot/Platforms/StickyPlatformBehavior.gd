extends Node2D

var nodesOnTopMapToPreviousParents = {}
var nodesToIgnore = {}

func _ready():
	nodesToIgnore[get_parent().get_instance_id()] = true
	nodesToIgnore[$Area2D.get_instance_id()] = true

func _on_Area2D_body_entered(body):
	
	if nodesToIgnore.has(body.get_instance_id()) || body is StaticBody2D:
		return
	setBodyParentToSelf(body)

func setBodyParentToSelf(body):
	body = getMainInstance(body)
	nodesOnTopMapToPreviousParents[body.get_instance_id()] = body.get_parent()
	add_child(body)    
	nodesToIgnore[body.get_instance_id()] = body

func getMainInstance(body):
	if body.has_method("getMainInstance"):
		return body.getMainInstance()
	return body

func _on_Area2D_body_exited(body):
	
	var bodyMain = getMainInstance(body)
	if !nodesOnTopMapToPreviousParents.has(bodyMain):
		return
		
	var parent = nodesOnTopMapToPreviousParents[bodyMain.get_instance_id()]
	var node = Node.new()
	remove_child(node)
	remove_child(bodyMain)
	nodesToIgnore.erase(bodyMain)
	
	if parent != null:
		parent.add_child(bodyMain)
