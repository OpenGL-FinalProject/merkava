#include "HitEffect.h"
#include "stdafx.h"
#include <math.h>
#include <random>

HitEffect::HitEffect()
{
	
}

HitEffect::~HitEffect()
{

}

void HitEffect::create_cube_set(const Vector3& _pattern_hit_pos, const int& patternHit)
{
	//patternHit.2 == perfect   patternHit.1 == good
	//patternHit.perfect - particle 3*3*3   patternHit.good - particle 2*2*2
	int particle_num_for_each_axis;

	if (patternHit == 2)
		particle_num_for_each_axis = 3;
	else if(patternHit==1)
		particle_num_for_each_axis = 2;
	// particle_num_for_each_axis = patternHit + 2;

	hit_effect_cube_set* temp_cube_set = new (hit_effect_cube_set);
	temp_cube_set->pattern_hit_pos = _pattern_hit_pos;

	//현재 파티클 125개씩 생성
	float temp_vector_lenght = 0.f;
	for (int i = 0; i < particle_num_for_each_axis; i++)
	{
		for (int j = 0; j < particle_num_for_each_axis; j++)
		{
			for (int k = 0; k < particle_num_for_each_axis; k++)
			{
				if ((i == particle_num_for_each_axis/2) && (j == particle_num_for_each_axis / 2)&&(k== particle_num_for_each_axis / 2)) //0,0,0 패스
					continue;
				hit_effect_cube* temp_cube = new(hit_effect_cube);
				//정규화
				temp_vector_lenght = sqrt((i - particle_num_for_each_axis / 2)*(i - particle_num_for_each_axis / 2) + (j - particle_num_for_each_axis / 2)*(j - particle_num_for_each_axis / 2) 
					+ (k - particle_num_for_each_axis / 2)*(k - particle_num_for_each_axis / 2));
				temp_cube->direction.x = (i - particle_num_for_each_axis / 2) / temp_vector_lenght;
				temp_cube->direction.y = (j - particle_num_for_each_axis / 2) / temp_vector_lenght;
				temp_cube->direction.z = (k - particle_num_for_each_axis / 2) / temp_vector_lenght;

				//색상 랜덤
				for (int l = 0; l < 3; l++)
					temp_cube->color[l] = rand() % 1001 / 1000.f;
				//기본 알파 범위 - 0.3 ~ 0.6
				temp_cube->start_alpha = rand() % 301 / 1000.f + 0.3f;
				//알파 감소 속도
				temp_cube->alpha_increase_speed = (1-temp_cube->start_alpha) / temp_cube->life_span;
				temp_cube->speed = float(rand() % 5 + 10);
				temp_cube->life_span = (rand() % 25 + 75) / 100.f;
				temp_cube->elapsed_time = 0.f;
				

				temp_cube_set->hit_effect_cubes.push_back(temp_cube);
			}
		}		
	}
	hit_effect_cube_sets.push_back(temp_cube_set);
}


void HitEffect::update(float fDeltaTime)
{
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
			hit_effect_cube_sets[i]->hit_effect_cubes[j]->elapsed_time += fDeltaTime;

			//지속시간 다 지나면 삭제
			if (hit_effect_cube_sets[i]->hit_effect_cubes[j]->life_span < hit_effect_cube_sets[i]->hit_effect_cubes[j]->elapsed_time)
			{
				hit_effect_cube_sets[i]->hit_effect_cubes.erase(hit_effect_cube_sets[i]->hit_effect_cubes.begin() + j);
				j--;
				continue;
			}

		}
	}
}

void HitEffect::render()
{
	float temp_speed_offset;
	for (int i = 0; i < hit_effect_cube_sets.size(); i++)
	{
		for (int j = 0; j < hit_effect_cube_sets[i]->hit_effect_cubes.size(); j++)
		{
			temp_speed_offset = hit_effect_cube_sets[i]->hit_effect_cubes[j]->speed*hit_effect_cube_sets[i]->hit_effect_cubes[j]->elapsed_time;
			glPushMatrix();
			{
				glTranslatef(hit_effect_cube_sets[i]->pattern_hit_pos.x + hit_effect_cube_sets[i]->hit_effect_cubes[j]->direction.x *temp_speed_offset,
					hit_effect_cube_sets[i]->pattern_hit_pos.y + hit_effect_cube_sets[i]->hit_effect_cubes[j]->direction.y *temp_speed_offset,
					hit_effect_cube_sets[i]->pattern_hit_pos.z + hit_effect_cube_sets[i]->hit_effect_cubes[j]->direction.z *temp_speed_offset);

				glEnable(GL_CULL_FACE);
				glEnable(GL_BLEND);
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
				glColor4f(hit_effect_cube_sets[i]->hit_effect_cubes[j]->color[0], hit_effect_cube_sets[i]->hit_effect_cubes[j]->color[1], hit_effect_cube_sets[i]->hit_effect_cubes[j]->color[2],
					hit_effect_cube_sets[i]->hit_effect_cubes[j]->start_alpha + hit_effect_cube_sets[i]->hit_effect_cubes[j]->alpha_increase_speed*hit_effect_cube_sets[i]->hit_effect_cubes[j]->elapsed_time);
				//현재 출력 - 큐브
				glutWireCube(0.8);
				glDisable(GL_BLEND);
			}
			glPopMatrix();
		}

	}
}