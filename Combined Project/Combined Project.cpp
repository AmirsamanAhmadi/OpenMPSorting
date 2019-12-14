#include "stdafx.h"
#include <omp.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <random>
#include <chrono>
using namespace std;
#define max_threads 80
#define n_buckets 15



struct My_Bucket {
	int integer;
	int bucket_index;
};
bool int_sorter(const int &lhs, const int &rhs) {
	return lhs < rhs;
}
bool struct_compare(My_Bucket const &lhs, My_Bucket const &rhs) 
{ return lhs.integer < rhs.integer; }
//Swap function
void swap(int *a, int *b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}
float BucketSort(vector<int> input_vector) {
	vector<My_Bucket> my_new_vec;
	vector<My_Bucket> bucket_zero;
	vector<My_Bucket> bucket_one;
	vector<My_Bucket> bucket_two;
	vector<My_Bucket> bucket_three;
	vector<My_Bucket> bucket_four;
	vector<My_Bucket> bucket_five;
	vector<My_Bucket> bucket_six;
	vector<My_Bucket> bucket_seven;
	vector<My_Bucket> bucket_eight;
	vector<My_Bucket> bucket_nine;
	vector<My_Bucket> bucket_ten;
	vector<My_Bucket> bucket_elev;
	vector<My_Bucket> bucket_twelv;
	vector<My_Bucket> bucket_thirteen;
	vector<My_Bucket> bucket_fourteen;
	vector<My_Bucket> bucket_fifteen;

	for (int i = 0; i < input_vector.size(); i++)
	{
		my_new_vec.push_back({ input_vector[i],0 });
	}
	auto minmax_vec = minmax_element(begin(my_new_vec), end(my_new_vec), [](My_Bucket const &lhs, My_Bucket const &rhs) {return lhs.integer < rhs.integer; });
	int divider = ceil((minmax_vec.second->integer + 1) / n_buckets);
	//cout << "Vector Size: " << my_new_vec.size() << endl;
	cout << "Divider: " << divider << endl;

	omp_set_num_threads(n_buckets);

	float t1 = omp_get_wtime();
	int i, j;
#pragma omp parallel private(j)
	{
		/*int thread_id = omp_get_thread_num();
		vector<int> bucket;
		int cnt = 0;*/

#pragma omp for
		for (i = 0; i < input_vector.size(); i++)
		{
			j = floor(my_new_vec[i].integer / divider);
			//cout << "The value of j is: " << j << endl;
#pragma omp critical
			{
				switch (j)
				{
				case 0:
					bucket_zero.push_back(my_new_vec[i]);
					//cout << "From bucket 0" << endl;
					break;
				case 1:
					bucket_one.push_back(my_new_vec[i]);
					//cout << "From bucket 1" << endl;
					break;
				case 2:
					bucket_two.push_back(my_new_vec[i]);
					break;
				case 3:
					bucket_three.push_back(my_new_vec[i]);
					//cout << "From bucket 3" << endl;
					break;
				case 4:
					bucket_four.push_back(my_new_vec[i]);
					break;
				case 5:
					bucket_five.push_back(my_new_vec[i]);
					break;
				case 6:
					bucket_six.push_back(my_new_vec[i]);
					break;
				case 7:
					bucket_seven.push_back(my_new_vec[i]);
					break;
				case 8:
					bucket_eight.push_back(my_new_vec[i]);
					break;
				case 9:
					bucket_nine.push_back(my_new_vec[i]);
					break;
				case 10:
					bucket_ten.push_back(my_new_vec[i]);
					break;
				default:
					//cout << "Somthing wrong just happend!!!!!!!!!" << endl;
					//cout << my_new_vec[i].integer << endl;
					break;
				}
			}

		}
#pragma omp sections
		{
#pragma omp section
			{
				sort(bucket_zero.begin(), bucket_zero.end(), struct_compare);
				//cout << "From section 0" << endl;
			}
#pragma omp section
			{
				sort(bucket_one.begin(), bucket_one.end(), struct_compare);
				//cout << "From section 1" << endl;
			}
#pragma omp section
			{
				sort(bucket_two.begin(), bucket_two.end(), struct_compare);
				//cout << "From section 2" << endl;
			}
#pragma omp section
			{
				sort(bucket_three.begin(), bucket_three.end(), struct_compare);
			}
#pragma omp section
			{
				sort(bucket_four.begin(), bucket_four.end(), struct_compare);
			}
#pragma omp section
			{
				sort(bucket_five.begin(), bucket_five.end(), struct_compare);
			}
#pragma omp section
			{
				sort(bucket_six.begin(), bucket_six.end(), struct_compare);
			}
#pragma omp section
			{
				sort(bucket_seven.begin(), bucket_seven.end(), struct_compare);
			}
#pragma omp section
			{
				sort(bucket_eight.begin(), bucket_eight.end(), struct_compare);
			}
#pragma omp section
			{
				sort(bucket_nine.begin(), bucket_nine.end(), struct_compare);
			}
#pragma omp section
			{
				sort(bucket_ten.begin(), bucket_ten.end(), struct_compare);
			}

		}


#pragma omp master
		{

		}
#pragma omp barrier			

	}
	float total = omp_get_wtime() - t1;
	return total;
}

