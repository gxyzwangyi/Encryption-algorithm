#include "hmac.h"
#include<cstring>
#include <stddef.h>
#include <iostream>


// stuct
typedef struct _MD5CTX {
	unsigned int	aState[4];		// state
	unsigned int	aCount[2];		// origin lenth(bit)
	unsigned char 	aBuffer[64];	// origin data
} MD5CTX;



void MD5_Init( MD5CTX* pstruContext )
{
	const unsigned int *MDOriginState;

	MDOriginState = MD5_ARGUMENTS.p;
	pstruContext->aState[0] = MDOriginState[0];
	pstruContext->aState[1] = MDOriginState[1];
	pstruContext->aState[2] = MDOriginState[2];
	pstruContext->aState[3] = MDOriginState[3];
	pstruContext->aCount[0] = pstruContext->aCount[1] = 0;
}

void MD5_Transform( unsigned int* pState, unsigned int* px )
{
	const unsigned int (*MDOffTable)[16];
	unsigned int a,b,c,d;

	MDOffTable = MD5_ARGUMENTS.q;
	a = pState[0], b = pState[1], c = pState[2], d = pState[3];

	// 1
	FF(a, b, c, d, px[ 0], MDShiftTable[0][0], MDOffTable[0][ 0]);
	FF(d, a, b, c, px[ 1], MDShiftTable[0][1], MDOffTable[0][ 1]);
	FF(c, d, a, b, px[ 2], MDShiftTable[0][2], MDOffTable[0][ 2]);
	FF(b, c, d, a, px[ 3], MDShiftTable[0][3], MDOffTable[0][ 3]);
	FF(a, b, c, d, px[ 4], MDShiftTable[0][0], MDOffTable[0][ 4]);
	FF(d, a, b, c, px[ 5], MDShiftTable[0][1], MDOffTable[0][ 5]);
	FF(c, d, a, b, px[ 6], MDShiftTable[0][2], MDOffTable[0][ 6]);
	FF(b, c, d, a, px[ 7], MDShiftTable[0][3], MDOffTable[0][ 7]);
	FF(a, b, c, d, px[ 8], MDShiftTable[0][0], MDOffTable[0][ 8]);
	FF(d, a, b, c, px[ 9], MDShiftTable[0][1], MDOffTable[0][ 9]);
	FF(c, d, a, b, px[10], MDShiftTable[0][2], MDOffTable[0][10]);
	FF(b, c, d, a, px[11], MDShiftTable[0][3], MDOffTable[0][11]);
	FF(a, b, c, d, px[12], MDShiftTable[0][0], MDOffTable[0][12]);
	FF(d, a, b, c, px[13], MDShiftTable[0][1], MDOffTable[0][13]);
	FF(c, d, a, b, px[14], MDShiftTable[0][2], MDOffTable[0][14]);
	FF(b, c, d, a, px[15], MDShiftTable[0][3], MDOffTable[0][15]);

	// 2
	GG(a, b, c, d, px[ 1], MDShiftTable[1][0], MDOffTable[1][ 0]);
	GG(d, a, b, c, px[ 6], MDShiftTable[1][1], MDOffTable[1][ 1]);
	GG(c, d, a, b, px[11], MDShiftTable[1][2], MDOffTable[1][ 2]);
	GG(b, c, d, a, px[ 0], MDShiftTable[1][3], MDOffTable[1][ 3]);
	GG(a, b, c, d, px[ 5], MDShiftTable[1][0], MDOffTable[1][ 4]);
	GG(d, a, b, c, px[10], MDShiftTable[1][1], MDOffTable[1][ 5]);
	GG(c, d, a, b, px[15], MDShiftTable[1][2], MDOffTable[1][ 6]);
	GG(b, c, d, a, px[ 4], MDShiftTable[1][3], MDOffTable[1][ 7]);
	GG(a, b, c, d, px[ 9], MDShiftTable[1][0], MDOffTable[1][ 8]);
	GG(d, a, b, c, px[14], MDShiftTable[1][1], MDOffTable[1][ 9]);
	GG(c, d, a, b, px[ 3], MDShiftTable[1][2], MDOffTable[1][10]);
	GG(b, c, d, a, px[ 8], MDShiftTable[1][3], MDOffTable[1][11]);
	GG(a, b, c, d, px[13], MDShiftTable[1][0], MDOffTable[1][12]);
	GG(d, a, b, c, px[ 2], MDShiftTable[1][1], MDOffTable[1][13]);
	GG(c, d, a, b, px[ 7], MDShiftTable[1][2], MDOffTable[1][14]);
	GG(b, c, d, a, px[12], MDShiftTable[1][3], MDOffTable[1][15]);
                        
	// 3    
	HH(a, b, c, d, px[ 5], MDShiftTable[2][0], MDOffTable[2][ 0]);
	HH(d, a, b, c, px[ 8], MDShiftTable[2][1], MDOffTable[2][ 1]);
	HH(c, d, a, b, px[11], MDShiftTable[2][2], MDOffTable[2][ 2]);
	HH(b, c, d, a, px[14], MDShiftTable[2][3], MDOffTable[2][ 3]);
	HH(a, b, c, d, px[ 1], MDShiftTable[2][0], MDOffTable[2][ 4]);
	HH(d, a, b, c, px[ 4], MDShiftTable[2][1], MDOffTable[2][ 5]);
	HH(c, d, a, b, px[ 7], MDShiftTable[2][2], MDOffTable[2][ 6]);
	HH(b, c, d, a, px[10], MDShiftTable[2][3], MDOffTable[2][ 7]);
	HH(a, b, c, d, px[13], MDShiftTable[2][0], MDOffTable[2][ 8]);
	HH(d, a, b, c, px[ 0], MDShiftTable[2][1], MDOffTable[2][ 9]);
	HH(c, d, a, b, px[ 3], MDShiftTable[2][2], MDOffTable[2][10]);
	HH(b, c, d, a, px[ 6], MDShiftTable[2][3], MDOffTable[2][11]);
	HH(a, b, c, d, px[ 9], MDShiftTable[2][0], MDOffTable[2][12]);
	HH(d, a, b, c, px[12], MDShiftTable[2][1], MDOffTable[2][13]);
	HH(c, d, a, b, px[15], MDShiftTable[2][2], MDOffTable[2][14]);
	HH(b, c, d, a, px[ 2], MDShiftTable[2][3], MDOffTable[2][15]);
                        
	// 4    
	II(a, b, c, d, px[ 0], MDShiftTable[3][0], MDOffTable[3][ 0]);
	II(d, a, b, c, px[ 7], MDShiftTable[3][1], MDOffTable[3][ 1]);
	II(c, d, a, b, px[14], MDShiftTable[3][2], MDOffTable[3][ 2]);
	II(b, c, d, a, px[ 5], MDShiftTable[3][3], MDOffTable[3][ 3]);
	II(a, b, c, d, px[12], MDShiftTable[3][0], MDOffTable[3][ 4]);
	II(d, a, b, c, px[ 3], MDShiftTable[3][1], MDOffTable[3][ 5]);
	II(c, d, a, b, px[10], MDShiftTable[3][2], MDOffTable[3][ 6]);
	II(b, c, d, a, px[ 1], MDShiftTable[3][3], MDOffTable[3][ 7]);
	II(a, b, c, d, px[ 8], MDShiftTable[3][0], MDOffTable[3][ 8]);
	II(d, a, b, c, px[15], MDShiftTable[3][1], MDOffTable[3][ 9]);
	II(c, d, a, b, px[ 6], MDShiftTable[3][2], MDOffTable[3][10]);
	II(b, c, d, a, px[13], MDShiftTable[3][3], MDOffTable[3][11]);
	II(a, b, c, d, px[ 4], MDShiftTable[3][0], MDOffTable[3][12]);
	II(d, a, b, c, px[11], MDShiftTable[3][1], MDOffTable[3][13]);
	II(c, d, a, b, px[ 2], MDShiftTable[3][2], MDOffTable[3][14]);
	II(b, c, d, a, px[ 9], MDShiftTable[3][3], MDOffTable[3][15]);	

	pState[0] += a;
	pState[1] += b;
	pState[2] += c;
	pState[3] += d;
}

