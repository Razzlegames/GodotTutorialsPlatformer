extends HTTPRequest

class_name GetPublicIpHTTPRequest
signal ipReceivedOrGiveUp
signal _callComplete

var publicIpAddress = null
var result
var responseCode
var headers
var body

func getIpAddressAsync() -> void:
		
	var retries = 0
	
	while retries < 3:
		request("http://bot.whatismyipaddress.com/")
		yield(self, "_callComplete")
		if successfullCall():
			emit_signal("ipReceivedOrGiveUp")
			return
		
		yield(get_tree().create_timer(.5), "timeout")
		retries += 1 
	emit_signal("ipReceivedOrGiveUp")
	
func successfullCall():
	return result == RESULT_SUCCESS

func _on_GetPublicIpHTTPRequest_request_completed(result, response_code, 
		headers, body):
	
	publicIpAddress = body.get_string_from_utf8()
	print("Result code: " + str(result) +
		 " Public IP result:" + publicIpAddress)
	
	self.result = result
	self.responseCode = responseCode
	self.headers = headers
	self.body = body
	
	emit_signal("_callComplete")
