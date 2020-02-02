extends Node

class_name ChatRoom

const UDP_PORT = 1507
var socketUDP = PacketPeerUDP.new()
var publicIpAddress = null

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
	enum Type { HEART_BEAT, CHAT_MESSAGE, CONNECT_REQUEST, CONNECT_ACCEPT, CLIENT_LIST } 
	
	var type: int
	var chatMessage: String
	var publicIpAddress: String
	var dataMap = {}
	
func _ready():
	getYourPublicIp()
	sendClientListMessageForever()
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
		var packetDictionary = socketUDP.get_var()
		checkForErrors()
		if packetDictionary != null:
			print("Packet received: " + str(packetDictionary))
			processPacket(dict2inst(packetDictionary) as Packet)

func sendClientListMessageForever():
	while true:
		for client in connectedClients.values():
			sendClientListMessage(client)
		yield(get_tree().create_timer(4), "timeout")

func getYourPublicIp():
	var getPublicIpHttpRequest = $GetPublicIpHTTPRequest
	getPublicIpHttpRequest.getIpAddressAsync()
	yield(getPublicIpHttpRequest, "ipReceivedOrGiveUp")
	
	if !getPublicIpHttpRequest.successfullCall():
		print("Cannot get public IP Address for client!")
		assert(getPublicIpHttpRequest.successfullCall())
	publicIpAddress = getPublicIpHttpRequest.publicIpAddress

func purgeOldClients():
	
	var toPurge = []
	for client in connectedClients.values():
		var inactiveSeconds: int = OS.get_unix_time() - client.lastActivityTimeStampSeconds
		if inactiveSeconds >= MAX_CLIENT_INACTIVE_SECONDS:
			toPurge.push_back(client)
	
	for client in toPurge:
		connectedClients.erase(toClientKey(client))
			
func processPacket(packet: Packet):
		
	var localIpAddress: String = socketUDP.get_packet_ip()
	var ipAddress: String = packet.publicIpAddress
	var port: int = socketUDP.get_packet_port()
	
	var client: Client = connectedClients.get(
		toKey(ipAddress, localIpAddress, port))
	if client == null:
		client = addConnectedClient(ipAddress, localIpAddress, port)
	
	match packet.type:
		Packet.Type.HEART_BEAT:
			pass
		Packet.Type.CHAT_MESSAGE:
			pass
		Packet.Type.CONNECT_REQUEST:
			pass
		Packet.Type.CONNECT_ACCEPT:
			pass
		
	client.lastActivityTimeStampSeconds = OS.get_unix_time()
	print("Packet processed for: " + toClientKey(client))

func sendClientListMessage(client: Client):
	
	var packet = Packet.new()
	packet.type = Packet.Type.CLIENT_LIST
	packet.publicIpAddress
	
	var clientList = []
	for c in connectedClients.values():
		clientList.append(inst2dict(c))
	packet.dataMap.clientList = to_json(clientList)
	socketUDP.set_dest_address(client.localIpAddress, client.port)
	socketUDP.put_var(inst2dict(packet))

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
	return toKey(client.ipAddress, client.localIpAddress, client.port)
	
func toKey(ipAddress: String, localAddress: String, port: int) -> String:
	return ipAddress + ":" + localAddress + ":" + str(port)

