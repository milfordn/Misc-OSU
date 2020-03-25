#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <dirent.h>
#include <signal.h>
#include <fcntl.h>

#include "linklist.h"

#define PROMPT_LEN_MAX 2048
#define ARGS_LEN_MAX 512
#define STATUS_LEN 64

// I know this is non-reentrant (thanks strlen)
int autowrite(int fp, char * data){
	write(fp, data, strlen(data));
}

int prompt(char * show, char * result, int reslen){
S_prompt: autowrite(1, show);
	memset(result, '\0', reslen);
	int numread = getline(&result, &reslen, stdin);

	//try again if interrupted
	if(numread == -1) goto S_prompt; //I'm so sorry, but it works
	if(numread == 0) exit(0); //end of file reached

	result[numread-1] = '\0';//remove new line
	return numread;
}

//change foreground-only mode, write a message
char isFGonly = 0;
void toggleFGOnly(int i){
	if(isFGonly)
		write(1, "\nExiting foreground-only mode\n", 30);
	else
		write(1, "\nEntering foreground-only mode\n", 31);

	isFGonly = !isFGonly;
}

//returns true if the command should be run as a background process
int isBackground(char * input){
	while(*(++input));
	return *(input - 1) == '&';
}

void parseCommand(char * input, char ** argslist){
	const char del[2] = " ";
	
	char * token;

	//get next space delimited argument
	for(token = strtok(input, del); token; token = strtok(NULL, del)){
		//copy that argument to the argslist array
		*(argslist++) = token;
	}
	//mark last argument with null
	*(argslist) = NULL;
}

#define REDIR_FI 1
#define REDIR_FO 2
int getFileRedirects(char ** argslist, int * fpin, int * fpout){
	int outValue = 0;

	char ** c;
	//loop through all arguments
	for(c = argslist; *c; c++){ //insert c++ joke here
		if(**c == '<'){ //stdin redirect operator
			*fpin = open(*(c+1), O_RDONLY); //set parameter to new file pointer
			outValue |= REDIR_FI;
			*c = NULL; //fix argument list for exec

			if(*fpin < 0){
				return -(int)(*(c+1));
			}
		}
		else if(**c == '>'){ //stdout redirect operator
			*fpout = open(*(c+1), O_WRONLY | O_TRUNC | O_CREAT, 0666); //set parameter to new file pointer
			outValue |= REDIR_FO;
			*c = NULL;

			if(*fpout < 0){
				return -(int)(*(c+1));
			}
		}
	}

	return outValue;
}

//put the PID wherever a $$ is located
void addPID(char * input, int parentPID){
	char temp[PROMPT_LEN_MAX];
	char * loc = strstr(input, "$$");
	if(!loc) return;

	//replace $$ with %d and sprintf
	loc[0] = '%'; loc[1] = 'd';
	sprintf(temp, input, parentPID);
	strcpy(input, temp);
	printf(input);
}

//find out motive, means, and opportunity of the killing.
int autopsy(int exitMethod, char * buffer){
	int val;
	char * format;

	if(WIFEXITED(exitMethod)){
		val = WEXITSTATUS(exitMethod);
		format = "exit value %d\n";
	}
	else if(WIFSIGNALED(exitMethod)){
		val = WTERMSIG(exitMethod);
		format = "terminated by signal %d\n";
	}
	else format = "oh shit we fucked up";

	sprintf(buffer, format, val);
	return val;
}

//change working directory to arg.
//Ignore cur, it's left over.
int cd(char * cur, char * arg){
	char fullpath[4096]; //max path length as defined by Unix

	if(!arg || *arg == '~'){
		char * homePath = getenv("HOME");
		if(arg) arg++; //skip ~ character
		strcpy(fullpath, homePath); //replace with home
		if(arg) strcat(fullpath, arg); //add next part of path
	}
	else strcpy(fullpath, arg); //else just use the raw argument
	
	char * last = fullpath + strlen(fullpath) - 1;
	if(*last == '/') *last = '\0'; //get rid of last directory slash for consistency

	DIR *d;
	d = opendir(fullpath);

	if(d){ //dir is not null, so we can assume it exists
		strcpy(cur, fullpath);
		chdir(fullpath);
		closedir(d);
		return 1;
	}
	else{ //dir is null, assumed to not exist
		autowrite(1, "cd: ");
		autowrite(1, fullpath);
		autowrite(1, ": No such file or directory\n");
		return 0;
	}
}

