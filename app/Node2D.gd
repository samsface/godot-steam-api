extends Node2D

func _ready():
	Steam.clear_achievement("gator_god")
	Steam.set_achievement("gator_god")
