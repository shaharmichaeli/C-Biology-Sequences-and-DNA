#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "seq.h"

#define SIZE 256
#define STAR 0x0
#define DOT 0x1
#define TWODOT 0x2
#define SPACE 0x3
#define CLOSER_SIZE 9 // CLOSER GROUPS SIZE
#define COMMON_SIZE 11 // COMMON GROUPS SIZE
#define CLMAXROWSIZE 5
#define COMAXROWSIZE 7 
#define INGROUP_NUMBER 2

Sequence* createSequence(char* fileName) {
	if (fileName == NULL) {
		return NULL;
	}
	FILE* fp = fopen(fileName, "r");
	if (!fp) {
		return NULL;
	}

	Sequence* SEQ = (Sequence*)malloc(sizeof(Sequence));
	if (!SEQ) {
		return NULL;
	}

	char temp[100];
	fgets(temp, SIZE, fp);

	SEQ->length = (int)strlen(temp);
	SEQ->seq = (char*)malloc(sizeof(char)*SEQ->length);
	if (!SEQ->seq) {
		fclose(fp);
		return NULL;
	}
	strcpy(SEQ->seq, temp);
	fclose(fp);
	return SEQ;
}

Sign* createSigns(const Sequence* SEQ1, const Sequence* SEQ2, int n) {
	//	star - same char
	//	space - diff chars and not in group
	//	2dots - closer group
	//	dot - common group

	if (SEQ1 == NULL || SEQ2 == NULL) {
		return NULL;
	}
	char charSEQ1, charSEQ2;

	Sign* signs = (Sign*)malloc(sizeof(Sign) * SEQ2->length);
	if (!signs) {
		return NULL;
	}

	for (int i = 0; i < SEQ2->length; i++)
	{
		charSEQ1 = SEQ1->seq[n + i];
		charSEQ2 = SEQ2->seq[i];
		if (charSEQ1 == '-' || charSEQ2 == '-') {
			signs[i].sign = SPACE;
		}
		if (charSEQ1 == charSEQ2) {
			signs[i].sign = STAR;
		}
		else if (checkCloserAttributes(charSEQ1, charSEQ2) == INGROUP_NUMBER) {
			signs[i].sign = TWODOT;
		}
		else if (checkCommonAttributes(charSEQ1, charSEQ2) == INGROUP_NUMBER) {
			signs[i].sign = DOT;
		}
		else {
			signs[i].sign = SPACE;
		}
	}
	return signs;
}

void printSigns(Sign* signs, int size) {
	printf("Signs:\t\t [");
	for (int i = 0; i < size; i++)
	{
		if (signs[i].sign == STAR) {
			printf("*");
		}
		else if (signs[i].sign == DOT) {
			printf(".");
		}
		else if (signs[i].sign == TWODOT) {
			printf(":");
		}
		else {
			printf(" ");
		}
	}
	printf("]\n");
}

int checkCloserAttributes(char s1, char s2) {
	// Splitted to array of chars to check if the chars from the sequence are in the same group.

	char closerGroup[CLOSER_SIZE][CLMAXROWSIZE] = {
		{'S','T','A','\0'},	{'N','E','Q','K','\0'},	{'N','D','E','Q','\0'},
		{'N','H','Q','K','\0'},	{'Q','H','R','K','\0'},	{'M','I','L','V','\0'},
	{'M','I','L','F','\0'},	{'H','Y','\0'},	{'F','Y','W','\0'} };
	int count = 0;

	for (int i = 0; i < CLOSER_SIZE; i++) {
		for (int j = 0; j < strlen(closerGroup[i]); j++) {
			if (s1 == closerGroup[i][j]) {
				count++;
			}
			if (s2 == closerGroup[i][j]) {
				count++;
			}
			if (count == INGROUP_NUMBER) {
				return INGROUP_NUMBER;
			}
		}
		count = 0;
	}
	return 0;

}
int	checkCommonAttributes(char s1, char s2) {
	// Splitted to array of chars to check if the chars from the sequence are in the same group.

	char commonGroup[COMMON_SIZE][COMAXROWSIZE] = {
		{'C','S','A','\0'},	{'A','T','V','\0'},	{'S','A','G','\0'},
		{'S','T','N','K','\0'},	{'S','T','P','A','\0'},	{'S','G','N','D','\0'},
		{'S','N','D','E','Q','K','\0'},	{'N','D','E','Q','H','K','\0'},	{'N','E','Q','H','R','K','\0'},
		{'F','V','L','I','M','\0'},	{'H','F','Y','\0'} };

	int count = 0;
	for (int i = 0; i < COMMON_SIZE; i++) {
		for (int j = 0; j < strlen(commonGroup[i]); j++) {
			if (s1 == commonGroup[i][j]) {
				count++;
			}
			if (s2 == commonGroup[i][j]) {
				count++;
			}
			if (count == INGROUP_NUMBER) {
				return INGROUP_NUMBER;
			}

		}
		count = 0;
	}
	return 0;
}

int getCount(Sign* signs, int size) {
	int countStars = 0;
	int countColons = 0;
	for (int i = 0; i < size; i++) {
		if (signs[i].sign == STAR) {
			countStars++;
		}
		else if (signs[i].sign == TWODOT) {
			countColons++;
		}
	}

	return countStars - countColons;
}


int evaluateDifference(Sequence* SEQ1, Sequence* SEQ2, int n) {
	Sign* signs = createSigns(SEQ1, SEQ2, n);
	int RES = getCount(signs, SEQ2->length);
	free(signs);
	return RES;

}

int* createDiffArray(Sequence* SEQ1, Sequence* SEQ2, int* diffLength) {
	*diffLength = SEQ1->length - SEQ2->length;
	int* diffArray = (int*)malloc(sizeof(int)*(*diffLength));
	if (!diffArray) {
		return NULL;
	}

	for (int i = 0; i < *diffLength; i++)
	{
		diffArray[i] = evaluateDifference(SEQ1, SEQ2, i);
	}
	return diffArray;
}

int compareDiffValue(void* n1, void* n2) {
	int* s1 = (int*)n1;
	int* s2 = (int*)n2;
	return *s1 - *s2;
}