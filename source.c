#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Point{
	float x;
	float y;
} Point;

float Random_Number(){
	srand(clock());
	int integer;
	float whole;
	float decimal;

	integer = rand() % 1000;
	decimal = (float)integer;
	decimal /= 1000;

	integer = rand() % 501;
	whole = (float)integer;

	return whole + decimal;
}


void Array_Define(int size, struct Point **ptr){
	(*ptr) = malloc(size * sizeof(*(*ptr)));
}

void Array_Fill_Random(int size, struct Point *ptr){
	for(int i = 0; i < size; i++){
		ptr[i].x = Random_Number();
		ptr[i].y = Random_Number();
	}
}

void Array_Display(int size, struct Point *ptr){
	for(int i = 0; i < size; i++){
		printf("%d- %f %f\n", i + 1, ptr[i].x, ptr[i].y);
	}
}
	
int main(){
	Point *ptr;
	int size;

	printf("How many random points do you want to create?\n");
	scanf("%d", &size);

	Array_Define(size, &ptr);
	Array_Fill_Random(size, ptr);
	Array_Display(size, ptr);
	free(ptr);
}
