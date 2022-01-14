#include "Commandline.h"
const int MAX_INPUT_SIZE = 1000000;

const string OUTPUT_FILE = "output.txt";
const string INPUT_FILE = "input.txt";
int indexOf(vector<string> v, string s) {
    for (int i = 0; i < v.size(); i++) {
        if (v[i] == s) return i;
    }
    return -1;
}
bool isNumber(string s) {
    for (char &c : s) {
        if (c > '9' || c < '0') return false;
    }
    return true;
}
void copyPtrArray(int *arr, int *&arrCopy, int n) {
    arrCopy = new int[n];
    for (int i = 0; i < n; i++) {
        arrCopy[i] = arr[i];
    }
}
bool validArgument(int argc, int ans) {
    if(argc == ans) return true;
    if (argc < ans) {
        cout << "Too few arguments" << endl;
    }
    if (argc > ans) {
        cout << "Too many arguments" << endl;
    }
    exit(0);
}
bool validAlgorithm(string _algorithm) {
    if (indexOf(SORT_ALGORITHM, _algorithm) == -1) {
        cout << "Invalid [Algorithm]" << endl;
        exit(0);
    }
    return true;
}
bool validInputSize(char *input) {
    if (!isNumber(input)) {
        cout << "Invalid [Input Size]. " << "\"" << input << "\"" << " is not a number."  << endl;
        exit(0);
    }
    int inputSize = atoi(input);
    if (inputSize <= 0 || inputSize > MAX_INPUT_SIZE) {
        cout << "Invalid [Input size]. It must be in range [1.." << MAX_INPUT_SIZE <<"]." << endl;
        exit(0);
    }
    return true;
}
bool validInputOrder(string _inputOrder) {
    if (indexOf(DATA_ORDER, _inputOrder) == -1) {
        cout << "Invalid [Input order]" << endl;
        exit(0);
    }
    return true;
}
bool validOutputParam(string _outputParam) {
    if (indexOf(OUTPUT_PARAM, _outputParam) == -1) {
        cout << "Invalid [Output param]" << endl;
        exit(0);
    }
    return true;
}
bool readInputFile(int *&arr, int &n, string inputFile) {
    ifstream fin(inputFile);
    if (!fin.is_open()) {
        cout << "Cannot open file: " << inputFile << endl;
        exit(1);
    }
    fin >> n;
    arr = new int[n];
    for (int i = 0; i < n; i++) {
        fin >> arr[i];
    }
    fin.close();
    return true;
}
void writeOutputFile(int *arr, int n, string outputFile) {
    ofstream fout(outputFile);
    fout << n << endl;
    for (int i = 0; i < n; i++) {
        fout << arr[i] << " ";
    }
    fout << endl;
    fout.close();
}
void printGivenInput(string inputFile, int inputSize) {
    cout << "Input file: " << inputFile << endl;
    cout << "Input size: " << inputSize << endl;
}
void printGeneratedInput(int inputSize, string inputOrder) {
    
    cout << "Input size: " << inputSize << endl;
    string dataOrderName = DATA_ORDER_NAME[indexOf(DATA_ORDER, inputOrder)];
    cout << "Input order: " << dataOrderName << endl;
}
void printAM(string _algorithm) {
    cout << "ALGORITHM MODE" << endl;
    string sortAlgorithmName = SORT_ALGORITHM_NAME[indexOf(SORT_ALGORITHM, _algorithm)];
    cout << "Algorithm: " << sortAlgorithmName << endl;
}
void printParamAM(pii res, string outputParam) {
    cout << "-------------------------" << endl;
    if(outputParam == "-time" || outputParam == "-both") 
        cout << "Running time: " << res.first << "ms" << endl;
    if(outputParam == "-comp" || outputParam == "-both") 
        cout << "Comparisions: " << res.second << endl;
}
void printCM(string _algorithm1, string _algorithm2) {
    cout << "COMPARE MODE" << endl;
    string sortAlgorithmName1 = SORT_ALGORITHM_NAME[indexOf(SORT_ALGORITHM, _algorithm1)];
    string sortAlgorithmName2 = SORT_ALGORITHM_NAME[indexOf(SORT_ALGORITHM, _algorithm2)];
    cout << "Algorithm: " << sortAlgorithmName1 << " | " << sortAlgorithmName2 << endl;
}
void printParamCM(pii res1, pii res2) {
    cout << "-------------------------" << endl;
    cout << "Running time: " << res1.first << "ms" << " | " << res2.first << "ms" <<endl;
    cout << "Comparisions: " << res1.second << " | " << res2.second <<endl;
}
void handleCommand1(string _algorithm, int argc, char **argv) {
    validArgument(argc, 5);
    string inputFile = argv[3];
    string outputParam = argv[4];
    validOutputParam(outputParam);
    int *arr, n = 0;
    readInputFile(arr, n, inputFile);
    printAM(_algorithm);
    printGivenInput(inputFile, n);
    auto res = runSort(arr, n, _algorithm, outputParam);
    printParamAM(res, outputParam);
    writeOutputFile(arr, n, OUTPUT_FILE);
    delete[] arr;
}

