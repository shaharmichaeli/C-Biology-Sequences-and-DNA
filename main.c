#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "seq.h"

#define CONST_NUMBER_5 5
#define PRINT_SEQUENCES

#ifdef PRINT_SEQUENCES
#define PRINT_SEQ(str,n) printf(#str " = \t%s\n",str);
#define PRINT_SIGNS(signs,size) printSigns(signs,size);
#define PRINT_VALUE(x) printf("\n\nDifference Value : %d\n",x);
#endif

//	Please enter files name "Seq1.txt" "Seq2.txt" in arg to main.

int main(int argc, char* argv[]) {
	if (argc != 3) {
		return;
	}

	char* fileName1 = argv[1];
	char* fileName2 = argv[2];
	Sequence* SEQ1 = createSequence("Seq1.txt");
	Sequence* SEQ2 = createSequence("Seq2.txt");
	int DiffValue = evaluateDifference(SEQ1, SEQ2, CONST_NUMBER_5);
	int diffLength = 0;

	int* diffArray = createDiffArray(SEQ1, SEQ2, &diffLength);
	qsort(diffArray, diffLength, sizeof(int), compareDiffValue);



#ifdef  PRINT_SEQUENCES
	PRINT_SEQ(SEQ1->seq);
	PRINT_SEQ(SEQ2->seq);
	printSigns(createSigns(SEQ1, SEQ2, CONST_NUMBER_5), SEQ2->length);
	PRINT_VALUE(DiffValue);

	printf("Difference Value Arrays:\n");
	for (int i = 0; i < diffLength; i++)
	{
		printf("%d ", diffArray[i]);
	}
	printf("\n");
#endif 




	free(diffArray);
	free(SEQ1);
	free(SEQ2);
	printf("Bye!\n\n");
}