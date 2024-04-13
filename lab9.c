#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

// RecordType
struct RecordType
{
	int		id;
	char	name;
	int		order; 
};
 
// Fill out this structure
struct HashType
{
	struct RecordType *rPtr;
	struct HashType *next;
}; 

// Compute the hash function
int hash(int x)
{
	int index = 30 % x;
	return index;
	
}

// parses input file to an integer array
int parseData(char* inputFileName, struct RecordType** ppData)
{
	FILE* inFile = fopen(inputFileName, "r");
	int dataSz = 0;
	int i, n;
	char c;
	struct RecordType *pRecord;
	*ppData = NULL;

	if (inFile)
	{
		fscanf(inFile, "%d\n", &dataSz);
		*ppData = (struct RecordType*) malloc(sizeof(struct RecordType) * dataSz);
		// Implement parse data block
		if (*ppData == NULL)
		{
			printf("Cannot allocate memory\n");
			exit(-1);
		}
		for (i = 0; i < dataSz; ++i)
		{
			pRecord = *ppData + i;
			fscanf(inFile, "%d ", &n);
			pRecord->id = n;
			fscanf(inFile, "%c ", &c);
			pRecord->name = c;
			fscanf(inFile, "%d ", &n);
			pRecord->order = n;

			
		}

		fclose(inFile);
	}
	return dataSz;
}

// prints the records
void printRecords(struct RecordType pData[], int dataSz)
{
	int i;
	printf("\nRecords:\n");
	for (i = 0; i < dataSz; ++i)
	{
		printf("\t%d %c %d\n", pData[i].id, pData[i].name, pData[i].order);
	}
	printf("\n\n");
}

// display records in the hash structure
// skip the indices which are free
// the output will be in the format:
// index x -> id, name, order -> id, name, order ....
void displayRecordsInHash(struct HashType *pHashArray, int hashSz)
{
	int i;

	for (i=0;i<hashSz;i++)
	{
		// if index is occupied with any records, print all
		if(pHashArray != NULL){
			struct HashType *temp = pHashArray->rPtr;
			while(temp[i].next!= NULL){
				printf("index [%d] -> %d, %c, %d\n", temp[i].rPtr->order, temp[i].rPtr->id, temp[i].rPtr->name, temp[i].rPtr->order);
				if (temp->next == NULL)
				{
					break;
				}
				if(temp->next!=NULL ){
					temp = temp->next;
				}
				
			}
				
		}
	}
}

int main(void)
{
	struct RecordType *pRecords;
	int recordSz = 0;

	recordSz = parseData("input_lab_9.txt", &pRecords);
	printRecords(pRecords, recordSz);
	// Your hash implementation
	 struct HashType *hashElement = (struct HashType*)malloc(sizeof(struct HashType));
	 hashElement->rPtr = NULL;
	 hashElement->next = NULL;
	 struct HashType *temp;
	 struct HashType * data;
	 struct HashType ** hArray = (struct HashType*)malloc(sizeof(struct HashType)*recordSz);
	
	 int index;
	 if(pRecords != NULL){
		for(int i=0; i < recordSz; i++){
			if(hashElement->rPtr == NULL){
				hashElement->rPtr = pRecords;
			}
			if(i > 0){
				index = hash(pRecords[i].order);
				temp = hashElement;
				while(temp->rPtr->order!= index && temp->next!= NULL){
					temp = temp->next;
				}

				if((temp->rPtr) == NULL){
				data = (struct HashType*)malloc(sizeof(struct HashType));
				data->next = NULL;
				if(data){
					data->rPtr = pRecords + i;
					data->rPtr->order = index;
					temp->next= data;

				}
				}
				if (temp->rPtr != NULL && temp->rPtr->order == index){
					while(temp->next!= NULL){
						temp = temp->next;
					}

					data = (struct HashType*)malloc(sizeof(struct HashType));
					data->next = NULL;
					if(data){
						data->rPtr = pRecords+i;
						data->rPtr->order = index;
						temp->next= data;
						

					}
				}
				else{

					data = (struct HashType*)malloc(sizeof(struct HashType));
					data->next = NULL;
					if(data){
						data->rPtr = pRecords+i;
						data->rPtr->order = index;
						temp->next= data;
					}
			
				}	
				*(hArray+data->rPtr->order) = hashElement;
			}
		}


	}	

	displayRecordsInHash(hArray, 23);
	//free(hashLinkedList);

}