#include <stdio.h>
#include <stdlib.h>
#include <math.h>
/*1220505072 hamza can alt�ntop
BIRCH (Balanced Iterative Reducing and Clustering using Hierarchies) algoritmas�n� kullanarak bir k�meleme i�lemi ger�ekle�tirir. A�a��da kodun amac�, a��klamalar� ve �al��ma bi�imi hakk�nda bilgi verilmi�tir:

Amac�: Kodun amac�, verilen veri noktalar�n� k�melere ay�rmak ve her bir k�menin merkezini ve i�erdi�i noktalar�n say�s�n� hesaplamakt�r. Bu �ekilde, veriler daha k���k ve daha anlaml� gruplara ayr�larak analiz edilebilir.

A��klamalar�: Kod, Nokta ve Kume isimli iki yap�y� kullan�r. Nokta yap�lar�, iki boyutlu koordinatlar� tutmak i�in kullan�l�r. Kume yap�lar� ise bir k�menin merkez noktas�n�, i�erdi�i nokta say�s�n� ve noktalar� tutmak i�in kullan�l�r.

�al��ma Bi�imi: Kodun �al��ma bi�imi a�a��daki ad�mlarla ger�ekle�tirilir:

�lk olarak, veri noktalar� rastgele bir �ekilde olu�turulur ve veri_noktalari dizisine kaydedilir.

Ard�ndan, ba�lang�� k�me merkezlerini rastgele se�er ve her bir k�meye birer nokta atar.

K�meleme i�lemi, veri noktalar�n� d�ng�yle gezerek ger�ekle�tirilir. Her bir veri noktas� i�in en yak�n k�me merkezini bulur ve mesafeyi hesaplar.

E�er mesafe, belirli bir e�ik de�erinden b�y�kse yeni bir k�me olu�turulur ve bu yeni k�menin merkezi olarak veri noktas� atan�r.

E�er mesafe, e�ik de�erinden k���kse en yak�n k�me merkezine veri noktas� eklenir.

Sonu� olarak, olu�an k�melerin merkez noktalar�, i�erdikleri nokta say�lar� ve noktalar� ekrana yazd�r�l�r.

Bu �ekilde, veri noktalar� birbirlerine benzerliklerine g�re k�melere ayr�l�r ve k�meleme sonu�lar� ekrana yazd�r�l�r.*/

#define MAKS_NOKTALAR 100 //kodun �al��t��� veri setinde en fazla 100 nokta olabilir
#define MAKS_BOYUT 2 // her bir noktan�n boyutunu belirtir.
//her bir noktan�n koordinatlar�n� tutmak i�in kullan�l�r.
typedef struct {
    double koordinatlar[MAKS_BOYUT]; //her bir noktan�n double boyutta koordinatlar� saklanabilir.
} Nokta;

typedef struct {
    Nokta merkez;
    int nokta_sayisi;
    Nokta *noktalar;
} Kume;

