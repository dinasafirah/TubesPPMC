#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*-------------------------------------------------------------------------------------------------------------------------------*/
// deklarasi vairabel, tipe data, fungsi dan procedure
typedef struct {
    char matkul[6], rombongan;
    int nomor;
} praktikum_t;

typedef struct {
    char asisten1, asisten2;
} asisten_t;

typedef struct {
    int minggu;
    char hari[10];
} rule_t;

praktikum_t arrJadwal[12][5][4];
asisten_t arrAsisten[12][5][4];
praktikum_t LAB1[12][5], LAB2[12][5], LAB3[12][5], LSS[12][5];

//fungsi rule checker
int ruleCheck(FILE fRule, praktikum_t arrJadwal[12][5][4], asisten_t arrAsisten[12][5][4]);
//fungsi konversi hari
int konversiHari (char str[]);
//fungsi konversi ruang
int konversiRuang (char str[5]);
//fungai validasi asisten
int validasiAsisten(char str, int minggu, int hari, int ruang, praktikum_t arrJadwal[12][5][4]);
//procedure menampilkan status asisten
void statusAsisten(asisten_t arrAsisten[12][5][4]);
//procedure assign asisten manual
void assignAsisten(asisten_t arrAsisten[12][5][4], praktikum_t arrJadwal[12][5][4]);
//procedure menampilkan schedule sementara
void tampilSchedule(praktikum_t arrJadwal[12][5][4]);
//procedure schedule manual
void scheduleManual(praktikum_t arrJadwal[12][5][4]);
/*---------------------------------------------------------------------------------------------------------------*/
//MAIN PROGRAM
int main()
{
    FILE *fileJadwal, *fileAsisten, *fileRule;
    char namaFile[80], line[100];
    int kode, i, j, k, l, minggu = 0, hari = 0;
    char* token = NULL;
    char arrHari[5][6] = {"Senin", "Selasa", "Rabu", "Kamis", "Jumat"};
    praktikum_t arrJadwal[12][5][4];
    asisten_t arrAsisten[12][5][4];
    
    printf("Menu: \n");
    printf("    1. Buat Proyek Baru\n");
    printf("    2. Muat Proyek dari Berkas\n");
    printf("    3. Keluar\n");
    printf("Masukan : "); scanf("%d", &kode);
    
    //validasi input menu
    while (kode > 3 || kode < 1)
    {
        printf("Masukan salah, silahkan ulangi");
        printf("Menu: \n");
        printf("    1. Buat Proyek Baru\n");
        printf("    2. Muat Proyek dari Berkas\n");
        printf("    3. Keluar\n");
        printf("Masukan : "); scanf("%d", &kode);
    }
    
    switch(kode)
    {
        case 1:
            //Membuat proyek baru
            printf("====== Membuat Proyek Baru ======\nMasukkan nama proyek:");
            scanf("%s", namaFile);
            fileJadwal = fopen(strcat(namaFile, "_rombongan.csv"), "w+");
            fileAsisten = fopen(strcat(namaFile, "_asisten.csv"), "w+");
            //inisialisasi array
            for (i=1; i<=12; i++)
            {
                for (j=1; j<=5; j++)
                {
                    for (k=1; k<=4; k++)
                    {
                        for (l=1; l<=6; l++)
                        {
                            arrJadwal[i][j][k].matkul[l] = NULL;
                        }
                        arrJadwal[i][j][k].nomor = NULL;
                        arrJadwal[i][j][k].rombongan = NULL;
                        arrAsisten[i][j][k].asisten1 = NULL;
                        arrAsisten[i][j][k].asisten2 = NULL;
                        
                    }
                }
            }
            
            printf("[Menu Utama]\nPilih Mode:\n1. Tampilkan Schedule\n2. Schedule Manual\n3. Tampilkan Status Assignment Asisten\n");
            printf("4. Assign Asisten Manual\n5. Schedule Otomatis\n6. Assign Otomatis\n7. Rule Checker\n8. Simpan Proyek dan Keluar\n");
            printf("Pilih Mode : ");
            scanf("%d", &kode);
            //validasi input untuk menu utama
            
            while ((kode < 1) || (kode >8))
            {
                printf("Masukan salah. Masukan pilihan menu ulang");
                printf("[Menu Utama]\nPilih Mode:\n1. Tampilkan Schedule\n2. Schedule Manual\n3. Tampilkan Status Assignment Asisten\n");
                printf("4. Assign Asisten Manual\n5. Schedule Otomatis\n6. Assign Otomatis\n7. Rule Checker\n8. Simpan Proyek dan Keluar\n");
                printf("Pilih Mode : ");
                scanf("%d", &kode);
            }
            while (kode != 8)
            {
                switch(kode)
                {
                    case 1:
                        //tampilkan schedule
                        tampilSchedule(arrJadwal);
                        break;
                    case 2:
                        //schedule manual
                        scheduleManual(arrJadwal);
                        break;
                    case 3:
                        //Tampilkan Status Assignment Asisten
                        statusAsisten(arrAsisten);
                        break;
                    case 4:
                        //Assign Asisten Manual
                        assignAsisten(arrAsisten, arrJadwal);
                        break;
                    case 5:
                        //Schedule Otomatis
                        printf("fitur belum tersedia");
                        break;
                    case 6:
                        //Assign Otomatis
                        printf("fitur belum tersedia");
                        break;
                    case 7:
                        //Rule Checker
                        printf("[DRC]\nMasukkan File DRC (dalam format .txt):");
                        scanf("%s", namaFile);
                        fileRule = fopen(strcat(namaFile,".txt"), "r");
                        while (fileRule==NULL){
                            printf("Masukan file salah, coba masukan kembali");
                            printf("[DRC]\nMasukkan File DRC (dalam format .txt):");
                            scanf("%s", namaFile);
                            fileRule = fopen(strcat(namaFile,".txt"), "r");
                        }
                        ruleCheck(*fileRule, arrJadwal, arrAsisten);
                        fclose(fileRule);
                        break;
                }
                printf("[Menu Utama]\nPilih Mode:\n1. Tampilkan Schedule\n2. Schedule Manual\n3. Tampilkan Status Assignment Asisten\n");
                printf("4. Assign Asisten Manual\n5. Schedule Otomatis\n6. Assign Otomatis\n7. Rule Checker\n8. Simpan Proyek dan Keluar\n");
                printf("Pilih Mode : ");
                scanf("%d", &kode);
                //validasi input menu utama
                while (kode < 1 || kode > 8)
                {
                    printf("Masukan salah. Masukan pilihan menu ulang");
                    printf("[Menu Utama]\nPilih Mode:\n1. Tampilkan Schedule\n2. Schedule Manual\n3. Tampilkan Status Assignment Asisten\n");
                    printf("4. Assign Asisten Manual\n5. Schedule Otomatis\n6. Assign Otomatis\n7. Rule Checker\n8. Simpan Proyek dan Keluar\n");
                    printf("Pilih Mode : ");
                    scanf("%d", &kode);
                }
            }
            
            // jika simpan proyek dan keluar
            if (kode == 8)
            {
                //Simpan dan keluar
                fprintf(fileJadwal, "Ruang Praktikum, LAB1, LAB2, LAB3 , LSS\n");
                for (minggu=3; minggu<=12; minggu++)
                {
                    for(hari=1; hari<=5; hari++)
                    {
                        for (i = 1; i<=4; i++)
                        {
                            fprintf(fileJadwal, "%d,%s,", minggu, arrHari[hari]);
                            if (arrJadwal[minggu][hari][i].rombongan != NULL)
                            {
                                if (arrJadwal[minggu][hari][i].nomor != NULL)
                                { fprintf(fileJadwal,"%s-%c%d",arrJadwal[minggu][hari][i].matkul,arrJadwal[minggu][hari][i].rombongan,
                                          arrJadwal[minggu][hari][i].nomor);
                                }
                                else
                                {   fprintf(fileJadwal,"%s-%c",arrJadwal[minggu][hari][i].matkul,arrJadwal[minggu][hari][i].rombongan);
                                }
                            }
                            else
                            {
                                fprintf(fileJadwal,",,");
                            }
                            fprintf(fileJadwal,"\n");
                        }
                    }
                }
                
                fprintf(fileAsisten, "Ruang Praktikum, LAB1, LAB2, LAB3 , LSS\n");
                for (minggu=3; minggu<=12; minggu++)
                {
                    for(hari=1; hari<=5; hari++)
                    {
                        for (i = 1; i<=4; i++)
                        {
                            fprintf(fileAsisten, "%d,%s,", minggu, arrHari[hari]);
                            if (arrAsisten[minggu][hari][i].asisten1 != NULL)
                            { fprintf(fileAsisten,"%c,%c",arrAsisten[minggu][hari][i].asisten1,arrAsisten[minggu][hari][i].asisten2);
                            }
                            else
                            {
                                fprintf(fileAsisten,",,");
                            }
                            fprintf(fileAsisten, "\n");
                        }
                    }
                }
                fclose(fileAsisten);
                fclose(fileJadwal);
                return 0;
            }
            break;
            break;
            
            //kode 2
        case 2:
            //Load proyek dari data
            printf("====== Load Proyek dari Data ======\nMasukkan nama proyek:");
            scanf("%s", namaFile);
            fileJadwal = fopen(strcat(namaFile, "_rombongan.csv"), "r+");
            fileAsisten = fopen(strcat(namaFile, "_asisten.csv"), "r+");
            i = 0;
            
            //baca file jadwal csv
            while ((fgets(line, 100, fileJadwal) != NULL) && (i < 60))
            {
                j = 0;
                for (token = strtok(line, ","); token != NULL && j < 6; token = strtok(NULL, ","))
                {
                    if (j == 0)
                    {
                        minggu = token;
                        j = 1;
                    }
                    else if (j == 1)
                    {
                        for (k=1;k<=5;k++)
                        {
                            if(strcmp(token, arrHari[k]) == 0)
                            {
                                hari = k;
                            }
                        }
                    }
                    else
                    {
                        strncpy(arrJadwal[minggu][hari][j].matkul,token,6);
                        strncpy(arrJadwal[minggu][hari][j].rombongan,&token[7],1);
                        if (strlen(token) == 8)
                        {
                            strncpy(arrJadwal[minggu][hari][j].nomor,&token[8],1);
                        }
                    }
                }
                i++;
            }
            
            i = 0;
            //baca file asisten csv
            while ((fgets(line, 100, fileAsisten) != NULL)&&(i < 60))
            {
                j = 0;
                l = 0;
                for (token = strtok(line, ","); token != NULL && j < 6; token = strtok(NULL, ","))
                {
                    if (j == 0)
                    {
                        minggu = token;
                    }
                    else if (j == 1)
                    {
                        for (k=1;k<=5;k++)
                        {
                            if(strcmp(token, arrHari[k])==0)
                                hari = k;
                        }
                    }
                }
                if ((token < 79) && (token > 64) && ((l%2) == 0))
                {
                    strncpy(arrAsisten[minggu][hari][j].asisten1,token,1);
                    l++;
                }
                else if((token < 79) && (token > 64) && ((l%2) == 1))
                {
                    strncpy(arrAsisten[minggu][hari][j].asisten2,token,1);
                    l++;
                }
                i++;
            }
            /*Asalnya mau disatuin, tapi karena berada dalam kondisional dan ada kondisional ke 3 jadinya susah. Copas yang atas deh.*/
            printf("[Menu Utama]\nPilih Mode:\n1. Tampilkan Schedule\n2. Schedule Manual\n3. Tampilkan Status Assignment Asisten\n");
            printf("4. Assign Asisten Manual\n5. Schedule Otomatis\n6. Assign Otomatis\n7. Rule Checker\n8. Simpan Proyek dan Keluar\n");
            printf("Pilih Mode : ");
            scanf("%d", &kode);
            //validasi input menu utama
            while (kode < 1 || kode > 8)
            {
                printf("Masukan salah. Masukan pilihan menu ulang");
                printf("[Menu Utama]\nPilih Mode:\n1. Tampilkan Schedule\n2. Schedule Manual\n3. Tampilkan Status Assignment Asisten\n");
                printf("4. Assign Asisten Manual\n5. Schedule Otomatis\n6. Assign Otomatis\n7. Rule Checker\n8. Simpan Proyek dan Keluar\n");
                printf("Pilih Mode : ");
                scanf("%d", &kode);
            }
            
            while (kode != 8)
            {
                
                switch(kode)
                {
                    case 1:
                        //tampilkan schedule
                        tampilSchedule(arrJadwal);
                        break;
                    case 2:
                        //schedule manual
                        scheduleManual(arrJadwal);
                        break;
                    case 3:
                        //Tampilkan Status Assignment Asisten
                        statusAsisten(arrAsisten);
                        break;
                    case 4:
                        //Assign Asisten Manual
                        assignAsisten(arrAsisten, arrJadwal);
                        break;
                    case 5:
                        //Schedule Otomatis
                        printf("fitur belum tersedia");
                        break;
                    case 6:
                        //Assign Otomatis
                        printf("fitur belum tersedia");
                        break;
                    case 7:
                        //Rule Checker
                        printf("[DRC]\nMasukkan File DRC (dalam format .txt):");
                        scanf("%s", namaFile);
                        fileRule = fopen(strcat(namaFile,".txt"), "r");
                        while (fileRule==NULL){
                            printf("Masukan file salah, coba masukan kembali");
                            printf("[DRC]\nMasukkan File DRC (dalam format .txt):");
                            scanf("%s", namaFile);
                            fileRule = fopen(strcat(namaFile,".txt"), "r");
                        }
                        ruleCheck(*fileRule, arrJadwal, arrAsisten);
                        fclose(fileRule);
                        break;
                }
                printf("[Menu Utama]\nPilih Mode:\n1. Tampilkan Schedule\n2. Schedule Manual\n3. Tampilkan Status Assignment Asisten\n");
                printf("4. Assign Asisten Manual\n5. Schedule Otomatis\n6. Assign Otomatis\n7. Rule Checker\n8. Simpan Proyek dan Keluar\n");
                printf("Pilih Mode : ");
                scanf("%d", &kode);
                //validasi input menu utama
                while (kode < 1 || kode > 8)
                {
                    printf("Masukan salah. Masukan pilihan menu ulang");
                    printf("[Menu Utama]\nPilih Mode:\n1. Tampilkan Schedule\n2. Schedule Manual\n3. Tampilkan Status Assignment Asisten\n");
                    printf("4. Assign Asisten Manual\n5. Schedule Otomatis\n6. Assign Otomatis\n7. Rule Checker\n8. Simpan Proyek dan Keluar\n");
                    printf("Pilih Mode : ");
                    scanf("%d", &kode);
                }
            }
            if (kode == 8)
            {
                //Simpan dan keluar
                fprintf(fileJadwal, "Ruang Praktikum, LAB1, LAB2, LAB3 , LSS\n");
                for (minggu=3; minggu<=12; minggu++)
                {
                    for(hari=1; hari<=5; hari++)
                    {
                        for (i = 1; i<=4; i++)
                        {
                            fprintf(fileJadwal, "%d,%s,", minggu, arrHari[hari]);
                            if (arrJadwal[minggu][hari][i].rombongan != NULL)
                            {
                                if (arrJadwal[minggu][hari][i].nomor != NULL)
                                { fprintf(fileJadwal,"%s-%c%d",arrJadwal[minggu][hari][i].matkul,arrJadwal[minggu][hari][i].rombongan,
                                          arrJadwal[minggu][hari][i].nomor);
                                }
                                else
                                {   fprintf(fileJadwal,"%s-%c",arrJadwal[minggu][hari][i].matkul,arrJadwal[minggu][hari][i].rombongan);
                                }
                            }
                            else
                            {
                                fprintf(fileJadwal,",,");
                            }
                            fprintf(fileJadwal,"\n");
                        }
                    }
                }
                
                fprintf(fileAsisten, "Ruang Praktikum, LAB1, LAB2, LAB3 , LSS\n");
                for (minggu=3; minggu<=12; minggu++)
                {
                    for(hari=1; hari<=5; hari++)
                    {
                        for (i = 1; i<=4; i++)
                        {
                            fprintf(fileAsisten, "%d,%s,", minggu, arrHari[hari]);
                            if (arrAsisten[minggu][hari][i].asisten1 != NULL)
                            { fprintf(fileAsisten,"%c,%c",arrAsisten[minggu][hari][i].asisten1,arrAsisten[minggu][hari][i].asisten2);
                            }
                            else
                            {
                                fprintf(fileAsisten,",,");
                            }
                            fprintf(fileAsisten, "\n");
                        }
                    }
                }
                fclose(fileAsisten);
                fclose(fileJadwal);
                return 0;
            }

            break;
            break;
            
        case 3:
            printf("Keluar dari program...");
            return 0;
            break;
        default:
            printf("Masukan salah, pilih angka 1, 2 atau 3");
    }
    return 0;
}
/*---------------------------------------------------------------------------------------------------------------*/
//algoritma procedure dan fungsi
int konversiHari (char str[])
{
    //deklarasi variabel lokal
    int angka;
    char str1[] = "Senin";
    char str2[] = "Selasa";
    char str3[] = "Rabu";
    char str4[] = "Kamis";
    char str5[] = "Jumat";
    
    //algoritma fungsi
    
    //mengubah nama hari menjadi integer
    if (strcmp(str, str1) == 0)
    {
        angka = 1;
    }
    else if (strcmp(str, str2) == 0)
    {
        angka = 2;
    }
    else if (strcmp(str, str3) == 0)
    {
        angka = 3;
    }
    else if (strcmp(str, str4) == 0)
    {
        angka = 4;
    }
    else if (strcmp(str, str5) == 0)
    {
        angka = 5;
    }
    else
    {
        angka = 6;
    }
    return angka;
}

