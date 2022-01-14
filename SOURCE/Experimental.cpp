#include "Experimental.h"

void makeFull(string &col, int colSize){
    while(col.size() < colSize){
        col += " ";
    }
}
void printResult(string dataOrder, int dataSize, vector<pii> res){
    string AlgorithmColumn = "|     Algorithm     ";
    string TimeColumn = "|     Time(ms)     ";
    string ComparisonsColumn = "|   Comparisons   ";
    string subTitle = AlgorithmColumn + TimeColumn + ComparisonsColumn + "|";
    string splitLine = ""; 
    for(int i = 0; i < subTitle.size(); i++) splitLine += "-";
    string title = "|    DATA ORDER: " + dataOrder;
    makeFull(title, subTitle.size() / 2);
    title += "|    DATA SIZE: " + to_string(dataSize);
    makeFull(title, subTitle.size() - 1);
    title += "|";

    vector<string> line;
    for(int i = 0; i < res.size(); i++){
        string Algorithm = "| " + SORT_ALGORITHM_NAME[i];
        makeFull(Algorithm, AlgorithmColumn.size());
        string Time = "| " + to_string(res[i].first) + "ms";
        makeFull(Time, TimeColumn.size());
        string Comparisons = "| " + to_string(res[i].second);
        makeFull(Comparisons, ComparisonsColumn.size());
        line.push_back(Algorithm + Time + Comparisons + "|");
    }
    cout << splitLine << endl;
    cout << title << endl;
    cout << splitLine << endl;
    cout << subTitle << endl;
    cout << splitLine << endl;
    for(int i = 0; i < line.size(); i++){
        cout << line[i] << endl;
    }
    cout << splitLine << endl;
    cout << endl;
}
vector<int> DATA_SIZE = {10000, 30000, 50000, 100000, 300000, 500000};
// vector<int> DATA_SIZE = {20};

void runExperimental(string printType) {
    auto start = high_resolution_clock::now();
    string file = "experimental";
    if(printType == "csv"){
        file += ".csv";
    }else if(printType == "console"){
        file = "console";
    }else if(printType == "txt"){
        file += ".txt";
    }else{
        cout << "Invalid print type" << endl;
    }
    if(file != "console")
        freopen(file.c_str(), "w", stdout);
    for (int i = 0; i < DATA_ORDER.size(); i++) {
        if(printType != "console")
            cerr << "DATA ORDER: " << DATA_ORDER[i] << endl;
        string subtitleCSV = "DATA ORDER,ALGORITHM,";
        vector<string> algorithmCSV;
        for(int j = 0; j < SORT_ALGORITHM.size(); j++) 
            algorithmCSV.push_back(DATA_ORDER_NAME[i] + "," + SORT_ALGORITHM_NAME[j] +',');
        string titleDataSize = ", DATA SIZE,";
        for (int &dataSize : DATA_SIZE) {
            if(printType != "console")
                cerr << "DATA SIZE: " << dataSize << endl;
            titleDataSize += to_string(dataSize) + ", ";
            titleDataSize += to_string(dataSize) + ", ";
            vector<pii> res;
            subtitleCSV += "TIME(s), COMPARISION,";
            int *arr = new int[dataSize];
            for(int j = 0; j < SORT_ALGORITHM.size(); j++) {
                GenerateData(arr, dataSize, DATA_ORDER[i]);  
                res.push_back(runSort(arr, dataSize, SORT_ALGORITHM[j], "-comp"));
                if(printType == "csv"){
                    double time = res[j].first / 1000.0;
                    algorithmCSV[j] += to_string(time) + ",";
                    algorithmCSV[j] += to_string(res.back().second) + ",";
                }
            }
            delete[] arr;
            if(printType == "txt" || printType == "console")
                printResult(DATA_ORDER_NAME[i], dataSize, res);
        }
        if(printType == "csv"){
            cout << titleDataSize << endl;
            cout << subtitleCSV << endl;
            for(int j = 0; j < algorithmCSV.size(); j++){
                cout << algorithmCSV[j] << endl;
            }
            cout << endl;
        }
    }
    fclose(stdout);
    freopen ("/dev/tty", "a", stdout);
    cout << "Experimental finished." << endl;
    cout << "Output file: " << file << endl;
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<seconds>(stop - start);
    cout << "Time: " << duration.count() << "s" << endl;
    exit(0);
}