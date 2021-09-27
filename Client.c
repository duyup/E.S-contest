#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

#define  BUF_SIZE   1024
void error_handling(char *message);

int main( int argc, char *argv[])
{
   char send_socket[BUF_SIZE]= {0,};
   int sock,j,i, k;
   char message[BUF_SIZE];
   char buf[BUF_SIZE];
   char buff[256];

   struct sockaddr_in serv_adr;
   FILE *fp;
   FILE *fp1;
   if(argc != 3) {
      printf("Usage : %s <IP> <PORT>\n", argv[0]);
      exit(1);
   }
   
   sock= socket( PF_INET, SOCK_STREAM, 0); // 소켓 생성
   if( -1 ==sock)
      error_handling("socket() error");

   memset( &serv_adr, 0, sizeof( serv_adr)); // memset 함수 초기화
   serv_adr.sin_family     = AF_INET;
   serv_adr.sin_addr.s_addr= inet_addr(argv[1]);
   serv_adr.sin_port       = htons(atoi(argv[2]));
  

   if( -1 == connect(sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr) ) ) //connect 함수 호출
   {
      printf( "접속 실패\n");
      exit( 1);
   }
   
   
   while(1){
      fp = fopen("object.txt","r"); // 읽기 모드로 TXT파일을 열기
      fscanf(fp, "%s",message); // TXT파일내 문장을 읽기
      //printf("MES : %s",message);
      fclose(fp); // 파일닫기
      if(strcmp(message,send_socket)==0)
      {
      	continue;
      }
      else{         
         strcpy(send_socket,message); // message의 문장을 send_socket으로 붙여넣기
         printf("SEND : %s\n", send_socket); // 보낸 메세지를 표시
         write(sock,message,sizeof(message)-1); //write 함수를 통해 데이터 송신
         sleep(0.5);
      }
      for (j = 0; j < 100; j++) 
         {
         message[j] = 0; //100글자까지 초기화, 문장이 반복되는것을 방지
	      }
   }
   close(sock);
   return 0;
}

void error_handling(char *message)
{
   fputs(message,stderr);
   fputc('\n',stderr);
   exit(1);
}
