#include "SortAlgorithmWithCount.h"
void swapWithCount(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}
void selectionSortWithCount(int arr[], int n, long long &cnt) {
    int i, j, min_idx;
    for (i = 0; ++cnt && i < n - 1; i++) {
        min_idx = i;
        for (j = i + 1; ++cnt && j < n; j++)
            if (++cnt && arr[j] < arr[min_idx])
                min_idx = j;
        swapWithCount(&arr[min_idx], &arr[i]);
    }
}
void insertionSortWithCount(int arr[], int n, long long &cnt) {
    int i, key, j;
    for (i = 1; ++cnt && i < n; i++) {
        key = arr[i];
        j = i - 1;
        while ((cnt += 2) && j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}
void shellSortWithCount(int arr[], int n, long long &cnt) {
    for (int gap = n / 2; ++cnt && gap > 0; gap /= 2) {
        for (int i = gap; ++cnt && i < n; i += 1) {
            int temp = arr[i];
            int j;
            for (j = i; (cnt += 2) && j >= gap && arr[j - gap] > temp; j -= gap)
                arr[j] = arr[j - gap];
            arr[j] = temp;
        }
    }
}
void bubbleSortWithCount(int arr[], int n, long long &cnt) {
    for (int i = 0; ++cnt && i < n - 1; i++)
        for (int j = n - 1; ++cnt && j > i; j--)
			if (++cnt && arr[j] < arr[j - 1])
				swapWithCount(&arr[j], &arr[j - 1]);
}
void shakerSortWithCount(int a[], int n, long long &cnt) {
    bool swapWithCountped = true;
    int start = 0;
    int end = n - 1;
    while (swapWithCountped) {
        swapWithCountped = false;
        for (int i = start; ++cnt && i < end; ++i) {
            if (++cnt && a[i] > a[i + 1]) {
                swapWithCount(&a[i], &a[i + 1]);
                swapWithCountped = true;
            }
        }
        if (!swapWithCountped)
            break;
        swapWithCountped = false;
        --end;
        for (int i = end - 1; ++cnt && i >= start; --i) {
            if (++cnt && a[i] > a[i + 1]) {
                swapWithCount(&a[i], &a[i + 1]);
                swapWithCountped = true;
            }
        }
        ++start;
    }
}
void heapifyWithCount(int arr[], int n, int i, long long &cnt) {
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    if ((cnt += 2) && l < n && arr[l] > arr[largest])
        largest = l;
    if ((cnt += 2) && r < n && arr[r] > arr[largest])
        largest = r;
    if (++cnt && largest != i) {
        swapWithCount(&arr[i], &arr[largest]);
        heapifyWithCount(arr, n, largest, cnt);
    }
}
void heapSortWithCount(int arr[], int n, long long &cnt) {
    for (int i = n / 2 - 1; ++cnt && i >= 0; i--)
        heapifyWithCount(arr, n, i, cnt);
    for (int i = n - 1; ++cnt && i > 0; i--) {
        swapWithCount(&arr[0], &arr[i]);
        heapifyWithCount(arr, i, 0, cnt);
    }
}
void mergeWithCount(int arr[], int l, int m, int r, long long &cnt);
void mergeSortFunctionWithCount(int arr[], int l, int r, long long &cnt) {
    if (++cnt && l < r) {
        int m = l + (r - l) / 2;
        mergeSortFunctionWithCount(arr, l, m, cnt);
        mergeSortFunctionWithCount(arr, m + 1, r, cnt);
        mergeWithCount(arr, l, m, r, cnt);
    }
}
void mergeSortWithCount(int arr[], int n, long long &cnt) {
    mergeSortFunctionWithCount(arr, 0, n - 1, cnt);
}
void mergeWithCount(int arr[], int l, int m, int r, long long &cnt) {
    int k;
    int n1 = m - l + 1;
    int n2 = r - m;
    int *L = new int[n1], *R = new int[n2];
    for (int i = 0; ++cnt && i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; ++cnt && j < n2; j++)
        R[j] = arr[m + 1 + j];
    int i = 0;
    int j = 0;
    k = l;
    while ((cnt +=2) && i < n1 && j < n2) {
        if (++cnt && L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while (++cnt && i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (++cnt && j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
    delete[] L;
    delete[] R;
}
void quickSortFunctionWithCount(int arr[], int l, int r, long long &cnt) {
    if(++cnt && l <= r) {
        int i = l, j = r, pivot = arr[(l + r) / 2];
        while(++cnt && i < j) {
            while(++cnt && arr[i] < pivot) i++;
            while(++cnt && arr[j] > pivot) j--;
            if(++cnt && i <= j) {
                swapWithCount(&arr[i], &arr[j]);
                i++;
                j--;
            }
        }
        if(++cnt && l < j) quickSortFunctionWithCount(arr, l, j, cnt);
        if(++cnt && i < r) quickSortFunctionWithCount(arr, i, r, cnt);
    }
}
void quickSortWithCount(int arr[], int n, long long &cnt) {
    quickSortFunctionWithCount(arr, 0, n - 1, cnt);
}
int getMaxWithCount(int arr[], int n, long long &cnt) {
    int mx = arr[0];
    for (int i = 1; ++cnt && i < n; i++)
        if (++cnt && arr[i] > mx)
            mx = arr[i];
    return mx;
}
void countingSortWithCount(int arr[], int n, long long &cnt) {
    int MAX = getMaxWithCount(arr, n, cnt) + 1;
    int *counter = new int[MAX];
    for (int i = 0; ++cnt && i < MAX; i++) counter[i] = 0;
    for (int i = 0; ++cnt && i < n; i++)
        counter[arr[i]]++;
    int curIdx = 0;
    for (int i = 0; ++cnt && i < MAX; i++)
        while (++cnt && counter[i] > 0) {
            arr[curIdx] = i;
            curIdx++;
            counter[i]--;
        }
    delete[] counter;
}
void countSort_radixWithCount(int arr[], int n, int exp, long long &cnt) {
    int *output = new int[n];
    int i, count[10] = {0};
    for (i = 0; ++cnt && i < n; i++)
        count[(arr[i] / exp) % 10]++;
    for (i = 1; ++cnt && i < 10; i++)
        count[i] += count[i - 1];
    for (i = n - 1; ++cnt && i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }
    for (i = 0; ++cnt && i < n; i++)
        arr[i] = output[i];
    delete[] output;
}
void radixSortWithCount(int arr[], int n, long long &cnt) {
    int m = getMaxWithCount(arr, n, cnt);
    for (int exp = 1; ++cnt && m / exp > 0; exp *= 10)
        countSort_radixWithCount(arr, n, exp, cnt);
}
void flashSortWithCount(int a[], int n, long long &cnt) { // Mr Phuong
    int min = a[0], max = a[0];
    for (int i = 1; ++cnt && i < n; i++)
    {
        if (++cnt && a[i] < min) min = a[i];
        if (++cnt && a[i] > max) max = a[i];
    }
    int k, m = 0.43 * n;
    int* L = new int[m];
    for (int i = 0; ++cnt && i < m; i++) L[i] = 0;
    for (int i = 0; ++cnt && i < n; i++) {
        k = 1ll * (m - 1) * (a[i] - min) / (max - min);
        L[k]++;
    }
    for (int k = 1; ++cnt && k < m; k++) {
        L[k] += L[k - 1];
    }
    int count = 1;
    int i = 0;
    k = m - 1;
    while (++cnt && count <= n) {
        while (++cnt && i > L[k] - 1) {
            i++;
            k = 1ll * (m - 1) * (a[i] - min) / (max - min);
        }
        int x = a[i];
        if (++cnt && k < 0) break;
        while (++cnt && i <= L[k] - 1) {
            k = 1ll * (m - 1) * (x - min) / (max - min);
            int y = a[L[k] - 1];
            a[L[k] - 1] = x;
            x = y;
            L[k]--;
            count++;
        }
    }
    for (k = 1; ++cnt && k < m; k++) {
        for (int i = L[k] - 1; ++cnt && i >= L[k - 1]; i--) {
            if (++cnt && a[i] > a[i + 1]) {
                int t = a[i];
                int j = i;
                while (++cnt && t > a[j + 1])
                    a[j++] = a[j + 1];
                a[j] = t;
            }
        }
    }
    delete[] L;
}
typedef void (*FnPtr)(int[], int, long long &);
map<string, FnPtr> runWithCount;
void sortWithCountInit() {
    runWithCount["selection-sort"] = selectionSortWithCount;
    runWithCount["insertion-sort"] = insertionSortWithCount;
    runWithCount["bubble-sort"] = bubbleSortWithCount;
    runWithCount["shaker-sort"] = shakerSortWithCount;
    runWithCount["shell-sort"] = shellSortWithCount;
    runWithCount["heap-sort"] = heapSortWithCount;
    runWithCount["merge-sort"] = mergeSortWithCount;
    runWithCount["quick-sort"] = quickSortWithCount;
    runWithCount["counting-sort"] = countingSortWithCount;
    runWithCount["radix-sort"] = radixSortWithCount;
    runWithCount["flash-sort"] = flashSortWithCount;
}
void runSortWithCount(int arr[], int n, string _algorithm, long long &cnt) {
    runWithCount[_algorithm](arr, n, cnt);
}