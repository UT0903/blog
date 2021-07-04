#include <stdio.h>
#include <setjmp.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <assert.h>
#include "scheduler.h"
#define SIGUSR3 SIGWINCH
jmp_buf MAIN_FUNC, SCHEDULER;
struct sigaction act1, act2, act3;
sigset_t newmask, oldmask, pendmask;
int idx, P, Q, T, S, mutex, now;
char arr[10000];
FCB_ptr Current, Head;
int queue[5];
FCB fcb[4];
static void sig_func1(int signo){
	//fprintf(stderr, "in sig_func1 mutex = %d\n", mutex);
	if(sigprocmask(SIG_SETMASK, &newmask, NULL) < 0) fprintf(stderr, "SIG_BLOCK reset error\n");
	printf("ACK\n");
	fflush(stdout);
	if(setjmp(fcb[now - 1].Environment) == 0) longjmp(SCHEDULER, 1);
}
static void sig_func2(int signo){
	//fprintf(stderr, "in sig_func2 mutex = %d\n", mutex);
	if(sigprocmask(SIG_SETMASK, &newmask, NULL) < 0) fprintf(stderr, "SIG_BLOCK reset error\n");
	for(int i = 0; i < 5; i++){
		if(queue[(now + 1 + i) % 5] == 1){
			printf("%d", (now + 1 + i) % 5);
		}
	}
	printf("\n");
	fflush(stdout);
	Current = Current->Previous;
	if(setjmp(fcb[now - 1].Environment) == 0) longjmp(SCHEDULER, 1);
}
void funct_1(int name){
	if(setjmp(fcb[name-1].Environment) == 0) funct_5(name);
	int i, j;
	if(T == 1){
		for(j = 1; j <= P; j++){
			for(i = 1; i <= Q; i++){
				sleep(1);
				arr[idx++] = '1';
			}
		}
	}
	else if(T == 2){
		int cnt = 0;
		for(j = 1; j <= P; j++){
			if(cnt < S && (mutex == 0 || mutex == name)){
				mutex = name;
				cnt++;
				for(i = 1; i <= Q; i++){
					sleep(1);
					arr[idx++] = '1';
				}
			}
			else{
				cnt = 0;
				j--;
				mutex = 0;
				if(setjmp(fcb[name-1].Environment) == 0) longjmp(SCHEDULER, 1);
			}
		}
		mutex = 0;
	}
	else if(T == 3){
		for(j = 1; j <= P; j++){
			if(mutex != 0 && mutex != name){
				j--;
				setjmp(fcb[name-1].Environment);
				if(mutex != 0 && mutex != name){
					queue[name] = 1;
					longjmp(SCHEDULER, 1);
				}
				continue;
			}
			else{
				queue[name] = 0;
				mutex = name;
				//fprintf(stderr, "j = %d mutex = %d\n", j, mutex);
				for(i = 1; i <= Q; i++){
					sleep(1);
					arr[idx++] = '1';
					//fprintf(stderr, "append 1\n");
				}
				now = mutex;
				if(sigpending(&pendmask) < 0) fprintf(stderr, "pending error\n");
				if(sigismember(&pendmask, SIGUSR1) || sigismember(&pendmask, SIGUSR2) || sigismember(&pendmask, SIGUSR3)){
					if(sigismember(&pendmask, SIGUSR2)) mutex = 0;
					sigprocmask(SIG_SETMASK, &oldmask, NULL);
					sigprocmask(SIG_SETMASK, &newmask, NULL);
				}
			}
		}
		// release the lock
		mutex = 0;
		queue[name] = 0;
		// jump back to the scheduler (*)
		// do the longjmp or setjmp
	}
	longjmp(SCHEDULER, -2);
}
void funct_2(int name){
	if(setjmp(fcb[name-1].Environment) == 0) funct_5(name);
	int i, j;
	if(T == 1){
		for(j = 1; j <= P; j++){
			for(i = 1; i <= Q; i++){
				sleep(1);
				arr[idx++] = '2';
			}
		}
	}
	else if(T == 2){
		int cnt = 0;
		for(j = 1; j <= P; j++){
			if(cnt < S && (mutex == 0 || mutex == name)){
				mutex = name;
				cnt++;
				for(i = 1; i <= Q; i++){
					sleep(1);
					arr[idx++] = '2';
				}
			}
			else{
				cnt = 0;
				j--;
				mutex = 0;
				if(setjmp(fcb[name-1].Environment) == 0) longjmp(SCHEDULER, 1);
			}
		}
		mutex = 0;
	}
	else if(T == 3){
		for(j = 1; j <= P; j++){
			if(mutex != 0 && mutex != name){
				j--;
				setjmp(fcb[name-1].Environment);
				if(mutex != 0 && mutex != name){
					queue[name] = 1;
					longjmp(SCHEDULER, 1);
				}
				continue;
			}
			else{
				queue[name] = 0;
				mutex = name;
				//fprintf(stderr, "j = %d mutex = %d\n", j, mutex);
				for(i = 1; i <= Q; i++){
					sleep(1);
					arr[idx++] = '2';
					//fprintf(stderr, "append 2\n");
				}
				now = mutex;
				if(sigpending(&pendmask) < 0) fprintf(stderr, "pending error\n");
				if(sigismember(&pendmask, SIGUSR1) || sigismember(&pendmask, SIGUSR2) || sigismember(&pendmask, SIGUSR3)){
					if(sigismember(&pendmask, SIGUSR2)) mutex = 0;
					sigprocmask(SIG_SETMASK, &oldmask, NULL);
					sigprocmask(SIG_SETMASK, &newmask, NULL);
				}
			}
		}
		// release the lock
		mutex = 0;
		queue[name] = 0;
		// jump back to the scheduler (*)
		// do the longjmp or setjmp
	}
	longjmp(SCHEDULER, -2);
}
void funct_3(int name){
	if(setjmp(fcb[name-1].Environment) == 0) funct_5(name);
	int i, j;
	if(T == 1){
		for(j = 1; j <= P; j++){
			for(i = 1; i <= Q; i++){
				sleep(1);
				arr[idx++] = '3';
			}
		}
	}
	else if(T == 2){
		int cnt = 0;
		for(j = 1; j <= P; j++){
			if(cnt < S && (mutex == 0 || mutex == name)){
				mutex = name;
				cnt++;
				for(i = 1; i <= Q; i++){
					sleep(1);
					arr[idx++] = '3';
				}
			}
			else{
				cnt = 0;
				j--;
				mutex = 0;
				if(setjmp(fcb[name-1].Environment) == 0) longjmp(SCHEDULER, 1);
			}
		}
		mutex = 0;
	}
	else if(T == 3){
		for(j = 1; j <= P; j++){
			if(mutex != 0 && mutex != name){
				j--;
				setjmp(fcb[name-1].Environment);
				if(mutex != 0 && mutex != name){
					queue[name] = 1;
					longjmp(SCHEDULER, 1);
				}
				continue;
			}
			else{
				queue[name] = 0;
				mutex = name;
				//fprintf(stderr, "j = %d mutex = %d\n", j, mutex);
				for(i = 1; i <= Q; i++){
					sleep(1);
					arr[idx++] = '3';
					//fprintf(stderr, "append 3\n");
				}
				now = mutex;
				if(sigpending(&pendmask) < 0) fprintf(stderr, "pending error\n");
				if(sigismember(&pendmask, SIGUSR1) || sigismember(&pendmask, SIGUSR2) || sigismember(&pendmask, SIGUSR3)){
					if(sigismember(&pendmask, SIGUSR2)) mutex = 0;
					sigprocmask(SIG_SETMASK, &oldmask, NULL);
					sigprocmask(SIG_SETMASK, &newmask, NULL);
				}
			}
		}
		// release the lock
		mutex = 0;
		queue[name] = 0;
		// jump back to the scheduler (*)
		// do the longjmp or setjmp
	}
	longjmp(SCHEDULER, -2);
}
void funct_4(int name){
	if(setjmp(fcb[name-1].Environment) == 0) longjmp(MAIN_FUNC, 1);
	int i, j;
	if(T == 1){
		for(j = 1; j <= P; j++){
			for(i = 1; i <= Q; i++){
				sleep(1);
				arr[idx++] = '4';
			}
		}
	}
	else if(T == 2){
		int cnt = 0;
		for(j = 1; j <= P; j++){
			if(cnt < S && (mutex == 0 || mutex == name)){
				mutex = name;
				cnt++;
				for(i = 1; i <= Q; i++){
					sleep(1);
					arr[idx++] = '4';
				}
			}
			else{
				cnt = 0;
				j--;
				mutex = 0;
				if(setjmp(fcb[name-1].Environment) == 0) longjmp(SCHEDULER, 1);
			}
		}
		mutex = 0;
	}
	else if(T == 3){
		for(j = 1; j <= P; j++){
			if(mutex != 0 && mutex != name){
				j--;
				setjmp(fcb[name-1].Environment);
				if(mutex != 0 && mutex != name){
					queue[name] = 1;
					longjmp(SCHEDULER, 1);
				}
				continue;
			}
			else{
				queue[name] = 0;
				mutex = name;
				//fprintf(stderr, "j = %d mutex = %d\n", j, mutex);
				for(i = 1; i <= Q; i++){
					sleep(1);
					arr[idx++] = '4';
					//fprintf(stderr, "append 4\n");
				}
				now = mutex;
				if(sigpending(&pendmask) < 0) fprintf(stderr, "pending error\n");
				if(sigismember(&pendmask, SIGUSR1) || sigismember(&pendmask, SIGUSR2) || sigismember(&pendmask, SIGUSR3)){
					if(sigismember(&pendmask, SIGUSR2)) mutex = 0;
					sigprocmask(SIG_SETMASK, &oldmask, NULL);
					sigprocmask(SIG_SETMASK, &newmask, NULL);
				}
			}
		}
		// release the lock
		mutex = 0;
		queue[name] = 0;
		// jump back to the scheduler (*)
		// do the longjmp or setjmp
	}
	longjmp(SCHEDULER, -2);
}
void funct_5(int name){
	int a[10000];
	switch(name){
		case 0:
			funct_1(name + 1);
		case 1:
			funct_2(name + 1);
		case 2:
			funct_3(name + 1);
		case 3:
			funct_4(name + 1);
	}
}
void Build_link(){
	for(int i = 0; i < 4; i++){
		fcb[i].Next = &fcb[(i + 1) % 4];
		fcb[i].Previous = &fcb[(i + 3) % 4];
		fcb[i].Name = i + 1;
	}
	Current = &fcb[3];
}
int main(int argc, char *argv[]){
	assert(argc == 5);
	P = atoi(argv[1]);
	Q = atoi(argv[2]);
	T = atoi(argv[3]);
	S = atoi(argv[4]);
	Build_link();
	if(T == 3){
		act1.sa_handler = sig_func1;
		act1.sa_flags = 0;
		if(sigaction(SIGUSR1, &act1, NULL) < 0) fprintf(stderr, "SIG1_ERR\n");
		act2.sa_handler = sig_func1;
		act2.sa_flags = 0;
		if(sigaction(SIGUSR2, &act2, NULL) < 0) fprintf(stderr, "SIG2_ERR\n");
		act3.sa_handler = sig_func2;
		act3.sa_flags = 0;
		if(sigaction(SIGUSR3, &act3, NULL) < 0) fprintf(stderr, "SIG3_ERR\n");
		sigemptyset(&newmask); sigaddset(&newmask, SIGUSR1); sigaddset(&newmask, SIGUSR2); sigaddset(&newmask, SIGUSR3);
		sigprocmask(SIG_SETMASK, &newmask, NULL);
		sigemptyset(&oldmask);
	}
	if(setjmp(MAIN_FUNC) == 0) funct_5(0);
	Scheduler();
	
}