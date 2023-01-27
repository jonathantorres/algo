#include <stdio.h>
#include <string.h>

// a very simple implementation
// of the setbuf function from the IO Standard Library

void Setbuf(FILE *restrict fp, char *restrict buf);

int main(void)
{
    char buf[BUFSIZ];
    memset(buf, 0, BUFSIZ);
    Setbuf(stderr, buf);

    fprintf(stderr, "This is some text\n");
    return 0;
}

void Setbuf(FILE *restrict fp, char *restrict buf)
{
    int mode = _IOFBF;
    if (buf == NULL) {
        mode = _IONBF;
    }
    setvbuf(fp, buf, mode, BUFSIZ);
}
