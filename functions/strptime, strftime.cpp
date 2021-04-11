// http://www.cplusplus.com/reference/clibrary/ctime/strftime/
#include <stdio.h>
#include <time.h>
#include <iostream>
#include <string.h>

using namespace std;

int main() {
	time_t rawtime;
	struct tm* timeinfo;
	char buffer[80];

	cout << time(&rawtime) << endl; // 값이 같음
	cout << rawtime << endl; // 값이 같음

	timeinfo = localtime(&rawtime);

	memset(buffer, 0, 80);
	strftime(buffer, 80, "Now it's %I:%M%p.", timeinfo);
	puts(buffer);

	memset(buffer, 0, 80);
	strptime(buffer, "Now it's %I:%M%p.", timeinfo);
	puts(buffer);
	return 0;
}
