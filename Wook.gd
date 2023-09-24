extends Sprite2D


# Called when the node enters the scene tree for the first time.
@onready var player = $"../player"
@onready var arm = $Wook_Arm

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
#Bottom (18, 493)
#Top(18, 6)
#Center (18, 252)
#Wow Godot it would have been sick if I knew this function existed
	#thanks for burying it under a load of documentation and tutorials really helpful
		#Definitely didn't spend too much time making trig formulas just to rotate an arm haha 
	arm.look_at(player.position)

