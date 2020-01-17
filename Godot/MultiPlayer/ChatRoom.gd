extends Node

const UDP_PORT = 1507
var socketUDP = PacketPeerUDP.new()

func _ready():
	startListening()

func startListening():
	var result = socketUDP.listen(UDP_PORT)
	print("Listening result: "+ str(result))

func _process(delta):
	
	var packetCount = socketUDP.get_available_packet_count()
	if packetCount <= 0:
		return 
	print("Packets to get: "+ str(packetCount))
	var packet = socketUDP.get_var()
	checkForErrors()
	
	if packet != null:
		print(str(packet))

func checkForErrors():
	var error = socketUDP.get_packet_error()
	if error != OK:
		print("Error: "+ str(error))
		print("Packet count: " + str(socketUDP.get_available_packet_count()))