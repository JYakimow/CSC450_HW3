#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(void) 
{
    //set num variable
    int num;
    
    //set file to 0
    FILE* f1 = fopen("info.dat", "w");
    fprintf(f1, "%d", 0);
    fclose(f1);
    
    for(int i = 0; i < 2; i++)
    {
        int pid = fork();
        if(pid == 0)
        {
            for(int a = 0; a < 5; a++)
            {
                FILE* fptr = fopen("info.dat", "r");
                int num;
                
                fscanf(fptr, "%d", &num);
                printf("the value is: %d (child)\n", num);
                num++;
                fclose(fptr);
                fptr = fopen("info.dat", "w");
                fprintf(fptr, "%d", num);
                fclose(fptr);
                printf("value increased by 1\n");
                
                //printf("child \n");
                sleep(2);
            }
        }
        else
        {
            wait(NULL);
            
            //this prevents final print from happening twice
            if(i == 1)
            {
                //display
                FILE* fptr = fopen("info.dat", "r");
                int num;
                fscanf(fptr, "%d", &num);
                printf("the value is: %d (parent final read to verify) (final) \n", num);
                fclose(fptr);
            }
            
            return 0;
        }
    }
}
