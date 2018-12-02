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
		float start_alpha; //������ ���°� ���� ����� �Žÿ��� ����������� �⺻ ���İ��̿���
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