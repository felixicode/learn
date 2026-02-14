#include "common.h"

void send_message(int msgid, const char *text)
{
	struct message msg = { 0 };

	msg.mtype = 1;
	strncpy(msg.mtext, text, MSG_SIZE - 1);

	if (msgsnd(msgid, &msg, strlen(msg.mtext) + sizeof(long), 0) == -1)
		perror("msgsnd");
	else
		printf("send: %s\n", text);
}

void receive_message(int msgid)
{
	struct message msg;
	if(msgrcv(msgid, &msg, sizeof(msg), 0, 0) == -1)
		perror("msgrcv");
	else
		printf("receive: %s\n", msg.mtext);
}

int main()
{
	int msgid_to_peer, msgid_from_peer;
	char send_buf[MSG_SIZE];

	msgid_to_peer = msgget(QUEUE_B_KEY, IPC_CREAT | 0666);
	msgid_from_peer = msgget(QUEUE_A_KEY, IPC_CREAT | 0666);

	if (msgid_to_peer == -1 || msgid_from_peer == -1) {
		perror("msgget error");
		exit(1);
	}

	for (int i = 0; i < 3; i++) {
		receive_message(msgid_from_peer);

		snprintf(send_buf, MSG_SIZE, "hello A, %d", (i + 1));
		send_message(msgid_to_peer, send_buf);

		sleep(1);
	}

	if (msgctl(msgid_from_peer, IPC_RMID, NULL) == -1)
		perror("clearAerr");
	else
		printf("clearA\n");
	if (msgctl(msgid_to_peer, IPC_RMID, NULL) == -1)
		perror("clearBerr");
	else
		printf("clearB\n");

	return 0;
}