int konversiRuang (char str[5])
{
    //deklarasi variabel lokal
    int angka;
    char str1[5] = "LAB1";
    char str2[5] = "LAB2";
    char str3[5] = "LAB3";
    char str4[5] = "LSS";
    
    //algoritma fungsi
    
    //mengubah nama ruangan menjadi integer
    if (strcmp(str, str1) == 0)
    {
        angka = 1;
    }
    else if (strcmp(str, str2) == 0)
    {
        angka = 2;
    }
    else if (strcmp(str, str3) == 0)
    {
        angka = 3;
    }
    else if (strcmp(str, str4) == 0)
    {
        angka = 4;
    }
    else
    {
        angka = 5;
    }
    return angka;
}

int validasiAsisten(char str, int minggu, int hari, int ruang, praktikum_t arrJadwal[12][5][4])
{
    //deklarasi variabel lokal
    int cek = 0;
    char str1[] = "EL2205";
    char str2[] = "EL2208";
    char str3[] = "EB2200";
    
    //algoritma fungsi
    
    //memvalidasi nama asisten dengan praktikum dan hari berhalangan
    if (str == 'A')
    {
        if (strncmp(arrJadwal[minggu][hari][ruang].matkul, str1, 5) == 0)
        {
            if (hari != 3)
            {
                cek = 1;
            }
        }
    }
    else if (str == 'B')
    {
        if (strncmp(arrJadwal[minggu][hari][ruang].matkul, str1, 5) == 0)
        {
            if (hari != 1)
            {
                cek = 1;
            }
        }
    }
    else if (str == 'C')
    {
        if (strncmp(arrJadwal[minggu][hari][ruang].matkul, str1, 5) == 0)
        {
            if ((hari != 2) || hari != 3)
            {
                cek = 1;
            }
        }
    }
    else if (str == 'D')
    {
        if (strncmp(arrJadwal[minggu][hari][ruang].matkul, str1, 5) == 0)
        {
            if ((hari != 1) || hari != 3)
            {
                cek = 1;
            }
        }
    }
    else if (str == 'E')
    {
        if (strncmp(arrJadwal[minggu][hari][ruang].matkul, str1, 5) == 0 || strncmp(arrJadwal[minggu][hari][ruang].matkul, str2, 5) == 0)
        {
            cek = 1;
        }
    }
    else if (str == 'F')
    {
        if (strncmp(arrJadwal[minggu][hari][ruang].matkul, str1, 5) == 0)
        {
            if (hari != 2)
            {
                cek = 1;
            }
        }
    }
    else if (str == 'G')
    {
        if (strncmp(arrJadwal[minggu][hari][ruang].matkul, str1, 5 ) == 0 || strncmp(arrJadwal[minggu][hari][ruang].matkul, str3, 5) == 0)
        {
            if (hari != 4)
            {
                cek = 1;
            }
        }
    }
    else if (str == 'H')
    {
        if (strncmp(arrJadwal[minggu][hari][ruang].matkul, str2, 5) == 0)
        {
            if (hari != 4)
            {
                cek = 1;
            }
        }
    }
    else if (str == 'I')
    {
        if (strncmp(arrJadwal[minggu][hari][ruang].matkul, str1, 5) == 0 || strncmp(arrJadwal[minggu][hari][ruang].matkul, str2, 5) == 0 || strncmp(arrJadwal[minggu][hari][ruang].matkul, str3, 5) == 0)
        {
            if (hari != 3)
            {
                cek = 1;
            }
        }
    }
    else if (str == 'J')
    {
        if (strncmp(arrJadwal[minggu][hari][ruang].matkul, str2, 5) == 0)
        {
            if (hari != 5)
            {
                cek = 1;
            }
        }
    }
    else if (str == 'K')
    {
        if (strncmp(arrJadwal[minggu][hari][ruang].matkul, str2, 5) == 0 || strncmp(arrJadwal[minggu][hari][ruang].matkul, str3, 5) == 0)
        {
            if (hari != 5)
            {
                cek = 1;
            }
        }
    }
    else if (str == 'L')
    {
        if (strncmp(arrJadwal[minggu][hari][ruang].matkul, str2, 5) == 0)
        {
            cek = 1;
        }
    }
    else if (str == 'M')
    {
        if (strncmp(arrJadwal[minggu][hari][ruang].matkul, str2, 5) == 0)
        {
            if ((hari != 3) ||(hari != 4))
            {
                cek = 1;
            }
        }
    }
    else if (str == 'N')
    {
        if (strncmp(arrJadwal[minggu][hari][ruang].matkul, str2, 5) == 0 || strncmp(arrJadwal[minggu][hari][ruang].matkul, str3, 5) == 0)
        {
            if (hari != 2)
            {
                cek = 1;
            }
        }
    }
    return cek;
}

