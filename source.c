#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

typedef struct Point{
	float x;
	float y;
	float distance;
	float angle;
} Point;

void Swap(struct Point *point_1, struct Point *point_2){
	Point swapper;
	swapper = *point_1;
	*point_1 = *point_2;
	*point_2 = swapper;
}

int Compare_Float(float *num_1, float *num_2){
	int integer_1 = (int)(*num_1 * 1000000);
	int integer_2 = (int)(*num_2 * 1000000);
	return (integer_1 >= integer_2);
}

float Calculate_Angle(struct Point *point_1, struct Point *point_2){
	return acosf((((point_1->x) * (point_2->x)) + ((point_1->y) * (point_2->y))) / (point_1->distance * point_2->distance));
}

float Calculate_Distance(struct Point *point_1, struct Point *point_2){
	return sqrt(pow(point_1->x - point_2->x, 2.0) + pow(point_1->y - point_2->y, 2.0));
}

float Calculate_Area(struct Point *point_1, struct Point *point_2){
	float angle = 0.0;
	angle = Calculate_Angle(point_1, point_2);
	return (point_1->distance * point_2->distance * sinf(angle)) * 1/2;
}	

float Random_Number(){
	srand(clock());
	int integer;
	float whole;
	float decimal;

	integer = rand() % 1000000;
	decimal = (float)integer;
	decimal /= 1000000;

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

void Point_Calculate_Angle(int size, struct Point *points){
	Point unit_vector = {1.0, 0.0, 1.0, 0.0};
	for(int i = 0; i < size; i++){
		if(points[i].y >= 0){
			points[i].angle = Calculate_Angle(&points[i], &unit_vector) * 180/M_PI;
		}else{
			points[i].angle = -1 * ((Calculate_Angle(&points[i], &unit_vector) * 180/M_PI) - 360);
		}
	}
}

void Point_Calculate_Distance(int size, struct Point *points){
	Point zero = {0.0, 0.0, 0.0, 0.0};
	for(int i = 0; i < size; i++){
		points[i].distance = Calculate_Distance(&points[i], &zero);
	}
}

float Point_Calculate_Area(int size, struct Point *points){
	float area = 0.0;
	for(int i = 0; i < size - 1; i++){
		area += Calculate_Area(&points[i], &points[i + 1]);
	}
	area += Calculate_Area(&points[size - 1], &points[0]);
	return area;
}

int Point_Sort_Angle(struct Point *points, int start, int end){
        if(start >= end){
                return 0;
        }
        int pivot = end;
        int greater = start;
        for(int i = start; i < end; i++){
                if(Compare_Float(&points[pivot].angle, &points[i].angle)){
                        Swap(&points[greater], &points[i]);
                        greater++;
                }
        }
        Swap(&points[pivot], &points[greater]);
        Point_Sort_Angle(points, start, greater - 1);
        Point_Sort_Angle(points, greater + 1, end);
}


void Array_Define(int size, struct Point **points){
	(*points) = malloc(size * sizeof(*(*points)));
}

void Array_Initialize(int size, struct Point *points){
	for(int i = 0; i < size; i++){
		points[i].x = Random_Number();
		points[i].y = Random_Number();
		points[i].distance = 0;
		points[i].angle = 0;
	}
}

void Array_Display(int size, struct Point *points){
	for(int i = 0; i < size; i++){
		printf("%4d- Point: (%3f, %3f) | Distance: %4f | Angle: %3f\n", i + 1, points[i].x, points[i].y, points[i].distance, points[i].angle);
	}
	printf("\n");
}
	
int main(){
	Point *points;
	Point median;
	int size;

	printf("How many random points do you want to create?\n");
	scanf("%d", &size);

	Array_Define(size, &points);
	Array_Initialize(size, points);
	Point_Median(size, points, &median);
	Array_Display(size, points);
	Point_Transpose(size, points, &median);
	Point_Calculate_Distance(size, points);
	Point_Calculate_Angle(size, points); 
	Array_Display(size, points);
	Point_Sort_Angle(points, 0, size - 1);
	Array_Display(size, points);
	printf("Area of polygon: %f\n", Point_Calculate_Area(size, points));
	free(points);
}
