#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "Primitive.h"
#include "PhysVehicle3D.h"
#include "PhysBody3D.h"


ModulePlayer::ModulePlayer(Application* app, bool start_enabled) : Module(app, start_enabled), vehicle(NULL)
{
	turn = acceleration = brake = 0.0f;
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

	VehicleInfo car;

	// Car properties ----------------------------------------
	car.chassis_size.Set(2, 1, 4);
	car.chassis_offset.Set(0, 0.5f, 0);
	car.mass = 500.0f;
	car.suspensionStiffness = 15.88f;
	car.suspensionCompression = 0.53f;
	car.suspensionDamping = 0.88f;
	car.maxSuspensionTravelCm = 1000.0f;
	car.frictionSlip = 50.5;
	car.maxSuspensionForce = 8000.0f;

	// Wheel properties ---------------------------------------
	float connection_height = 1.0f;
	float wheel_radius = 0.6f;
	float wheel_width = 0.85f;
	float suspensionRestLength = 1;

	// Don't change anything below this line ------------------

	float half_width = car.chassis_size.x*0.5f;
	float half_length = car.chassis_size.z*0.5f;
	
	vec3 direction(0,-1,0);
	vec3 axis(-1,0,0);
	
	car.num_wheels = 4;
	car.wheels = new Wheel[4];

	// FRONT-LEFT ------------------------
	car.wheels[0].connection.Set(car.chassis_size.x - wheel_width, connection_height, half_length - wheel_radius);
	car.wheels[0].direction = direction;
	car.wheels[0].axis = axis;
	car.wheels[0].suspensionRestLength = suspensionRestLength;
	car.wheels[0].radius = wheel_radius;
	car.wheels[0].width = wheel_width;
	car.wheels[0].front = true;
	car.wheels[0].drive = true;
	car.wheels[0].brake = false;
	car.wheels[0].steering = true;

	// FRONT-RIGHT ------------------------
	car.wheels[1].connection.Set(-car.chassis_size.x +  wheel_width, connection_height, half_length - wheel_radius);
	car.wheels[1].direction = direction;
	car.wheels[1].axis = axis;
	car.wheels[1].suspensionRestLength = suspensionRestLength;
	car.wheels[1].radius = wheel_radius;
	car.wheels[1].width = wheel_width;
	car.wheels[1].front = true;
	car.wheels[1].drive = true;
	car.wheels[1].brake = false;
	car.wheels[1].steering = true;

	// REAR-LEFT ------------------------
	car.wheels[2].connection.Set(car.chassis_size.x -  wheel_width, connection_height, -half_length + wheel_radius);
	car.wheels[2].direction = direction;
	car.wheels[2].axis = axis;
	car.wheels[2].suspensionRestLength = suspensionRestLength;
	car.wheels[2].radius = wheel_radius;
	car.wheels[2].width = wheel_width;
	car.wheels[2].front = false;
	car.wheels[2].drive = false;
	car.wheels[2].brake = true;
	car.wheels[2].steering = false;

	// REAR-RIGHT ------------------------
	car.wheels[3].connection.Set(-car.chassis_size.x + wheel_width, connection_height, -half_length + wheel_radius);
	car.wheels[3].direction = direction;
	car.wheels[3].axis = axis;
	car.wheels[3].suspensionRestLength = suspensionRestLength;
	car.wheels[3].radius = wheel_radius;
	car.wheels[3].width = wheel_width;
	car.wheels[3].front = false;
	car.wheels[3].drive = false;
	car.wheels[3].brake = true;
	car.wheels[3].steering = false;

	vehicle = App->physics->AddVehicle(car);
	vehicle->SetPos(0, 3, 0);
	vehicle->type = PLAYER;
	vehicle->collision_listeners.add(App->scene_intro);


	Cube phitBox(4, 4, 4);
	hitBox = App->physics->AddBody(phitBox);
	hitBox->type = PLAYER;
	hitBox->SetAsSensor(true);
	hitBox->collision_listeners.add(App->scene_intro);

	carModel = new Model();

	carModel->model = App->models->LoadModel("Assets/Models/car_2.obj");
	carModel->colR = 1;
	carModel->colG = 0;
	carModel->colB = 0;
	carModel->scale = 2;
	vehicle->GetTransform(initialM);
	return true;
}


// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");
	delete carModel;

	return true;
}
update_status ModulePlayer::PreUpdate(float dt)
{
	position.x = GetPosition().getX();
	position.y = GetPosition().getY();
	position.z = GetPosition().getZ();

	
	
	orientation = vehicle->vehicle->getRigidBody()->getOrientation().normalized();
	carModel->orientation = -orientation;
	

	float m[16];
	vehicle->GetTransform(m);
	hitBox->SetTransform(m);
	deltaPosition = position - lastPosition;
	//float deltaPos = sqrt((deltaPosition.x * deltaPosition.x) + (deltaPosition.y * deltaPosition.y) + (deltaPosition.z * deltaPosition.z));
	/*if (deltaPos > 0.2f)
	{
		carModel->x = position.x;
		carModel->y = position.y - 0.4;
		carModel->z = position.z;
	}*/
	carModel->x = position.x;
	carModel->y = position.y - 0.4;
	carModel->z = position.z;

	turn = acceleration = brake = 0.0f;

	Movement();




	forwardVec = vehicle->vehicle->getForwardVector();

	return UPDATE_CONTINUE;
}

// Update: draw background
update_status ModulePlayer::Update(float dt)
{



	vehicle->ApplyEngineForce(acceleration);
	vehicle->Turn(turn);
	vehicle->Brake(brake);
	btVector3 pos = App->player->GetPosition();
	LOG("Player pos y %2.2f", pos.getY());
	
	
	
	if ((pos.getY() < 1)||(App->input->GetKey(SDL_SCANCODE_0)==KEY_DOWN))
	{
		lifes--;
		score = 0;
		vehicle->Brake(vehicle->GetKmh());
		vehicle->SetTransform(initialM);
		vehicle->SetPos(0, 8, 0);
		
	}

	char title[80];
	sprintf_s(title, "%.1f Km/h", vehicle->GetKmh());
	App->window->SetTitle(title);

	return UPDATE_CONTINUE;
}

update_status ModulePlayer::PostUpdate(float dt)
{
	lastPosition = position;
	carModel->RenderModel();
	
	return UPDATE_CONTINUE;
}

btVector3 ModulePlayer::GetPosition()
{
	btVector3 pos = vehicle->vehicle->getChassisWorldTransform().getOrigin();


	return pos;
}

void ModulePlayer::Movement()
{
	if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
	{
		if (vehicle->GetKmh() < maxVelocity)
		{
			acceleration = MAX_ACCELERATION;

		}
	}
	else if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_IDLE)
	{
		brake = 0.1f * BRAKE_POWER;
	}

	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
	{
		if (turn < TURN_DEGREES)
			turn += TURN_DEGREES;
	}

	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
	{
		if (turn > -TURN_DEGREES)
			turn -= TURN_DEGREES;


	}

	if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
	{
		if (vehicle->GetKmh() <= 0.1f)
		{
			if (vehicle->GetKmh() > -maxVelocity / 2) acceleration = -MAX_ACCELERATION / 2;
		}
		else brake = BRAKE_POWER;
	}
}

