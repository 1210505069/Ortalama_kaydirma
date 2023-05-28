#include <stdio.h>
#include <stdlib.h>
#include <math.h>


// Veri yapisi
typedef struct {
    float x;
    float y;
    int renk;
} Veri;

// Ortalama kaydirmali kumeleme algoritmasi
void ortalamaKaydirmaKumeleme(Veri veriler[], int n, float epsilon_x, float epsilon_y, float epsilon_renk, float minNoktaMesafe) {
    int* atananKume = (int*)malloc(n * sizeof(int)); 
	// Atanan kume indeksleri
    int* kumeSayisi = (int*)malloc(n * sizeof(int)); 
	// Kume icindeki nokta sayisi

    int kumeSayac = 0; 
	// Toplam kume sayisi

    for (int i = 0; i < n; i++) {
        atananKume[i] = -1; 
		// Baslangicta hicbir nokta bir küme ile iliskilendirilmedi
    }

    for (int i = 0; i < n; i++) {
        if (atananKume[i] == -1) {
            // Yeni bir kume olusturuldu
            atananKume[i] = kumeSayac;
            kumeSayisi[kumeSayac] = 1;
            kumeSayac++;

            // Yeni kume merkezi
            float merkezX = veriler[i].x;
            float merkezY = veriler[i].y;

            int iterasyon = 0;
            int noktaEklendi = 1;

            while (noktaEklendi) {
                noktaEklendi = 0;

                // Verileri gez
                for (int j = 0; j < n; j++) {
                    if (atananKume[j] == -1) {
                        // Nokta henuz bir küme ile iliskilendirilmedi

                        // Nokta ile kume merkezi arasindaki mesafeleri hesapla
                        float mesafe_x = fabs(veriler[j].x - merkezX);
                        float mesafe_y = fabs(veriler[j].y - merkezY);
                        float mesafe_renk = (veriler[j].renk != veriler[i].renk) ? 1.0 : 0.0;

                        // Mesafe kriterlerini kontrol et
                        if (mesafe_x <= epsilon_x && mesafe_y <= epsilon_y && mesafe_renk <= epsilon_renk && kumeSayisi[atananKume[i]] < minNoktaMesafe) {
                            // Nokta kume ile iliskilendirilebilir
                            atananKume[j] = atananKume[i];
                            kumeSayisi[atananKume[i]]++;
                            noktaEklendi = 1;

                            // Kume merkezini guncelle (ortalama degerler)
                            merkezX = (merkezX * (kumeSayisi[atananKume[i]] - 1) + veriler[j].x) / kumeSayisi[atananKume[i]];
                            merkezY = (merkezY * (kumeSayisi[atananKume[i]] - 1) + veriler[j].y) / kumeSayisi[atananKume[i]];
                        }
                    }
                }

                iterasyon++;
            }
        }
    }

    // Kumeleme sonuclarini yazdir
    for (int i = 0; i < kumeSayac; i++) {
        printf("Kume %d:\n", i+1);
        for (int j = 0; j < n; j++) {
            if (atananKume[j] == i) {
                printf("(%.2f, %.2f, %d)\n", veriler[j].x, veriler[j].y, veriler[j].renk);
            }
        }
        printf("\n");
    }

    free(atananKume);
    free(kumeSayisi);
}


int main(int argc, char *argv[]) {
    int n;
    printf("Veri sayisini girin: ");
    scanf("%d", &n);

    Veri* veriler = (Veri*)malloc(n * sizeof(Veri));

    for (int i = 0; i < n; i++) {
        printf("Veri %d:\n", i + 1);
        printf("X koordinatini girin: ");
        scanf("%f", &veriler[i].x);
        printf("Y koordinatini girin: ");
        scanf("%f", &veriler[i].y);
        printf("Renk degerini girin: ");
        scanf("%d", &veriler[i].renk);
        printf("\n");
    }

    float epsilon_x = 150; // Kumeleme yaricapi (X koordinatý icin)
    float epsilon_y = 120; // Kumeleme yaricapi (Y koordinatý icin)
    float epsilon_renk = 1; // Kumeleme yaricapi (Renk icin)
    float minNoktaMesafe = 3; // Kumeleme icin minimum nokta sayisi

    // Kumeleme algoritmasýný cagir
    ortalamaKaydirmaKumeleme(veriler, n, epsilon_x, epsilon_y, epsilon_renk, minNoktaMesafe);

    free(veriler);
    return 0;
}

