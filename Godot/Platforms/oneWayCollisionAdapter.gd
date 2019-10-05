extends Node2D

onready var mainPhysicsObject = get_parent() 

func setOneWayCollision(one_way, physics_object):
	if(one_way):
		mainPhysicsObject.add_collision_exception_with(physics_object)
	else:
		yield(get_tree().create_timer(.2,true), "timeout")
		mainPhysicsObject.remove_collision_exception_with(physics_object)
  