void MD5_Update( MD5CTX* pstruContext, const unsigned char* pInput, unsigned int dwInputLen )
{
	unsigned int i, dwIndex, dwPartLen, dwBitsNum;

	dwIndex = (pstruContext->aCount[0] >> 3) & 0x3F;

	dwBitsNum = dwInputLen << 3;
	pstruContext->aCount[0] += dwBitsNum;
	
	if(pstruContext->aCount[0] < dwBitsNum)
	{
		pstruContext->aCount[1]++;
	}

	pstruContext->aCount[1] += dwInputLen >> 29;

	dwPartLen = 64 - dwIndex;
	if(dwInputLen >= dwPartLen)
	{
		memcpy( pstruContext->aBuffer+dwIndex, pInput, dwPartLen );
		MD5_Transform( pstruContext->aState, (unsigned int*)pstruContext->aBuffer );

		for(i = dwPartLen; i + 63 < dwInputLen; i += 64 )
		{
			MD5_Transform( pstruContext->aState, (unsigned int*)(pInput + i) );
		}

		dwIndex = 0;
	}
	else
	{
		i = 0;
	}

	memcpy( pstruContext->aBuffer + dwIndex, pInput + i, dwInputLen - i );
}

void MD5_Final( MD5CTX* pstruContext )
{
	unsigned int dwIndex, dwPadLen;
	unsigned char pBits[8];
	
	memcpy( pBits, pstruContext->aCount, 8 );
	

	dwIndex = (pstruContext->aCount[0] >> 3) & 0x3F;

	// K*64+56
	dwPadLen = (dwIndex < 56) ? (56-dwIndex) : (120-dwIndex);
	MD5_Update( pstruContext, MDPadding, dwPadLen );
	MD5_Update( pstruContext, pBits, 8 );
}

