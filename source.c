#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct Point{
	float x;
	float y;
	float distance;
	float angle;
} Point;

float Calculate_Angle(struct Point *point_1, struct Point *point_2){
	return acos( ( ( (point_1->x) * (point_2->x) ) + ( (point_1->y) * (point_2->y) ) ) / point_1->distance * point_2->distance ) * 180/M_PI;
}

float Calculate_Distance(struct Point *point_1, struct Point *point_2){
	return sqrt( pow(point_1->x - point_2->x, 2.0) + pow(point_1->y - point_2->y, 2.0) );
}

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

void Point_Median(int size, struct Point *points, struct Point *median){
	float sum_x = 0;
	float sum_y = 0;
	for(int i = 0; i < size; i++){
		sum_x += points[i].x;
		sum_y += points[i].y;
	}
	median->x = sum_x / size;
	median->y = sum_y / size;
}

void Point_Transpose(int size, struct Point *points, struct Point *median){
	for(int i = 0; i < size; i++){
		points[i].x -= median->x;
		points[i].y -= median->y;
	}
	median->x -= median->x;
	median->y -= median->y;
}

void Array_Define(int size, struct Point **points){
	(*points) = malloc(size * sizeof(*(*points)));
}

void Array_Initialize(int size, struct Point *points){
	Point zero = {0, 0, 0 ,0};
	for(int i = 0; i < size; i++){
		points[i].x = Random_Number();
		points[i].y = Random_Number();
		points[i].distance = 0;
		points[i].angle = 0;
	}
}

void Array_Display(int size, struct Point *points){
	for(int i = 0; i < size; i++){
		printf("%4d- Point:(%4f, %4f), Distance: %4f Angle: %4f\n", i + 1, points[i].x, points[i].y, points[i].distance, points[i].angle);
	}
	printf("\n");
}
	
int main(){
	srand(clock());
	Point *points;
	Point median;
	Point unit_vector = {1.0, 0.0, 1.0, 0.0};
	int size;
	printf("How many random points do you want to create?\n");
	scanf("%d", &size);

	Array_Define(size, &points);
	Array_Initialize(size, points);
	Point_Median(size, points, &median);
	Array_Display(size, points);
	Point_Transpose(size, points, &median);
	for(int i = 0; i < size; i++){
		points[i].distance = Calculate_Distance(&points[i], &median);
		if(points[i].y >= 0){
			points[i].angle = Calculate_Angle(&points[i], &unit_vector);
		}else{
			points[i].angle = -1 * (Calculate_Angle(&points[i], &unit_vector) - 360);
		}
	}
	Array_Display(size, points);
	free(points);
}
/* TODO:
 *vector->angle = -1 * ( (acos( (vector->x) / sqrt( pow(vector->x, 2.0) + pow(vector->y, 2.0) ) ) * 180/M_PI) - 360);
 */
