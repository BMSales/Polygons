#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Point{
	float x;
	float y;
} Point;

float Random_Number(){
	int integer;
	float whole;
	float decimal;

	integer = rand() % 1000;
	decimal = (float)integer;
	decimal /= 1000;

	integer = rand() % 500;
	whole = (float)integer;

	return whole + decimal;
}

void Point_Median(int size, struct Point* points, struct Point* median){
	float sum_x = 0;
	float sum_y = 0;
	for(int i = 0; i < size; i++){
		sum_x += points[i].x;
		sum_y += points[i].y;
	}
	median->x = sum_x / size;
	median->y = sum_y / size;
}

void Point_Transpose(int size, struct Point* points, struct Point* median){
	for(int i = 0; i < size; i++){
		points[i].x -= median->x;
		points[i].y -= median->y;
	}
	median->x -= median->x;
	median->y -= median->y;
}

void Array_Define(int size, struct Point** points){
	(*points) = malloc(size * sizeof(*(*points)));
}

void Array_Fill_Random(int size, struct Point* points){
	for(int i = 0; i < size; i++){
		points[i].x = Random_Number();
		points[i].y = Random_Number();
	}
}

void Array_Display(int size, struct Point* points){
	for(int i = 0; i < size; i++){
		printf("%d- (%f, %f)\n", i + 1, points[i].x, points[i].y);
	}
}
	
int main(){
	srand(clock());
	Point* points;
	Point median;
	int size;
	printf("How many random points do you want to create?\n");
	scanf("%d", &size);

	Array_Define(size, &points);
	Array_Fill_Random(size, points);
	Point_Median(size, points, &median);
	Array_Display(size, points);
	Point_Transpose(size, points, &median);
	Array_Display(size, points);
	free(points);
}
/* TODO:
 * calculate the angles of every point
 * */
