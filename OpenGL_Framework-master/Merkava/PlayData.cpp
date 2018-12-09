#include "stdafx.h"
#include "PlayData.h"

PlayData* PlayData::inst;

PlayData::PlayData(const PlayData &other)
{
	score = other.score;
	patternNum = other.patternNum;

	memcpy(patternHit, other.patternHit, sizeof(float) * 600);
}
