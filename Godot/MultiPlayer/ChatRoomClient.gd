extends Node

const UDP_PORT = 1507
var socketUDP = PacketPeerUDP.new()
var count = 0

func _process(delta):
	sendTest()

func sendTest():
	var test = "test"
	socketUDP.set_dest_address("127.0.0.1", UDP_PORT)
	socketUDP.put_var(test)
	print("test sent: "+ str(count))
	count += 1