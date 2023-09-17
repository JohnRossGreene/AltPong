extends Sprite2D


# Called when the node enters the scene tree for the first time.
@onready var player = $"../player"
@onready var arm = $Wook_Arm


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
#bottom (18, 493)
#Top(18, 6)
#center (18, 252)
	if Input.is_key_pressed(KEY_W):
		arm.rotation_degrees -= .5
	if Input.is_key_pressed(KEY_S):
		arm.rotation_degrees += .5
	pass
