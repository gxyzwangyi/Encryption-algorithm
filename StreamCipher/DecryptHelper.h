#ifndef DECRYPTHELPER_H_
#define DECRYPTHELPER_H_

#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
using namespace std;

#define MAX_KEY_LENGTH 300
#define SPACE 32
#define STAR 42

class DecryptHelper {
private:
	vector<string> ciphertext;
	vector<string> targetCiphertext;
	vector<int> key;
	vector< vector<int> > ciphertextInt;
	vector< vector<int> > targetCiphertextInt;
public:
	DecryptHelper();
	~DecryptHelper();
	void addCiphertext(const string& text);
	void addTargetCiphertext(const string& text);
	void decrypt();
	string getKey();
	void printKey();
	string decryptTarget(int index);
private:
	int hexChar2DecInt(const char& c);
	void convertString2IntArray();
	void decryptKey();
	void decryptKeyAtPosition(int position);
	bool testKeyAtPosition(int tryKey, int position);
};

#endif