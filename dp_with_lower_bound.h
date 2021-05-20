#pragma once
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <queue>
#include <cmath>
#include <math.h>
#include <fstream>
#include <vector>
#include <chrono>
#include <locale.h>
#include "classical_dp.h"

class DP_with_lower_bound_Solver
{
public:
	int W;
	int number_items;
	std::vector <int> values;
	std::vector <int> weights;
	DP_with_lower_bound_Solver(std::vector <int> tmp_values, std::vector <int> tmp_weights, int tmp_W, int tmp_number_items);
	int** create2DArray(unsigned height, unsigned width);
	void clear2DArray(int** array, unsigned height);
	std::pair <long, long> solve();
};