void birch(Kume *kumeler, Nokta *veri_noktalari, int kume_sayisi, int veri_nokta_sayisi, double esik) {
	int i,j,k;
    // �lk k�meleri rastgele se�me
    for ( i = 0; i < kume_sayisi; i++) {//D�ng� kullan�larak her bir k�me i�in a�a��daki i�lemler yap�l�r:
        kumeler[i].merkez = veri_noktalari[i];//K�me merkezi, veri_noktalari dizisindeki ilgili noktaya e�itlenir.
        kumeler[i].nokta_sayisi = 1;//K�menin nokta say�s� 1 olarak ayarlan�r.
        kumeler[i].noktalar = (Nokta *)malloc(sizeof(Nokta));//Bellekte bir Nokta boyutunda yer ayr�l�r ve bu noktaya, k�menin merkez noktas� atan�r.
        kumeler[i].noktalar[0] = veri_noktalari[i];//Bu i�lemler sonucunda, ba�lang�� k�me merkezleri rastgele se�ilir ve her bir k�me sadece bir noktay� temsil eder. Bu ad�m, BIRCH algoritmas�n�n ba�lang�� durumunu olu�turur.
    }

    // K�meleme i�lemi
  for ( i = kume_sayisi; i < veri_nokta_sayisi; i++) {//kume_sayisi'ndan ba�layarak, veri_nokta_sayisi'ne kadar olan veri noktalar� �zerinde d�ng� olu�turulur.
        Nokta veri_noktasi = veri_noktalari[i];//Her bir veri noktas�, veri_noktalari dizisinden al�narak veri_noktasi de�i�kenine atan�r.
        double min_mesafe = INFINITY;//min_mesafe de�i�keni, sonsuz de�er (INFINITY) ile ba�lat�l�r.
        int en_yakin_kume_indeksi = -1;//en_yakin_kume_indeksi de�i�keni, en yak�n k�me merkezinin indisini tutar. Ba�lang��ta -1 olarak atan�r.

        // En yak�n k�me merkezini bulma
        for ( j = 0; j < kume_sayisi; j++) {//j de�i�keni, mevcut k�menin indisini temsil eder. �lk k�meden ba�layarak, kume_sayisi'ne kadar olan k�me merkezleri �zerinde d�ng� olu�turulur.
            double mesafe = 0.0;//Her bir k�me merkezi ile veri noktas� aras�ndaki mesafe hesaplan�r ve mesafe de�i�kenine atan�r. Ba�lang��ta mesafe s�f�r olarak atan�r.
            for ( k = 0; k < MAKS_BOYUT; k++) {
                double fark = veri_noktasi.koordinatlar[k] - kumeler[j].merkez.koordinatlar[k];//�� i�e d�ng� kullan�larak her bir boyut i�in fark hesaplan�r. Veri noktas�n�n her bir boyutu, ilgili k�me merkezinin ayn� boyutundan ��kar�l�r ve bu fark de�eri fark de�i�kenine atan�r.
                mesafe += fark * fark;//Her bir boyut i�in fark�n karesi hesaplan�r ve mesafe de�i�kenine eklenir.
            }
            mesafe = sqrt(mesafe);//Son olarak, hesaplanan mesafe de�eri, Euclidean mesafesi i�in karek�k al�narak g�ncellenir.
           //E�er hesaplanan mesafe, min_mesafe'den daha k���k ise, min_mesafe g�ncellenir ve en_yakin_kume_indeksi ilgili k�menin indisine atan�r. 
            if (mesafe < min_mesafe) {
                min_mesafe = mesafe;
                en_yakin_kume_indeksi = j;
            }
        }

        // E�er mesafe e�ik de�erinden b�y�kse yeni bir k�me olu�tur
           if (min_mesafe > esik) {// //E�er en yak�n k�me merkezi ile veri noktas� aras�ndaki mesafe (min_mesafe) e�ik de�erinden b�y�k ise, bu durumda yeni bir k�me olu�turulur. �lgili k�meye ait bilgiler g�ncellenir:
            kumeler[kume_sayisi].merkez = veri_noktasi;//kumeler[kume_sayisi].merkez, yeni olu�turulan k�menin merkezi olarak belirlenir ve veri_noktasi de�eri atan�r.
            kumeler[kume_sayisi].nokta_sayisi = 1;//kumeler[kume_sayisi].nokta_sayisi, 1 olarak ayarlan�r ��nk� yeni olu�turulan k�me yaln�zca veri noktas�n� i�erir.
            kumeler[kume_sayisi].noktalar = (Nokta *)malloc(sizeof(Nokta));//kumeler[kume_sayisi].noktalar, bellekte dinamik olarak ayr�lan bir alan olarak ayarlan�r ve veri_noktasi de�eri bu alana atan�r.
            kumeler[kume_sayisi].noktalar[0] = veri_noktasi;
            kume_sayisi++;//kume_sayisi de�i�keni bir art�r�l�r, ��nk� yeni bir k�me olu�turulmu�tur.
        } else {
            // En yak�n k�me merkezine veri noktas�n� ekle
            //E�er en yak�n k�me merkezi ile veri noktas� aras�ndaki mesafe (min_mesafe) e�ik de�erinden k���k veya e�it ise, bu durumda veri noktas� en yak�n k�me merkezine eklenir. �lgili k�meye ait bilgiler g�ncellenir:
            kumeler[en_yakin_kume_indeksi].nokta_sayisi++; //kumeler[en_yakin_kume_indeksi].nokta_sayisi bir art�r�l�r, ��nk� veri noktas� bu k�meye eklenmi�tir.
            kumeler[en_yakin_kume_indeksi].noktalar = (Nokta *)realloc(kumeler[en_yakin_kume_indeksi].noktalar,//kumeler[en_yakin_kume_indeksi].noktalar, bellekte yeniden boyutland�r�larak daha fazla veri noktas�n� i�erecek �ekilde g�ncellenir.
                                                                      kumeler[en_yakin_kume_indeksi].nokta_sayisi * sizeof(Nokta));
            kumeler[en_yakin_kume_indeksi].noktalar[kumeler[en_yakin_kume_indeksi].nokta_sayisi - 1] = veri_noktasi;//Veri noktas�, kumeler[en_yakin_kume_indeksi].noktalar dizisinin sonuna eklenir.
        }
    }
}

int main() {
	int i,j,k;//tan�mla
    Nokta veri_noktalari[MAKS_NOKTALAR];//tan�mla
    Kume kumeler[MAKS_NOKTALAR];//tan�mla
    int veri_nokta_sayisi = 10;//deger verildi
    int kume_sayisi = 3;//deger verildi
    double esik = 2.0;//deger verildi

    // Veri noktalar�n� olu�turma
    for ( i = 0; i < veri_nokta_sayisi; i++) {
        for (j = 0; j < MAKS_BOYUT; j++) {
            veri_noktalari[i].koordinatlar[j] = (double)rand() / RAND_MAX * 10.0;
        }
    }

    // Birch algoritmas� ile k�meleme yapma
    birch(kumeler, veri_noktalari, kume_sayisi, veri_nokta_sayisi, esik);

    // Elde edilen k�meleme sonu�lar�n� yazd�rma
    for ( i = 0; i < kume_sayisi; i++) {
        printf("Kume #%d:\n", i + 1);
        printf("Merkez: ");
        for ( j = 0; j < MAKS_BOYUT; j++) {
            printf("%.2f ", kumeler[i].merkez.koordinatlar[j]);
        }
        printf("\n");
        printf("Nokta Sayisi: %d\n", kumeler[i].nokta_sayisi);
        printf("Noktalar:\n");
        for ( j = 0; j < kumeler[i].nokta_sayisi; j++) {
            printf("(");
            for ( k = 0; k < MAKS_BOYUT; k++) {
                printf("%.2f", kumeler[i].noktalar[j].koordinatlar[k]);
                if (k != MAKS_BOYUT - 1) {
                    printf(", ");
                }
            }
            printf(")\n");
        }
        printf("\n");
    }

    return 0;
}