void statusAsisten(asisten_t arrAsisten[12][5][4])
{
    //deklarasi variabel lokal
    int minggu, hari, ruang;
    
    //algoritma fungsi
    printf("[Schedule Asisten Praktikum Sementara]\n");
    printf("|---------------------------------------------------------------------------------|\n");
    printf("| Ruang Praktikum |     LAB1      |      LAB2     |      LAB3     |      LSS      |\n");
    printf("|-----------------|---------------|---------------|---------------|---------------|\n");
    printf("| Minggu |  Hari  |---------------|---------------|---------------|---------------|\n");
    printf("|--------|--------|---------------|---------------|---------------|---------------|\n");
    
    for (minggu = 1; minggu <= 12; minggu++)
    {
        for (hari = 1; hari <= 5; hari++)
        {
            if (hari == 1)
            {
                if (minggu > 9)
                {
                    printf("|   %d   |  Senin |", minggu);
                }
                else
                {
                    printf("|    %d   |  Senin |", minggu);
                }
            }
            else if (hari == 2)
            {
                if (minggu > 9)
                {
                    printf("|   %d   | Selasa |", minggu);
                }
                else
                {
                    printf("|    %d   | Selasa |", minggu);
                }
            }
            else if (hari == 3)
            {
                if (minggu > 9)
                {
                    printf("|   %d   |  Rabu  |", minggu);
                }
                else
                {
                    printf("|    %d   |  Rabu  |", minggu);
                }
            }
            else if (hari == 4)
            {
                if (minggu > 9)
                {
                    printf("|   %d   |  Kamis |", minggu);
                }
                else
                {
                    printf("|    %d   |  Kamis |", minggu);
                }
            }
            else if (hari == 5)
            {
                if (minggu > 9)
                {
                    printf("|   %d   |  Jumat |", minggu);
                }
                else
                {
                    printf("|    %d   |  Jumat |", minggu);
                }
            }
            for (ruang = 1; ruang <= 4; ruang++)
            {
                if (arrAsisten[minggu][hari][ruang].asisten1 != NULL && arrAsisten[minggu][hari][ruang].asisten2 != NULL)
                {
                    printf("      %c , %c    |", arrAsisten[minggu][hari][ruang].asisten1, arrAsisten[minggu][hari][ruang].asisten2);
                }
                else if (arrAsisten[minggu][hari][ruang].asisten1 != NULL && arrAsisten[minggu][hari][ruang].asisten2 == NULL)
                {
                    printf("      %c        |", arrAsisten[minggu][hari][ruang].asisten1);
                }
                else
                {
                    printf("               |");
                }
            }
            printf("\n");
        }
        printf("|---------------------------------------------------------------------------------|\n");
    }
}

