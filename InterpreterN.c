#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main()
{
	char fname[40];
	char foutname[40];
	char arr[50];
	printf("enter 32bit input file\n");
	scanf("%s",fname);
	printf("enter name of outpur file\n");
	scanf("%s",foutname);

	FILE *fp = fopen ( fname, "r" );
	FILE *fpw = fopen ( foutname, "w" );
	if ( fp != NULL )
	{
      	char line [256];
     	while ( fgets(line,sizeof line,fp) != NULL ) /* read a line */
      	{
		if(strstr(line,"pushl")!=NULL)
		{
			strcpy(arr,"pushq	%rbp\n");
			fprintf(fpw,"%s",arr);
		}
		else if(strstr(line,"cfa_offset")!=NULL)
		{
			strcpy(arr,".cfi_def_cfa_offset 8\n");
				fprintf(fpw,"%s",arr);
		}
		else if(strstr(line,"cfi_offset")!=NULL){
		strcpy(arr,".cfi_offset 6 , -16\n");
				fprintf(fpw,"%s",arr);
		}
		else if(strstr(line,"movl	%esp, %ebp")!=NULL)
		{
		strcpy(arr,"movq	%rsp, %rbp\n");
		fprintf(fpw,"%s",arr);
		}
		else if(strstr(line,"_cfa_register 5")!=NULL)
		{strcpy(arr,".cfi_def_cfa_register 6\n");
		fprintf(fpw,"%s",arr);
		}


		else if(strstr(line,"andl	$-16, ")!=NULL)
		{
		continue;
		}
		else if(strstr(line,"subl	$16")!=NULL)
		{
		continue;

		//	continue;
		}
		else if(strstr(line,"$.LC0")!=NULL)
		{

		 strcpy(arr,"movl	$.LC0, %edi \n");
        fprintf(fpw,"%s",arr);
		}
		else if(strstr(line,"leave")!=NULL)
		{
		strcpy(arr,"popq	%rbp\n");
		fprintf(fpw,"%s",arr);
		}
		else if(strstr(line,"cfi_restore")!=NULL)
		{}
		else if(strstr(line,"cfi_def_cfa "))
		{
		strcpy(arr,".cfi_def_cfa 7, 8\n");
		fprintf(fpw,"%s",arr);
		}
		else
		fprintf(fpw,"%s",line);
	        /* write the line */

}
     	fclose ( fp );
   }
   else
   {
      perror ( fname ); /* why didn't the file open? */
   }

}
