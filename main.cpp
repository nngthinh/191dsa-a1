#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <cstring>
#include <sstream>
#include <math.h>

#include "dsaLib.h"
#include "dbLib.h"
#include "processData.h"

using namespace std;

int main() {
    Initialization();

    void*   pData = nullptr;
    void*   pOutput = nullptr;
    int     N;

	clock_t a, b; // Added
	a = clock(); // Added
    LoadData(pData);
	b = clock(); // Added
	cout << "Time:" << (double)(b - a) / CLOCKS_PER_SEC << endl; // Added
    assert(pData != nullptr);
    cout << fixed << setprecision(8);
    string req;
    while (true) {
        req = "";
        getline(cin, req);
        if (cin.bad()) {
            cin.clear();
            cin.ignore(1024, '\n');
            continue;
        }
        if (req == "Exit") {
            break;
        }
		a = clock(); // Added
        ProcessRequest(req.data(), pData, pOutput, N);
		b = clock(); // Added
		PrintReqOutput<int>(req.data(), (int*)pOutput, N);
        delete [] (int*)pOutput;
        pOutput = nullptr;
		cout << "\nTime:" << (double)(b - a) / CLOCKS_PER_SEC << endl; // Added
    }

    ReleaseData(pData);
    Finalization();
    return 0;
}