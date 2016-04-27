#ifndef __MODULESTRUCTURES_H__
#define __MODULESTRUCTURES_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"


#define MAX_BUILDINGS 8

enum buildingtype{ BAR, };

struct SDL_Texture;

struct Structure
{
	SDL_Rect Coll_Struct;
	Animation destroy;
	uint fx = 0;
	fPoint position;
	bool fx_played = false;
	Collider* collider = nullptr;
	buildingtype mytype;
	uint hits = 0;
	Structure();
	Structure(const Structure& p);
	~Structure();
	bool Update();
	const Collider* get_collider()const;
};


class ModuleStructures : public Module
{
public:
	ModuleStructures();
	~ModuleStructures();

	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(Collider* c1, Collider* c2);
	void AddStructure(const Structure& particle, int x, int y);


private:

	SDL_Texture* graphics = nullptr;
	Structure* active[MAX_BUILDINGS];
	uint last_building = 0;

public:


	Structure bar, bar2, bar3, bar4, bar5;

};

#endif // __MODULESTRUCTURES_H__