int MD5_Hash( const unsigned char* inputBuffer, int inputCount, unsigned char* outputBuffer )
{
	MD5CTX struContext;
	
	if( inputBuffer == NULL )
	{
		inputCount = 0;
	}

	MD5_Init( &struContext );		
	MD5_Update( &struContext, inputBuffer, inputCount );	
	MD5_Final( &struContext );	

	if( outputBuffer != NULL )
	{
		memcpy( outputBuffer, struContext.aState, 16 );
	}	

	return 16;
}

int HMAC_MD5_Hash( const unsigned char * inputBuffer, int inputCount, const unsigned char * userKey, int UserKeyLen, unsigned char * outputBuffer )
{	
	unsigned char  hmacKey[64] = {0};
	unsigned char  k_ipad[64];
	unsigned char  k_opad[64];
	MD5CTX struContext;

	if( inputBuffer == NULL )
	{
		inputCount = 0;
	}

	if( userKey == NULL )
	{
		UserKeyLen = 0;
	}

	// 保证密钥长度不超过64字节
	if( UserKeyLen > 64 )
	{
		 MD5_Hash( userKey, UserKeyLen, hmacKey );
	}
	else
	{
		memcpy( hmacKey, userKey, UserKeyLen );
	}

	for( int i = 0; i < 64; i++ )
	{
		k_ipad[i] = hmacKey[i] ^ 0x36;
		k_opad[i] = hmacKey[i] ^ 0x5C;
	}

	
	MD5_Init( &struContext );		
	MD5_Update( &struContext, k_ipad, 64 );	
	MD5_Update( &struContext, inputBuffer, inputCount );
	MD5_Final( &struContext );	
	memcpy( hmacKey, struContext.aState, 16 );

 	MD5_Init( &struContext );		
	MD5_Update( &struContext, k_opad, 64 );	
	MD5_Update( &struContext, hmacKey, 16 );	
	MD5_Final( &struContext );	

	if( outputBuffer != NULL )
	{
		memcpy( outputBuffer, struContext.aState, 16 );
	}	

	return 16;
}


int main(){
	unsigned char * output;
	const unsigned char * a = reinterpret_cast<const unsigned char *>( "wangyi" );
	const unsigned char * b = reinterpret_cast<const unsigned char *>( "wangyi" );
	// const unsigned char * a= "12";
	// const unsigned char * b ="45";
	HMAC_MD5_Hash(a,2,b,2,output);
	std::cout<<output;

}