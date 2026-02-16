#include "common.h"

int main()
{
	int shmid;
	char *buf;

	shmid = shmget(KEY, SHM_SIZE, IPC_CREAT | 0666);

	if (shmid == -1) {
		perror("failled to shmget");
		return 0;
	}

	printf("shmget ok\n");

	buf = shmat(shmid, NULL, 0);

	while (1) {
		if(buf[0] == '\0')
			printf("empty\n");
		else
			printf("%s\n", buf);
		if (strstr(buf, "bye"))
			break;
		sleep(1);
	}

	shmdt(buf);

	/* remove share memory explictly, since it will not be removed when process exit */
	shmctl(shmid, IPC_RMID, 0);

	return 0;
}
