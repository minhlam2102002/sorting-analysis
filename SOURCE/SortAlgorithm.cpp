#include "SortAlgorithm.h"  
vector<string> DATA_ORDER = {"-rand", "-nsorted", "-sorted", "-rev"};
vector<string> SORT_ALGORITHM = {
    "selection-sort", "insertion-sort", "bubble-sort", "shaker-sort",
    "shell-sort", "heap-sort", "merge-sort", "quick-sort",
    "counting-sort", "radix-sort", "flash-sort"};
vector<string> MODE = {"-a", "-c"};  // Algorithm mode / Comparison mode
vector<string> OUTPUT_PARAM = {"-time", "-comp", "-both"};
vector<string> DATA_ORDER_NAME = {"Randomize", "Nearly sorted", "Sorted", "Reversed"};
vector<string> SORT_ALGORITHM_NAME ={"Selection sort", "Insertion sort", "Bubble sort", "Shaker sort",
    "Shell sort", "Heap sort", "Merge sort", "Quick sort",
    "Counting sort", "Radix sort", "Flash sort"};

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}
void selectionSort(int arr[], int n) {
    int i, j, min_idx;
    for (i = 0; i < n - 1; i++) {
        min_idx = i;
        for (j = i + 1; j < n; j++)
            if (arr[j] < arr[min_idx])
                min_idx = j;
        swap(&arr[min_idx], &arr[i]);
    }
};
void insertionSort(int arr[], int n) {
    int i, key, j;
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}
void shellSort(int arr[], int n) {
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i += 1) {
            int temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap)
                arr[j] = arr[j - gap];
            arr[j] = temp;
        }
    }
}
void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++)
        for (int j = n - 1; j > i; j--)
			if (arr[j] < arr[j - 1])
				swap(&arr[j], &arr[j - 1]);
}
void shakerSort(int a[], int n) {
    bool swapped = true;
    int start = 0;
    int end = n - 1;
    while (swapped) {
        swapped = false;
        for (int i = start; i < end; ++i) {
            if (a[i] > a[i + 1]) {
                swap(&a[i], &a[i + 1]);
                swapped = true;
            }
        }
        if (!swapped)
            break;
        swapped = false;
        --end;
        for (int i = end - 1; i >= start; --i) {
            if (a[i] > a[i + 1]) {
                swap(&a[i], &a[i + 1]);
                swapped = true;
            }
        }
        ++start;
    }
}
void heapify(int arr[], int n, int i) {
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    if (l < n && arr[l] > arr[largest])
        largest = l;
    if (r < n && arr[r] > arr[largest])
        largest = r;
    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        heapify(arr, n, largest);
    }
}
void heapSort(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);
    for (int i = n - 1; i > 0; i--) {
        swap(&arr[0], &arr[i]);
        heapify(arr, i, 0);
    }
}
void merge(int arr[], int l, int m, int r);
void mergeSortFunction(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSortFunction(arr, l, m);
        mergeSortFunction(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}
void mergeSort(int arr[], int n) {
    mergeSortFunction(arr, 0, n - 1);
}
void merge(int arr[], int l, int m, int r) {
    int k;
    int n1 = m - l + 1;
    int n2 = r - m;
    int *L = new int[n1], *R = new int[n2];
    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];
    int i = 0;
    int j = 0;
    k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
    delete[] L;
    delete[] R;
}
void quickSortFunction(int arr[], int l, int r) { 
    if(l <= r) {
        int i = l, j = r, pivot = arr[(l + r) / 2];
        while(i < j) {
            while(arr[i] < pivot) i++;
            while(arr[j] > pivot) j--;
            if(i <= j) {
                swap(&arr[i], &arr[j]);
                i++;
                j--;
            }
        }
        if(l < j) quickSortFunction(arr, l, j);
        if(i < r) quickSortFunction(arr, i, r);
    }
}
void quickSort(int arr[], int n) {
    quickSortFunction(arr, 0, n - 1);
}
int getMax(int arr[], int n) {
    int mx = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > mx)
            mx = arr[i];
    return mx;
}
void countingSort(int arr[], int n) {
    int MAX = getMax(arr, n) + 1;
    int *counter = new int[MAX];
    for (int i = 0; i < MAX; i++) counter[i] = 0;
    for (int i = 0; i < n; i++)
        counter[arr[i]]++;
    int curIdx = 0;
    for (int i = 0; i < MAX; i++)
        while (counter[i] > 0) {
            arr[curIdx] = i;
            curIdx++;
            counter[i]--;
        }
    delete[] counter;
}
void countSort_radix(int arr[], int n, int exp) {
    int *output = new int[n];
    int i, count[10] = {0};
    for (i = 0; i < n; i++)
        count[(arr[i] / exp) % 10]++;
    for (i = 1; i < 10; i++)
        count[i] += count[i - 1];
    for (i = n - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }
    for (i = 0; i < n; i++)
        arr[i] = output[i];
    delete[] output;
}
void radixSort(int arr[], int n) {
    int m = getMax(arr, n);
    for (int exp = 1; m / exp > 0; exp *= 10)
        countSort_radix(arr, n, exp);
}
void flashSort(int a[], int n) { // Thay Phuong
    int min = a[0], max = a[0];
    for (int i = 1; i < n; i++){
        if (a[i] < min) min = a[i];
        if (a[i] > max) max = a[i];
    }
    int k, m = 0.43 * n;
    int* L = new int[m];
    for (int i = 0; i < m; i++) L[i] = 0;
    for (int i = 0; i < n; i++) {
        k = 1ll * (m - 1) * (a[i] - min) / (max - min);
        L[k]++;
    }
    for (int k = 1; k < m; k++) {
        L[k] += L[k - 1];
    }
    int count = 1;
    int i = 0;
    k = m - 1;
    while (count <= n) {
        while (i > L[k] - 1) {
            i++;
            k = 1ll * (m - 1) * (a[i] - min) / (max - min);
        }
        int x = a[i];
        if (k < 0) break;
        while (i <= L[k] - 1) {
            k = 1ll * (m - 1) * (x - min) / (max - min);
            int y = a[L[k] - 1];
            a[L[k] - 1] = x;
            x = y;
            L[k]--;
            count++;
        }
    }
    for (k = 1; k < m; k++) {
        for (int i = L[k] - 1; i >= L[k - 1]; i--) {
            if (a[i] > a[i + 1]) {
                int t = a[i];
                int j = i;
                while (t > a[j + 1])
                    a[j++] = a[j + 1];
                a[j] = t;
            }
        }
    }
    delete[] L;
}

