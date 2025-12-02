#include <stdio.h>

#define RESET "\x1b[0m"
#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define YELLOW "\x1b[33m"
#define BLUE "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN "\x1b[36m"
#define WHITE "\x1b[37m"

char ruangan[3][20] = {"Reguler", "VIP", "Premium"};
int status[3] = {1, 1, 1}; 
int hargaPerJam[3] = {5000, 10000, 15000};
int nomor = 1;

char paket[4][30] = {"Paket Hemat (2 Jam)", "Paket Lama (4 Jam)", "Paket Nyaman (3 Jam)", "Tidak Ada Paket"};
int durasiPaket[4] = {2, 4, 3, 0};
int hargaPaket[4] = {9000, 18000, 14000, 0};

void menu();
void tampilkanRuangan();
void sewaRuangan();
void simpanFile(char nama[], char ruangan[], char paket[], int durasiPaket, int tambahanJam, int totalHarga);

int main()
{
    menu();
    return 0;
}

void menu()
{
    int pilih;
    do
    {
        printf(YELLOW "\n====== MENU WARNET Si IJAN ======\n" RESET);
        printf("1. Lihat Ruangan\n");
        printf("2. Sewa Ruangan\n");
        printf("3. Keluar\n");
        printf(BLUE "Pilih: " RESET);
        scanf("%d", &pilih);

        switch (pilih)
        {
        case 1:
            tampilkanRuangan();
            break;
        case 2:
            sewaRuangan();
            break;
        case 3:
            printf(MAGENTA "\nTerima kasih sudah main di Warnet kami!!\n" RESET);
            break;
        default:
            printf(RED "Pilihan tidak valid!\n" RESET);
            break;
        }
    } while (pilih != 3);
}

void tampilkanRuangan()
{
    printf(YELLOW "\n========== Daftar Ruangan ==========\n" RESET);
    for (int i = 0; i < 3; i++)
    {
        printf("%d. %s %s - Rp %d/jam\n", i + 1, ruangan[i], status[i] ? "(Tersedia)" : "(Dipakai)", hargaPerJam[i]);
    }
}

void sewaRuangan()
{
    int pilihRuangan, pilihPaket, tambahanJam;
    int totalDurasi, totalHarga;
    char nama[50];

    printf(BLUE "\nMasukkan Nama Penyewa: " RESET);
    scanf(" %[^\n]", nama);

    tampilkanRuangan();
    printf(GREEN "Pilih ruangan (1-3): " RESET);
    scanf("%d", &pilihRuangan);

    if (pilihRuangan < 1 || pilihRuangan > 3)
    {
        printf(RED "Pilihan ruangan tidak valid!\n" RESET);
        return;
    }
    if (status[pilihRuangan - 1] == 0)
    {
        printf(RED "Ruangan sedang dipakai!\n" RESET);
        return;
    }

    printf(YELLOW "\n========== PILIH PAKET ==========\n" RESET);
    for (int i = 0; i < 4; i++) 
    {
        printf("%d. %s - Rp %d\n", i + 1, paket[i], hargaPaket[i]);
    }

    while (1)
    {
        printf(GREEN "Pilih paket (1-4): " RESET); 
        scanf("%d", &pilihPaket);
        if (pilihPaket >= 1 && pilihPaket <= 4)
            break;
        printf(RED "Pilihan paket tidak valid!\n" RESET);
    }

    if (pilihPaket != 3)
    {
        do
        {
            printf(GREEN "Masukkan tambahan jam (=> 0): " RESET);
            scanf("%d", &tambahanJam);
            if (tambahanJam < 0)
                printf(RED "Input tidak valid! Tambahan jam tidak boleh kurang dari 0.\n" RESET);
        } while (tambahanJam < 0);
    }
    else
    {
        do
        {
            printf(GREEN "Masukkan total jam sewa (> 0): " RESET);
            scanf("%d", &tambahanJam);
            if (tambahanJam <= 0)
                printf(RED "Input tidak valid! Jam sewa harus lebih dari 0.\n" RESET);
        } while (tambahanJam <= 0);
    }

    int idx = pilihRuangan - 1;
    int harga = hargaPerJam[idx];

    if (pilihPaket == 3)
    {
        totalDurasi = tambahanJam;
        totalHarga = tambahanJam * harga;
    }
    else
    {
        totalDurasi = durasiPaket[pilihPaket - 1] + tambahanJam;
        totalHarga = hargaPaket[pilihPaket - 1] + (tambahanJam * harga);
    }


    printf(YELLOW "\n============== STRUK PEMBAYARAN ==============\n" RESET);
    printf(CYAN "Nama Penyewa  :" RESET " %s\n", nama);
    printf(CYAN "Ruangan       :" RESET " %s\n", ruangan[idx]);
    printf(CYAN "Harga/Jam     :" RESET " Rp %d\n", harga);
    printf(CYAN "Paket         :" RESET " %s\n", paket[pilihPaket - 1]);
    if (pilihPaket != 3)
    {
        printf(CYAN "Durasi Paket  :" RESET " %d Jam\n", durasiPaket[pilihPaket - 1]);
        printf(CYAN "Tambahan Jam  :" RESET " %d Jam\n", tambahanJam);
    }
    printf(CYAN "Total Durasi  :" RESET " %d Jam\n", totalDurasi);
    printf(YELLOW "----------------------------------------------\n" RESET);
    printf(CYAN "Total Harga   :" RESET " Rp %d\n", totalHarga);
    printf(YELLOW "==============================================\n" RESET);

    status[idx] = 0;

    simpanFile(nama, ruangan[idx], paket[pilihPaket - 1], durasiPaket[pilihPaket - 1], tambahanJam, totalHarga);
}

void simpanFile(char nama[], char ruangan[], char paket[], int durasiPaket, int tambahanJam, int totalHarga)
{
    FILE *f = fopen("transaksi.txt", "a");
    if (f == NULL)
    {
        printf(RED "Gagal membuka file!\n" RESET);
        return;
    }

    fprintf(f, "%d. Nama: %s | Ruangan: %s | Paket: %s | Durasi Paket: %d | Tambahan Jam: %d | Total Bayar: %d\n",
           nomor++, nama, ruangan, paket, durasiPaket, tambahanJam, totalHarga);

    fclose(f);
}