extends RayCast2D

# If this is use to disable collisions
export(bool) var disable_collisions = false;
# What to set/remove collisions against
export(NodePath) var physics_path

var physics_object

func _ready():

	print( "Physics object: "+ str(physics_path))
	physics_object = get_node(physics_path)
	add_exception(physics_object)
	set_exclude_parent_body(true)

func setDisableCollisions(_disable):
	disable_collisions = _disable

func _physics_process(delta):
	
	var collision_obj_to_add_back = []
	if is_colliding():
		var col = get_collider()

		if col is TileMap:
			return
		if  col is PhysicsBody2D :
			col.propagate_call("setOneWayCollision", [disable_collisions, physics_object], true)
		if !(col is Area2D):
			collision_obj_to_add_back.append(col)
		add_exception(col)
		force_raycast_update()

	for col in collision_obj_to_add_back:
		remove_exception(col)

