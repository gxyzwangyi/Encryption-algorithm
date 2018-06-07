

#include "aes.h"

using namespace std;
vector<vector<unsigned char> > sBoxVector(16, vector<unsigned char>(16,0));
//vector<vector<unsigned char> > rConVector(11, vector<unsigned char>(4,0));



//
vector<vector<unsigned char> > storeArray(vector<unsigned char> byte, int tick, int maxTick){
	vector<vector<unsigned char> > roundArry(4, vector<unsigned char> ( 4, 0 ));

	for (int i =0; i<4; i++){
		for(int j = 0; j<4;j++){
			if (tick<maxTick){
				roundArry[i][j] = byte[tick];
				tick+=1;
			}
			else
				roundArry[i][j] = 0;
		}
	}
	/*
	for (int i =0; i<4; i++){
		for(int j = 0; j<4;j++){
			cout << "["<<roundArry[i][j]<<"]";
		}
		cout<<endl;
	}
	*/
	return roundArry;
}

vector<unsigned char> rconMe(char count){
	vector<unsigned char> rconResult(4,0);
	unsigned char temp = Rcon[count];
	rconResult[0] = temp;
	for(int i = 1;i<4;i++){
		rconResult[i] = 0;
	}
	return rconResult;
}
/**
*
* Takes the already alocated s-box and configure it to be used as a 2-d table.
*/

void fill_Box(){
	int count = 0;
	for (int i =0; i<16; i++){
		for(int j = 0; j<16;j++){
			sBoxVector[i][j] = sBoxArray[count];
			count++;
		}
	}
}
 
 


 
vector<unsigned char> subBytes(vector<unsigned char> subMe){
	for(int i =0;i<4;i++){
		//cout<<((subMe[i]>>4)&0xf)<<(subMe[i]&0xf)<<endl;
		subMe[i] = sBoxVector[((subMe[i]>>4)&0xf)][(subMe[i]&0xf)];
	}
	return subMe;
}
vector<unsigned char> rotate(vector<unsigned char> & inputWord,int numRotate){
	//cout<<"Before State. Iteration of "<<numRotate<<endl;
 	for (int j = 0; j<numRotate;j++){
		unsigned char temp = inputWord[0];
		for (int i = 1; i<4;i++)
			inputWord[i-1] = inputWord[i];
		inputWord[3] = temp;
	}
	//cout<<"After State."<<endl;
 	return inputWord;
}

unsigned char charMult(unsigned char a, unsigned char b){
	unsigned char returnValue;
		returnValue = (a<<1);
		if((a>>7)==1)
			returnValue^=0x1b;
		if(b==3)
			returnValue^=a;

	return returnValue;
}
	//for every Produce of 2, we have to shift left by 1 and xor with 0x1b if the left most bit is before shifted is 1
vector<unsigned char> shiftColumns(vector<unsigned char> input){
	vector<unsigned char> mixedColumns (4,0);
	unsigned char aMatrix[4][4] = {{0x02, 0x01, 0x01, 0x03}, 
									{0x03, 0x02, 0x01, 0x01}, 
									{0x01, 0x03, 0x02, 0x01},
									{0x01, 0x01, 0x03, 0x02}};
	
	mixedColumns[0] = charMult(input[0],2)^charMult(input[1],0x3)^input[2]^input[3];
	mixedColumns[1] = input[0]^charMult(input[1],2)^charMult(input[2],0x3)^input[3];
	mixedColumns[2] = input[0]^input[1]^charMult(input[2],2)^charMult(input[3],0x03);
	mixedColumns[3] = charMult(input[0],3)^input[1]^input[2]^charMult(input[3],2);

	return mixedColumns;
}
vector<unsigned char> g(vector<unsigned char> &test,int round){
 	test = rotate(test,1);
 	test = subBytes(test);
 	vector<unsigned char> newRecon = rconMe(round);
	for(int i = 0; i< 4;i++)
		test[i] = test[i] ^ newRecon[i];
 	return test;
}