void assignAsisten(asisten_t arrAsisten[12][5][4], praktikum_t arrJadwal[12][5][4])
{
    //variabel lokal
    char asisten;
    int minggu, intHari, intRuang, value, i;
    char hari[10];
    char ruang[5];
    char matkul[6];
    
    //algoritma fungsi
    printf("[Mode Assign Asisten]\n");
    printf("Isi 'q' atau 'Q' untuk kembali ke menu\n");
    printf("Pilih Asisten (A-N) : "); scanf(" %c", &asisten);
    
    while ((asisten != 'q') && (asisten != 'Q'))
    {
        //printf("Pilih Asisten (A-N) : ");
        //scanf(" %c", &asisten);
        //baca input minggu
        printf("Minggu: "); scanf("%d", &minggu);
        while ((minggu < 3) || (minggu > 12))
        {
            printf("Input salah, silakan masukkan ulang\n");
            printf("Minggu: "); scanf("%d", &minggu);
        }
        
        //baca input hari
        printf("Hari: "); scanf("%s", hari);
        intHari = konversiHari(hari);
        
        while ( intHari > 5)
        {
            printf("Input salah, silakan masukkan ulang\n");
            printf("Hari: "); scanf("%s", hari);
            intHari = konversiHari(hari);
        }
        
        //baca input ruang
        printf("Ruang: ");
        scanf("%s", ruang);
        intRuang = konversiRuang(ruang);
        
        while (intRuang > 4)
        {
            printf("Input salah, silakan masukkan ulang\n");
            printf("Ruang: ");
            scanf("%s", ruang);
            intRuang = konversiRuang(ruang);
        }
        
        value = validasiAsisten(asisten, minggu, intHari, intRuang, arrJadwal);
        if (value == 1)
        {
            if (arrAsisten[minggu][intHari][intRuang].asisten1 == NULL)
            {
                arrAsisten[minggu][intHari][intRuang].asisten1 = asisten;
            }
            else
            {
                arrAsisten[minggu][intHari][intRuang].asisten2 = asisten;
            }
        }
        else
        {
            if (arrJadwal[minggu][intHari][intRuang].matkul[1] == NULL)
            {
                printf("Tidak ada jadwal praktikum");
            }
            else
            {
                for (i=0; i<=6; i++)
                {
                    matkul[i] = arrJadwal[minggu][intHari][intRuang].matkul[i];
                }
                
                //pesan kesalahan
                if (asisten == 'A')
                {
                    printf("Jadwal Asisten Praktikum Amir tidak sesuai (tidak ada Rombongan %s)\n", matkul);
                }
                else if (asisten == 'B')
                {
                    printf("Jadwal Asisten Praktikum Budi tidak sesuai (tidak ada Rombongan %s)\n", matkul);
                }
                else if (asisten == 'C')
                {
                    printf("Jadwal Asisten Praktikum Cici tidak sesuai (tidak ada Rombongan %s)\n", matkul);
                }
                else if (asisten == 'D')
                {
                    printf("Jadwal Asisten Praktikum Doni tidak sesuai (tidak ada Rombongan %s)\n", matkul);
                }
                else if (asisten == 'E')
                {
                    printf("Jadwal Asisten Praktikum Endang tidak sesuai (tidak ada Rombongan %s)\n", matkul);
                }
                else if (asisten == 'F')
                {
                    printf("Jadwal Asisten Praktikum Fadel tidak sesuai (tidak ada Rombongan %s)\n", matkul);
                }
                else if (asisten == 'G')
                {
                    printf("Jadwal Asisten Praktikum Gilang tidak sesuai (tidak ada Rombongan %s)\n", matkul);
                }
                else if (asisten == 'H')
                {
                    printf("Jadwal Asisten Praktikum Hero tidak sesuai (tidak ada Rombongan %s)\n", matkul);
                }
                else if (asisten == 'I')
                {
                    printf("Jadwal Asisten Praktikum Intan tidak sesuai (tidak ada Rombongan %s)\n", matkul);
                }
                else if (asisten == 'J')
                {
                    printf("Jadwal Asisten Praktikum Joko tidak sesuai (tidak ada Rombongan %s)\n", matkul);
                }
                else if (asisten == 'K')
                {
                    printf("Jadwal Asisten Praktikum Kiki tidak sesuai (tidak ada Rombongan %s)\n", matkul);
                }
                else if (asisten == 'L')
                {
                    printf("Jadwal Asisten Praktikum Luis tidak sesuai (tidak ada Rombongan %s)\n", matkul);
                }
                else if (asisten == 'M')
                {
                    printf("Jadwal Asisten Praktikum Mini tidak sesuai (tidak ada Rombongan %s)\n", matkul);
                }
                else if (asisten == 'N')
                {
                    printf("Jadwal Asisten Praktikum Nina tidak sesuai (tidak ada Rombongan %s)\n", matkul);
                }
            }
        }
        printf("\n");
        
        printf("Pilih Asisten (A-N) : ");
        scanf(" %c", &asisten);
    }
    return ;
}
//husna
int ruleCheck(FILE fRule, praktikum_t arrJadwal[12][5][4], asisten_t arrAsisten[12][5][4]){
    rule_t arrRule[5];
    int x, minggu, i, j, check;
    i = 0;
    j = 0;
    check = 1;
    while(fscanf(&fRule,"%d %s",&arrRule[i].minggu, &arrRule[i].hari) != NULL){
        x = konversiHari(arrRule[i].hari);
        minggu = arrRule[i].minggu;
        for (j = 0; j < 4; j++){
            if (arrJadwal[minggu][x][j].matkul != NULL){
                check = 0;
                printf("Rule ke %d tidak terpenuhi.", i+1);
            }
        }
        i++;
    }
    printf("%d/%d Rule Is Checked", i,i);
    return 0;
}
//rozin
void scheduleManual(praktikum_t arrJadwal[12][5][4])
{
    int minggu, intHari, intRuang, value, i;
    char rombongan;
    int nomor;
    char hari[10];
    char ruang[5];
    char matkul[6];
    char str1[] = "EL2205";
    char str2[] = "EL2208";
    char str3[] = "EB2200";
    
    
    printf("[Mode Schedule] \n");
    printf("Isi 'q' atau 'Q' untuk kembali ke menu\n");
    printf("Pilih Kode Praktikum (EL2205, EL2208, EB2200) :");
    scanf("  %s", matkul);
    
    
    while (strcmp(matkul, "q")!= 0 && strcmp(matkul, "Q")!= 0)
    {
        
        while (strncmp(matkul, str1, 6) != 0 && strncmp(matkul, str2, 6) != 0 && strncmp(matkul, str3, 6) != 0)
        {
            printf("Kode Praktikum Salah, silahkan input ulang");
            printf("Pilih Kode Praktikum (EL2205, EL2208, EB2200) :");
            scanf("%s", matkul);
        }
        //untuk matkul EL2205
        if (strcmp(matkul, str1) == 0)
        {
            //input rombongan
            printf("Rombongan (A1, A2, B1, B2, C1, atau C2) :");
            scanf(" %c%d", &rombongan, &nomor);
            while ((rombongan != 'A') && (rombongan != 'B') && (rombongan != 'C'))
            {
                printf("Rombongan salah, silahkan input ulang \n");
                printf("Rombongan (A1, A2, A3, B1, B2, B3, atau C) :");
                scanf("%c%d", &rombongan, &nomor);
            }
            
            //baca input minggu
            printf("Minggu ke : "); scanf("%d", &minggu);
            while ((minggu < 3) || (minggu > 12))
            {
                printf("Input salah, silakan masukkan ulang\n");
                printf("Minggu: "); scanf("%d", &minggu);
            }
            
            //baca input hari
            printf("Hari: "); scanf("%s", hari);
            intHari = konversiHari(hari);
            
            while ( intHari > 5)
            {
                printf("\nInput salah, silakan masukkan ulang\n");
                printf("Hari: "); scanf("%s", hari);
                intHari = konversiHari(hari);
            }
            
            //baca input ruang
            printf("Ruangan: ");
            scanf("%s", ruang);
            intRuang = konversiRuang(ruang);
            
            while (intRuang > 3)
            {
                printf("\nInput salah, silakan masukkan ulang\n");
                printf("Ruangan: "); scanf("%s", ruang);
                intRuang = konversiRuang(ruang);
            }
            
            if (rombongan != 'C')
            {
                for (i = 1; i <= 4; i++)
                {
                    if (strcmp(arrJadwal[minggu][intHari][i].matkul, str2)  == 0 )
                    {
                        printf("Praktikum PMC dan Elka tidak bisa dilaksanakan pada hari yang sama \n");
                    }
                    else
                    {
                        if (arrJadwal[minggu][intHari][intRuang].matkul[1] == NULL)
                        {
                            for (i = 0; i<=6; i++)
                            {
                                arrJadwal[minggu][intHari][intRuang].matkul[i] = matkul[i];
                            }
                            arrJadwal[minggu][intHari][intRuang].rombongan = rombongan;
                            arrJadwal[minggu][intHari][intRuang].nomor = nomor;
                        }
                        else
                        {
                            printf("Sudah ada jadwal \n");
                        }
                        
                    }
                }
            }
            else //rombongan C
            {
                if (arrJadwal[minggu][intHari][intRuang].matkul[1] == NULL)
                {
                    for (i = 0; i<=6; i++)
                    {
                        arrJadwal[minggu][intHari][intRuang].matkul[i] = matkul[i];
                    }
                    arrJadwal[minggu][intHari][intRuang].rombongan = rombongan;
                    arrJadwal[minggu][intHari][intRuang].nomor = nomor;
                }
                else
                {
                    printf("Sudah ada jadwal");
                }
            }
        }
        
        //Praktikum EL2208
        else if (strcmp(matkul, str2) == 0)
        {
            
            //input rombongan
            printf("Rombongan (A1, A2, A3, B1, B2, B3, atau C) :");
            scanf(" %c%d", &rombongan, &nomor);
            while ((rombongan != 'A') && (rombongan != 'B') && (rombongan != 'C'))
            {
                printf("Rombongan salah, silahkan input ulang");
                printf("Rombongan (A1, A2, A3, B1, B2, B3, atau C) :");
                scanf(" %c%d", &rombongan, &nomor);
            }
            
            //baca input minggu
            printf("Minggu ke : "); scanf("%d", &minggu);
            while ((minggu < 3) || (minggu > 12))
            {
                printf("Input salah, silakan masukkan ulang\n");
                printf("Minggu: "); scanf("%d", &minggu);
            }
            
            if (rombongan != 'C')
            {
                //baca input hari
                printf("Hari: "); scanf("%s", hari);
                intHari = konversiHari(hari);
                
                while ( intHari > 5)
                {
                    printf("\nInput salah, silakan masukkan ulang\n");
                    printf("Hari: "); scanf("%s", hari);
                    intHari = konversiHari(hari);
                }
                
                //baca input ruang
                printf("Ruangan: ");
                scanf("%s", ruang);
                intRuang = konversiRuang(ruang);
                
                while (intRuang > 4)
                {
                    printf("\nInput salah, silakan masukkan ulang\n");
                    printf("Ruangan: "); scanf("%s", ruang);
                    intRuang = konversiRuang(ruang);
                }
                
                for (i = 1; i <= 4; i++)
                {
                    if (strcmp(arrJadwal[minggu][intHari][i].matkul, str1)  == 0 )
                    {
                        printf("Praktikum PMC dan Elka tidak bisa dilaksanakan pada hari yang sama");
                    }
                    else
                    {
                        if (arrJadwal[minggu][intHari][intRuang].matkul[1] == NULL)
                        {
                            for (i = 0; i<=6; i++)
                            {
                                arrJadwal[minggu][intHari][intRuang].matkul[i] = matkul[i];
                            }
                            arrJadwal[minggu][intHari][intRuang].rombongan = rombongan;
                            arrJadwal[minggu][intHari][intRuang].nomor = nomor;
                        }
                        else
                        {
                            printf("Sudah ada jadwal");
                        }
                    }
                }
            }
            else //rombongan C
            {
                //baca input hari
                printf("Hari: "); scanf("%s", hari);
                intHari = konversiHari(hari);
                
                while ( intHari != 3)
                {
                    printf("\nInput salah, rombongan C hanya bisa hari rabu, silakan masukkan ulang\n");
                    printf("Hari: "); scanf("%s", hari);
                    intHari = konversiHari(hari);
                }
                
                //baca input ruang
                printf("Ruangan: ");
                scanf("%s", ruang);
                intRuang = konversiRuang(ruang);
                
                while (intRuang > 4)
                {
                    printf("\nInput salah, silakan masukkan ulang\n");
                    printf("Ruangan: "); scanf("%s", ruang);
                    intRuang = konversiRuang(ruang);
                }
                
                if (arrJadwal[minggu][intHari][intRuang].matkul[1] == NULL)
                {
                    for (i = 0; i<=6; i++)
                    {
                        arrJadwal[minggu][intHari][intRuang].matkul[i] = matkul[i];
                    }
                    arrJadwal[minggu][intHari][intRuang].rombongan = rombongan;
                    arrJadwal[minggu][intHari][intRuang].nomor = nomor;
                }
            }
            
        }
        
        //Praktikum EB2200
        else if (strcmp(matkul, str3) == 0)
        {
            //input rombongan
            printf("Rombongan (A atau B) :");
            scanf( "%c", &rombongan);
            while ((rombongan != 'A') && (rombongan != 'B'))
            {
                printf("Rombongan salah, silahkan input ulang");
                printf("Rombongan (A atau B) :");
                scanf(" %c", &rombongan);
            }
            
            //baca input minggu
            printf("Minggu ke : "); scanf("%d", &minggu);
            while ((minggu < 3) || (minggu > 12))
            {
                printf("Input salah, silakan masukkan ulang\n");
                printf("Minggu: "); scanf("%d", &minggu);
            }
            
            //baca input hari
            printf("Hari: "); scanf("%s", hari);
            intHari = konversiHari(hari);
            
            while ( intHari != 2 && intHari != 4)
            {
                printf("\nInput salah, praktikum teknik biomedis hanya bisa hari selasa dan kamis, silahkan masukkan ulang\n");
                printf("Hari: "); scanf("%s", hari);
                intHari = konversiHari(hari);
            }
            
            //baca input ruang
            printf("Ruangan: ");
            scanf("%s", ruang);
            intRuang = konversiRuang(ruang);
            
            while (intRuang > 3)
            {
                printf("\nInput salah, silakan masukkan ulang\n");
                printf("Ruangan: "); scanf("%s", ruang);
                intRuang = konversiRuang(ruang);
            }
            
            if (arrJadwal[minggu][intHari][intRuang].matkul[1] == NULL)
            {
                for (i = 0; i<=6; i++)
                {
                    arrJadwal[minggu][intHari][intRuang].matkul[i] = matkul[i];
                }
                arrJadwal[minggu][intHari][intRuang].rombongan = rombongan;
                arrJadwal[minggu][intHari][intRuang].nomor = NULL;
            }
            else
            {
                printf("Sudah ada jadwal");
            }
        }
        printf("\nPilih Kode Praktikum (EL2205, EL2208, EB2200) :");
        scanf("  %s", matkul);
    }
    return;
}

