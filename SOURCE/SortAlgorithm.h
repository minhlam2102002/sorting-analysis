#pragma once
#include "DataGenerator.h"
#include "SortAlgorithmWithCount.h"

extern vector<string> SORT_ALGORITHM;
extern vector<string> MODE;
extern vector<string> DATA_ORDER;
extern vector<string> OUTPUT_PARAM;
extern vector<string> DATA_ORDER_NAME;
extern vector<string> SORT_ALGORITHM_NAME;
typedef pair<int, long long> pii;

void sortInit();
pii runSort(int arr[], int n, string typeSort, string outputParam);
void printArray(int arr[], int n);