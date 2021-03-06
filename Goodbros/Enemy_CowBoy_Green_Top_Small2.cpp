#include "Application.h"
#include "Enemy_CowBoy_Green_Top_Small2.h"
#include "ModuleCollision.h"
#include "ModulePlayer.h"
#include "ModuleEnemies.h"
#include "ModuleSceneFirst.h"

Enemy_CowBoy_Green_Top_Small2::Enemy_CowBoy_Green_Top_Small2(float x, float y) : Enemy(x, y)
{
	forward.PushBack({ 898, 2903, 20, 30 });
	forward.PushBack({ 932, 2903, 20, 30 });
	forward.PushBack({ 965, 2903, 20, 30 });
	forward.PushBack({ 994, 2903, 20, 30 });
	forward.PushBack({ 1028, 2903, 20, 30 });
	forward.PushBack({ 1061, 2903, 20, 30 });
	forward.speed = 0.15f;
	forward.loop = true;

	backward.PushBack({ 460, 2934, 20, 30 });
	backward.PushBack({ 491, 2934, 20, 30 });
	backward.PushBack({ 522, 2934, 20, 30 });
	backward.PushBack({ 557, 2934, 20, 30 });
	backward.PushBack({ 589, 2934, 20, 30 });
	backward.PushBack({ 620, 2934, 20, 30 });
	backward.speed = 0.09f;
	backward.loop = true;

	dieshot.PushBack({ 714, 2934, 20, 30 });
	dieshot.PushBack({ 747, 2934, 20, 30 });
	dieshot.PushBack({ 777, 2934, 13, 30 });
	dieshot.PushBack({ 794, 2934, 20, 30 });
	dieshot.speed = 0.09f;
	dieshot.loop = false;

	dieexplotion.PushBack({ 744, 397, 36, 54 });
	dieexplotion.PushBack({ 798, 397, 36, 54 });
	dieexplotion.PushBack({ 844, 397, 36, 54 });
	dieexplotion.PushBack({ 889, 397, 36, 54 });
	dieexplotion.speed = 0.3f;

	grenadeSm.PushBack({ 591, 1058, 25, 40 });
	grenadeSm.PushBack({ 624, 1058, 25, 40 });
	grenadeSm.PushBack({ 655, 1058, 25, 40 });
	grenadeSm.PushBack({ 687, 1058, 25, 40 });
	grenadeSm.PushBack({ 717, 1058, 25, 40 });
	grenadeSm.PushBack({ 742, 1058, 25, 40 });
	grenadeSm.speed = 0.1f;
	grenadeSm.loop = false;

	shoot.PushBack({ 651, 2934, 25, 40 });
	shoot.PushBack({ 683, 2934, 25, 40 });
	shoot.speed = 0.10f;
	shoot.loop = false;


	idle.PushBack({ 651, 2934, 25, 40 });
	idle.loop = true;



	jumpSm.PushBack({ 780, 2981, 20, 30 });
	jumpSm.PushBack({ 749, 2981, 20, 30 });
	jumpSm.PushBack({ 749, 2981, 20, 30 });
	jumpSm.PushBack({ 780, 2981, 25, 40 });
	jumpSm.loop = true;
	jumpSm.speed = 0.05f;



	spawnn.PushBack({ 477, 2984, 20, 30 });
	spawnn.PushBack({ 509, 2984, 20, 30 });
	spawnn.PushBack({ 541, 2984, 20, 30 });
	spawnn.PushBack({ 572, 2999, 20, 30 });
	spawnn.speed = 0.08f;

	collider = App->collision->AddCollider({ 0, -20, 20, 30 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);


	if (x == 185){

		path.PushBack({ 0, 0 }, 50, &spawnn);
		path.PushBack({ -0.6f, 0 }, 40, &backward);
		path.PushBack({ 0, 0 }, 15, &idle);
		path.PushBack({ 0.6f, 0 }, 120, &forward);
		path.PushBack({ 0, 0 }, 30, &shoot);
		path.PushBack({ 0, -1.50f }, 5, &jumpSm);
		path.PushBack({ 0, 1.50f }, 30, &jumpSm);
		path.PushBack({ 0.6f, 0 }, 300, &forward);
		path.loop = false;

	}

	if (x == 215){

		path.PushBack({ 0, 0 }, 50, &spawnn);
		path.PushBack({ -0.6f, 0 }, 40, &backward);
		path.PushBack({ 0, 0 }, 15, &idle);
		path.PushBack({ 0.6f, 0 }, 80, &forward);
		path.PushBack({ 0, 0 }, 30, &shoot);
		path.PushBack({ 0, -1.50f }, 5, &jumpSm);
		path.PushBack({ 0, 1.50f }, 30, &jumpSm);
		path.PushBack({ 0.6f, 0 }, 300, &forward);
		path.loop = false;

	}

	if ( x == 135){



		path.PushBack({ 0, 0 }, 50, &spawnn);
		path.PushBack({ 0.6f, 0 }, 30, &forward);
		path.PushBack({ 0, 0 }, 15, &shoot);
		path.PushBack({ 0.6f, 0 }, 500, &forward);
		path.loop = false;

	}




	




	original_pos.x = x;
	original_pos.y = y;

}

void Enemy_CowBoy_Green_Top_Small2::Move()
{
	position = original_pos + path.GetCurrentSpeed(&animation);
	if (original_pos.x == 135){
		if (path.GetFrame() == 85){
			App->particles->AddParticle(App->particles->enemyshot, position.x + 5, position.y + 10, COLLIDER_ENEMY_SHOT, 0);
		}
	}
	if (original_pos.x == 215 || original_pos.x == 185){
		if (path.GetFrame() == 235){
			App->particles->AddParticle(App->particles->enemyshot, position.x + 5, position.y + 10, COLLIDER_ENEMY_SHOT, 0);
		}
	}
	if (dieshot.Finished() == true)
	{
		finished = true;
	}

}

void Enemy_CowBoy_Green_Top_Small2::Die()
{
	collider->type = COLLIDER_NONE;
	App->player->win_condition++;
	path.Erase();
	path.PushBack({ 0.0f, 0.0f }, 40, &dieshot);
	path.loop = false;
}