vector<vector<unsigned char> > expandKey(vector<vector<unsigned char> > key,int keyLength,int round){
	vector<vector<unsigned char> > expandedKey(4*(round+1),vector<unsigned char> (4,0));
	vector<unsigned char> word(4,0);
	vector<unsigned char> temp(4,0);
	int nK;
	if(keyLength==192)
		nK = 6;
	else if (keyLength==256)
		nK = 8;
	else
		nK = 4;
	int currentRound = 0;
	//Initialize the extended with the regular key
	for(int i = 0; i<4;i++){
		for(int j = 0; j<4;j++){
			expandedKey[i][j] = key[i][j];
		}
		currentRound++;
	}
	//cout<<currentRound<<endl;
	//Start expanding key
	while(currentRound<4*(round+1)){
		temp[0] = expandedKey[currentRound-1][0];
		temp[1] = expandedKey[currentRound-1][1];
		temp[2] = expandedKey[currentRound-1][2];
		temp[3] = expandedKey[currentRound-1][3];
 		if(currentRound %nK == 0){
			temp = g(temp,currentRound);
 		}
		else if(nK>6&&currentRound%nK ==4)
			temp= subBytes(temp);
 		expandedKey[currentRound][0] = expandedKey[currentRound-nK][0]^temp[0];
		expandedKey[currentRound][1] = expandedKey[currentRound-nK][1]^temp[1];
		expandedKey[currentRound][2] = expandedKey[currentRound-nK][2]^temp[2];
		expandedKey[currentRound][3] = expandedKey[currentRound-nK][3]^temp[3];
		currentRound++;
 	}
 
	return expandedKey;
}
vector<vector<unsigned char> > encypt(vector<vector<unsigned char> > roundKey, vector<vector<unsigned char> > dataSet,int rounds){
	vector<vector<unsigned char> > encyptedData(4, vector<unsigned char>(4,0));
	vector<unsigned char> tempWord(4,0);
	//Initial encrypt
	for (int i = 0; i<4;i++){
		for(int j = 0; j<4;j++){
			encyptedData[i][j] = dataSet[i][j] ^ roundKey[i][j]; 
		}
	}	
	for (int r = 1;r < 11;r++){
		//Subbing bytes
		for(int col = 0;col <4;col++){
			tempWord[0] =  encyptedData[col][0];
			tempWord[1] =  encyptedData[col][1];
			tempWord[2] =  encyptedData[col][2];
			tempWord[3] =  encyptedData[col][3];
			tempWord =subBytes(tempWord);
			encyptedData[col][0] = tempWord[0];
			encyptedData[col][1] = tempWord[1];   
			encyptedData[col][2] = tempWord[2]; 
			encyptedData[col][3] = tempWord[3];  
		}
		//Rotate Rows
		for (int row =0;row<4;row++){
			tempWord[0] =  encyptedData[0][row];
			tempWord[1] =  encyptedData[1][row];
			tempWord[2] =  encyptedData[2][row];
			tempWord[3] =  encyptedData[3][row];
			tempWord = rotate(tempWord,row);
			encyptedData[0][row] = tempWord[0];
			encyptedData[1][row] = tempWord[1];   
			encyptedData[2][row] = tempWord[2]; 
			encyptedData[3][row] = tempWord[3]; 	
		}
		//Mix Columns
		if(r!=10)
		for(int col1 = 0; col1 <4;col1++){
			tempWord[0] =  encyptedData[col1][0];
			tempWord[1] =  encyptedData[col1][1];
			tempWord[2] =  encyptedData[col1][2];
			tempWord[3] =  encyptedData[col1][3];
			tempWord = shiftColumns(tempWord);
			encyptedData[col1][0] = tempWord[0];
			encyptedData[col1][1] = tempWord[1];   
			encyptedData[col1][2] = tempWord[2]; 
			encyptedData[col1][3] = tempWord[3];  
		}
		//add round key
		//round 0 uses key 0-3, round 1 uses 4-7, round 2 uses 8-11
		int currentRoundKey = 4*r;
			for(int i = 0; i <4;i++){
			encyptedData[i][0] = encyptedData[i][0] ^ roundKey[currentRoundKey+i][0]; 
			encyptedData[i][1] = encyptedData[i][1] ^ roundKey[currentRoundKey+i][1]; 
			encyptedData[i][2] = encyptedData[i][2] ^ roundKey[currentRoundKey+i][2]; 
			encyptedData[i][3] = encyptedData[i][3] ^ roundKey[currentRoundKey+i][3]; 
		}
	}
	
return encyptedData;
}

int main(){
	int choice = 0,keyLength = 128,numRounds = 10, countBytes =0, counter = 0, numCoversion = 0;
	string defaultKey = "wangyi",stringInput ="wangyi";
	bool defString = false;
 	unsigned char testKey[16] ={0x53,0x4f,0x4d, 0x45, 0x20, 0x31, 0x32, 0x38, 0x20, 0x42, 0x49, 0x54 ,0x20, 0x4b,0x45,0x59}; 
	unsigned char testString[16] = {0x41, 0x54, 0x54, 0x41, 0x43, 0x4b, 0x20, 0x41, 0x54, 0x20, 0x44, 0x41, 0x57, 0x4e, 0x21, 0x00};
	vector<unsigned char> key(16);
	vector<vector<unsigned char> > extendedKey(44);
	fill_Box();
	srand((unsigned) time(NULL));


	for (int i =0;i<16;i++){
		key[i]=defaultKey[i];
		 }
	 
	extendedKey = expandKey(storeArray(key,0,16),keyLength,numRounds);


	countBytes = stringInput.length();
	countBytes=16;
	
	vector<unsigned char> plainBytes(countBytes,0);
	for(int i =0;i<countBytes;i++)
	plainBytes[i] = testString[i];
	if (countBytes%16 != 0)
		numCoversion = (countBytes/16)+1;
	else
		numCoversion = (countBytes/16);
	vector<vector<vector<unsigned char> > > vectorList(numCoversion, vector<vector<unsigned char> >(4, vector<unsigned char>(4, 0)));
	for (int i=0;i<numCoversion;i++){
		vectorList[i]=storeArray(plainBytes,16*i,countBytes);
	}
	vector<vector<unsigned char> > encryptedBox = encypt(extendedKey,vectorList[0],numRounds);
	string *outputArray;
	outputArray = new string[32];
	int stringCount =0;
	int n;
	char buffer [32];
	string buffer2;
	
 
	for(int i =0; i<4;i++){
		for (int j =0; j<4; j++){
			sprintf (buffer, "%02X",(unsigned int)encryptedBox[i][j]);
			printf ("%s",buffer);
		}

	}


 
	return 0;
}
