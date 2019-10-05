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
var platformSnap = Vector2.DOWN * 32

func _process(delta):
	updateGraphics(velocity)

func _physics_process(delta):
	
	if Input.is_action_pressed("walk_left"):
		walkLeft()
	elif Input.is_action_pressed("walk_right"):
		walkRight()
	else:
		stopWalking()
	
	applyStandardGravity()

	var currentSnap = platformSnap
		
	if Input.is_action_just_pressed("jump"):
		if jump():
			currentSnap = Vector2.ZERO
		
	velocity = move_and_slide_with_snap(velocity,  currentSnap, UP_AXIS )
	# TODO Due to a current bug if we use "stop_on_slope" in move_and_slide_with_snap
	#   we need to detect when on a platform and use regular move_and_slide for those cases
	#velocity = move_and_slide(velocity,  UP_AXIS )

func applyStandardGravity():
	velocity.y += GRAVITY  

func stopWalking():
	velocity.x = 0

func walkLeft():
	 velocity.x = -SPEED 
	
func walkRight():
	velocity.x = SPEED

func jump():
	if is_on_floor():
		animationPlayer.play("Jump")
		velocity.y = -JUMP_VELOCITY 
		return true
	return false

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

		