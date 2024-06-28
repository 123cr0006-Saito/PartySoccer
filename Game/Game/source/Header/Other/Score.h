#pragma once
#include <map>
#include <string>
class Score
{
public:
	Score();
	~Score();
	static Score* GetInstance() { return _instance; }
	bool GetIsDraw() {return _score["Goal_1"] == _score["Goal_2"];};
	void AddScore(const std::string& name,const int score){_score[name] +=score; };
	int GetScore(const std::string& name) {return _score[name]; };
	std::string GetWinner() { return GetIsDraw() ? "Draw" : _score["Goal_1"] > _score["Goal_2"] ? "Team_1" : "Team_2"; };
protected:
	static Score* _instance;
	std::map<std::string,int> _score;
};