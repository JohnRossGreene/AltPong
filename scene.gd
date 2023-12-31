extends Node2D

# Member variables
var screen_size
var pad_size
var direction = Vector2(1.0, 0.0)

#Ball shpeed
const INITIAL_BALL_SPEED = 80
#Ball shpeed but again. it doesnt get faster i decided against it
var ball_speed = INITIAL_BALL_SPEED
# Constant for pads speed
const PAD_SPEED = 150

func _ready():
	#screen_size = get_viewport_rect().size
	pad_size = get_node("left").get_texture().get_size()
	set_process(true)
	
func _process(delta):
	var ball_pos = get_node("ball").get_position()
	print(direction.y)
	var left_rect = Rect2( get_node("left").get_position() - pad_size*0.5, pad_size )
	var right_rect = Rect2( get_node("right").get_position() - pad_size*0.5, pad_size )
	# Integrate new ball position
	ball_pos += direction * ball_speed * delta
	# Flip when touching roof or floor
	if ((ball_pos.y < 0 and direction.y < 0) or (ball_pos.y > screen_size.y and direction.y > 0)):
		direction.y = -direction.y
	# Flip, change direction and increase speed when touching pads
	if ((left_rect.has_point(ball_pos) and direction.x < 0) or (right_rect.has_point(ball_pos) and direction.x > 0)):
		direction.x = -direction.x
		direction.y = randf()*2.0 - 1
		direction = direction.normalized()
		ball_speed *= 1.1
		# Check gameover
	if (ball_pos.x < 0 or ball_pos.x > screen_size.x):
		ball_pos = screen_size*0.5
		ball_speed = INITIAL_BALL_SPEED
		direction = Vector2(-1, 0)
	get_node("ball").set_position(ball_pos)


# Move left pad
	var left_pos = get_node("left").get_position()

	if (left_pos.y > 0 and Input.is_action_pressed("left_move_up")):
		left_pos.y += -PAD_SPEED * delta
	if (left_pos.y < screen_size.y and Input.is_action_pressed("left_move_down")):
		left_pos.y += PAD_SPEED * delta

	get_node("left").set_position(left_pos)

	# Move right pad
	var right_pos = get_node("right").get_position()

	if (right_pos.y > 0 and Input.is_action_pressed("right_move_up")):
		right_pos.y += -PAD_SPEED * delta
	if (right_pos.y < screen_size.y and Input.is_action_pressed("right_move_down")):
		right_pos.y += PAD_SPEED * delta

	get_node("right").set_position(right_pos)
