/*
 * The MIT License
 *
 * Copyright 2017 Sébastien Serre <sserre at msha.fr>.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

/*
 * File:   oaih.c
 * Author: Sébastien Serre <sserre at msha.fr>
 *
 * Created on 27 février 2017, 16:58
 */


#include <stdio.h>
#include <stdlib.h>
#include <cargo.h>
#include <task.h>
#include <sys/socket.h>

#define STACK_SIZE 32768

void
dialtask(void *v) {
    int fd, remotefd;
    if ((remotefd = netdial(TCP, "www.example.com", 80)) < 0) {
        close(fd);
        return;
    }

    printf("Succefuly opened tcp socket");
    shutdown(fd, SHUT_RDWR);
    close(fd);
}

/*
 *
 */
void
taskmain(int argc, char** argv) {

    taskcreate(dialtask, NULL, STACK_SIZE);

    printf("end of main fun\n");

}