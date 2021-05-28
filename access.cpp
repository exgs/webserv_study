#include <iostream>
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>

using namespace std;

namespace ft
{
	bool access(std::string absolute_path, int temp);
	bool isFilePath(const std::string &path);
	bool isDirPath(const std::string &path);
}

bool ft::isFilePath(const std::string &path)
{
	struct stat info;

	if (stat(path.c_str(), &info) == 0)
	{
		if (S_ISREG(info.st_mode))
			return 1;
		else
			return 0;
	}
	else
		return 0;
}

/*
 * isDirPath : path가 directory path인지 체크하는 함수
 * @param  {std::string} path : 경로
 * @return {bool}             : 1 : 폴더 경로, 0 : 폴더 경로 x
 */
bool ft::isDirPath(const std::string &path)
{
	struct stat info;

	if (stat(path.c_str(), &info) == 0)
	{
		if (S_ISDIR(info.st_mode))
			return 1;
		else
			return 0;
	}
	else
		return 0;
}

bool ft::access(std::string absolute_path, int temp)
{
	if (ft::isDirPath(absolute_path) == true)
	{
		DIR *dir;
		dir = opendir(absolute_path.c_str());
		closedir(dir); // NOTE 추가함
		if (dir == NULL)
			return (false);
		else
			return (true);
	}
	else if (ft::isFilePath(absolute_path) == true)
	{
		int fd = open(absolute_path.c_str(), 0);
		close(fd);
		if (fd == -1)
			return (false);
		else
			return (true);
	}
	return (false);
}

int main()
{
	int ret;
	errno = 0;
	cout << " ---------------------file--------------------- " << endl;
	ret = ft::access("./file", F_OK);
	cout << "ret: " << ret << endl;
	perror("perror: "); // NOTE 20 Not a directory
	errno = 0;
	ret = ft::access("./file/", F_OK);
	cout << "ret: " << ret << endl;
	perror("perror: ");

	errno = 0;
	ret = ft::access("./file2/", F_OK);
	cout << "ret: " << ret << endl;
	perror("perror: "); // NOTE 2 NO such file or directory

	cout << " ---------------------directory--------------------- " << endl;

	errno = 0;
	ret = ft::access("./directory", F_OK);
	cout << "ret: " << ret << endl;
	perror("perror: ");
	errno = 0;
	ret = access("./directory/", F_OK);
	cout << "ret: " << ret << endl;
	perror("perror: ");
	cout << "hello world" << endl;
	return (1);
}