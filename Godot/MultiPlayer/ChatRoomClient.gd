extends Node

const UDP_PORT = 1507
var socketUDP = PacketPeerUDP.new()


func _ready():
	sendTest()

func sendTest():
	var count = 0
	
	var dictionary = {}
	while true:
		var test = "test"
		socketUDP.set_dest_address("127.0.0.1", UDP_PORT)
		dictionary[test] = count
		
		var packetType = "HEARTBEAT"
		dictionary["packetType"] = packetType
		
		socketUDP.put_var(dictionary)
		print("test sent: "+ str(count))
		count += 1
		yield(get_tree().create_timer(4), "timeout")