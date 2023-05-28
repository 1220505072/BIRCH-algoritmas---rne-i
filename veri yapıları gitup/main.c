#include <stdio.h>
#include <stdlib.h>
#include <math.h>
/*1220505072 hamza can altýntop
BIRCH (Balanced Iterative Reducing and Clustering using Hierarchies) algoritmasýný kullanarak bir kümeleme iþlemi gerçekleþtirir. Aþaðýda kodun amacý, açýklamalarý ve çalýþma biçimi hakkýnda bilgi verilmiþtir:

Amacý: Kodun amacý, verilen veri noktalarýný kümelere ayýrmak ve her bir kümenin merkezini ve içerdiði noktalarýn sayýsýný hesaplamaktýr. Bu þekilde, veriler daha küçük ve daha anlamlý gruplara ayrýlarak analiz edilebilir.

Açýklamalarý: Kod, Nokta ve Kume isimli iki yapýyý kullanýr. Nokta yapýlarý, iki boyutlu koordinatlarý tutmak için kullanýlýr. Kume yapýlarý ise bir kümenin merkez noktasýný, içerdiði nokta sayýsýný ve noktalarý tutmak için kullanýlýr.

Çalýþma Biçimi: Kodun çalýþma biçimi aþaðýdaki adýmlarla gerçekleþtirilir:

Ýlk olarak, veri noktalarý rastgele bir þekilde oluþturulur ve veri_noktalari dizisine kaydedilir.

Ardýndan, baþlangýç küme merkezlerini rastgele seçer ve her bir kümeye birer nokta atar.

Kümeleme iþlemi, veri noktalarýný döngüyle gezerek gerçekleþtirilir. Her bir veri noktasý için en yakýn küme merkezini bulur ve mesafeyi hesaplar.

Eðer mesafe, belirli bir eþik deðerinden büyükse yeni bir küme oluþturulur ve bu yeni kümenin merkezi olarak veri noktasý atanýr.

Eðer mesafe, eþik deðerinden küçükse en yakýn küme merkezine veri noktasý eklenir.

Sonuç olarak, oluþan kümelerin merkez noktalarý, içerdikleri nokta sayýlarý ve noktalarý ekrana yazdýrýlýr.

Bu þekilde, veri noktalarý birbirlerine benzerliklerine göre kümelere ayrýlýr ve kümeleme sonuçlarý ekrana yazdýrýlýr.*/

#define MAKS_NOKTALAR 100 //kodun çalýþtýðý veri setinde en fazla 100 nokta olabilir
#define MAKS_BOYUT 2 // her bir noktanýn boyutunu belirtir.
//her bir noktanýn koordinatlarýný tutmak için kullanýlýr.
typedef struct {
    double koordinatlar[MAKS_BOYUT]; //her bir noktanýn double boyutta koordinatlarý saklanabilir.
} Nokta;

typedef struct {
    Nokta merkez;
    int nokta_sayisi;
    Nokta *noktalar;
} Kume;

