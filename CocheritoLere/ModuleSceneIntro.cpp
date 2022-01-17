#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "PhysBody3D.h"
#include <gl/GL.h>
#include <gl/GLU.h>

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	App->camera->Move(vec3(1.0f, 1.0f, 0.0f));
	App->camera->LookAt(vec3(0, 0, 0));
	
	
	ReferenceCube = new Model();
	ReferenceCube->model = App->models->LoadModel("Assets/Models/def_cube.obj");
	ReferenceCube->colB = 255;
	ReferenceCube->colG = 0;
	ReferenceCube->colR = 0;
	ReferenceCube->x = 5;
	ReferenceCube->y = 0;
	ReferenceCube->z = 0;
	
	road = new Model();
	road->colR = 0;
	road->colG = 10;
	road->colB = 10;
	//road->scale = 0.5;
	road->x = 0;
	road->y = -8;
	road->z = 0;
	road->scale = 2;
	
	road->orientation = { 0, 1, 0, 0 };
	//road->orientation = { 0.5, 0.5, 0.5, -0.5 };
	
	Cube obstacleGeo(4, 4, 4);
	obstacle = App->physics->AddBody(obstacleGeo,0); //objects with 0 mass act as kinematic
	obstacle->SetPos(5, 0, 0);
	
	
	road->model = App->models->LoadModel("Assets/Models/car_1.obj");

	//cube = App->modelLoader->LoadModel("Assets/Models/full_train.obj");
	//pyramid = App->modelLoader->LoadModel("Assets/Models/pyramid.obj");
	//tracks = App->modelLoader->LoadModel("Assets/Models/tracks.obj");
	//train = App->modelLoader->LoadModel("Assets/Models/full_train.obj");
	//mod_car = App->modelLoader->LoadModel("Assets/Models/car_1.obj");
	

	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");
	delete ReferenceCube;
	delete road;

	return true;
}

// Update
update_status ModuleSceneIntro::Update(float dt)
{
	Plane p(0, 1, 0, 0);
	p.axis = true;
	p.Render();

	if (App->input->GetKey(SDL_SCANCODE_L) == KEY_DOWN)
	{
		wireframeActive = !wireframeActive;
	}
	
	//glBegin(GL_TRIANGLES);
	//
	//
	//glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
	//
	//glVertex3f(0.0f, 0.0f, 0.0f);
	//glVertex3f(1.0f, 0.0f, 0.0f);
	//glVertex3f(1.0f, 1.0f, 0.0f);
	//glVertex3f(0.0f, 1.0f, 0.0f);
	//
	//
	//
	//
	//
	//glEnd();
	
	btVector3 playerPosition = App->player->GetPosition();
		
	road->RenderModel();

	ReferenceCube->RenderModel();
	
	

	
	return UPDATE_CONTINUE;
}
update_status ModuleSceneIntro::PostUpdate(float dt)
{
	

	return UPDATE_CONTINUE;
}
void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
}

