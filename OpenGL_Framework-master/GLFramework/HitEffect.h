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
		Vector3 direction;
		float speed;
		float color[3];
		float start_alpha; //변수명 짓는게 제일 어려운 거시에오 만들어졌을때 기본 알파값이에오
		float alpha_increase_speed;
		float life_span;  //elapsed_tim >= life_spane -> kill this object
		float elapsed_time;
		
	};
	typedef struct hit_effect_cube_set
	{
		Vector3 pattern_hit_pos;
		std::vector<hit_effect_cube*> hit_effect_cubes;
	};

	void create_cube_set(const Vector3& _pattern_hit_pos, const int& patternHit);
	void update(float fDeltaTime);
	void render();

private:

	
	std::vector<hit_effect_cube_set*> hit_effect_cube_sets;
};