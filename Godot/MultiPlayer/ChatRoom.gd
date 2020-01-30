extends Node

class_name ChatRoom

const UDP_PORT = 1507
var socketUDP = PacketPeerUDP.new()

var connectedClients = {}
const MAX_CLIENT_INACTIVE_SECONDS = 2 * 60

class Client:
	var ipAddress: String
	var localIpAddress: String
	var port: int
	var lastActivityTimeStampSeconds: int

	func toString() -> String:
		return str(lastActivityTimeStampSeconds) + ":" + ipAddress + ":" + str(port)

class Packet:
	enum Type { HEART_BEAT, CHAT_MESSAGE, CONNECT_REQUEST, CONNECT_ACCEPT} 
	
	var type: int
	var chatMessage: String
	var publicIpAddress: String
	var dataMap = {}

func _ready():
	startListening()

func startListening():
	var result = socketUDP.listen(UDP_PORT)
	print("Listening result: "+ str(result))

func _process(delta):
	purgeOldClients()
	
	var packetCount = socketUDP.get_available_packet_count()
	if packetCount <= 0:
		return 
	print("Packets to get: "+ str(packetCount))
	
	for i in range(packetCount):
		var packet = socketUDP.get_var()
		checkForErrors()
		if packet != null:
			processPacket(packet)

func purgeOldClients():
	
	var toPurge = []
	for client in connectedClients.values():
		var inactiveSeconds: int = OS.get_unix_time() - client.lastActivityTimeStampSeconds
		if inactiveSeconds >= MAX_CLIENT_INACTIVE_SECONDS:
			toPurge.push_back(client)
	
	for client in toPurge:
		connectedClients.erase(toClientKey(client))
			
func processPacket(packet):
		print("Packet received: " + str(packet))
		var localIpAddress: String = socketUDP.get_packet_ip()
		var ipAddress: String = packet.publicIpAddress
		var port: int = socketUDP.get_packet_port()
		
		var client: Client = connectedClients.get(toKey(ipAddress, port))
		if client == null:
			client = addConnectedClient(ipAddress, localIpAddress, port)

		client.lastActivityTimeStampSeconds = OS.get_unix_time()
		print("Packet processed for: " + client.toString())

func addConnectedClient(ipAddress: String, localIpAddress: String, port: int) -> Client:
	
	var client  = Client.new()
	client.ipAddress = ipAddress
	client.localIpAddress = localIpAddress
	client.port = port
	
	connectedClients[toClientKey(client)] = client
	print("Added client: " + client.toString())
	socketUDP.set_dest_address(client.localIpAddress, client.port)
	socketUDP.put_var("Added client on server" + str(inst2dict(client)))
	return client

func checkForErrors():
	var error = socketUDP.get_packet_error()
	if error != OK:
		print("Error: "+ str(error))
		print("Packet count: " + str(socketUDP.get_available_packet_count()))

func toClientKey(client: Client) -> String:
	return toKey(client.ipAddress, client.port)
	
func toKey(ipAddress: String, port: int) -> String:
	return ipAddress + ":" +  str(port)