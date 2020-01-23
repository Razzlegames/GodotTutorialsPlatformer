extends Node

class_name ChatRoom

const UDP_PORT = 1507
var socketUDP = PacketPeerUDP.new()

class Packet:
	enum Type { HEART_BEAT, CHAT_MESSAGE, CONNECT_REQUEST, CONNECT_ACCEPT} 
	enum DataKey { MESSAGE, SOURCE_IP_ADDRESS, SOURCE_PORT, DESTINATION_IP_ADDRESS, DESTINATION_PORT }
	var type: int
	var dataMap = {}

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
	
	for i in range(packetCount):
		var packet = socketUDP.get_var()
		checkForErrors()
		
		if packet != null:
			print(str(packet))

func checkForErrors():
	var error = socketUDP.get_packet_error()
	if error != OK:
		print("Error: "+ str(error))
		print("Packet count: " + str(socketUDP.get_available_packet_count()))