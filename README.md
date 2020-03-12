# SoalShiftSISOP20_modul2_A01

Mochamad Haikal Ghiffari - 05111840000095

# Soal1

Soal : Buatlah program C yang menyerupai crontab untuk menjalankan script bash dengan
ketentuan sebagai berikut:
a. Program menerima 4 argumen berupa:
i. Detik: 0-59 atau * (any value)
ii. Menit: 0-59 atau * (any value)
iii. Jam: 0-23 atau * (any value)
iv. Path file .sh
b. Program akan mengeluarkan pesan error jika argumen yang diberikan tidak
sesuai
c. Program hanya menerima 1 config cron
d. Program berjalan di background (daemon)
e. Tidak boleh menggunakan fungsi system()

# Jawaban

A. Dalam bagian ini, kita harus memastikan bahwa program menerima 4 argumen serta sesuai dengan apa yang kita inginkan. Oleh karena itu, dibuat beberapa error handling untuk mewujudkan hal tersebut. Contohnya :
```
  // Mengecek apabila argumen sama dengan 4
  if(argc != 5){ //Argumen terakhir untuk NULL
    printf("Harus 4 Argumen!!!\n");
    return 0;
  }
  ```
Dalam potongan kode ini, kami memastikan bahwa argumen yang dimasukan berisi 5 argumen yang ditandai dengan argc (Argumen yang terakhir merupakan NULL). Oleh karena itu, jika argumen tidak sama dengan 5 program tidak akan berjalan dan memberitahu bahwa user hanya bisa memberikan 4 argumen.
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
Setelah itu, kami memastikan bahwa argumen untuk detik merupakan angka dan berada dalam range 0-59. Untuk memastikan itu, kami membuat suatu fungsi yang dinamakan cekdigit. Fungsi cekdigit berbentuk sebagai berikut:
```
int cekdigit(char* input){
  int i=0;
  for(i; i < strlen(input); i++){
    if(isalpha(input[i])) return -1;
  }
  return 1;
}
```
Fungsi cekdigit dibangun agar dapat dipakai dalam error handling untuk argumen detik,menit,jam. - NICO LANJUTIN JANGAN NGELIVE NJIR
