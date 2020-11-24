#pragma once
#include "sign.h"


typedef struct {
	int length;
	char* seq;
}Sequence;


Sequence* createSequence(char* fileName);
Sign* createSigns(const Sequence* SEQ1, const Sequence* SEQ2, int n);
void printSigns(Sign* signs, int size);
int checkCloserAttributes(char s1, char s2);
int	checkCommonAttributes(char s1, char s2);
int getCount(Sign* signs, int size);
int evaluateDifference(Sequence* SEQ1, Sequence* SEQ2, int n);
int* createDiffArray(Sequence* SEQ1, Sequence* SEQ2, int* diffLength);
int compareDiffValue(void* n1, void* n2);