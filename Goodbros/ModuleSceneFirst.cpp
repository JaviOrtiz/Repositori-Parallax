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
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleStructures.h"
#include "ModuleUI.h"

ModuleSceneFirst::ModuleSceneFirst()
{}

ModuleSceneFirst::~ModuleSceneFirst()
{}

// Load assets
bool ModuleSceneFirst::Start()
{
	// Loading textures
	LOG("Loading first stage scene");
	background = App->textures->Load("bloodbros/level1destroyed.png");
	App->audio->Load("bloodbros/level1.ogg");
	
	// Loading various modules
	App->particles->Start();
	App->player->Enable();
	App->particles->Enable();
	App->enemiesback->Enable();
	App->enemiesfront->Enable();
	App->collision->Enable();
	App->aim->Enable();
	App->structuresfront->Enable();
	App->UserUI->Enable();
	App->enemies->Enable();
	App->love->Enable();
	App->smoke->Enable();

	// Player reset position & death animation
	App->player->position.x = 120;
	App->player->position.y = 150;

	// Buildings
	App->structuresback->AddStructure(App->structuresback->inn, 0, 32);
	App->structuresback->AddStructure(App->structuresback->hotel, 105, 35);
	App->structuresback->AddStructure(App->structuresback->smallest_b, 175, 42);
	App->structuresmiddle->AddStructure(App->structuresmiddle->fabten, 0, 8);
	App->structuresmiddle->AddStructure(App->structuresmiddle->bar, 145, 0);
	//App->structuresfront->AddStructure(App->structuresfront->column, 155, 88);

	App->enemies->AddEnemy(ENEMY_TYPES::CAN, SCREEN_WIDTH / 2 + 5, 130, NULL, NULL);
	App->enemies->AddEnemy(ENEMY_TYPES::GIRL, 0, 105, NULL, NULL);
	App->barrelroll->AddEnemy(ENEMY_TYPES::BARREL_ROLL, 0, 130, NULL, NULL);

	App->structuresmiddle->bardest = false;
	App->structuresmiddle->fabtendest = false;
	couple = false;
	poop = false;

	//Barrels
	App->structuresfront->AddStructure(App->structuresfront->barrel, 6, 144);
	App->structuresfront->AddStructure(App->structuresfront->barrel, 38, 144);
	App->structuresfront->AddStructure(App->structuresfront->barrel, 198, 144);

	// Time counters
	time = SDL_GetTicks();
	time2 = SDL_GetTicks();
	time3 = SDL_GetTicks();

	return true;
}

// UnLoad assets
bool ModuleSceneFirst::CleanUp()
{
	LOG("Unloading first scene");

	App->player->windance.Reset();
	App->player->gwindance.Reset();
	App->textures->Unload(background);
	App->player->Disable();
	App->aim->Disable();
	App->structuresfront->Disable();
	App->structuresmiddle->Disable();
	App->structuresback->Disable();
	App->enemies->Disable();
	App->barrelroll->Disable();
	App->points->Disable();
	App->smoke->Disable();
	App->collision->Disable();
	App->enemiesfront->Disable();
	App->enemiesback->Disable();
	App->love->Disable();
	return true;
}

