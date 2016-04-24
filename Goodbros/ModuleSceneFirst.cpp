#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModuleSceneFirst.h"
#include "ModuleAim.h"
#include "ModuleAudio.h"
#include "ModuleEnemies.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModuleSceneFirst::ModuleSceneFirst()
{}

ModuleSceneFirst::~ModuleSceneFirst()
{}

// Load assets
bool ModuleSceneFirst::Start()
{
	LOG("Loading space scene");
	
	background = App->textures->Load("bloodbros/level1.png");
	App->audio->Enable(1);
	App->player->Enable(0);
	App->particles->Enable(0);
	App->collision->Enable(0);
	App->aim->Enable(0);
	
	// Colliders ---
	App->collision->AddCollider({0, 224, 3930, 16}, COLLIDER_WALL);


	App->enemies->AddEnemy(ENEMY_TYPES::PIG, 210, 130);

	return true;
}

// UnLoad assets
bool ModuleSceneFirst::CleanUp()
{
	LOG("Unloading space scene");

 	App->textures->Unload(background);
	App->player->Disable();
	App->collision->Disable();
	App->particles->Disable();
	App->aim->Disable();
	
	return true;
}

// Update: draw background
update_status ModuleSceneFirst::Update()
{
	// Move camera forward -----------------------------
	int scroll_speed = 0;

	App->player->position.x += 0;
	App->render->camera.x -= 0;
	

	// Draw everything --------------------------------------
	App->render->Blit(background, 0, 0, NULL);
	
	return UPDATE_CONTINUE;
}