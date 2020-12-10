#include "multi_thread_launch_server.h"

THREAD_RESULT handle_connection(void* psocket) {
	CHECK_IO(psocket, -1, "Empty connection thread data\n");
	SOCKET socket;
	CHECK_IO((socket = *((SOCKET*)psocket)) > 0, -1, "Invalid connection thread data\n");
	sockaddr_in addr;
	socklen_t addr_len = sizeof(addr);
	CHECK_IO(!getpeername(socket, (sockaddr*)&addr, &addr_len), -1, "Error retrieving peer info\n");
    char* str_in_addr = inet_ntoa(addr.sin_addr);
    printf("[%s:%d]>>%s\n", str_in_addr, ntohs(addr.sin_port), "Establish new connection");

	int rc = 1;
    while (rc > 0) {
        LaunchProgRequest request;
		memset(&request, sizeof(request), 0);

		LaunchProgResponse response;
		memset(&request, sizeof(request), 0);

        rc = recv(socket, (char*)&request, sizeof(request), 0);
		compute(&request, &response);
		rc = send(socket, (char*)&response, sizeof(response), 0); //pomenyat' SquareRootResponse i SquareRootRequest v shared tcp include

    }
    close_socket(socket);
    printf("[%s]>>%s", str_in_addr, ntohs(addr.sin_port),"Close incomming connection");
}

LaunchProgResponse* compute(LaunchProgRequest* rq, LaunchProgResponse* rs) {
	//pipe for program location
	char  psBuffer[128] = "";
	FILE   *pPipe;

	/* Run DIR so that it writes its output to a pipe. Open this
	* pipe with read text attribute so that we can read it
	* like a text file.
	*/

	if (!(pPipe = _popen(rq->data, "r"))) {
		strcpy(rs->data, "Cant find programm !");
	}
	else {
		while (!feof(pPipe))
		{
			fgets(psBuffer, 128, pPipe);
				strcat(rs->data, psBuffer);
			memset(psBuffer, 0, sizeof(psBuffer));
		}
		_pclose(pPipe);
	}

	return rs;
}
