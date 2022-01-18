#pragma once
#include "Module.h"
#include "Globals.h"
#include "p2Point.h"
#include "OBJ_Model.h"

struct PhysVehicle3D;
class Model;

#define MAX_ACCELERATION 1000.0f
#define TURN_DEGREES 15.0f * DEGTORAD
#define BRAKE_POWER 10.0f

class ModulePlayer : public Module
{
public:
	ModulePlayer(Application* app, bool start_enabled = true);
	virtual ~ModulePlayer();

	bool Start();
	update_status PreUpdate(float dt);
	update_status Update(float dt);
	update_status PostUpdate(float dt);
	bool CleanUp();

	btVector3 GetPosition();

	Model* carModel;
	
	btQuaternion orientation;
public:

	PhysVehicle3D* vehicle;
	float turn;
	float acceleration;
	float maxVelocity = 30.0f;
	float brake;

	vec3 lastPosition;
	vec3 position;

	btVector3 forwardVec;

	PhysBody3D* hitBox = nullptr;
};