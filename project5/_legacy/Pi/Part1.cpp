/* Simple send and receive C example (line-mode terminal program with local echo) 
* for communicating with the Arduino using /dev/ttyS0. */

#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<termios.h>
#include<string.h>
#include <cstdlib>

int main(){
   int file, count;

   if ((file = open("/dev/ttyS0", O_RDWR | O_NOCTTY | O_NDELAY))<0){
      perror("UART: Failed to open the file.\n");
      return -1;
   }

   struct termios options;

   tcgetattr(file, &options);

   options.c_cflag = B115200 | CS8 | CREAD | CLOCAL;
   options.c_iflag = IGNPAR | ICRNL;
   tcflush(file, TCIFLUSH);
   tcsetattr(file, TCSANOW, &options);

   // send the string plus the null character
  /** if ((count = write(file, argv[1], strlen(argv[1])+1))<0){
      perror("Failed to write to the output\n");
      return -1;
   }*/
    int min =25*1023/500; 
    int max=215*1023/500;
    int send;

   unsigned char receive[100];
    while (1){
        unsigned char receive[100]={0};
   if ((count = read(file, (void*)receive, 100))<0){
      perror("Failed to read from the input\n");
      //return -1;
   }

   if (count==0) printf("There was no data available to read!\n");
   else {
      receive[count]=0;  
      printf("The following was read in [%d]: %s\n",count,receive);
      
      int receiveI = atoi((char*)receive);
        send=receiveI*255/(max-min);
        printf("The PWM value send: %d\n",send);
      write(file, receive, count);
   }
    }
   close(file);
   return 0;
}