//check in on background processes, collect bodies if necessary
int reapBG(struct LList *l, char * buffer){
	int rVal = 0;

	//no processes? no problem.
	if(isEmptyLL(l)) return 0;

	struct Llink *k = l->start->next;
	struct Llink *kprev = l->start;
	for(; k; kprev = k, k = k->next){
		int pid = k->value;
		int cexit = 0;

		//check if process is kill
		if(!waitpid(pid, cexit, WNOHANG)) continue;

		//remove process from structure, indicate that we removed something
		rmNextLink(kprev);
		rVal = 1;

		//create and add message to buffer
		char tempStat[STATUS_LEN];
		sprintf(tempStat, "background pid %d is done: ", pid);
		strcat(buffer, tempStat);
		autopsy(cexit, tempStat);
		strcat(buffer, tempStat);
	}

	return rVal;
}

//just fill signal structures with stuff
void setupSignals(struct sigaction * SIGSTOP_action, struct sigaction * ignore_action, struct sigaction *default_action){
	SIGSTOP_action->sa_handler = toggleFGOnly;
	sigfillset(&SIGSTOP_action->sa_mask);
	SIGSTOP_action->sa_flags = 0;

	ignore_action->sa_handler = SIG_IGN;
	default_action->sa_handler = SIG_DFL;

	sigaction(SIGTSTP, SIGSTOP_action, NULL);
	sigaction(SIGINT, ignore_action, NULL);
}

int main(int argc, char * argv[]){

	// ----- DECLARATIONS -----
	
	char input[PROMPT_LEN_MAX];
	char * args[ARGS_LEN_MAX];
	char bgstatus[STATUS_LEN * 8];
	char status[STATUS_LEN];
	char curPath[4096];
	int parentPID;
	int devnull;

	struct sigaction SIGSTOP_action = {0}, ignore_action = {0}, default_action = {0};
	struct LList * procLL;

	// ----- INITIALIZATION -----

	parentPID = getpid();
	getcwd(curPath, sizeof(curPath));
	setupSignals(&SIGSTOP_action, &ignore_action, &default_action);
	devnull = open("/dev/null", O_RDWR);
	memset(bgstatus, '\0', sizeof(bgstatus));

	procLL = malloc(sizeof(struct LList));
	initLL(procLL);

	// ----- MAIN LOOP -----

	while(1){

		if(reapBG(procLL, bgstatus)){
			autowrite(1, bgstatus);
			memset(bgstatus, '\0', sizeof(bgstatus));
		}

		prompt(": ", input, PROMPT_LEN_MAX);
		
		char * token, * del = "\n";

		// ----- BUILT IN COMMANDS -----
	
		if(*input == '#' || *input == '\0'){ //command is comment or empty
			continue;
		}	
		else if(!strcmp(input, "exit")){ //command is exit
			break;
		}
		else if(!strncmp(input, "status", 6)){ //command is status
			autowrite(1, status);
			continue;
		}
		else if(!strncmp(input, "cd", 2)){ //command is cd *
			parseCommand(input, args);
			cd(curPath, args[1]);
			continue;
		}

		// ----- EXTERNAL COMMANDS -----

		int pid;
		if(pid = fork()){ //parent
			int cexit;
			
			int mode;
			if(!isFGonly && isBackground(input)){ //background process
				mode = WNOHANG; 
				pushLL(procLL, pid);

				//print background message
				autowrite(1, "background pid is ");
				
				char pidBuffer[6];
				sprintf(pidBuffer, "%d", pid);
				autowrite(1, pidBuffer);
				autowrite(1, "\n");
			}
			else mode = 0;

			waitpid(pid, &cexit, mode);
			autopsy(cexit, status);
		}
		else{ // child
			int isbg = isBackground(input);
			if(isbg){
				//remove last & argument
				input[strlen(input) - 1] = '\0';
			}
			isbg &= !isFGonly;
			if(!isbg){ //is not background COMMAND, or terminal is in foreground-only mode
				sigaction(SIGINT, &default_action, NULL);
			}

			// deal with the command itself
			addPID(input, parentPID);
			parseCommand(input, args);
			
			//redirect files
			int fp_in = 0, fp_out = 0;
			int res = getFileRedirects(args, &fp_in, &fp_out);

			if(res < 0){
				printf("%s: no such file or directory\n", (char *)(-res));
				exit(1);
			}
			else{
				if(fp_in){
					dup2(fp_in, 0);
					close(fp_in);
				}
				else if(isbg){
					dup2(devnull, 0);
				}
					
				if(fp_out){
					dup2(fp_out, 1);
					close(fp_out);
				}
				else if(isbg){
					dup2(devnull, 1);
				}
			}

			//exec
			execvp(args[0], args);

			//exec fails
			autowrite(1, args[0]);
			autowrite(1, ": no such file or directory\n");
			exit(1);
		}
	}

	return 0;
}

