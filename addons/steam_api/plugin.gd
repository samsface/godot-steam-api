tool
extends EditorPlugin

var setup:Control

func _enter_tree():
	setup = load("res://addons/steam_api/setup.tscn").instance()
	add_control_to_container(CONTAINER_PROJECT_SETTING_TAB_RIGHT, setup)
	
	setup.connect("disable", self, "_on_disabled")

	var existing_steam_autoload = ProjectSettings.get("autoload/Steam")
	if not existing_steam_autoload:
		_on_disabled(setup.settings.disable)

func _on_disabled(value:bool) -> void:
	remove_autoload_singleton("Steam")

	if value:
		print("disable steam integration")
		add_autoload_singleton("Steam", "res://addons/steam_api/steam_i.gd")
	else:
		print("enable steam integration")
		add_autoload_singleton("Steam", "res://addons/steam_api/steam.gd")

func disable_plugin():
	remove_autoload_singleton("Steam")
	remove_control_from_container(CONTAINER_PROJECT_SETTING_TAB_RIGHT, setup)
	setup.queue_free()
