extends Node

const UDP_PORT = 1507
var socketUDP = PacketPeerUDP.new()
var publicIpAddress = null

func _ready():
	getYourPublicIp()
	startTestAfterPublicIpIsSaved()
	
func startTestAfterPublicIpIsSaved():
	while publicIpAddress == null:
		yield(get_tree().create_timer(0.2), "timeout")
	sendTest()

func sendTest():
	var count = 0
	
	while true:
		var test = "test"
		socketUDP.set_dest_address("127.0.0.1", UDP_PORT)
		#socketUDP.set_dest_address("192.168.99.100", UDP_PORT)
		#socketUDP.set_dest_address("172.17.0.2", UDP_PORT)
		
		var packet = ChatRoom.Packet.new()
		packet.dataMap[test] = count
		packet.publicIpAddress = publicIpAddress
		packet.type = ChatRoom.Packet.Type.HEART_BEAT
		
		var jsonPacket = inst2dict(packet)
		print("Json packet: " + str(jsonPacket))
		socketUDP.put_var(jsonPacket)
		print("test sent: "+ str(count))
		count += 1
		yield(get_tree().create_timer(4), "timeout")

func getYourPublicIp():
	$HTTPRequest.request("http://bot.whatismyipaddress.com/")

func _process(delta):
	
	var packetCount = socketUDP.get_available_packet_count()
	if packetCount <= 0:
		return 
	print("Packets to get: "+ str(packetCount))
	
	for i in range(packetCount):
		var packet = socketUDP.get_var()
		checkForErrors()
		processPacket(packet)

func processPacket(packet):
	print("Server packet Received: " + str(packet))
		
func checkForErrors():
	var error = socketUDP.get_packet_error()
	if error != OK:
		print("Error: "+ str(error))
		print("Packet count: " + str(socketUDP.get_available_packet_count()))
	
func _on_HTTPRequest_request_completed(result, response_code, headers, body):
	var ip = body.get_string_from_utf8()
	print("Public IP result:" + ip)
	publicIpAddress = ip
