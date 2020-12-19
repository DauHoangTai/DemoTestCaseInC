#include<iostream>
#include<fstream>
#include<string>
#include<cstring>
using namespace std;

int main(int argc, char *argv[])
{
	ifstream fri(argv[2], ios::in);
	ifstream frd(argv[3], ios::in);
	
	char compileStr[512];
	char inp[256];
	char out[256];
	char des[256];
	char runStr[512];
	int count = 0;
	int desCount = 0;
	
	sprintf(compileStr, "g++ %s -o child", argv[1]);
	system(compileStr);
	
	while(fri)
	{
		fri.getline(inp, 256);
		if (strlen(inp)) {
			sprintf(runStr, "echo %s | ./child >> tmp", inp);
			system(runStr);
		}
	}
	
	ifstream fro("tmp", ios::in);
	
	while(frd)
	{
		fro.getline(out, 256);
		frd.getline(des, 256);
		if (strlen(des)) {
			desCount++;
			if (!(strcmp(des, out))) {
				cout << "OK" << endl;
				count++;
			} else {
				cout << "Fail" << endl;
			}
		}
	}
	cout << (float(count)/desCount)*100 << "%"<<endl;
	remove("tmp");
	return 0;
}