bool checkSortedArray(int arr[], int n) {
    for (int i = 1; i < n; i++)
        if (arr[i] < arr[i - 1]) {
            return false;
        }
    return true;
}
void printArray(int arr[], int n) {
    for (int i = 0; i < n; ++i)
        cout << arr[i] << " ";
    cout << endl;
}
typedef void (*FnPtr)(int[], int);
map<string, FnPtr> run;
void sortInit() {
    sortWithCountInit();
    generatorInit();
    run["selection-sort"] = selectionSort;
    run["insertion-sort"] = insertionSort;
    run["bubble-sort"] = bubbleSort;
    run["shaker-sort"] = shakerSort;
    run["shell-sort"] = shellSort;
    run["heap-sort"] = heapSort;
    run["merge-sort"] = mergeSort;
    run["quick-sort"] = quickSort;
    run["counting-sort"] = countingSort;
    run["radix-sort"] = radixSort;
    run["flash-sort"] = flashSort;
}

pii runSort(int arr[], int n, string _algorithm, string outputParam){
    pii result;
    if(outputParam == "-comp" || outputParam == "-both") {
        int *arrWithCount = new int[n];
        for (int i = 0; i < n; i++)
            arrWithCount[i] = arr[i];
        result.second = 0;
        runSortWithCount(arrWithCount, n, _algorithm, result.second);
        if(outputParam == "-comp") 
            for (int i = 0; i < n; i++)
                arr[i] = arrWithCount[i];
        delete[] arrWithCount;
    }   
    if(outputParam == "-time" || outputParam == "-both"){
        FnPtr runSortAlgorithm = run[_algorithm];
        auto start = high_resolution_clock::now();
        runSortAlgorithm(arr, n);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<milliseconds>(stop - start);
        result.first = duration.count();
    }
    if(checkSortedArray(arr, n) == false) cerr << "ERROR: Array is not sorted" << endl;
    return result;
}