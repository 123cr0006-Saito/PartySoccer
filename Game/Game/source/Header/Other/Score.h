#pragma once
#include <map>
#include <string>
class Score
{
	public:
	Score();
	~Score();
	static Score* GetInstance() { return _instance; }
	void AddScore(std::string name,int score){_score[name] +=score; };
	int GetScore(std::string name){return _score[name]; };
	std::string GetWinner() { return _score["Goal_1"] > _score["Goal_2"] ? "Goal_1" : "Goal_2";};
protected:
	static Score* _instance;
	std::map<std::string,int> _score;
};