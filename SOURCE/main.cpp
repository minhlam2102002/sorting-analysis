#include "DataGenerator.h"
#include "SortAlgorithm.h"
#include "Experimental.h"
#include "CommandLine.h"

void printIntruction() {
    cout << "Basic usage: ./sort [Mode] ..." << endl;
    cout << "Mode: -a: Algorithm mode" << endl;
    cout << "\tCommand 1: Run a sorting algorithm on the given input data." << endl;
    cout << "\t\ttPrototype: ./sort -a [Algorithm] [Given input] [Output parameter(s)]" << endl;
    cout << "\tCommand 2: Run a sorting algorithm on the data generated automatically with specifiedsize and order." << endl;
    cout << "\t\tPrototype: ./sort -a [Algorithm] [Input size] [Input order] [Output parameter(s)]" << endl;
    cout << "\tCommand 3: Run a sorting algorithm on ALL data arrangements of a specified size." << endl;
    cout << "\t\tPrototype: ./sort -a [Algorithm] [Input size] [Output parameter(s)]" << endl;
    cout << "Mode: -c: Comparison mode" << endl;
    cout << "\tCommand 4: Run two sorting algorithms on the given input." << endl;
    cout << "\t\tPrototype: ./sort -c [Algorithm 1] [Algorithm 2] [Given input]" << endl;
    cout << "\tCommand 5: Run two sorting algorithms on the data generated automatically." << endl;
    cout << "\t\tPrototype: ./sort -c [Algorithm 1] [Algorithm 2] [Input size] [Input order]" << endl;
    cout << "Other command" << endl;
    cout << "./sort -h: Print this instruction" << endl;
    cout << "./sort -v: Print version" << endl;
    cout << "./sort -i: Print information" << endl;
    cout << "./sort -e [File]: Run experimental and print to [File]." << endl;
    cout << "\t [File] can be \"csv\", \"txt\", \"console\" (default)" << endl;
    exit(0);
}
void printVersion() {
    const string version = "1.0.0";
    const string author = "Tran Kieu Minh Lam";
    cout << "Version: " << version << endl;
    cout << "Author: " << author << endl;
    exit(0);
}
void printInfo() {
    cout << "This program is a command line interface for sorting algorithms." << endl;
    cout << "It can caculate the times and comparisons of any sorting algorithm" << endl;
    cout << "It can run a sorting algorithm on the given input data or on the data generated automatically with specified size and order." << endl;
    cout << "It can compare two or all sorting algorithms on the given input or on the data generated automatically." << endl;
    cout << "It includes " << SORT_ALGORITHM_NAME.size() << " sorting algorithms:" << endl;
    for(int i = 0; i < SORT_ALGORITHM_NAME.size(); i++){
        cout << " -  " << SORT_ALGORITHM_NAME[i] << endl;
    }
    exit(0);
}

int main(int argc, char **argv) {
    sortInit();
    if (argc == 1 || argc == 2 && !strcmp(argv[1], "-h")) printIntruction();
    if (argc == 2 && !strcmp(argv[1], "-v")) printVersion();
    if (argc == 2 && !strcmp(argv[1], "-i")) printInfo();
    if (argc >= 2 && !strcmp(argv[1], "-e")) {
        cout << "EXPERIMENTAL MODE" << endl;
        cout << "Running experimental..." << endl;
        if(argc == 3) 
            runExperimental(argv[2]);
        else
            runExperimental("console");
        return 0;
    }
    commandRouter(argc, argv);
    return 0;
}