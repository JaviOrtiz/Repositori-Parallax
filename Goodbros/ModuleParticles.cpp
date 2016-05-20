#include <math.h>
#include "Globals.h"
#include "Application.h"
#include "ModuleAudio.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"

#include "SDL/include/SDL_timer.h"

ModuleParticles::ModuleParticles()
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
		active[i] = nullptr;

	//shot.anim.PushBack({ 625, 288, 22, 14 });
	enemyshot.anim.PushBack({ 399, 494, 9, 9});
	enemyshot.anim.PushBack({ 429, 494, 9, 9 });
	
	enemyshot.anim.loop = true;
	enemyshot.anim.speed = 0.035f;
	enemyshot.speed.y = 1.5f;
	enemyshot.life = 2000;


	//smoke.anim.pushback;
	smoke.anim.PushBack({ 27, 45, 127, 30 });
	smoke.anim.PushBack({ 27, 77, 127, 30 });
	smoke.anim.PushBack({ 27, 112, 127, 30 });
	smoke.anim.PushBack({ 27, 153, 127, 30 });
	smoke.anim.PushBack({ 27, 45, 127, 30 });
	smoke.anim.PushBack({ 27, 77, 127, 30 });
	smoke.anim.PushBack({ 27, 112, 127, 30 });
	smoke.anim.PushBack({ 27, 153, 127, 30 });
	smoke.anim.PushBack({ 27, 45, 127, 30 });
	smoke.anim.PushBack({ 27, 77, 127, 30 });
	smoke.anim.PushBack({ 27, 112, 127, 30 });
	smoke.anim.PushBack({ 27, 153, 127, 30 });
	smoke.anim.PushBack({ 27, 45, 127, 30 });
	smoke.anim.PushBack({ 27, 77, 127, 30 });
	smoke.anim.PushBack({ 27, 112, 127, 30 });
	smoke.anim.PushBack({ 27, 153, 127, 30 });
	smoke.anim.PushBack({ 27, 45, 127, 30 });
	smoke.anim.PushBack({ 27, 77, 127, 30 });
	smoke.anim.PushBack({ 27, 112, 127, 30 });
	smoke.anim.PushBack({ 27, 153, 127, 30 });
	smoke.anim.PushBack({ 27, 45, 127, 30 });
	smoke.anim.PushBack({ 27, 77, 127, 30 });
	smoke.anim.PushBack({ 27, 112, 127, 30 });
	smoke.anim.PushBack({ 27, 153, 127, 30 });
	smoke.anim.PushBack({ 27, 45, 127, 30 });
	smoke.anim.PushBack({ 27, 77, 127, 30 });
	smoke.anim.PushBack({ 27, 112, 127, 30 });
	smoke.anim.PushBack({ 27, 153, 127, 30 });
	smoke.anim.PushBack({ 27, 45, 127, 30 });
	smoke.anim.PushBack({ 27, 77, 127, 30 });
	smoke.anim.PushBack({ 27, 112, 127, 30 });
	smoke.anim.PushBack({ 27, 153, 127, 30 });
	smoke.anim.PushBack({ 27, 45, 127, 30 });
	smoke.anim.PushBack({ 27, 77, 127, 30 });
	smoke.anim.PushBack({ 27, 112, 127, 30 });
	smoke.anim.PushBack({ 27, 153, 127, 30 });
	smoke.anim.PushBack({ 27, 45, 127, 30 });
	smoke.anim.PushBack({ 27, 77, 127, 30 });

	smoke.anim.loop = true;
	smoke.anim.speed = 0.14f;
	smoke.life = 12000;

	barrel1.anim.PushBack({ 77, 3358, 23, 41 });
	barrel1.anim.loop = true;
	barrel1.anim.speed = 0.1f;
	barrel1.life = 1200;

	barrel2.anim.PushBack({ 77, 3358, 23, 41 });
	barrel2.anim.PushBack({ 112, 3357, 47, 45 });
	barrel2.anim.loop = true;
	barrel2.anim.speed = 0.1f;
	barrel2.life = 1200;

	barrel3.anim.PushBack({ 77, 3358, 23, 41 });
	barrel3.anim.PushBack({ 112, 3357, 47, 45 });
	barrel3.anim.PushBack({ 164, 3359, 62, 59 });
	barrel3.anim.loop = true;
	barrel3.anim.speed = 0.1f;
	barrel3.life = 1200;
}
   

ModuleParticles::~ModuleParticles()
{}

// Load assets
bool ModuleParticles::Start()
{
	LOG("Loading particles");

	shot.fx = App->audio->LoadFx("bloodbros/shot.wav");

	graphics = App->textures->Load("bloodbros/Stuff.png");

	return true;
}

// Unload assets
bool ModuleParticles::CleanUp()
{
	LOG("Unloading particles");
	App->textures->Unload(graphics);

	// Unload fx

	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if (active[i] != nullptr)
		{
			delete active[i];
			active[i] = nullptr;
		}
	}

	return true;
}

// Update: draw background
update_status ModuleParticles::Update()
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		Particle* p = active[i];

		if (p == nullptr)
			continue;

		if (p->Update() == false)
		{
			delete p;
			active[i] = nullptr;
		}
		else if (SDL_GetTicks() >= p->born)
		{
			App->render->Blit(graphics, p->position.x, p->position.y, &(p->anim.GetCurrentFrame()));
			if (p->fx_played == false)
			{
				p->fx_played = true;
				App->audio->PlayFx(p->fx);
				
			}
		}
	}
	return UPDATE_CONTINUE;
}

void ModuleParticles::AddParticle(const Particle& particle, float x, float y, COLLIDER_TYPE collider_type, Uint32 delay)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if (active[i] == nullptr)
		{
			Particle* p = new Particle(particle);
			p->position.x = x;
			p->position.y = y;
			if (collider_type != COLLIDER_NONE)
				p->collider = App->collision->AddCollider(p->anim.GetCurrentFrame(), collider_type, this);

			active[i] = p;
			break;
		}
	}
}

void ModuleParticles::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		// Always destroy particles that collide
		if (active[i] != nullptr && active[i]->collider == c1)
		{
			//AddParticle(explosion, active[i]->position.x, active[i]->position.y);
			delete active[i];
			active[i] = nullptr;
			break;
		}
	}
	if (c1 == App->player->player_coll || c2 == App->player->player_coll){
		App->player->Status = DIE;
		
	}
}

// -------------------------------------------------------------
// -------------------------------------------------------------

Particle::Particle()
{
	position.SetToZero();
	speed.SetToZero();
}

Particle::Particle(const Particle& p) :
anim(p.anim), position(p.position), speed(p.speed),
fx(p.fx), born(p.born), life(p.life)
{}

Particle::~Particle()
{
	if (collider != nullptr)
		App->collision->EraseCollider(collider);
}

bool Particle::Update()
{
	bool ret = true;

	if (anim.Finished())
		ret = false;

	position.x += speed.x;
	position.y += speed.y;

	if (collider != nullptr)
		collider->SetPos(position.x, position.y);

	return ret;
}

