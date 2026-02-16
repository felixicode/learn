#include "common.h"

int main()
{
	int shmid, num = 0;
	char *buf;

	shmid = shmget(KEY, SHM_SIZE, IPC_CREAT | 0666);

	if (shmid == -1) {
		perror("failled to shmget");
		return 0;
	}

	printf("shmget ok\n");

	buf = shmat(shmid, NULL, 0);

	while(num <= 10) {
		num++;
		sprintf(buf + strlen(buf), "%d ", num);
		sleep(2);
	}

	sprintf(buf + strlen(buf), "bye");
	shmdt(buf);

	return 0;
}