//mencetak schedule praktikum sementarta
void tampilSchedule(praktikum_t arrJadwal[12][5][4])
{
    int minggu, hari, ruang;
    
    //algoritma fungsi
    printf("[Schedule Asisten Praktikum Sementara]\n");
    printf("|---------------------------------------------------------------------------------|\n");
    printf("| Ruang Praktikum |     LAB1      |      LAB2     |      LAB3     |      LSS      |\n");
    printf("|-----------------|---------------|---------------|---------------|---------------|\n");
    printf("| Minggu |  Hari  |---------------|---------------|---------------|---------------|\n");
    printf("|--------|--------|---------------|---------------|---------------|---------------|\n");
    
    for (minggu = 1; minggu <= 12; minggu++)
    {
        for (hari = 1; hari <= 5; hari++)
        {
            if (hari == 1)
            {
                if (minggu > 9)
                {
                    printf("|   %d   |  Senin |", minggu);
                }
                else
                {
                    printf("|    %d   |  Senin |", minggu);
                }
            }
            else if (hari == 2)
            {
                if (minggu > 9)
                {
                    printf("|   %d   | Selasa |", minggu);
                }
                else
                {
                    printf("|    %d   | Selasa |", minggu);
                }
            }
            else if (hari == 3)
            {
                if (minggu > 9)
                {
                    printf("|   %d   |  Rabu  |", minggu);
                }
                else
                {
                    printf("|    %d   |  Rabu  |", minggu);
                }
            }
            else if (hari == 4)
            {
                if (minggu > 9)
                {
                    printf("|   %d   |  Kamis |", minggu);
                }
                else
                {
                    printf("|    %d   |  Kamis |", minggu);
                }
            }
            else if (hari == 5)
            {
                if (minggu > 9)
                {
                    printf("|   %d   |  Jumat |", minggu);
                }
                else
                {
                    printf("|    %d   |  Jumat |", minggu);
                }
            }
            for (ruang = 1; ruang <= 4; ruang++)
            {
                if (arrJadwal[minggu][hari][ruang].matkul[1] != NULL)
                {
                    printf(" %8s - %c%d |", arrJadwal[minggu][hari][ruang].matkul, arrJadwal[minggu][hari][ruang].rombongan, arrJadwal[minggu][hari][ruang].nomor);
                }
                else
                {
                    printf("               |");
                }
            }
            printf("\n");
        }
        printf("|---------------------------------------------------------------------------------|\n");
    }
}
