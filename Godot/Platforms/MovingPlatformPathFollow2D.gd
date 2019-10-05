extends PathFollow2D

var curveSpeed = 60

enum Direction {
 FORWARD = 1, REVERSE = -1	
}

var pathDirection = Direction.FORWARD

func _physics_process(delta):
	moveOnPath(delta)
	
func moveOnPath(delta):
	
	var prevSpeed = curveSpeed * pathDirection
	var speed = lerp(prevSpeed, curveSpeed * pathDirection, delta)
	offset = offset + speed * delta
		
	if unit_offset >= 0.991 && pathDirection == Direction.FORWARD:
		pathDirection = Direction.REVERSE
	
	elif unit_offset <= 0.01 && pathDirection == Direction.REVERSE:
		pathDirection = Direction.FORWARD
		

	
	
