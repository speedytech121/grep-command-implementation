#include<stdio.h>
#include<regex.h>
#include<sys/types.h>

int main(int argc,char* argv[]){
	FILE *stream;
	char *line=NULL;
	size_t len=0;
	ssize_t nread;
	if(argc<3){
		printf("usage: command pattern file\n");
		return 0;
	}
	regex_t regex;
	int result;
	
	stream=fopen(argv[2],"r");
	if(stream==NULL){
		perror("fopen\n");
		return 0;
	}
	while((nread=getline(&line,&len,stream))!=-1){
		
		result=regcomp(&regex,argv[1],0);
		result=regexec(&regex,line,0,NULL,0);
		if(result==0){
			printf("pattern matched\n");
			return 0;
		}
		else if(result==REG_NOMATCH) printf("patter not matched\n");
		else printf("error occur\n");
		fwrite(line,nread,1,stdout);
	}
	

	fclose(stream);
	
	return 0;
}

