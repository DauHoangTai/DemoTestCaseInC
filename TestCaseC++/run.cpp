#include<iostream>
#include<fstream>
#include<string>
#include<cstring>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

using namespace std;


int child_pid = 0;
void timer_handler(int pid) {
  printf("time is over, child will be killed");
  kill(child_pid, SIGKILL);
  exit(0);
}
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

	signal(SIGALRM, timer_handler);

    pid_t pid = fork();
    child_pid = pid;

    if (pid == 0) { // child process
      while(fri)
      {
        fri.getline(inp, 256);
        if (strlen(inp)) {
          if(sprintf(runStr, "echo %s | ./child >> tmp", inp)){
            system(runStr);
          }
          else
          {
            cout << "Compile Error"<<endl;
            break;
          }
        }
      }
    } else { // parent process
      alarm(5);
      int state;
      waitpid(pid, &state, 0);
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
	cout<< "Point: ";
	cout << (float(count)/desCount)*100 << "%"<<endl;
	remove("tmp");
	return 0;
}
