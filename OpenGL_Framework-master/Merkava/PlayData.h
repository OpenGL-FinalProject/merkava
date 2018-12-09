#pragma once
class PlayData
{
private:
	PlayData() {}
	~PlayData() {}
	PlayData(const PlayData& other);
	static PlayData* inst;
public:
	static PlayData* getInstance() {
		if (inst == 0) inst = new PlayData();
		return inst;
	}

	int score;

	int patternHit[600];
	int patternNum;
};