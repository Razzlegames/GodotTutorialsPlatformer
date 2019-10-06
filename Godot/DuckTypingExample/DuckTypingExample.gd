extends Node2D

class Duck:
	func quack():
		print("Quack Duck")
	func walk():
		print("Walk Duck")

class Goose:
	func quack():
		print("Quack Goose")
	func walk():
		print("Walk Goose")

class Ostrich:
	func quack():
		print("Quack Ostrich")
	func walk():
		print("Walk Ostrich")
	
var ducks = []

func _ready():
	ducks.append(Ostrich.new())
	ducks.append(Goose.new())
	ducks.append(Duck.new())
	
	for duck in ducks:
		duck.quack()
		duck.walk()
	
