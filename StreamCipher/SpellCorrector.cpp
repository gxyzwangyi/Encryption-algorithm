#include "SpellCorrector.h"

SpellCorrector::SpellCorrector() {
	dic.clear();
	trainModel();
}

SpellCorrector::~SpellCorrector() {

}

string SpellCorrector::correct(string s) {
	stringstream ss;
	string word, result;
	ss << s;
	while (ss >> word) {
		if (dic.count(word) > 0) {
			result += (word + " ");
			continue;
		}
		c.count = -1;
		enumm(word, 1);
		if (dic.count(c.correctWord) != 0) {
			result += (c.correctWord + " ");
		} else {
			result += (word + " ");
		}
	}
	return result;
}

void SpellCorrector::trainModel() {
	ifstream fin("model/small.txt");
	string s;
	while (fin >> s) {
		if (dic.count(s) == 0) {
			dic[s] = 1;
		} else {
			dic[s] = dic.at(s) + 1;
		}
	}
	fin.close();
}

bool SpellCorrector::enumm(string s, int time) {
	if (time > MAX_ENUM_TIME) {
		return false;
	}
	char alphabet[27] = "abcdefghijklmnopqrstuvwxyz";

	// delete
	/*for (int i = 0; i < s.length(); i++) {
		string temp = s.substr(0, i) + s.substr(i + 1);
		if (judge(temp)) {
			return true;
		} else if (enumm(temp, time + 1)) {
			return true;
		}
	}*/

	// transportation
	/*for (int i = 0; i < s.length() - 1; i++) {
		string temp(s);
		swap(temp[i], temp[i + 1]);
		if (judge(temp)) {
			return true;
		} else if (enumm(temp, time + 1)) {
			return true;
		}
	}*/

	// alterneration
	for (int i = 0; i < s.length(); i++) {
		for (int j = 0; j < 26; j++) {
			string temp(s);
			temp[i] = alphabet[j];
			if (judge(temp)) {
				return true;
			} else if (enumm(temp, time + 1)) {
				return true;
			}
		}
	}

	// insertion
	/*for (int i = 0; i <= s.length(); i++) {
		for (int j = 0; j < 26; j++) {
			string temp = s.substr(0, i) + alphabet[j] + s.substr(i);
			if (judge(temp)) {
				return true;
			} else if (enumm(temp, time + 1)) {
				return true;
			}
		}
	}*/
	return false;
}

bool SpellCorrector::judge(string s) {
	int num = -1;
	if (dic.count(s) == 0) {
		num = -1;
	} else {
		num = dic.at(s);
	}
	if (num > c.count) {
		c.count = num;
		c.correctWord = s;
		return true;
	}
	return false;
}
