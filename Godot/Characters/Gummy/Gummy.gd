extends KinematicBody2D

const SPEED = 100
const gravity = 30

const IDLE_FRAME = 2
const UP = Vector2(0, -1)
const MIN_VALUE = 0.004

onready var graphics = $Sprite
onready var animationPlayer = $Sprite/AnimationPlayer

var velocity = Vector2(0, 0)

func _physics_process(delta):
	
	velocity.y += gravity
	
	if Input.is_action_pressed("walk_left"):
		velocity.x = -SPEED
	elif Input.is_action_pressed("walk_right"):
		velocity.x = SPEED
	else:
		velocity.x = 0
	
	if is_on_floor() && Input.is_action_pressed("jump"):
		animationPlayer.play("Jump")

		var jumpVelocity =  gravity*20
		velocity.y = clamp(velocity.y - jumpVelocity, 
			-abs(jumpVelocity), abs(jumpVelocity))
		
	
	velocity = move_and_slide(velocity, UP)
	call_deferred("updateGraphics", Vector2(velocity.x, velocity.y))
	
func updateGraphics(velocity):
	
	if is_on_floor():
		if abs(velocity.x) <= MIN_VALUE:
			graphics.frame = IDLE_FRAME
			animationPlayer.stop()
		else:
			animationPlayer.play("Walk")
	if velocity.x > MIN_VALUE:
		graphics.flip_h = false
	elif velocity.x < -MIN_VALUE:
		graphics.flip_h = true

		