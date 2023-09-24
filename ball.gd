extends CharacterBody2D


const SPEED = 100.0
var direction = Vector2.ZERO

func _ready():
	direction.y = [1,-1].pick_random()
	direction.x = [1,-1].pick_random()

func _physics_process(delta):
	if direction:
		velocity = direction * SPEED
		if direction.x > 0:
			self.rotation_degrees += 1
		else:
			self.rotation_degrees -= 1
	else:
		velocity = velocity.move_toward(Vector2.ZERO, SPEED)
	move_and_slide()
