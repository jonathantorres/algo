#include <errno.h>
#include <shadow.h>
#include <stdio.h>
#include <stdlib.h>

// a very simple program to print the shadow password
// of the provided user name in the system
// this program required adminstrative privileges

int main(void)
{
    struct spwd *ptr = NULL;

    if ((ptr = getspnam("jonathan")) == NULL) {
        perror("getspnam error");
        exit(EXIT_FAILURE);
    }
    printf("sp_pwdp = %s\n", ptr->sp_pwdp == NULL || ptr->sp_pwdp[0] == 0 ? "(null)" : ptr->sp_pwdp);
    return 0;
}