// Update: draw background
update_status ModuleSceneFirst::Update()
{
	if (SDL_GetTicks() > time + 100)
	{
		App->enemiesfront->AddEnemy(ENEMY_TYPES::GREEN_COWBOY_BIG_LEFT, -14, 106, NULL, 5000);
		App->enemiesfront->AddEnemy(ENEMY_TYPES::GREEN_COWBOY_BIG_RIGHT, 250, 106, NULL, 5000);
		App->enemies->AddEnemy(ENEMY_TYPES::GREEN_COWBOY_MEDIUM_LEFT, -14, 107, NULL, 7000);
		App->enemies->AddEnemy(ENEMY_TYPES::GREEN_COWBOY_MEDIUM_RIGHT, 250, 107, NULL, 7000);
		App->enemies->AddEnemy(ENEMY_TYPES::PIG, 250, 137, NULL, 4000);
		App->enemies->AddEnemy(ENEMY_TYPES::GREEN_COWBOY_MEDIUM_LEFT, -14, 100, NULL, 8000);
		App->enemies->AddEnemy(ENEMY_TYPES::GREEN_COWBOY_MEDIUM_RIGHT, 250, 100, NULL, 8000);
		App->enemies->AddEnemy(ENEMY_TYPES::HORSE_RIGHT, 250, 90, NULL, 9000);
		App->enemiesfront->AddEnemy(ENEMY_TYPES::RIDER, 257, 98, NULL, 9000);
		
		time = SDL_GetTicks() + 30000;
	}
	if (SDL_GetTicks() > time2 + 14000)
	{
		if (App->structuresmiddle->bardest == false && App->structuresfront->bardest == false && App->structuresback->bardest == false)
		{
			App->enemiesback->AddEnemy(ENEMY_TYPES::WHEELBARROW, 250, 95, 1, 1000);
			App->enemiesback->AddEnemy(ENEMY_TYPES::HORSE_SMALL_RIGHT, 250, 95, NULL, 1000);
			App->enemiesback->AddEnemy(ENEMY_TYPES::RIDER_SMALL_RIGHT, 257, 92, NULL, 1000);
			App->enemies->AddEnemy(ENEMY_TYPES::GREEN_COWBOY_RIGHT_TUMBLE, 210, 100, NULL, 3000);
			App->enemies->AddEnemy(ENEMY_TYPES::BLUE_COWBOY_TOP_FABTEN, 170, 47, NULL, 4000);
			App->enemies->AddEnemy(ENEMY_TYPES::GREEN_COWBOY_TOP_BAR, 215, 45, NULL, 4200);
		}
		else
		{
			App->enemiesback->AddEnemy(ENEMY_TYPES::GREEN_COWBOY_TOP_SMALL2, 215, 55, NULL, 3000);
			App->enemiesback->AddEnemy(ENEMY_TYPES::GREEN_COWBOY_TOP_SMALL2, 185, 55, NULL, 3200);
			App->enemiesback->AddEnemy(ENEMY_TYPES::GREEN_COWBOY_TOP_SMALL, 155, 55, NULL, 3400);
			App->enemiesback->AddEnemy(ENEMY_TYPES::GREEN_COWBOY_TOP_SMALL, 120, 55, NULL, 3600);
			App->enemiesback->AddEnemy(ENEMY_TYPES::GREEN_COWBOY_TOP_SMALL2, 135, 90, NULL, 1000);
			App->enemiesback->AddEnemy(ENEMY_TYPES::GREEN_COWBOY_TOP_SMALL, 195, 90, NULL, 1000);

			App->enemiesback->AddEnemy(ENEMY_TYPES::GREEN_COWBOY_TOP_SMALL3, 110, 31, NULL, 5200);
			App->enemiesback->AddEnemy(ENEMY_TYPES::GREEN_COWBOY_TOP_SMALL3, 170, 31, NULL, 5100);
			App->enemiesback->AddEnemy(ENEMY_TYPES::GREEN_COWBOY_TOP_SMALL3, 230, 31, NULL, 5300);
		}
		time2 = SDL_GetTicks() + 16000;
	}
	if (SDL_GetTicks() > time4 + 9000)
	{
		App->enemiesback->AddEnemy(ENEMY_TYPES::WHEELBARROW, SCREEN_WIDTH, 98, NULL, 200);
		App->enemiesback->AddEnemy(ENEMY_TYPES::WHEELBARROW, SCREEN_WIDTH, 98, NULL, 600);
		App->enemiesback->AddEnemy(ENEMY_TYPES::WHEELBARROW, SCREEN_WIDTH, 98, NULL, 900);
		time4 = SDL_GetTicks() + 16000;

	}
	if (SDL_GetTicks() > time3 + 22000)
	{
		if (App->structuresmiddle->fabtendest == false && App->structuresfront->fabtendest == false && App->structuresback->fabtendest == false)
		{
			App->enemies->AddEnemy(ENEMY_TYPES::BLUE_COWBOY_TOP_FABTEN, 7, 100, NULL, NULL);
			App->enemies->AddEnemy(ENEMY_TYPES::BLUE_COWBOY_TOP_FABTEN, 45, 100, NULL, NULL);
			App->enemies->AddEnemy(ENEMY_TYPES::GREEN_COWBOY_TOP_BAR, 3, 47, NULL, 2000);
			App->enemies->AddEnemy(ENEMY_TYPES::GREEN_COWBOY_TOP_BAR, 25, 47, NULL, 2100);
			App->enemies->AddEnemy(ENEMY_TYPES::GREEN_COWBOY_TOP_BAR, 50, 47, NULL, 2200);
		}
		else
		{
			App->enemiesback->AddEnemy(ENEMY_TYPES::BLUE_COWBOY_TOP_SMALL, 70, 95, NULL, NULL);
			App->enemiesback->AddEnemy(ENEMY_TYPES::BLUE_COWBOY_TOP_SMALL, 40, 95, NULL, 100);
			App->enemiesback->AddEnemy(ENEMY_TYPES::BLUE_COWBOY_TOP_SMALL, 10, 95, NULL, 200);


			App->enemiesback->AddEnemy(ENEMY_TYPES::GREEN_COWBOY_TOP_SMALL4, 70, 50, NULL, 2000);
			App->enemiesback->AddEnemy(ENEMY_TYPES::GREEN_COWBOY_TOP_SMALL4, 40, 50, NULL, 2200);
			App->enemiesback->AddEnemy(ENEMY_TYPES::GREEN_COWBOY_TOP_SMALL4, 10, 50, NULL, 2400);

			App->enemiesback->AddEnemy(ENEMY_TYPES::GREEN_COWBOY_TOP_SMALL3, 5, 15, NULL, 5600);
			App->enemiesback->AddEnemy(ENEMY_TYPES::GREEN_COWBOY_TOP_SMALL3, 20, 15, NULL, 5500);
			App->enemiesback->AddEnemy(ENEMY_TYPES::GREEN_COWBOY_TOP_SMALL3, 35, 15, NULL, 5400);
			App->enemiesback->AddEnemy(ENEMY_TYPES::GREEN_COWBOY_TOP_SMALL3, 50, 15, NULL, 5300);
			App->enemiesback->AddEnemy(ENEMY_TYPES::GREEN_COWBOY_TOP_SMALL3, 65, 15, NULL, 5200);
			App->enemiesback->AddEnemy(ENEMY_TYPES::GREEN_COWBOY_TOP_SMALL3, 80, 15, NULL, 5100);
		}

		time3 = SDL_GetTicks() + 8000;
	}
	if (App->structuresmiddle->bardest == true && couple == false)
	{
		App->enemiesback->AddEnemy(ENEMY_TYPES::COUPLE_GUY, 170, 95, NULL, 1000);
		App->enemiesback->AddEnemy(ENEMY_TYPES::COUPLE_GIRL, 180, 95, NULL, 1000);
		App->love->AddParticle(App->particles->love, 176, 90, COLLIDER_NONE, 2500);
		App->love->AddParticle(App->particles->love, 176, 90, COLLIDER_NONE, 2900);

		couple = true;
	}
	if (App->structuresmiddle->fabtendest == true && poop == false)
	{
		App->enemiesback->AddEnemy(ENEMY_TYPES::POOPING_GUY, 45, 95, NULL, 2000);
		App->love->AddParticle(App->particles->WC, 50, 117, COLLIDER_NONE, 2300);
		poop = true;
	}
	if (App->input->keyboard[SDL_SCANCODE_F2] == KEY_STATE::KEY_DOWN)
	{
		App->enemies->AddEnemy(ENEMY_TYPES::GREEN_COWBOY_TOP_SMALL, 120, 55, NULL, 1000);
		App->enemies->AddEnemy(ENEMY_TYPES::GREEN_COWBOY_TOP_SMALL, 155, 55, NULL, 1000);
		App->enemies->AddEnemy(ENEMY_TYPES::GREEN_COWBOY_TOP_SMALL2, 185, 55, NULL, 1000);
		App->enemies->AddEnemy(ENEMY_TYPES::GREEN_COWBOY_TOP_SMALL2, 215, 55, NULL, 1000);
		App->enemies->AddEnemy(ENEMY_TYPES::GREEN_COWBOY_TOP_SMALL2, 135, 90, NULL, 1000);
		App->enemies->AddEnemy(ENEMY_TYPES::GREEN_COWBOY_TOP_SMALL, 195, 90, NULL, 1000);
		App->enemies->AddEnemy(ENEMY_TYPES::GREEN_COWBOY_TOP_SMALL3, 105, 31, NULL, 1000);
		App->enemies->AddEnemy(ENEMY_TYPES::GREEN_COWBOY_TOP_SMALL3, 172, 31, NULL, 1000);
		App->enemies->AddEnemy(ENEMY_TYPES::GREEN_COWBOY_TOP_SMALL3, 232, 31, NULL, 1000);
	}
	if (App->input->keyboard[SDL_SCANCODE_F3] == KEY_STATE::KEY_DOWN)
	{
		App->barrelroll->AddEnemy(ENEMY_TYPES::BARREL_ROLL, 0, 130, NULL, NULL);
		App->enemies->AddEnemy(ENEMY_TYPES::CAN, SCREEN_WIDTH / 2 + 5, 130, NULL, NULL);
	}
	if (App->input->keyboard[SDL_SCANCODE_F4] == KEY_STATE::KEY_DOWN)
	{
		App->enemies->AddEnemy(ENEMY_TYPES::GREEN_COWBOY_BIG_LEFT, -14, 110, NULL, NULL);
		App->enemies->AddEnemy(ENEMY_TYPES::GREEN_COWBOY_BIG_RIGHT, SCREEN_WIDTH, 110, NULL, NULL);
		App->enemies->AddEnemy(ENEMY_TYPES::GREEN_COWBOY_MEDIUM_LEFT, -14, 100, NULL, NULL);
		App->enemies->AddEnemy(ENEMY_TYPES::GREEN_COWBOY_MEDIUM_RIGHT, SCREEN_WIDTH, 100, NULL, NULL);
	}
	if (App->input->keyboard[SDL_SCANCODE_F5] == KEY_STATE::KEY_DOWN)
	{
		App->enemies->AddEnemy(ENEMY_TYPES::HORSE_RIGHT, SCREEN_WIDTH, 100, NULL, NULL);
		App->enemies->AddEnemy(ENEMY_TYPES::HORSE_SMALL_RIGHT, SCREEN_WIDTH, 100, NULL, NULL);
	}
	if (App->input->keyboard[SDL_SCANCODE_F6] == KEY_STATE::KEY_DOWN)
	{
		App->points->AddEnemy(ENEMY_TYPES::POINTS, 50, 50, 4, NULL);
		App->enemies->AddEnemy(ENEMY_TYPES::GREEN_COWBOY_RIGHT_TUMBLE, 210, 107, NULL, NULL);
	}
	if (App->input->keyboard[SDL_SCANCODE_F7] == KEY_STATE::KEY_DOWN)
	{
		App->enemies->AddEnemy(ENEMY_TYPES::BLUE_COWBOY_TOP_FABTEN, 7, 100, NULL, NULL);
		App->enemies->AddEnemy(ENEMY_TYPES::BLUE_COWBOY_TOP_FABTEN, 45, 100, NULL, NULL);
	}

	// Draw everything
	App->render->Blit(background, 0, 0, NULL);
	if (App->player->win_condition >= 28)
	{
		App->audio->Load("bloodbros/Victory.ogg");
		App->player->Status = WIN;
		App->player->win_condition = 0;
	}
	if (App->UserUI->continue_counter == 0)
	{
		App->player->lose = 0;
		App->player->win_condition = 0;
	}
	return UPDATE_CONTINUE;
}