float SelectionSort(vector<int> input_vector) {
	//vector<int> input_vector;
	//for (unsigned int i = 0; i < dim; i++) {
	//	input_vector.push_back(rand() % lim);
	//	//cout << input_vector[i] << " " << flush;
	//}
	int i = 0;
	double start_time;
	start_time = omp_get_wtime();

	for (unsigned int num = 0; num < input_vector.size(); num++)
	{
#pragma omp parallel
		{
			int thread_num = omp_get_thread_num();
#pragma omp for
			for (i = num + 1; i < input_vector.size(); i++)
			{
				if (input_vector[i] < input_vector[num])
				{
					swap(input_vector[i], input_vector[num]);
				}
				//				cout << "Thread " << thread_num << " is working" << endl;

			}


		}
	}
	double total = omp_get_wtime() - start_time;

	cout << endl;
	/*for (unsigned int var = 0; var < input_vector.size(); ++var)
	{
	cout << input_vector[var] << " " << flush;
	}*/
	//printf("Running Time:              %f", total);
	//cout << endl;
	return total;
}

float BubbleSort(vector<int> input_vector) {
	int input_vector_size = input_vector.size();
	int i = 0, j = 0;
	int begin_element;
	double start_time;
	start_time = omp_get_wtime();
	for (i = 0; i < input_vector_size - 1; i++)
	{
		begin_element = i % 2;
#pragma omp parallel for
		for (j = begin_element; j < input_vector_size - 1; j += 1)
		{
			if (input_vector[j] > input_vector[j + 1])
			{
				swap(&input_vector[j], &input_vector[j + 1]);
			}
			//cout << "Hello" << endl;
		}
	}
	double total = omp_get_wtime() - start_time;
	cout << endl;
	/*for (i = 0; i<input_vector_size; i++)
	{
	printf(" %d", input_vector[i]);
	}*/
	return total;
}

int main()
{


	cout << "Please give the lenght of array to sort." << endl;
	int dim;
	cin >> dim;
	int lim = 100000;
	float total = 0;

	vector<int> input_vector;
	for (unsigned int i = 0; i < dim; i++) {
		input_vector.push_back(rand() % lim);
		//cout << input_vector[i] << " " << flush;
	}
	
	total = BucketSort(input_vector);
	cout << "Numbers before sorting.\n";
	/*for each (My_Bucket item in my_new_vec)
	{
	cout << item.integer << " - " << flush;
	}*/
	
	cout << "Numbers After sorting.\n";
	//cout << "Size of final vector: " << my_new_vec.size() << "\n";
	cout << "\n" << "Bucket Sort: Running time: " << total << endl;

	total = SelectionSort(input_vector);

	cout << "\n" << "Selection Sort: Running time: " << total << endl;

	total = BubbleSort(input_vector);

	cout << "\n" << "Bubble Sort: Running time: " << total << endl;

	cin.get();



	return 0;
}



