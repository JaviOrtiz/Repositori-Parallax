#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"
#include "ModuleFadeToBlack.h"
#include "ModulePlayer.h"
#include "ModuleAim.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModuleAim::ModuleAim()
{
	idle.PushBack({ 542, 289, 23, 21 });

	shoot.PushBack({ 542, 289, 23, 21 });
	shoot.PushBack({ 579, 289, 23, 31 });
	shoot.speed = 0.2f;
	
}

ModuleAim::~ModuleAim()
{}

// Load assets
bool ModuleAim::Start()
{
	LOG("Loading Aim");

	graphics = App->textures->Load("bloodbros/Stuff.png");

	position.x = 110;
	position.y = 75;

	Aim = App->collision->AddCollider({ position.x + 3, position.y + 3, 22, 20 }, COLLIDER_PLAYER_SHOT);

	return true;
}

// Unload assets
bool ModuleAim::CleanUp()
{
	LOG("Unloading player");

	App->textures->Unload(graphics);

	return true;
}

// Update: draw background
update_status ModuleAim::Update()
{
	int speed = 3;
	current_animation = &shoot;

	if (App->input->keyboard[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_REPEAT&&position.x>2)
	{

		position.x -= speed;
	}

	if (App->input->keyboard[SDL_SCANCODE_RIGHT] == KEY_STATE::KEY_REPEAT&&position.x<230)
	{
		
		position.x += speed;
	}

	if (App->input->keyboard[SDL_SCANCODE_UP] == KEY_STATE::KEY_REPEAT&&position.y>2)
	{
	;
		position.y -= speed;
	}
	if (App->input->keyboard[SDL_SCANCODE_DOWN] == KEY_STATE::KEY_REPEAT&&position.y<157)
	{
		position.y += speed;
	}
	if (App->input->keyboard[SDL_SCANCODE_Z] == KEY_STATE::KEY_DOWN)
	{
		App->particles->AddParticle(App->particles->shot, position.x + 2, position.y + 3);
	}

	Aim->rect.x = position.x + 1;
	Aim->rect.y = position.y + 1;

	/*if(App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_IDLE
	&& App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_IDLE && App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_IDLE && App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_IDLE)
	current_animation = &idle;*/


	// Draw everything --------------------------------------
	App->render->Blit(graphics, position.x, position.y, &(current_animation->GetCurrentFrame()));

	return UPDATE_CONTINUE;
}