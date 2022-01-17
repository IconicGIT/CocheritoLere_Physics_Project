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
	
	cube = new Model();

	cube->model = App->models->LoadModel("Assets/Models/def_cube.obj");
	cube->colB = 255;
	cube->colG = 0;
	cube->colR = 0;
	cube->x = 0;
	cube->y = 0;
	cube->z = 0;
	
	road = new Model();
	road->colB = 0;
	road->colG = 255;
	road->colG = 255;
	road->x = 0;
	road->y = 0;
	road->z = 0;
	
	Cube obstacleGeo(4, 4, 4);
	obstacle = App->physics->AddBody(obstacleGeo,0);
	obstacle->SetPos(0, 0, 0);
	
	
	road->model = App->models->LoadModel("Assets/Models/trail/race_base_floor.obj");

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
	delete cube;

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
		

	cube->RenderModel();
	road->RenderModel();
	


	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
}

