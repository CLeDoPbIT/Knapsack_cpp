#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <cmath>
#include <math.h>
#include <fstream>
#include <vector>
#include <chrono>
#include <locale.h>
#include <ctime>
#include <unordered_map>
#include <map>
#include <limits>
#include <unordered_set>
#include "dp_with_lower_bounds_and_cache.h"


struct Subject
{
	int weight;
	int value;
};


bool compare_subjects__(Subject a, Subject b) {
	return a.weight < b.weight;
}


DP_With_Lower_Bounds_and_Cache_Solver::DP_With_Lower_Bounds_and_Cache_Solver(std::vector<int> tmp_values, std::vector<int> tmp_weights, int tmp_W, int tmp_number_items)
{
	W = tmp_W;
	number_items = tmp_number_items;
	values = tmp_values;
	weights = tmp_weights;
}

//int DP_With_Cache_Solver::solve() {
//
//	std::unordered_map <int, int> table, table_new;
//	std::unordered_map<int, int>::iterator it;
//
//	table[0] = 0;
//	table_new[0] = 0;
//	int tmp_weight = -1;
//	int tmp_value = -1;
//	int counter = 0;
//
//
//
//	for (int n = 1; n <= number_items; n++) {
//
//
//		for(auto & x: table) {
//			tmp_weight = weights[n] + x.first;
//			if (tmp_weight <= W) {
//				tmp_value = values[n] + x.second;
//				counter++;
//				if (table.count(tmp_weight)) {
//					table_new[tmp_weight] = std::max(tmp_value, table[tmp_weight]);
//				}
//				else {
//					table_new[tmp_weight] = tmp_value;
//				}
//			}
//
//		}
//		table = table_new;
//	}
//
//	std::cout << counter << std::endl;
//	std::unordered_map<int, int>::iterator best = std::max_element(table_new.begin(), table_new.end(), [](const std::pair<char, int>& a, const std::pair<char, int>& b)->bool { return a.second < b.second; });
//
//	return best->second;
//
//}

int** DP_With_Lower_Bounds_and_Cache_Solver::create2DArray(unsigned height, unsigned width)
{
	int** array2D = 0;
	array2D = new int* [height];

	for (int h = 0; h < height; h++)
	{
		array2D[h] = new int[width];

		for (int w = 0; w < width; w++)
		{
			array2D[h][w] = 0;
		}
	}

	return array2D;
};

void DP_With_Lower_Bounds_and_Cache_Solver::clear2DArray(int** array, unsigned height) {
	for (int h = 0; h < height; h++)
	{
		delete[] array[h];
	}

}

std::pair <long, long> DP_With_Lower_Bounds_and_Cache_Solver::solve() {

	std::vector<Subject> subjects;
	int* keys = 0;
	keys = new int[W];

	for (int i = 0; i <= number_items; i++) {
		Subject tmp;
		tmp.value = values[i];
		tmp.weight = weights[i];
		subjects.push_back(tmp);
	}
	subjects[0].weight = std::numeric_limits<int>::max();;
	std::sort(subjects.rbegin(), subjects.rend(), compare_subjects__);

	int* left_bounds = 0;
	left_bounds = new int[number_items + 1];
	left_bounds[number_items] = W;

	int j = number_items;
	for (int i = number_items; i >= 0; i--) {
		if (left_bounds[j] - subjects[i].weight > 0) {
			left_bounds[j - 1] = left_bounds[j] - subjects[i].weight;
		}
		else {
			left_bounds[j - 1] = left_bounds[j];
		}
		j--;
	}


	//int** table = create2DArray(number_items + 1, W + 1);
	int* table = 0;
	table = new int[W + 1];
	std::vector <float> time_count;
	//table[0] = 0;
	memset(table, 0, 4*(W+1));
	//for (int n = 0; n < W + 1; n++) {
	//	std::cout << table[n] << std::endl;
	//}
	keys[left_bounds[1]] = 1;
	keys[0] = 1;
	int tmp_weight = -1;
	int tmp_value = -1;
	int counter = 0;
	float dur_seconds = 0;
	int size = 0;
	std::time_t startTime = time(0);
	int tmp_max = -1;

	for (int n = 1; n <= number_items; n++) {
		for (int w = W; w >= left_bounds[n]; w--) {

			//if (time(0) > startTime + 15) {
			//	goto skip;
			//}
			if (w >= subjects[n].weight) {
				if (keys[w - subjects[n].weight] == 1) {
					counter++;
					if (subjects[n].weight > w) {
						table[w] = table[w];
					}
					else {
						table[w] = std::max(table[w], table[w - subjects[n].weight] + subjects[n].value);
					}
					keys[w] = 1;
				}
			}
			else {
				if (keys[w] == 1) {
					counter++;
					if (subjects[n].weight > w) {
						table[w] = table[w];
					}
					else {
						table[w] = std::max(table[w], table[w - subjects[n].weight] + subjects[n].value);
					}
					keys[w] = 1;
				}
			}
		}
	}

	//std::cout << counter << std::endl;

	for (int i = 1; i <= W + 1; i++) {
		if (tmp_max < table[i]) {
			tmp_max = table[i];
		}
	}
skip:
	delete(table);
	//clear2DArray(table, number_items + 1);
	if (time(0) > startTime + 15) {
		return std::make_pair(0, 0);
	}
	else {
		return std::make_pair(tmp_max, counter);
	}
}
