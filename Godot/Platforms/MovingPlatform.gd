extends Path2D

export var curveSpeed = 60 setget setCurveSpeed

func _ready():
	setCurveSpeed(curveSpeed)
	
func setCurveSpeed(speed):
	curveSpeed = speed
	call_deferred("setPathFollowSpeed")
	
func setPathFollowSpeed():
	$MovingPlatformPathFollow2D.curveSpeed = curveSpeed