void handleCommand2(string _algorithm, int inputSize, int argc, char **argv) {
    validArgument(argc, 6);
    string inputOrder = argv[4];
    validInputOrder(inputOrder);
    string outputParam = argv[5];
    validOutputParam(outputParam);
    int *arr = new int[inputSize];
    GenerateData(arr, inputSize, inputOrder);
    writeOutputFile(arr, inputSize, INPUT_FILE);
    auto res = runSort(arr, inputSize, _algorithm, outputParam);
    printAM(_algorithm);
    printGeneratedInput(inputSize, inputOrder);
    printParamAM(res, outputParam);
    delete[] arr;
}
void handleCommand3(string _algorithm, int inputSize, int argc, char **argv) {
    validArgument(argc, 5);
    printAM(_algorithm);
    cout << "Input size: " << inputSize << endl << endl;
    string outputParam = argv[4];
    validOutputParam(outputParam);
    int *arr = new int[inputSize];
    for (int i = 0; i < DATA_ORDER.size(); i++) {
        cout << "Input order: " << DATA_ORDER_NAME[i] << endl;
        GenerateData(arr, inputSize, DATA_ORDER[i]);
        writeOutputFile(arr, inputSize, "input_" + to_string(i+1) + ".txt");
        auto res = runSort(arr, inputSize, _algorithm, outputParam);
        printParamAM(res, outputParam);
        cout << endl;
    }
    delete[] arr;
}
void handleCommand4(string _algorithm1, string _algorithm2, int argc, char **argv) {
    validArgument(argc, 5);
    string inputFile = argv[4];
    int *arr1, *arr2, n;
    readInputFile(arr1, n, inputFile);
    copyPtrArray(arr1, arr2, n);
    auto res1 = runSort(arr1, n, _algorithm1, "-both");
    auto res2 = runSort(arr2, n, _algorithm2, "-both");
    printCM(_algorithm1, _algorithm2);
    printGivenInput(inputFile, n);
    printParamCM(res1, res2);
    writeOutputFile(arr1, n, OUTPUT_FILE);
    delete[] arr1;
    delete[] arr2;
}
void handleCommand5(string _algorithm1, string _algorithm2, int argc, char **argv) {
    validArgument(argc, 6);
    validInputSize(argv[4]);
    int inputSize = atoi(argv[4]);
    string inputOrder = argv[5];
    validInputOrder(inputOrder);
    int *arr1, *arr2, n = inputSize;
    arr1 = new int[n];
    GenerateData(arr1, n, inputOrder);
    writeOutputFile(arr1, n, INPUT_FILE);
    copyPtrArray(arr1, arr2, n);
    auto res1 = runSort(arr1, n, _algorithm1, "-both");
    auto res2 = runSort(arr2, n, _algorithm2, "-both");
    printCM(_algorithm1, _algorithm2);
    printGeneratedInput(inputSize, inputOrder);
    printParamCM(res1, res2);
    delete[] arr1;
    delete[] arr2;
}
void algorithmMode(int argc, char **argv, string &_algorithm){
    if (isNumber(argv[3]) == false) {  
        //[Given input] [Output parameter(s)]
        handleCommand1(_algorithm, argc, argv);
    } else {  
        //[Input size]
        validInputSize(argv[3]);
        int inputSize = atoi(argv[3]);
        if (indexOf(DATA_ORDER, argv[4]) != -1) {  
            //[Input order] [Output parameter(s)]
            handleCommand2(_algorithm, inputSize, argc, argv);
        } else if (indexOf(OUTPUT_PARAM, argv[4]) != -1) {  
            //[Output parameter(s)]
            handleCommand3(_algorithm, inputSize, argc, argv);
        } else {
            cout << "Invalid command";
            exit(0);
        }
    }
}
void compareMode(int argc, char **argv, string _algorithm1, string _algorithm2) {
    if(isNumber(argv[4]) == false){  
        //[Given input] 
        handleCommand4(_algorithm1, _algorithm2, argc, argv);
    }else{ 
        //[Input size] [Input order]
        handleCommand5(_algorithm1, _algorithm2, argc, argv);
    }
}
void commandRouter(int argc, char **argv){
    if(argc < 4 || argc > 6){
        cout << "Invalid size of argument" << endl;
        exit(0);
    }
    if (argv[1] == MODE[0]) {  
        //[Execution file] -a [Algorithm]
        string _algorithm = argv[2];
        validAlgorithm(_algorithm);
        algorithmMode(argc, argv, _algorithm);
    } else if (argv[1] == MODE[1]) {  
        //[Execution file] -c [Algorithm 1] [Algorithm 2]
        string _algorithm1 = argv[2];
        string _algorithm2 = argv[3];
        validAlgorithm(_algorithm1);
        validAlgorithm(_algorithm2);
        compareMode(argc, argv, _algorithm1, _algorithm2);
    } else {
        cout << "Invalid [Mode]" << endl;
        exit(0);
    }
}