#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <string>
#include "DecryptHelper.h"
#include "SpellCorrector.h"
using namespace std;

#define MAX_NUM_TEXT 10

DecryptHelper helper;

void readTextFromFile(const char* folderDir);
void correctSentence(string s);

int main() {
	setbuf(stdout, NULL); // Fix input and output order problem

	string ciphertextsDir = "ciphertexts/";
	readTextFromFile(ciphertextsDir.c_str());
	helper.decrypt();
	printf("\ndecrypt key = \n");
	// printf("%s\n", helper.getKey().c_str());
	helper.printKey();
	int studentId;
	printf("Enter your student id: ");
	scanf("%d", &studentId);
	printf("\nDecrypt result is \n");
	string resultStr = helper.decryptTarget(studentId % 10);
	printf("%s\n", resultStr.c_str());
	printf("\nAfter correction is \n");
	correctSentence(resultStr);
	return 0;
}

// 从文件中读取样本密文和待解密密文
void readTextFromFile(const char* folderDir) {
	string ciphertext, targetCiphertext;
	fstream fin;
	char fileDir[50];
	int formatStringResult;
	for (int i = 0; i < MAX_NUM_TEXT; i++) {
		// 读入样本密文
		formatStringResult = sprintf(fileDir, "%sciphertext%d.txt", folderDir, i);
		if (formatStringResult >= 0) {
			fin.open(fileDir, fstream::in);
			fin >> ciphertext;
			helper.addCiphertext(ciphertext);
			fin.close();
		} else {
			printf("read ciphertext%d.txt failed.\n", i);
		}
		// 读入待解密密文
		formatStringResult = sprintf(fileDir, "%stargetCiphertext%d.txt", folderDir, i);
		if (formatStringResult >= 0) {
			fin.open(fileDir, fstream::in);
			fin >> targetCiphertext;
			helper.addTargetCiphertext(targetCiphertext);
			fin.close();
		} else {
			printf("read targetCiphertext%d.txt failed.\n", i);
		}
	}
}

// 格式化句子并输出显示
void correctSentence(string s) {
	SpellCorrector corrector;
	bool hasPoint = false;
	char point;
	if (s[s.length() - 1] == '.' || s[s.length() - 1] == '!') {
		hasPoint = true;
		point = s[s.length() - 1];
		s = s.substr(0, s.length() - 1);
	}
	if (isalpha(s[0])) {
		s[0] = tolower(s[0]);
	}
	s = corrector.correct(s);
	if (hasPoint) {
		printf("%c%s%c\n", toupper(s[0]), s.substr(1, s.length() - 2).c_str(), point);
	} else {
		printf("%c%s\n", toupper(s[0]), s.substr(1, s.length() - 2).c_str());
	}
}
