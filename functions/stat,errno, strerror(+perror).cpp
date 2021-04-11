/*
	stat 구조체
	stat 함수로 검색한 inode 정보는 stat 구조체에 저장됩니다.
	stat 구조체(struct stat)는 <sys/stat.h> 파일에 정의되어 있으며,
	구조는 다음과 같습니다.

	struct stat {
		dev_t       st_dev;
		ino_t       st_ino;
		mode_t      st_mode;
		nlink_t     st_nlink;
		uid_t       st_uid;
		gid_t       st_gid;
		dev_t       st_rdev;
		off_t       st_size;
		time_t      st_atime;
		time_t      st_mtime;
		time_t      st_ctime;
		blksize_t   st_blksize;
		blkcnt_t    st_blocks;
		char        st_fstype[_ST_FSTYPSZ];
	};
	st_dev: inode가 저장되어 있는 장치의 장치 번호를 저장한다.
	st_ino: 해당 파일의 inode 번호를 저장한다.
	st_mode: 파일의 형식과 접근 권한을 저장한다
	st_nlink: 하드링크의 개수를 저장한다.
	st_uid: 파일 소유자의 UID를 저장한다.
	st_gid: 파일 소유 그룹의 GID를 저장한다.
	st_rdev: 장치 파일이면 주 장치 번호와 부 장치 번호를 저장한다. 장치 파일이 아니면 아무 의미가 없다.
	st_atime: 마지막으로 파일을 읽거나, 실행한 시각을 저장한다. 이때 시각은 1970년 1월 1일 이후의 시간을 초 단위로 저장한다.
	st_mtime: 마지막으로 파일의 내용을 변경(쓰기)한 시각을 저장한다.
	st_ctime: 마지막으로 inode의 내용을 변경한 시각을 저장한다. inode의 내용은 소유자/그룹 변경, 파일 크기 변경, 링크 개수 변경 등을 수행할 때 변경된다.
	st_blksize: 파일의 내용을 입출력할 때 사용하는 버퍼의 크기를 저장한다.
	st_blocks: 파일을 512바이트씩 블록으로 나눈 개수를 저장한다.
	st_fstype: 파일시스템 종류 정보를 저장한다.

	출처: https://12bme.tistory.com/215?category=753165 [길은 가면, 뒤에 있다.]
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

int main(void)
{
	struct stat buf;
	
	printf("%d\n", stat("stat", &buf));

	printf("Inode = %d\n", (int)buf.st_ino);
	printf("Mode = %o\n", (unsigned int)buf.st_mode);
	printf("Nlink = %o\n", (unsigned int)buf.st_nlink);
	printf("UID = %d\n", (int)buf.st_uid);
	printf("GID = %d\n", (int)buf.st_gid);
	printf("SIZE = %d\n", (int)buf.st_size);
	printf("Atime = %d\n", (int)buf.st_atime);
	printf("Mtime = %d\n", (int)buf.st_mtime);
	printf("Ctime = %d\n", (int)buf.st_ctime);
	printf("Blksize = %d\n", (int)buf.st_blksize);
	printf("Blocks = %d\n", (int)buf.st_blocks);
	printf("--------------------\n");
	printf("%d\n", errno);
	printf("%s\n", strerror(errno));
	perror("perror:");
	return (0);
}

// unix.txt 파일이 없으면 값들이 이상하게 나온다. 그러나 출력은 한다.
