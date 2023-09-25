extends CharacterBody2D


const SPEED = 300.0
@export var side = 'p1'
var lasttouched = false
#var input_direction: get = _get_input_direction
var input_direction = Vector2.ZERO
var prev_dir = Vector2.ZERO
func _physics_process(delta):
	if(Input.is_key_pressed(KEY_SPACE)):
		self.visible = true
		$"../spell".hide()
		$"../magic".play()
		$Timer.start()
		$MagicEffect.visible = true
		$MagicEffect.play()
	if(Input.is_action_pressed('left_move_down')):
		input_direction = Vector2.DOWN
	elif(Input.is_action_pressed("left_move_up")):
		input_direction = Vector2.UP
	elif(Input.is_action_pressed("left_move_left")):
		input_direction = Vector2.LEFT
	elif(Input.is_action_pressed("left_move_right")):
		input_direction = Vector2.RIGHT
	elif(Input.is_action_pressed("stop")):
		input_direction = Vector2.ZERO
	
	velocity = input_direction * SPEED
	move_and_slide()

#func _get_input_direction():
#	var x = -int(Input.is_action_pressed("left_move_left")) + int(Input.is_action_pressed("left_move_right"))
#	var y = -int(Input.is_action_pressed("left_move_up")) + int(Input.is_action_pressed("left_move_down"))
#	input_direction = Vector2(x,y).normalized()
#	return input_direction


func _on_area_2d_body_entered(body):
	if lasttouched == false:
		$"../aipaddle".lasttouched = false
		lasttouched = true
		body.direction.x *= -1
		Main.side = side

func get_spell_name():
	var spellist = ['MAGIC SUBSCRIPTION EXPIRED', "CAST NOW", "TIME TO GET CASTING", "INSERT CASH OR SELECT PAYMENT TYPE", "KAMEHAMEHA", "WAZOO", "ZAP", "ZIPPITY ZAPPITY ZOOTLE", "MAN."]
	var rand_index:int = randi() % spellist.size()
	if spellist[rand_index]:
		return spellist[rand_index]

	
func _on_timer_timeout():
	self.hide()
	$"../spell".text = get_spell_name()
	$"../spell".visible = true
	$"../cast".play()
	$Timer.stop()
	
	