void birch(Kume *kumeler, Nokta *veri_noktalari, int kume_sayisi, int veri_nokta_sayisi, double esik) {
	int i,j,k;
    // Ýlk kümeleri rastgele seçme
    for ( i = 0; i < kume_sayisi; i++) {//Döngü kullanýlarak her bir küme için aþaðýdaki iþlemler yapýlýr:
        kumeler[i].merkez = veri_noktalari[i];//Küme merkezi, veri_noktalari dizisindeki ilgili noktaya eþitlenir.
        kumeler[i].nokta_sayisi = 1;//Kümenin nokta sayýsý 1 olarak ayarlanýr.
        kumeler[i].noktalar = (Nokta *)malloc(sizeof(Nokta));//Bellekte bir Nokta boyutunda yer ayrýlýr ve bu noktaya, kümenin merkez noktasý atanýr.
        kumeler[i].noktalar[0] = veri_noktalari[i];//Bu iþlemler sonucunda, baþlangýç küme merkezleri rastgele seçilir ve her bir küme sadece bir noktayý temsil eder. Bu adým, BIRCH algoritmasýnýn baþlangýç durumunu oluþturur.
    }

    // Kümeleme iþlemi
  for ( i = kume_sayisi; i < veri_nokta_sayisi; i++) {//kume_sayisi'ndan baþlayarak, veri_nokta_sayisi'ne kadar olan veri noktalarý üzerinde döngü oluþturulur.
        Nokta veri_noktasi = veri_noktalari[i];//Her bir veri noktasý, veri_noktalari dizisinden alýnarak veri_noktasi deðiþkenine atanýr.
        double min_mesafe = INFINITY;//min_mesafe deðiþkeni, sonsuz deðer (INFINITY) ile baþlatýlýr.
        int en_yakin_kume_indeksi = -1;//en_yakin_kume_indeksi deðiþkeni, en yakýn küme merkezinin indisini tutar. Baþlangýçta -1 olarak atanýr.

        // En yakýn küme merkezini bulma
        for ( j = 0; j < kume_sayisi; j++) {//j deðiþkeni, mevcut kümenin indisini temsil eder. Ýlk kümeden baþlayarak, kume_sayisi'ne kadar olan küme merkezleri üzerinde döngü oluþturulur.
            double mesafe = 0.0;//Her bir küme merkezi ile veri noktasý arasýndaki mesafe hesaplanýr ve mesafe deðiþkenine atanýr. Baþlangýçta mesafe sýfýr olarak atanýr.
            for ( k = 0; k < MAKS_BOYUT; k++) {
                double fark = veri_noktasi.koordinatlar[k] - kumeler[j].merkez.koordinatlar[k];//Ýç içe döngü kullanýlarak her bir boyut için fark hesaplanýr. Veri noktasýnýn her bir boyutu, ilgili küme merkezinin ayný boyutundan çýkarýlýr ve bu fark deðeri fark deðiþkenine atanýr.
                mesafe += fark * fark;//Her bir boyut için farkýn karesi hesaplanýr ve mesafe deðiþkenine eklenir.
            }
            mesafe = sqrt(mesafe);//Son olarak, hesaplanan mesafe deðeri, Euclidean mesafesi için karekök alýnarak güncellenir.
           //Eðer hesaplanan mesafe, min_mesafe'den daha küçük ise, min_mesafe güncellenir ve en_yakin_kume_indeksi ilgili kümenin indisine atanýr. 
            if (mesafe < min_mesafe) {
                min_mesafe = mesafe;
                en_yakin_kume_indeksi = j;
            }
        }

        // Eðer mesafe eþik deðerinden büyükse yeni bir küme oluþtur
           if (min_mesafe > esik) {// //Eðer en yakýn küme merkezi ile veri noktasý arasýndaki mesafe (min_mesafe) eþik deðerinden büyük ise, bu durumda yeni bir küme oluþturulur. Ýlgili kümeye ait bilgiler güncellenir:
            kumeler[kume_sayisi].merkez = veri_noktasi;//kumeler[kume_sayisi].merkez, yeni oluþturulan kümenin merkezi olarak belirlenir ve veri_noktasi deðeri atanýr.
            kumeler[kume_sayisi].nokta_sayisi = 1;//kumeler[kume_sayisi].nokta_sayisi, 1 olarak ayarlanýr çünkü yeni oluþturulan küme yalnýzca veri noktasýný içerir.
            kumeler[kume_sayisi].noktalar = (Nokta *)malloc(sizeof(Nokta));//kumeler[kume_sayisi].noktalar, bellekte dinamik olarak ayrýlan bir alan olarak ayarlanýr ve veri_noktasi deðeri bu alana atanýr.
            kumeler[kume_sayisi].noktalar[0] = veri_noktasi;
            kume_sayisi++;//kume_sayisi deðiþkeni bir artýrýlýr, çünkü yeni bir küme oluþturulmuþtur.
        } else {
            // En yakýn küme merkezine veri noktasýný ekle
            //Eðer en yakýn küme merkezi ile veri noktasý arasýndaki mesafe (min_mesafe) eþik deðerinden küçük veya eþit ise, bu durumda veri noktasý en yakýn küme merkezine eklenir. Ýlgili kümeye ait bilgiler güncellenir:
            kumeler[en_yakin_kume_indeksi].nokta_sayisi++; //kumeler[en_yakin_kume_indeksi].nokta_sayisi bir artýrýlýr, çünkü veri noktasý bu kümeye eklenmiþtir.
            kumeler[en_yakin_kume_indeksi].noktalar = (Nokta *)realloc(kumeler[en_yakin_kume_indeksi].noktalar,//kumeler[en_yakin_kume_indeksi].noktalar, bellekte yeniden boyutlandýrýlarak daha fazla veri noktasýný içerecek þekilde güncellenir.
                                                                      kumeler[en_yakin_kume_indeksi].nokta_sayisi * sizeof(Nokta));
            kumeler[en_yakin_kume_indeksi].noktalar[kumeler[en_yakin_kume_indeksi].nokta_sayisi - 1] = veri_noktasi;//Veri noktasý, kumeler[en_yakin_kume_indeksi].noktalar dizisinin sonuna eklenir.
        }
    }
}

int main() {
	int i,j,k;//tanýmla
    Nokta veri_noktalari[MAKS_NOKTALAR];//tanýmla
    Kume kumeler[MAKS_NOKTALAR];//tanýmla
    int veri_nokta_sayisi = 10;//deger verildi
    int kume_sayisi = 3;//deger verildi
    double esik = 2.0;//deger verildi

    // Veri noktalarýný oluþturma
    for ( i = 0; i < veri_nokta_sayisi; i++) {
        for (j = 0; j < MAKS_BOYUT; j++) {
            veri_noktalari[i].koordinatlar[j] = (double)rand() / RAND_MAX * 10.0;
        }
    }

    // Birch algoritmasý ile kümeleme yapma
    birch(kumeler, veri_noktalari, kume_sayisi, veri_nokta_sayisi, esik);

    // Elde edilen kümeleme sonuçlarýný yazdýrma
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

