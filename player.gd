extends CharacterBody2D


const SPEED = 300.0
@export var side = 'p1'
var input_direction: get = _get_input_direction

func _physics_process(delta):
	if(Input.is_key_pressed(KEY_SPACE)):
		self.visible = true
		$"../spell".hide()
		$Timer.start()
	velocity = input_direction * SPEED
	move_and_slide()

func _get_input_direction():
	var x = -int(Input.is_action_pressed("left_move_left")) + int(Input.is_action_pressed("left_move_right"))
	var y = -int(Input.is_action_pressed("left_move_up")) + int(Input.is_action_pressed("left_move_down"))
	input_direction = Vector2(x,y).normalized()
	return input_direction


func _on_area_2d_body_entered(body):
	body.direction.x *= -1
	Main.side = side

func get_spell_name():
	var spellist = ['RAZAMAFOO', "WHATEVER ITS 2009", "FOUR LOKO OVERDRIVE", "INSERT CASH OR SELECT PAYMENT TYPE", "KAMEHAMEHA", "WAZOO", "ZAP", "ZIPPITY ZAPPITY ZOOTLE", "MAN.", "GOVERNMENT UPON YE"]
	var rand_index:int = randi() % spellist.size()
	if spellist[rand_index]:
		return spellist[rand_index]

	
func _on_timer_timeout():
	self.hide()
	$"../spell".text = get_spell_name()
	$"../spell".visible = true
	$Timer.stop()
	
	
