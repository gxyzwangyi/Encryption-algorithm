#ifndef SPELLCORRECTOR_H_
#define SPELLCORRECTOR_H_

#include <fstream>
#include <map>
#include <string>
#include <sstream>
using namespace std;

#define MAX_ENUM_TIME 2

struct correction {
	string correctWord;
	int count;
};

class SpellCorrector {
private:
	map<string, int> dic;
	correction c;
public:
	SpellCorrector();
	~SpellCorrector();
	string correct(string s);
private:
	void trainModel();
	bool enumm(string s, int time);
	bool judge(string s);
};

#endif
