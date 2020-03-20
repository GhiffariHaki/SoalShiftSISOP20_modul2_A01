#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <sys/wait.h>

int cekdigit(char* input){
  int i=0;
  for(i; i < strlen(input); i++){
    if(isalpha(input[i])) return 1;
  }
  return 0;
}

int main(int argc, char *argv[]) {

  printf("%s, %s, %s, %s\n", argv[1], argv[2], argv[3], argv[4]);
  int jam,menit,detik;
  // Mengecek apabila argumen sama dengan 4
  if(argc != 5){ //Argumen terakhir untuk NULL
    printf("Harus 4 Argumen!!!\n");
    return 0;
  }

  // Mengecek apabila detik sesuai argumen yang diinginkan
  if(strcmp(argv[1],"*") == 0) detik = 60;
  else if(cekdigit(argv[1])){
    printf("Harus Input Angka 0-59!!\n");
    return 0;
  }
  else {
   detik = atoi(argv[1]);
   if(detik > 23 || detik < 0){
       printf("Harus Input Angka 0-23!!\n");
       return 0;
   }
  }

  // Mengecek apabila menit sesuai argumen yang diinginkan
  if(strcmp(argv[2],"*") == 0) menit = 60;
  else if(cekdigit(argv[2])){
    printf("Harus Input Angka 0-59!!\n");
    return 0;
  }
  else {
   menit = atoi(argv[2]);
   if(menit > 23 || menit < 0){
       printf("Harus Input Angka 0-23!!\n");
       return 0;
   }
  }


  // Mengecek apabila jam sesuai argumen yang diinginkan
  if(strcmp(argv[3],"*") == 0) jam = 24;
  else if(cekdigit(argv[3])){
    printf("Harus Input Angka 0-23!!\n");
    return 0;
  }
  else {
   jam = atoi(argv[3]);
   if(jam > 23 || jam < 0){
       printf("Harus Input Angka 0-23!!\n");
       return 0;
   }
  }

  printf("%d, %d, %d, %s\n", detik, menit, jam, argv[4]);

  // BEGIN CONTOH IMPLEMENTASI DAEMON MODUL
  pid_t pid, sid;        // Variabel untuk menyimpan PID

  pid = fork();     // Menyimpan PID dari Child Process

  /* Keluar saat fork gagal
  * (nilai variabel pid < 0) */
  if (pid < 0) {
    exit(EXIT_FAILURE);
  }

  /* Keluar saat fork berhasil
  * (nilai variabel pid adalah PID dari child process) */
  if (pid > 0) {
    exit(EXIT_SUCCESS);
  }

  umask(0);

  sid = setsid();
  if (sid < 0) {
    exit(EXIT_FAILURE);
  }

  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);
  // END CONTOH IMPLEMENTASI DAEMON MODUL

  while (1) {
    int status;
    time_t rawtime;
    struct tm*info;
    char buffer[80];
    time (&rawtime);

    info = localtime( &rawtime );

    //Print Jam sekarang
    //strftime(buffer,80,"%Y-%m-%d_%H:%M:%S", info);
    //printf("Jam Sekarang : %s",buffer);

    //Isi Struct tm : tutorialspoint.com/c_standard_library/c_function_localtime.htm
    if((info->tm_sec == detik || detik == 60 || detik == 0) && (info->tm_min == menit || menit == 60 || menit == 0) &&
(info->tm_hour == jam || jam == 24 || jam == 0)){
	pid_t child_id;
	child_id = fork();

	if(child_id == 0){
	  //CHILD
	  char *bashscr[] = {"bash", argv[4], NULL};
	  execv("/bin/bash", bashscr);
	}
	//PARENT GA NGAPA-NGAPAIN
	else while ((wait(&status)) > 0);
	//Mempunyai Jarak 1 detik
	sleep(1);
    }
  }
}
