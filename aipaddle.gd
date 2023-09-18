extends CharacterBody2D

const SPEED = 50
@onready var ball = %"../ball"
func _physics_process(delta):
	if is_instance_valid(ball) == false:
		ball = $"../ball"
	else:
		position.y += (ball.position.y - position.y)/SPEED
		
func _on_area_2d_body_entered(body):
	body.direction.x *= -1
