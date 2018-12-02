#pragma once
#include "Transformations.h"
#include <vector>


class HitEffect
{
public:
	HitEffect();
	~HitEffect();

	typedef struct hit_effect_cube
	{
		Vector3 cur_pos;
		float color[3];
		float life_span;

		//Vector3 rotate_axis; //회전축은 아닌데 생각나는 이름이 없네 
		//float rotate_speed;
		float translate_speed;
		
	};
	typedef struct hit_effect_cube_set
	{
		Vector3 pattern_hit_pos;
		std::vector<hit_effect_cube*> hit_effect_cubes;
	};

	void create_cube_set(const Vector3& _pattern_hit_pos);
	void update(float fDeltaTime);
	void render();

private:

	
	std::vector<hit_effect_cube_set*> hit_effect_cube_sets;
};