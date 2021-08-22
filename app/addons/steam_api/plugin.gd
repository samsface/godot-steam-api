tool
extends EditorPlugin

var setup:Control

func _enter_tree():
	add_autoload_singleton("Steam", "res://addons/steam_api/steam.tscn")
	setup = load("res://addons/steam_api/setup.tscn").instance()
	add_control_to_container(CONTAINER_PROJECT_SETTING_TAB_RIGHT, setup)

func _exit_tree():
	remove_autoload_singleton("Steam")
	remove_control_from_container(CONTAINER_PROJECT_SETTING_TAB_RIGHT, setup)
	setup.queue_free()
