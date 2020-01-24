extends Node

class_name ChatRoom

const UDP_PORT = 1507
var socketUDP = PacketPeerUDP.new()

var connectedClients = {}
const MAX_CLIENT_INACTIVE_SECONDS = 2 * 60

class Client:
	var ip_address: String
	var port: int
	var lastActivityTimeStampSeconds: int

	func toString() -> String:
		return str(lastActivityTimeStampSeconds) + ":" + ip_address + ":" + str(port)

class Packet:
	enum Type { HEART_BEAT, CHAT_MESSAGE, CONNECT_REQUEST, CONNECT_ACCEPT} 
	
	var type: int
	var chatMessage: String

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
		var packet: PoolByteArray = socketUDP.get_packet()
		checkForErrors()
		processPacket(packet)

func purgeOldClients():
	
	var toPurge = []
	for client in connectedClients:
		var inactiveSeconds: int = OS.get_unix_time() - client.lastActivityTimeStampSeconds
		if inactiveSeconds >= MAX_CLIENT_INACTIVE_SECONDS:
			toPurge.push_back(client)
	
	for client in toPurge:
		connectedClients.erase(client)
			
func processPacket(packet: PoolByteArray):
		var ip_address: String = socketUDP.get_packet_ip()
		var port: int = socketUDP.get_packet_port()
		
		var client: Client =  connectedClients.get(toKey(ip_address, port))
		if client == null:
			client = addConnectedClient(ip_address, port)

		var chatPacket: Packet = bytes2var(packet)
		client.lastActivityTimeStampSeconds = OS.get_unix_time()
		print("Packet processed for: " + client.toString())

func addConnectedClient(ip_address: String, port: int) -> Client:
	var client  = Client.new()
	client.ip_address = ip_address
	client.port = port
	
	connectedClients[toClientKey(client)] = client
	print("Added client: " + client.toString())
	return client

func checkForErrors():
	var error = socketUDP.get_packet_error()
	if error != OK:
		print("Error: "+ str(error))
		print("Packet count: " + str(socketUDP.get_available_packet_count()))

func toClientKey(client: Client) -> String:
	return toKey(client.ip_address, client.port)
	
func toKey(ip_address: String, port: int) -> String:
	return ip_address + ":" +  str(port)