#include "DecryptHelper.h"

DecryptHelper::DecryptHelper() {
	ciphertext.clear();
	targetCiphertext.clear();
	ciphertextInt.clear();
	targetCiphertextInt.clear();
	key.clear();
	for (int i = 0; i < MAX_KEY_LENGTH; i++) {
		key.push_back(STAR);
	}
}

DecryptHelper::~DecryptHelper() {

}

void DecryptHelper::addCiphertext(const string& text) {
	this->ciphertext.push_back(text);
}

void DecryptHelper::addTargetCiphertext(const string& text) {
	this->targetCiphertext.push_back(text);
}

void DecryptHelper::decrypt() {
	convertString2IntArray();
	decryptKey();
}

int DecryptHelper::hexChar2DecInt(const char& c) {
	if (c >= '0' && c <= '9') {
		return (c - '0');
	} else if (c >= 'a' && c <= 'f') {
		return (c - 'a' + 10);
	} else if (c >= 'A' && c <= 'F') {
		return (c - 'A' + 10);
	} else {
		printf("Input error -> %c\n", c);
		return 0;
	}
	return 0;
}

void DecryptHelper::convertString2IntArray() {
	// Convert ciphertext
	for (int i = 0; i < ciphertext.size(); i++) {
		string s = ciphertext[i];
		vector<int> vInt;
		for (int j = 0; j < s.size(); j += 2) {
			int firstChar = hexChar2DecInt(s[j]);
			int secondChar = hexChar2DecInt(s[j + 1]);
			vInt.push_back(firstChar * 16 + secondChar);
		}
		ciphertextInt.push_back(vInt);
	}
	// Convert targetCiphertext
	for (int i = 0; i < targetCiphertext.size(); i++) {
		string s = targetCiphertext[i];
		vector<int> vInt;
		for (int j = 0; j < s.size(); j += 2) {
			int firstChar = hexChar2DecInt(s[j]);
			int secondChar = hexChar2DecInt(s[j + 1]);
			vInt.push_back(firstChar * 16 + secondChar);
		}
		targetCiphertextInt.push_back(vInt);
	}
}

string DecryptHelper::getKey() {
	string returnKey = "";
	for (int i = 0; i < key.size(); i++) {
		returnKey += (char)key[i];
	}
	return returnKey;
}

void DecryptHelper::decryptKey() {
	for (int i = 0; i < MAX_KEY_LENGTH; i++) {
		decryptKeyAtPosition(i);
	}
}

string DecryptHelper::decryptTarget(int index) {
	string returnTarget = "";
	for (int i = 0; i < targetCiphertextInt[index].size(); i++) {
		if (key[i] != STAR) {
			returnTarget += (char)(targetCiphertextInt[index][i] ^ key[i]);
		} else {
			returnTarget += (char)(STAR);
		}
	}
	return returnTarget;
}

void DecryptHelper::printKey() {
	int enter = 0;
	for (int i = 0; i < key.size(); i++) {
		if (key[i] == STAR) {
			printf("*** ");
		} else {
			printf("%3d ", key[i]);
		}
		if (++enter == 20) {
			enter = 0;
			printf("\n");
		}
	}
	printf("\n");
}

void DecryptHelper::decryptKeyAtPosition(int position) {
	int maxCiphertext = ciphertextInt.size();
	int *spaceRatio = new int[maxCiphertext];
	int maxSpaceRatio = 0, maxSpaceRatioIndex = -1;
	// Statistics the space ratio for every ciphertext
	for (int i = 0; i < maxCiphertext; i++) {
		spaceRatio[i] = 0;
		if (position < ciphertextInt[i].size()) {
			int firstChar = ciphertextInt[i][position];
			for (int j = 0; j < ciphertextInt.size(); j++) {
				if (position < ciphertextInt[j].size() && j != i) {
					int secondChar = ciphertextInt[j][position];
					if (isalpha(firstChar ^ secondChar)) {
						spaceRatio[i]++;
						if (spaceRatio[i] >= 2 && spaceRatio[i] > maxSpaceRatio) {
							maxSpaceRatio = spaceRatio[i];
							maxSpaceRatioIndex = i;
						}
					}
				}
			}
		}
	}
	// Try to update the key
	while (maxSpaceRatioIndex != -1) {
		// Test if it is a real SPACE char
		int tryKey = ciphertextInt[maxSpaceRatioIndex][position] ^ SPACE;
		if (testKeyAtPosition(tryKey, position)) {
			key[position] = tryKey;
			break;
		}
		// Find another maxSpaceRatio key
		spaceRatio[maxSpaceRatioIndex] = 0;
		maxSpaceRatio = 0, maxSpaceRatioIndex = -1;
		for (int i = 0; i < maxCiphertext; i++) {
			if (spaceRatio[i] >= 2 && spaceRatio[i] > maxSpaceRatio) {
				maxSpaceRatio = spaceRatio[i];
				maxSpaceRatioIndex = i;
			}
		}
	}
	
	delete [] spaceRatio; 
}

bool DecryptHelper::testKeyAtPosition(int tryKey, int position) {
	int textCount = 0, alphaCount = 0;
	for (int i = 0; i < ciphertextInt.size(); i++) {
		if (position < ciphertextInt[i].size()) {
			textCount++;
			if (isalpha(ciphertextInt[i][position] ^ tryKey)) {
				alphaCount++;
			}
		}
	}
	if (alphaCount * 2 > textCount) {
		return true;
	}
	return false;
}
