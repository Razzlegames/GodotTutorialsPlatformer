extends Node2D


func _input(event):
	if  event.is_action_released("ui_home"):
		print("Home")
		print($Gummy)
		
		var pos_bytes = var2bytes($Gummy)
		for byte in pos_bytes:
			print(byte)
		print(bytes2var(pos_bytes) )