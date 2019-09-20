extends KinematicBody2D

const SPEED = 100
const GRAVITY = 30

const IDLE_ANIMATION_FRAME = 2
const UP_AXIS = Vector2.UP
const MIN_VELOCITY_X_TO_FLIP_GRAPHICS = 0.004
const JUMP_VELOCITY = GRAVITY*20

onready var graphics = $Sprite
onready var animationPlayer = $Sprite/AnimationPlayer

var velocity = Vector2(0, 0)
var platformSnap = Vector2.DOWN * 20
var collisions = {}

func _process(delta):
	updateGraphics(velocity)

func _physics_process(delta):
	
	if Input.is_action_pressed("walk_left"):
		velocity.x = -SPEED
	elif Input.is_action_pressed("walk_right"):
		velocity.x = SPEED
	else:
		velocity.x = 0
	 
	velocity.y += GRAVITY  
	
	var currentSnap = platformSnap
	
	if is_on_floor() && Input.is_action_just_pressed("jump"):
		animationPlayer.play("Jump")
		currentSnap = Vector2.ZERO

		velocity.y = -JUMP_VELOCITY + get_floor_velocity().y 

	velocity = move_and_slide_with_snap(velocity,  currentSnap, UP_AXIS )
	#velocity = move_and_slide(velocity,  UP_AXIS )
			


func updateGraphics(velocity):
	
	if is_on_floor():
		if abs(velocity.x) <= MIN_VELOCITY_X_TO_FLIP_GRAPHICS:
			graphics.frame = IDLE_ANIMATION_FRAME
			animationPlayer.stop()
		else:
			animationPlayer.play("Walk")
	if velocity.x > MIN_VELOCITY_X_TO_FLIP_GRAPHICS:
		graphics.flip_h = false
	elif velocity.x < -MIN_VELOCITY_X_TO_FLIP_GRAPHICS:
		graphics.flip_h = true

		