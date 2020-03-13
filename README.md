# SoalShiftSISOP20_modul2_A01

Mochamad Haikal Ghiffari - 05111840000095
Nikodemus Siahaan - 05111840000151

# Soal1

Source code : [soal1.c](https://github.com/GhiffariHaki/SoalShiftSISOP20_modul2_A01/blob/master/soal1/soal1.c)

Soal : Buatlah program C yang menyerupai crontab untuk menjalankan script bash dengan
ketentuan sebagai berikut:
a. Program menerima 4 argumen berupa:
i. Detik: 0-59 atau * (any value)
ii. Menit: 0-59 atau * (any value)
iii. Jam: 0-23 atau * (any value)
iv. Path file .sh
b. Program akan mengeluarkan pesan error jika argumen yang diberikan tidak sesuai
c. Program hanya menerima 1 config cron
d. Program berjalan di background (daemon)
e. Tidak boleh menggunakan fungsi system()

# Jawaban

A. Soal : Program menerima 4 argumen berupa detik, menit, jam, path file.
Dalam Soal ini, diberi tahu constraint dan argumen-argumen yang akan digunakan untuk soal-soal sebelumnya.

B. Soal : Program akan mengeluarkan pesan error jika argumen yang diberikan tidak sesuai.
Maksud dari soal ini yang kami tangkap adalah kami memastikan bahwa argumen untuk detik,menit,jam merupakan angka dan berada dalam suatu range. Untuk memastikan argumen berisi angka, kami membuat suatu fungsi yang dinamakan cekdigit. Fungsi cekdigit berbentuk sebagai berikut:
```
int cekdigit(char* input){
  int i=0;
  for(i; i < strlen(input); i++){
    if(isalpha(input[i])) return -1;
  }
  return 1;
}
```
Fungsi cekdigit dibangun agar dapat dipakai dalam error handling untuk argumen detik,menit,jam. Setelah dibuat fungsi cekdigit, kami membuat if-else yang menyaring range detiknya. Pertama kami membuat if untuk mengecek apakah argumen sama dengan * dan jika sesuai detik akan dimasukkan nilai yang diluar range yang akan digunakan pada if berikutnya. Setelah itu, kami memasukkan argumen kedalam cekdigit. Jika cekdigit memiliki nilai true, program akan berhenti dan memberitahu user argumen yang benar. Dan jika cekdigit memiliki nilai false, argumen akan dicek apakah detik/menit/jam sesuai dengan range yang ditentukan. Contoh implementasinya adalah sebagai berikut : 
 ```
  // Mengecek apabila detik sesuai argumen yang diinginkan
  if(strcmp(argv[1],"*") == 0) detik = 60;
  else if(cekdigit(argv[1])){
    printf("Harus Input Angka 0-59!!\n");
    return 0;
  }
  else{
    detik = atoi(argv[1]);
    if(detik > 59 || detik < 0){
      printf("Harus Input Angka 0-59!!\n");
      return 0;
    }
  }
```
Setelah itu, dibuat error-handling untuk menit & jam yang dibentuk mirip dengan error-handling untuk detik.

C. Soal : Program hanya memiliki 1 config cron.
Program hanya memiliki 1 config cron berarti program hanya akan menerima 1 set argumen. Oleh karena itu, dibuatlah error handling pada argumen agar hanya dapat menerima 4 argumen. Contoh implementasinya adalah sebagai berikut :
```
  // Mengecek apabila argumen sama dengan 4
  if(argc != 5){ //Argumen terakhir untuk NULL
    printf("Harus 4 Argumen!!!\n");
    return 0;
  }
```
Dalam potongan kode ini, kami memastikan bahwa argumen yang dimasukan berisi 5 argumen yang ditandai dengan argc (Argumen yang terakhir merupakan NULL). Oleh karena itu, jika argumen tidak sama dengan 5 program tidak akan berjalan dan memberitahu bahwa user hanya bisa memberikan 4 argumen.

D. Soal : Program berjalan di background (daemon).
Prgoram untuk menjalankan bash berjalan di daemon. Untuk pengimplementasiannya, kami menggunakan contoh implementasi dari modul sisop dan menuliskan program untuk run suatu bash. Implementasi program adalah sebagai berikut :
```
while (1) {
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
    if((info->tm_sec == detik || detik == 60) && (info->tm_min == menit || menit == 60) && (info->tm_hour == jam || jam == 24)){
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
```
Awalnya kami mendapatkan time dari system menggunakan fungsi localtime. Setelah itu dicek apakah argumen sesuai dengan waktu sekarang atau argumen merupakan * yang nantinya auto TRUE. Setelah itu, masuk kedalam proses yang menjalankan bashscript. Program menggunakan execv & wait agar tidak adanya Zombie Process. Proses tersebut diberi jeda `sleep(1)` sesuai dengan soal (1 Detik). Dan bash yang kami gunakan merupakan bashsoal1.sh yang diupload di dalam directory yang sama dengan sourcecode.

Kendala : Sebelum debugging, banyak munculin Zombie Process

E. Soal : Tidak boleh menggunakan fungsi system()
Kelihatan lah ya gak pake fungsi system :v
