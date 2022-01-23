#pragma once
#include "Module.h"
#include "p2DynArray.h"
#include "Globals.h"
#include "Primitive.h"
#include "OBJ_Model.h"

#define MAX_SNAKE 2

struct PhysBody3D;
struct PhysMotor3D;
class Model;

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(Application* app, bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start();
	update_status Update(float dt);
	update_status PostUpdate(float dt);
	bool CleanUp();

	void OnCollision(PhysBody3D* body1, PhysBody3D* body2);

	PhysBody3D* CreateSceneItem(float x, float y, float z, Type type);

public:
	/*
	PhysBody3D* pb_snake[MAX_SNAKE];
	Sphere s_snake[MAX_SNAKE];

	PhysBody3D* pb_snake2[MAX_SNAKE];
	Sphere s_snake2[MAX_SNAKE];
	*/

	PhysBody3D* pb_chassis;
	Cube p_chassis;

	PhysBody3D* pb_wheel;
	Cylinder p_wheel;

	PhysBody3D* pb_wheel2;
	Cylinder p_wheel2;

	PhysMotor3D* left_wheel;
	PhysMotor3D* right_wheel;


	bool wireframeActive = false;

	Model* ReferenceCube;
	PhysBody3D* obstacle;
	PhysBody3D* roadPtr;
	Cube* leftPole;
	Cube* rightPole;
	Cube* topPole;
	

	Model* baseFloor;
	float counter = 0;
	bool arrived = false;

	PhysBody3D* randomBall;

	/*Cube* cube;
	PhysBody3D* horse;*/
	p2List<PhysBody3D*> roadList;
};
