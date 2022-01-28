#include "header.h"

struct msghdr msg;
struct iovec iov[1];

static void reset(void) {
	common_reset(1);

	memset(&msg, 0, sizeof(msg));
	memset(iov, 0, sizeof(iov));

	iov[0].iov_base = buffer;
	iov[0].iov_len = BUFCAP;
	msg.msg_iov = &iov[0];
	msg.msg_iovlen = 1;
}

int main(void) {
	int retval;

	init();
	printf("init finished\n");

	// epoll_ctl on a not valid fd
	//

	epoll_ctl(epfd, EPOLL_CTL_MEMO, accept_fd, &event);
	printf("epoll_ctl_memo registered\n");

	// epoll_memo on a not valid epfd
	//

	// recv doesn't block, epoll_memo not executed
	reset();
	if (write(connect_fd, DATA, DATASZ) == -1) // write in advance so that read doesn't block
		errExit("write connect_fd");
	retval = recvmsg(accept_fd, &msg, 0);
	printf("buffer is %s\n", buffer);
	assert_retval(retval, DATASZ, 0, "recv");
	retval = epoll_ctl(epfd, EPOLL_CTL_ADD, accept_fd, &event);
	assert_retval(retval, 0, 0, "epoll_ctl_try_add"); // should not already been added

	// recv blocks, epoll_memo executed
	reset();
	retval = recvmsg(accept_fd, &msg, 0);
	assert_retval(retval, 0, 0, "read_epoll_ctl");
	retval = epoll_ctl(epfd, EPOLL_CTL_ADD, accept_fd, &event);
	assert_retval(retval, -1, EEXIST, "epoll_ctl_try_add"); // should already been added

	// recv blocks, epoll_memo executed, epfd not valid
	//

	finish();

	return 0;
}



