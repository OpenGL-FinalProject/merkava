#include "HitEffect.h"
#include "stdafx.h"
#include <random>

HitEffect::HitEffect()
{
	
}

HitEffect::~HitEffect()
{

}

void HitEffect::create_cube_set(const Vector3& _pattern_hit_pos)
{
	hit_effect_cube_set* temp_cube_set = new (hit_effect_cube_set);
	temp_cube_set->pattern_hit_pos = _pattern_hit_pos;

	for (int i = 0; i < 10; i++)
	{
		temp_cube_set->hit_effect_cubes.push_back(new hit_effect_cube{ {0,0,0},
			{rand() % 1001 / 1000.f,rand() % 1001 / 1000.f,rand() % 1001 / 1000.f}, (rand() % 25 + 75) / 100.f,
			float(rand() % 25 + 75) });
		
	}
	std::cout << temp_cube_set->hit_effect_cubes.size() << std::endl;
	hit_effect_cube_sets.push_back(temp_cube_set);
	std::cout << hit_effect_cube_sets.size() << std::endl;
	std::cout << "#####################"<< std::endl;

}


void HitEffect::update(float fDeltaTime)
{
	//재귀 싫어요
	//하드 코딩 체고오오
	for (int i = 0; i < hit_effect_cube_sets.size(); i++)
	{
		if (hit_effect_cube_sets[i]->hit_effect_cubes.size() == 0)
		{
			hit_effect_cube_sets.erase(hit_effect_cube_sets.begin() + i);
			i--;
			continue;
		}

		for (int j = 0; j < hit_effect_cube_sets[i]->hit_effect_cubes.size(); j++)
		{
			hit_effect_cube_sets[i]->hit_effect_cubes[j]->life_span -= fDeltaTime;

			if (hit_effect_cube_sets[i]->hit_effect_cubes[j]->life_span < 0)
			{
				hit_effect_cube_sets[i]->hit_effect_cubes.erase(hit_effect_cube_sets[i]->hit_effect_cubes.begin() + j);
				j--;
				continue;
			}
			else
			{
				hit_effect_cube_sets[i]->hit_effect_cubes[j]->cur_pos.x += hit_effect_cube_sets[i]->hit_effect_cubes[j]->translate_speed*fDeltaTime;
			}

		}
	}
}

void HitEffect::render()
{
	for (int i = 0; i < hit_effect_cube_sets.size(); i++)
	{
		for (int j = 0; j < hit_effect_cube_sets[i]->hit_effect_cubes.size(); j++)
		{

			glPushMatrix();
			{
				glTranslatef(hit_effect_cube_sets[i]->pattern_hit_pos.x, hit_effect_cube_sets[i]->pattern_hit_pos.y, hit_effect_cube_sets[i]->pattern_hit_pos.z);
				glTranslatef(hit_effect_cube_sets[i]->hit_effect_cubes[j]->cur_pos.x, hit_effect_cube_sets[i]->hit_effect_cubes[j]->cur_pos.y,
					hit_effect_cube_sets[i]->hit_effect_cubes[j]->cur_pos.z);

				glColor3f(hit_effect_cube_sets[i]->hit_effect_cubes[j]->color[0], hit_effect_cube_sets[i]->hit_effect_cubes[j]->color[1], hit_effect_cube_sets[i]->hit_effect_cubes[j]->color[2]);
				glutWireCube(0.8);
			}
			glPopMatrix();
		}

	}
}