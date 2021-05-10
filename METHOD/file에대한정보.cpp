#include "Method.hpp"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <iostream>
#include <sys/stat.h>



#include <pwd.h>


using namespace std;

int MethodGET(const char *filename)
{
	int acc = access(filename, R_OK);
	int fd = open(filename, O_RDONLY);
	perror("open: ");
	return (fd);
}

int main()
{
	uid_t id = getuid();
	cout << "id: " << id << endl;

	uid_t process;
	process = getpid();
	cout << "process: " << process << endl;


	gid_t group = getgid();
	cout << "group: " << group << endl;

	// #include <pwd.h>
	struct passwd *user_pw;

	user_pw = getpwuid(id);

	printf( "user name      :%s\n", user_pw->pw_name  );
	printf( "user id        :%d\n", user_pw->pw_uid   );
	printf( "group id       :%d\n", user_pw->pw_gid   );
	printf( "reall name     :%s\n", user_pw->pw_gecos );
	printf( "home directory :%s\n", user_pw->pw_dir   );
	printf( "shell program  :%s\n", user_pw->pw_shell );
	cout << " = = = = = = = = = = = =" << endl;
	

	int status = MethodGET("../test.txt");
	cout << "status: " << status << endl;
	cout << " - - - - - - - - - - --" << endl;
	struct stat buf;
	printf("stat: success == %d\n", stat("../test.txt", &buf));
	cout << "buf.st_gid: " << buf.st_gid << endl;
	cout << (buf.st_mode & S_IRWXU)  << endl;
	cout << (buf.st_mode & S_IRUSR)  << endl;
	cout << (buf.st_mode & S_IWUSR)  << endl;
	cout << (buf.st_mode & S_IXUSR)  << endl;
	cout << (buf.st_mode & S_IRWXG)  << endl;
	cout << (buf.st_mode & S_IRGRP)  << endl;
	cout << (buf.st_mode & S_IWGRP)  << endl;
	cout << (buf.st_mode & S_IXGRP)  << endl;
	cout << (buf.st_mode & S_IRWXO)  << endl;
	cout << (buf.st_mode & S_IROTH)  << endl;
	cout << (buf.st_mode & S_IWOTH)  << endl;
	cout << (buf.st_mode & S_IXOTH)  << endl;

	// S_IRWXU 00700 mask for file owner permissions 
	// S_IRUSR 00400 owner has read permission 
	// S_IWUSR 00200 owner has write permission 
	// S_IXUSR 00100 owner has execute permission 
	// S_IRWXG 00070 mask for group permissions 
	// S_IRGRP 00040 group has read permission 
	// S_IWGRP 00020 group has write permission 
	// S_IXGRP 00010 group has execute permission 
	// S_IRWXO 00007 mask for permissions for others (not in group) 
	// S_IROTH 00004 others have read permission 
	// S_IWOTH 00002 others have write permission 
	// S_IXOTH 00001 others have execute permission
	
	return (1);
}