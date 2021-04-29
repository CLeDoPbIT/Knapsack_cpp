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
#include "problem.h"

class Classic_DP_Solver {
private:
	int W;
	int number_items;
	std::vector <int> values;
	std::vector <int> weights;
	int** table;
public:
	Classic_DP_Solver(std::vector <int> tmp_values, std::vector <int> tmp_weights, int tmp_W, int tmp_number_items);
	int** create2DArray(unsigned height, unsigned width);
	int** get_table();
	int solve();
};