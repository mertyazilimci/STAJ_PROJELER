#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <math.h>


#define MAX_OYUNCU 30
#define MAX_MAC 10
#define MAX_GOL_ASIST 30
#define MAX_RAKIP 11



//---------------------------------------------------------Structlar------------------------------------------------------------------------------


struct oyuncu {
	
	int formaNo;
	char oyuncuAd[50];
	int toplamGol;
	int toplamAsist;
	int oynananMacSayisi;
	double oyuncuRating;
	
};



struct bizimIstatistik {
	
	char takimimAdi[50];
	int takimimNo;
	int oynananMac;
	int galibiyet;
	int beraberlik;
	int maglubiyet;
	int atilanGol;
	int yenilenGol;
	int averaj;
	int toplamPuan;
	int ratingler;
};



struct mac {
	
	int macNo;
	int takimGolu;
	int rakipGolu;
	char macTarihi[20];
	int golDakikalari[MAX_GOL_ASIST];
	int asistDakikalari[MAX_GOL_ASIST];
	
	int asistSayisi;	
};



struct rakip {
	
	char rakipAdi[15];
	int rakipNo;
	int oynananMac;
	int galibiyet;
	int beraberlik;
	int maglubiyet;
	int atilanGol;
	int yenilenGol;
	int averaj;
	int toplamPuan;
	int ratingler;
	
};


//-----------------------------------------------------------Global Deðiþkenler-----------------------------------------------------------------

int menu ();

int evDeplasman;
int oncekiDakikaGlobal = -1;
double toplamPerformansPuani = 0.0;
double atilanGollerinDakikaOrtalamasi = 0.0;
int encokGolatanlar[20];
int tut[2];

int golAtanlarKimler[300];
int oynayanFormaNo[11];
char takimAdi[50];
char takimlar [10][15] = {{"Fenerbahce"},{"Galatasaray"},{"Besiktas"},{"Trabzonspor"},{"Basaksehir"},{"Samsunspor"},{"Goztepe"},{"Kasimpasa"},{"Eyupspor"},{"Rizespor"}};
int takimlarRating [10] = {80, 80, 70, 65, 60, 55, 48, 45, 45, 45};

struct oyuncu oyuncular[MAX_OYUNCU];
int oyuncuSayisi = 0;

struct mac maclar[MAX_MAC];
 int macSayisi=0;


struct rakip rakipler[MAX_RAKIP];

struct bizimIstatistik bizimki;

int guvenli_Int();
void guvenli_String(char *hedef, int boyut);
int guvenli_FormaNo ();
int formaNo_Benzersizlik ();

void dosyayaOyuncuYaz();
void dosyayaTakimlariYaz ();
void dosyayaTakimlariYaz1 ();
void dosyayaEvdeplasmanYaz ();
void dosyayaEvdeplasmanYaz1 ();
void dosyayaMacYaz();
void dosyayaEncokGolAtanYaz ();
void dosyayaRakipYaz(struct rakip rakipler[], int sayi);
void dosyayaBizimkiYaz();

void dosyadanOyuncuOku();
void dosyadanTakimlariOku ();
void dosyadanTakimlariOku1 ();
void dosyadanEvdeplasmanOku ();
void dosyadanEvdeplasmanOku1 ();
void dosyadanMacOku();
void dosyadanEncokgolataniOku ();
void dosyadanRakipOku(struct rakip rakipler[], int *sayi);
void dosyadanBizimkiOku();

void oyuncuListele();
void oyuncuRatingHesapla();
int* oyuncuGelismisIstatistikHesapla(int skor, int golAtanlarFormaNo[]);
void ligIstatistikleriHesapla_1 ();
void bizimTakimiDahilEt ();
int ligIstatistikleriHesapla (int bizimtakimGol,int rakipTakimGol,int rakipNosu);

//-----------------------------------------------------------Güvenlik Fonksiyonlarý------------------------------------------------------------



int guvenli_Int() {
    char giris[100];
    int sayi;
    
    while (1) {
        fgets(giris, sizeof(giris), stdin);

        // Sadece enter'a basýldýysa veya boþluk girildiyse
        if (giris[0] == '\n') {
            printf("\nBos giris yapamazsiniz! Lutfen bir sayi giriniz:\n");
            continue;
        }

        // Girilen veri sayý mý?
        if (sscanf(giris, "%d", &sayi) == 1) {

            // Negatif sayi kontrolü
            if (sayi < 0) {
                printf("\nNegatif sayi girdiniz! Lutfen pozitif bir sayi giriniz:\n");
                continue;
            }

            // Aþýrý büyük sayý kontrolü (güvenlik amaçlý)
            if (sayi > 1000) {
                printf("\nCok buyuk bir sayi girdiniz! Lutfen daha kucuk bir deger girin:\n");
                continue;
            }

            return sayi;
        } else {
            printf("\nGecersiz giris! Lutfen bir sayi giriniz:\n");
        }
    }
}




void guvenli_String(char *hedef, int boyut) {
	
	int i;
	
    while (1) {
        if (fgets(hedef, boyut, stdin) != NULL) {
            int len = strlen(hedef);
            if (len > 0 && hedef[len - 1] == '\n') {
                hedef[len - 1] = '\0';  // '\n' varsa temizle
                len--;
            }

            // Boþluklarý say
            int bosKarakterSayisi = 0;
            for (i = 0; i < len; i++) {
                if (isspace((unsigned char)hedef[i])) {
                    bosKarakterSayisi++;
                }
            }

            if (len == 0 || bosKarakterSayisi == len) {
                printf("Bos giris yapamazsiniz, lutfen tekrar deneyin:\n");
                continue;  // Tekrar giriþ ister
            }

            break;  // Geçerli giriþ
        } else {
            printf("Giris hatasi, lutfen tekrar deneyin:\n");
            // stdin temizlenebilir istersen burada
        }
    }
}




int guvenli_FormaNo () {
	
	int formaNumara;

while (1) {
		
		printf ("\nForma numarasini giriniz:\n");
		formaNumara = guvenli_Int();
	
	if (formaNumara <= 99 && formaNumara > 0) {
		
		break;	
	}
	else {
		printf("\nLutfen 1-99 arasinda bir deger giriniz.\n");
	}
	
}	
	
return formaNumara;	
}




int formaNo_Benzersizlik ()  {
	
	int formaBenzersiz,i,cikis;
	
	while (1) {
		
		formaBenzersiz = guvenli_FormaNo ();
		cikis = 0;
	
	for (i = 0 ; i < oyuncuSayisi ; i ++) {
		
		if ( formaBenzersiz == oyuncular[i].formaNo ) {
			
			printf ("\nForma numarasi bos deðil.\n");
			cikis = 1;	
			break;
		 }
	  }
	
	if (cikis == 0) {
		 return formaBenzersiz;
	  }	
	}	
}




int gol_asistKontrol () {
	
	int skor;
	
	while (1) {
		
		skor = guvenli_Int ();
	
	if (skor > MAX_GOL_ASIST) {
		printf("\nGol sayisi maksimum 30 girilebilir.\n");
		continue;
	}
	
	break;
	}
	return skor;
}



int dakikaKontrol() {
	
    int dakika;
    
    while (1) {
    	
        dakika = guvenli_Int();
        
        if (dakika < 1 || dakika > 90) {
        	
            printf("\n1-90 arasi gir\n");
        continue;
        }
        
        if (oncekiDakikaGlobal == 90) {
    if (dakika != 90) {
        printf("\n90. dakikada gol var, buraya da sadece 90 yazabilirsin.\n");
        continue;
    }
    break;
}
        
        if (oncekiDakikaGlobal != -1 && dakika <= oncekiDakikaGlobal) {
            printf("\nDaha buyuk sayi gir\n");
           continue;
        }
        break;
    }
    oncekiDakikaGlobal = dakika;
    return dakika;
}



int menuyeDonVeyaCikis () {
    int secim;
    
    printf("\n0 - Ana menuye don.Devam icin herhangi bir sayi tuslayiniz.\n");
    secim = guvenli_Int();
    
    if (secim == 0) {
        return 0; // Menüye dön
    } else {
        return 1;
    }
}


void golAsistTemizle(int macIndex) {
	
	int i;
	
    for (i = 0; i < MAX_GOL_ASIST; i++) {
        maclar[macIndex].golDakikalari[i] = 0;
        maclar[macIndex].asistDakikalari[i] = 0;
    }
    maclar[macIndex].asistSayisi = 0;
}



//-------------------------------------------------------------Sýralama Fonksiyon---------------------------------------------------------------------


void bubble_Sort (int dizi[],int boyut) {
	
	int i,j;
	
	for(i=0;i<boyut;i++) {
		
		for(j=1;j<boyut-i;j++) {
			
			if(dizi[j-1] > dizi[j]) {
				
			int temp = dizi[j];	
			dizi[j] = dizi[j-1];
			dizi[j-1] = temp;
			}
		}
	}
}





//------------------------------------------------------------Sigmoid fonksiyonu--------------------------------------------------------------



double sigmoid_puan(double katki) {
    double k = 0.04;     // eðrilik katsayýsý - artarsa deðerler birbirine yaklaþýr
    double x0 = 50.0;    // eðrinin merkez noktasý

    double sonuc = 100.0 / (1.0 + exp(-k * (katki - x0)));
    return sonuc;
}



//-------------------------------------------------------------Menü Sistemi---------------------------------------------------------------------


int menu ()  {
	
	int secim;
	
	printf("------------------------------------------------------------------------------------------------------------------------");
	printf ("\nFUTBOL TAKIM YONETIMI\n\n\n1-)  Takim ismi belirle/Guncelle\n2-)  Oyuncu ekle\n3-)  Oyuncu sil\n4-)  Oyuncu guncelle\n5-)  Oyuncu listele\n6-)  Oyuncu istatistik sifirlama\n7-)  Fikstur olustur\n8-)  Fikstur goster\n9-)  Lig olustur/Mac yap\n10-) Mac sonuc listele\n11-) Takim istatistikleri\n12-) Oyuncu istatistikleri\n13-) Lig istatistikleri\n0-)  Cikis\n\nLutfen secim yapiniz.\n");
	
	secim = guvenli_Int ();
	
				return secim;
}


//------------------------------------------------------------Takým Yönetimi--------------------------------------------------------------------



void takimIsmiAl_Guncelle()   {
	 
	printf ("\nTakim adi:\n");
	guvenli_String (takimAdi,sizeof(takimAdi));
	
	dosyayaEvdeplasmanYaz ();
	
	printf("\nTakim adi: %s\n\n",takimAdi);
}  



//------------------------------------------------------------Oyuncu Yönetimi------------------------------------------------------------------



void oyuncuEkle() {
	
	if (oyuncuSayisi >= MAX_OYUNCU ) {
		
		printf("\nOyuncu kontenjani dolu.\n");
		return;
	}
		
	printf("\nOYUNCU EKLE:\n");	
		oyuncular[oyuncuSayisi].formaNo = formaNo_Benzersizlik ();
	
	printf("\nOyuncu adini giriniz.\n");
	guvenli_String(oyuncular[oyuncuSayisi].oyuncuAd,sizeof (oyuncular[oyuncuSayisi].oyuncuAd));
	
	oyuncuSayisi ++;
	dosyayaOyuncuYaz();
	
	printf("\nOyuncu basariyla eklendi.\n");
}





void oyuncuSil() {
	
	int i,j,sil,kontrol=0;
	
	if (oyuncuSayisi == 0) {	
		printf("\nSilinecek oyuncu yok.\n");
		return;
	}
	
	printf ("\nOYUNCU SIL\n");
	sil = guvenli_FormaNo ();
	
	for(i=0;i<oyuncuSayisi;i++) {
		
		if (sil == oyuncular[i].formaNo) {
			
			for (j=i;j<oyuncuSayisi-1;j++) {
				
				oyuncular[j] = oyuncular[j+1];
			}	
			oyuncuSayisi --;
				kontrol = 1;	
				break;
		}	
	}	
	
	if (kontrol == 0) {
		printf("\nOyuncu bulunamadi.\n");
		return;
	}
	dosyayaOyuncuYaz();
	printf("\nOyuncu basariyla silindi.\n");
}





void oyuncuGuncelle() {
	
	int guncelle,i,yeniNumara;
	
	if (oyuncuSayisi == 0) {	
		printf("\nGuncellenecek oyuncu yok.\n");
		return;
	}
	oyuncuListele();
	
	printf("\nGuncellemek istediginiz oyuncunun bilgilerini giriniz:\n");
	guncelle = guvenli_FormaNo ();
	
	for(i=0;i<oyuncuSayisi;i++) {
		
		if(guncelle == oyuncular[i].formaNo) {
			printf("\nOyuncu bulundu:\n\n%-8s %-30s %-5s %-6s %-12s %-7s\n\n", "FormaNo", "Oyuncu Adi", "Gol", "Asist", "Oynanan Mac", "Rating");
			printf("%-8d %-30s %-5d %-6d %-12d %-7.2f\n",oyuncular[i].formaNo,oyuncular[i].oyuncuAd,oyuncular[i].toplamGol,
			oyuncular[i].toplamAsist,oyuncular[i].oynananMacSayisi,oyuncular[i].oyuncuRating);
			
			printf("\nNumara degisimini atlamak icin 0 tuslayiniz.Devam etmek icin herhangi bir sayi tuslayiniz.\n");
			yeniNumara = guvenli_Int();
			
			if (yeniNumara != 0) {
				
				yeniNumara = formaNo_Benzersizlik ();
		   oyuncular[i].formaNo = yeniNumara;
			}
		   	
			printf("\nOyuncu adini giriniz.\n");
	guvenli_String(oyuncular[i].oyuncuAd,sizeof (oyuncular[i].oyuncuAd));
	
	dosyayaOyuncuYaz();
	
	printf("\nOyuncu basariyla guncellendi.\n");
		return;
		}
	}
	printf("\nOyuncu bulunamadi.\n");
}




void oyuncuListele() {
	
	int formaTut[oyuncuSayisi],i,j,k;
	
	dosyadanOyuncuOku();
	oyuncuRatingHesapla();
	
	for(i=0;i<oyuncuSayisi;i++) {
		
	formaTut[i] = oyuncular[i].formaNo;	
		
	}
	
	bubble_Sort (formaTut,oyuncuSayisi);
	
	printf("\n%-8s %-30s %-5s %-6s %-12s %-7s\n\n", "FormaNo", "Oyuncu Adi", "Gol", "Asist", "Oynanan Mac", "Rating");
	
	for (j=0;j<oyuncuSayisi;j++) {
		for (k=0;k<oyuncuSayisi;k++) {
			
			if(formaTut[j] == oyuncular[k].formaNo) {
				
				printf("%-8d %-30s %-5d %-6d %-12d %-7.2f\n",oyuncular[k].formaNo,oyuncular[k].oyuncuAd,oyuncular[k].toplamGol,
				oyuncular[k].toplamAsist,oyuncular[k].oynananMacSayisi,oyuncular[k].oyuncuRating);
			break;
			}	
		}
	}
	
	printf("\nOyuncular listelenmistir. Toplam oyuncu sayisi: %d\n",oyuncuSayisi);
}




void oyuncuIstatistikSifirla () {
	
	int i;
	
	for (i=0;i<oyuncuSayisi;i++) {
		
		oyuncular[i].oynananMacSayisi = 0;
		oyuncular[i].toplamGol = 0;
		oyuncular[i].toplamAsist = 0;
		oyuncular[i].oyuncuRating =0.0;
	}
	dosyayaOyuncuYaz();
}



//---------------------------------------------------------Lig ve Maç Yönetimi-----------------------------------------------------------------




void macTarihiOlustur (int macIndex) {
	
	int dakika,saat,gun,ay,yil;
	char dakikalar[] = {0, 15, 30, 45};

   srand(time(NULL));
   
   dakika = dakikalar[rand() % 4];
   
   saat = (rand() % 5) + 18;
   
   gun = 3*(macIndex) +1;
   
   ay = 8;
   
   yil = 2025;

sprintf(maclar[macIndex].macTarihi,"%d:%02d  %d/%d/%d",saat,dakika,gun,ay,yil);

}



int fiksturOlustur() {
	
	int i,j;
	
	char temp[15];
	int tempRating;
	srand(time(NULL));
	
	for (i = 9; i > 0; i--) {
        j = rand() % (i + 1);
        // swap iþlemi
        strcpy(temp,takimlar[i]);
        strcpy(takimlar[i],takimlar[j]);
        strcpy(takimlar[j],temp);
        
        tempRating = takimlarRating[i];
        takimlarRating[i] = takimlarRating[j];
        takimlarRating[j] = tempRating;
    }
    dosyayaTakimlariYaz ();
      
    for (i=0;i<10;i++) {
		
		strcpy(rakipler[i].rakipAdi,takimlar[i]);
		rakipler[i].ratingler = takimlarRating[i];
	}
   evDeplasman = rand() % 2;
   
   if (evDeplasman == 0) {
   	 	
   	dosyayaEvdeplasmanYaz ();
   	printf("\nFikstur olusturuldu.\n");
   	return 0;
   }
   else if(evDeplasman == 1) {

   	printf("\nFikstur olusturuldu.\n");
   	dosyayaEvdeplasmanYaz ();
   return 1;	
   }
}


void fiksturGoster () {
	
	int i;
	
	printf("\n");
	
	dosyadanEvdeplasmanOku ();
	dosyadanTakimlariOku ();
	
	if (evDeplasman == 0) {
		
		for (i = 0;i < 10; i+=2) {
			
		printf("%-20s - %20s\n",takimAdi,takimlar[i]);
		printf("%-20s - %20s\n",takimlar[i+1],takimAdi);	
		}
		printf("\nFikstur listelenmistir.\n");
	}
	
	else if (evDeplasman == 1) {
		
		for (i = 0;i < 10; i+=2) {
			
		printf("%-20s - %20s\n",takimlar[i],takimAdi);	
		printf("%-20s - %20s\n",takimAdi,takimlar[i+1]);	
		}
		printf("\nFikstur listelenmistir.\n");
	}
	
}




int oyuncuVarsa_golYaz (int golIndex) {
	
	int forma,i,j;
	
	while (1) {
		
		printf("\nGolu atan oyuncunun:\n");
	forma = guvenli_FormaNo ();
	
	   
	   for (i=0;i<11;i++) {     // önce seçilenlerde var mý bakar.Sonra varsa bu seçilenlerdeki oyuncu hangi indekste bulur ve iþlemleri yapar.
	   	
	   	if(forma == oynayanFormaNo[i]) {
	   		
	   		for (j=0;j<oyuncuSayisi;j++) {
	   			
	   			if (forma == oyuncular[j].formaNo) {
	   				
	   				golAtanlarKimler[golIndex] = forma;
	   				golIndex++;
	   				 oyuncular[j].toplamGol ++;
						return oyuncular[j].formaNo;
				   }
			   }
		   }
	   	
	   }
	printf("\nGirdiginiz forma numarasina ait oyuncu mac kadrosunda yok.\n");
	continue;	
	}
}




void oyuncuVarsa_asistYaz (int formatut) {
	
	int forma,i,j;
	
	while (1) {
		
		printf("\nAsist yapan oyuncunun:\n");
	forma = guvenli_FormaNo ();
	
	if(formatut == forma) {
		printf("\nGolu atan oyuncu ile asist yapan oyuncu ayni olamaz.\n");
		continue;
	}
	
 /*	for (i=0;i<oyuncuSayisi;i++) {
		
		if (forma == oyuncular[i].formaNo) {
			
			oyuncular[i].toplamAsist ++;
			return;
	 	  }
	   }  */
	   
	   for (i=0;i<11;i++) {     // önce seçilenlerde var mý bakar.Sonra varsa bu seçilenlerdeki oyuncu hangi indekste bulur ve iþlemleri yapar.
	   	
	   	if(forma == oynayanFormaNo[i]) {
	   		
	   		for (j=0;j<oyuncuSayisi;j++) {
	   			
	   			if (forma == oyuncular[j].formaNo) {
	   				
	   				 oyuncular[j].toplamAsist ++;
						return;
				   }
			   }
		   }
	   	
	   }
	printf("\nGirdiginiz forma numarasina ait oyuncu mac kadrosunda yok.\n");
	continue;	
	}
}




void gol_asistDakikaGirisi (int skor,int macIndex) {
	
	int i,varMI,tut;
	int asistIndex = 0;
	
	golAsistTemizle(macIndex);
	
	for(i=0;i<skor && i < MAX_GOL_ASIST;i++) {
		
		printf("\n%d. gol kacinci dakikada atildi?\n",i+1);
		maclar[macIndex].golDakikalari[i] = dakikaKontrol();
		tut = oyuncuVarsa_golYaz (i);
		
		printf("\n%d. golun asisti var mi? (Varsa 1 Yoksa herhangi bir sayi giriniz)\n",i+1);
		varMI = guvenli_Int ();
		
		if (varMI == 1) {
			
		maclar[macIndex].asistDakikalari[asistIndex] = maclar[macIndex].golDakikalari[i];
		oyuncuVarsa_asistYaz (tut);
		maclar[macIndex].asistSayisi ++;
		asistIndex++;
		
		printf("\nGol ve asist dakikasi kaydedildi.\n");
		continue;
		}
		printf("\nGol dakikasi kaydedildi.\n");
	}
}





void mactaOynayanlar () {

	int i,secim,j,secildi,tut;
	
	int otomatikMi,temp,tutOto;
	
	int dizi[oyuncuSayisi];
	
	srand (time (NULL));
	
	oyuncuListele();
	
	printf ("\nMacta oynayacak oyunculari otomatik secmek icin 0 tuslayiniz. Manuel secim icin herhangi bir rakam giriniz:\n");
	  otomatikMi = guvenli_Int ();
	  
	  if (otomatikMi == 0) {
	  	
	  	for (i=0;i<oyuncuSayisi;i++) {
	  		
	  		dizi[i] = oyuncular[i].formaNo;
		  }
		  
		  for (i = oyuncuSayisi-1; i > 0; i--) {
        j = rand() % (i + 1);
        // swap iþlemi
        temp = dizi[i];
        dizi[i] = dizi[j];
        dizi[j] = temp;
            }
          
          for (i=0;i<11;i++) {
          	
	  		 tutOto = dizi[i];
	  		 
	  		 for (j=0;j<oyuncuSayisi;j++) {
	  		 	
	  		 	if (oyuncular[j].formaNo == tutOto) {
	  		 		
               oyuncular[j].oynananMacSayisi += 10;
               oynayanFormaNo[i] = tutOto;
               break;
                    }
			   }
		  }
	  }
	  
	
	if (otomatikMi != 0) {
		
	printf("\nMacta oynayacak 11 oyuncu secimi: Sirayla oyuncularin forma numarasini giriniz.\n");
	
	secildi = 0;
	
	for (i=0;i<11;i++) {
		
		while (1) {
			
			printf("\n%d. Oyuncuyu seciniz:\n",i+1);
		secim = guvenli_FormaNo ();
		
		int bulundu = 0;
		secildi = 0;
		
		for (j=0;j<oyuncuSayisi;j++) {
		
		if (secim == oyuncular[j].formaNo) {
			
			tut = j;
			bulundu = 1;
			break;
	 	     }
	       }	
	       
	       if (bulundu == 0) {
                printf("\nBu forma numarasina sahip bir oyuncu bulunamadi.Tekrar deneyin.\n");
                continue;
            }
            
            for (j = 0; j < i; j++) {
                if (oynayanFormaNo[j] == secim) {
                    secildi = 1;
                    break;
                }
            }
            
            if (secildi) {
                printf("\nBu oyuncu zaten secildi! Lutfen farkli bir oyuncu secin.\n");
            } 
			
			else {
				oyuncular[tut].oynananMacSayisi += 10;
			//	dosyayaOyuncuYaz();
                oynayanFormaNo[i] = secim;
                break;
            }
		}	
	}	
	printf("\nMacta oynayacak oyuncular basariyla secildi.\n");	
  }
	
}



void takimYendiMi (int bizim,int rakip,int IndexAl) {
	
	if (bizim > rakip) {
		
		bizimki.galibiyet += 1;
	}
	
	if (bizim == rakip) {
		
		bizimki.beraberlik += 1;
	}
	
	if (bizim < rakip) {
		
		bizimki.maglubiyet += 1;
	}
	
}





void skorGirisiYap() {  //    Ana Fonksiyon 
	
	int i,skorEv,skorDeplasman,cikis;
	
	macSayisi=0;
		
		if ( macSayisi >= MAX_MAC ) {
			printf("\nMac sayisi sinirina ulasildi.\n");
			return;
		}
	 	
	 	// SkorGirisiYap fonksiyonun basina eklenecek
bizimki.oynananMac = 0;
bizimki.galibiyet = 0;
bizimki.beraberlik = 0;
bizimki.maglubiyet = 0;
bizimki.atilanGol = 0;
bizimki.yenilenGol = 0;
bizimki.averaj = 0;
bizimki.toplamPuan = 0;  
	 	
	 	// istatistik sýfýrlama
 for (i = 0; i < 11; i++) {
        rakipler[i].oynananMac = 0;
        rakipler[i].galibiyet = 0;
        rakipler[i].beraberlik = 0;
        rakipler[i].maglubiyet = 0;
        rakipler[i].atilanGol = 0;
        rakipler[i].yenilenGol = 0;
        rakipler[i].averaj = 0;
        rakipler[i].toplamPuan = 0;
    }

dosyayaRakipYaz(rakipler, 11);
	
	if (evDeplasman == 0) {
		
		cikis = menuyeDonVeyaCikis ();
			
			if (cikis == 0) {
				return;
			}
		
		mactaOynayanlar ();
		
		for (i = 0;i < 10; i+=2) {
			
			
		printf("\n%s - %s\n",takimAdi,takimlar[i]);
		
		printf("\n%s takiminin gol sayisini giriniz:\n",takimAdi);
		oncekiDakikaGlobal = -1;
		macSayisi ++;
		golAsistTemizle(macSayisi - 1);
		maclar[macSayisi-1].takimGolu = gol_asistKontrol ();
		gol_asistDakikaGirisi (maclar[macSayisi-1].takimGolu,macSayisi-1);
		
		
		int* dizi = oyuncuGelismisIstatistikHesapla(maclar[macSayisi-1].takimGolu,golAtanlarKimler);
		encokGolatanlar[(macSayisi-1)*2] = dizi[0];
		encokGolatanlar[(macSayisi-1)*2 + 1] = dizi[1];
		
		printf("\n%s takiminin gol sayisini giriniz:\n",takimlar[i]);
		maclar[macSayisi-1].rakipGolu = gol_asistKontrol ();
		
		maclar[macSayisi-1].macNo = macSayisi;
		macTarihiOlustur (macSayisi-1);
		
		takimYendiMi (maclar[macSayisi-1].takimGolu,maclar[macSayisi-1].rakipGolu,macSayisi-1);
		
		ligIstatistikleriHesapla (maclar[macSayisi-1].takimGolu,maclar[macSayisi-1].rakipGolu,macSayisi);
			
		
//-------------------------------------------------------------------------------- 2. maçlar		
		
		printf("\n%s - %s\n",takimlar[i+1],takimAdi);	
		
		printf("\n%s takiminin gol sayisini giriniz:\n",takimlar[i+1]);
		maclar[macSayisi].rakipGolu = gol_asistKontrol ();
		
		printf("\n%s takiminin gol sayisini giriniz:\n",takimAdi);
		oncekiDakikaGlobal = -1;
		macSayisi ++;
		golAsistTemizle(macSayisi - 1);
		maclar[macSayisi-1].takimGolu = gol_asistKontrol ();
		gol_asistDakikaGirisi (maclar[macSayisi-1].takimGolu,macSayisi-1);
		
		dizi = oyuncuGelismisIstatistikHesapla(maclar[macSayisi-1].takimGolu,golAtanlarKimler);
		encokGolatanlar[(macSayisi-1)*2] = dizi[0];    
        encokGolatanlar[(macSayisi-1)*2 + 1] = dizi[1];
		
		maclar[macSayisi-1].macNo = macSayisi;
		macTarihiOlustur (macSayisi-1);
		
		takimYendiMi (maclar[macSayisi-1].takimGolu,maclar[macSayisi-1].rakipGolu,macSayisi-1);
		
		
		ligIstatistikleriHesapla (maclar[macSayisi-1].takimGolu,maclar[macSayisi-1].rakipGolu,macSayisi);
		
		
		}
		ligIstatistikleriHesapla_1 ();
	//	golAsistTemizle(macSayisi - 1);
	dosyadanTakimlariOku ();
	dosyadanEvdeplasmanOku ();
	
	dosyayaOyuncuYaz();
	dosyayaTakimlariYaz1 ();
	dosyayaEvdeplasmanYaz1 ();
		dosyayaMacYaz();
		dosyayaEncokGolAtanYaz ();
		dosyayaBizimkiYaz();
		dosyayaRakipYaz(rakipler, 11);
		
	}
	
	else if (evDeplasman == 1) {
		
		cikis = menuyeDonVeyaCikis ();
			
			if (cikis == 0) {
				return;
			}
		
		mactaOynayanlar ();
		
		for (i = 0;i < 10; i+=2) {
			
			
		printf("\n%s - %s\n",takimlar[i],takimAdi);
		
		printf("\n%s takiminin gol sayisini giriniz:\n",takimlar[i]);
		maclar[macSayisi].rakipGolu = gol_asistKontrol ();
		
		printf("\n%s takiminin gol sayisini giriniz:\n",takimAdi);
		oncekiDakikaGlobal = -1;
		macSayisi ++;
		golAsistTemizle(macSayisi - 1);
		maclar[macSayisi-1].takimGolu = gol_asistKontrol ();
		gol_asistDakikaGirisi (maclar[macSayisi-1].takimGolu,macSayisi-1);
		
		int* dizi = oyuncuGelismisIstatistikHesapla(maclar[macSayisi-1].takimGolu,golAtanlarKimler);
		encokGolatanlar[(macSayisi-1)*2] = dizi[0];    
        encokGolatanlar[(macSayisi-1)*2 + 1] = dizi[1];
		
		maclar[macSayisi-1].macNo = macSayisi;
		macTarihiOlustur (macSayisi-1);
		
		takimYendiMi (maclar[macSayisi-1].takimGolu,maclar[macSayisi-1].rakipGolu,macSayisi-1);
		
		ligIstatistikleriHesapla (maclar[macSayisi-1].takimGolu,maclar[macSayisi-1].rakipGolu,macSayisi);
		
//-------------------------------------------------------------------------------- 2. maçlar

		printf("\n%s - %s\n",takimAdi,takimlar[i+1]);	
		
		printf("\n%s takiminin gol sayisini giriniz:\n",takimAdi);
		oncekiDakikaGlobal = -1;
		macSayisi ++;
		golAsistTemizle(macSayisi - 1);
		maclar[macSayisi-1].takimGolu = gol_asistKontrol ();
		gol_asistDakikaGirisi (maclar[macSayisi-1].takimGolu,macSayisi-1);
		
		dizi = oyuncuGelismisIstatistikHesapla(maclar[macSayisi-1].takimGolu,golAtanlarKimler);
		encokGolatanlar[(macSayisi-1)*2] = dizi[0];    
        encokGolatanlar[(macSayisi-1)*2 + 1] = dizi[1];
		
		printf("\n%s takiminin gol sayisini giriniz:\n",takimlar[i+1]);
		maclar[macSayisi-1].rakipGolu = gol_asistKontrol ();
		
		maclar[macSayisi-1].macNo = macSayisi;
		macTarihiOlustur (macSayisi-1);
		
		takimYendiMi (maclar[macSayisi-1].takimGolu,maclar[macSayisi-1].rakipGolu,macSayisi-1);
		
		ligIstatistikleriHesapla (maclar[macSayisi-1].takimGolu,maclar[macSayisi-1].rakipGolu,macSayisi);
		
		}
		ligIstatistikleriHesapla_1 ();
	//	golAsistTemizle(macSayisi - 1);
	dosyadanTakimlariOku ();
	dosyadanEvdeplasmanOku ();
	
	dosyayaOyuncuYaz();
	dosyayaTakimlariYaz1 ();
	dosyayaEvdeplasmanYaz1 ();
		dosyayaMacYaz();
		dosyayaEncokGolAtanYaz ();
		dosyayaBizimkiYaz();
		dosyayaRakipYaz(rakipler, 11);
	}	
}




void macSonucListele() {
	
	int i;
		
   if (macSayisi != MAX_MAC) {
		
		printf("\nMaclar tamamen bitmeden sonuclar listelenemez.\n");
		return;
	}
	   
	   dosyadanTakimlariOku1 ();
	   dosyadanEvdeplasmanOku1 ();
	   
        if (evDeplasman == 0) {
		
		printf ("\n");
		
		for (i=0;i<MAX_MAC;i+=2) {
		
		 printf ("%-15s  %d - %d  %15s\n",takimAdi,maclar[i].takimGolu,maclar[i].rakipGolu,takimlar[i]);
		 printf ("%-15s  %d - %d  %15s\n",takimlar[i+1],maclar[i+1].rakipGolu,maclar[i+1].takimGolu,takimAdi);
	}
  }
  
  if (evDeplasman == 1)  {
  	
  	printf ("\n");
  	
  	for (i=0;i<MAX_MAC;i+=2) {
		
		 printf ("%-15s  %d - %d  %15s\n",takimlar[i],maclar[i].rakipGolu,maclar[i].takimGolu,takimAdi);
		 printf ("%-15s  %d - %d  %15s\n",takimAdi,maclar[i+1].takimGolu,maclar[i+1].rakipGolu,takimlar[i+1]);
	    }
    }
    printf("\n\nEn son oynanan ligin sonuclari listelenmistir.\n");
}




//-------------------------------------------------------Ýstatistik ve Reyting-----------------------------------------------------------------




int* takimistatistikHesapla (double *toplamPerformansPuani,double *atilanGollerinDakikaOrtalamasi) {
	
	int i,j,dakika1_15=0,dakika15_30=0,dakika30_45=0,dakika45_60=0,dakika60_75=0,dakika75_90=0;
	int toplamTakimGolu= 0;
	int toplamRakipGolu= 0;
	int toplamTakimPuani = 0;
	int golYenmeyenMacSayisi = 0;
	int toplamTakimAsistSayisi = 0;
	int atilanGollerinDakikaToplami = 0;
	double puanPerformans=0.0,golYenmeyenPuan=0.0,asistPuan=0.0,golFarkiPuan=0.0;
	
	static int diziyiTut [12];
	
	dosyadanMacOku();
	
	for (i=0;i<MAX_MAC;i++) {
		
		toplamTakimGolu += maclar[i].takimGolu;
		toplamRakipGolu += maclar[i].rakipGolu;
		toplamTakimAsistSayisi += maclar[i].asistSayisi;
		
		diziyiTut [0] = toplamTakimGolu;
		diziyiTut [1] = toplamRakipGolu;
		diziyiTut [4] = toplamTakimAsistSayisi;
		
		if (maclar[i].rakipGolu == 0) {
			
			golYenmeyenMacSayisi ++;
			diziyiTut [3] = golYenmeyenMacSayisi;
		}
		
		if (maclar[i].takimGolu > maclar[i].rakipGolu) {
			toplamTakimPuani += 3;
			diziyiTut [2] = toplamTakimPuani;
		}
		if(maclar[i].takimGolu == maclar[i].rakipGolu) {
			toplamTakimPuani += 1;
			diziyiTut [2] = toplamTakimPuani;
		}
		if (maclar[i].takimGolu < maclar[i].rakipGolu) {
			toplamTakimPuani += 0;
			diziyiTut [2] = toplamTakimPuani;
		}
		
		
	for (j=0; j < maclar[i].takimGolu ;j++)	{
		
		if (maclar[i].golDakikalari[j] <= 15 && maclar[i].golDakikalari[j] >= 1) {
			
			dakika1_15 ++;
			diziyiTut [6] = dakika1_15;
		}
		
		if (maclar[i].golDakikalari[j] <= 30 && maclar[i].golDakikalari[j] > 15) {
			
			dakika15_30 ++;
			diziyiTut [7] = dakika15_30;
		}
		
		if (maclar[i].golDakikalari[j] <= 45 && maclar[i].golDakikalari[j] > 30) {
			
			dakika30_45 ++;
			diziyiTut [8] = dakika30_45;
		}
		
		if (maclar[i].golDakikalari[j] <= 60 && maclar[i].golDakikalari[j] > 45) {
			
			dakika45_60 ++;
			diziyiTut [9] = dakika45_60;
		}
		
		if (maclar[i].golDakikalari[j] <= 75 && maclar[i].golDakikalari[j] > 60) {
			
			dakika60_75 ++;
			diziyiTut [10] = dakika60_75;
		}
		
		if (maclar[i].golDakikalari[j] <= 90 && maclar[i].golDakikalari[j] > 75) {
			
			dakika75_90 ++;
			diziyiTut [11] = dakika75_90;
		}
		
		atilanGollerinDakikaToplami = (maclar[i].golDakikalari[j] + atilanGollerinDakikaToplami);
			
	  }
   }
   
	if (toplamTakimGolu != 0) {
    *atilanGollerinDakikaOrtalamasi = (double)atilanGollerinDakikaToplami / toplamTakimGolu;
        } 
			else  {
    			*atilanGollerinDakikaOrtalamasi = 0; // Veya -1 ile geçersiz deðer
 			  }
  //	diziyiTut [5] = atilanGollerinDakikaOrtalamasi;
	
	puanPerformans = toplamTakimPuani * 2;
	golYenmeyenPuan = golYenmeyenMacSayisi * 2;
	
	if (toplamTakimAsistSayisi >= 30 ){
		
		asistPuan = 10.0;
	}
	if (toplamTakimAsistSayisi < 30) {
		
		asistPuan = ((double)toplamTakimAsistSayisi / 30) * 10;
	}
	
	if( (toplamTakimGolu-toplamRakipGolu) >= 30 ) {
		
		golFarkiPuan = 10.0;
	}
	
	if ( (toplamTakimGolu-toplamRakipGolu) < 30 && (toplamTakimGolu-toplamRakipGolu) >= 0 ) {
		
		golFarkiPuan = ( ((double)(toplamTakimGolu - toplamRakipGolu)) / 30 ) * 10;
	}
	
	if ( (toplamTakimGolu-toplamRakipGolu) < 0) {
		
		golFarkiPuan = ( ((double)(toplamTakimGolu - toplamRakipGolu)) / 30 ) * 10;
	}
	
	*toplamPerformansPuani = puanPerformans + golYenmeyenPuan + golFarkiPuan + asistPuan;
		
	return diziyiTut;
}


void takimIstatistikGoster () {
	
	int* goster = takimistatistikHesapla (&toplamPerformansPuani,&atilanGollerinDakikaOrtalamasi);
	
	printf("\n\n   	    |--------------------------------Genel Takim istatistikleri--------------------------------|\n\n\n");
	
	printf("\n%-20s 	%s 	%s 	%s 	%s 	%s\n\n","Takim Adi","Atilan Gol","Asist Sayisi","Yenilen Gol","Gol Yenmeyen Mac","Toplam Puan");
	
	printf("\n%-20s 	   %d 	\t   %d 	\t   %d 	\t   %d 	\t 	  %d\n\n",takimAdi,goster[0],goster[4],goster[1],goster[3],goster[2]);

	printf ("\n\n\n\n");
	
	printf("    |------------------------------Atilan gollerin dakika araliklarina gore dagilimi------------------------------|\n\n\n");
	
	printf("		   %s	   %s	   %s	   %s	   %s	   %s\n\nGol Sayisi","1-15 arasi","15-30 arasi","30-45 arasi","45-60 arasi","60-75 arasi","75-90 arasi");
	printf ("		%d		%d		%d		%d		%d		%d\n\n",goster[6],goster[7],goster[8],goster[9],goster[10],goster[11]);
	
	printf ("\n\n\n\n");
	
	printf("     	   |------------------------------Atilan gollerin dakika Ortalamasi------------------------------|\n\n\n");
	
	printf ("						      %.3f\n",atilanGollerinDakikaOrtalamasi);
	
	printf ("\n\n\n\n");
	
	printf("   	    |------------------------------Takimin Genel Performans Puani------------------------------|\n\n\n");
	
	printf ("					              %.3f\n\n\n",toplamPerformansPuani);
}



void oyuncuRatingHesapla() {
	
    int i;
    double maxRating = 0.0;

         // 1. En yüksek verimlilikleri bul
    for (i = 0; i <oyuncuSayisi;i++) {
    	
        if (oyuncular[i].oynananMacSayisi > 0) {
        	
        	double verim = oyuncular[i].toplamGol + oyuncular[i].toplamAsist;
            double rating = verim / (double)oyuncular[i].oynananMacSayisi;

            if (rating > maxRating) maxRating = rating;
        }
    }  
    
    if (maxRating > 1.5) {
    	maxRating = 1.5;
	}

    // 2. Oyuncularýn ratingini hesapla
    for (i = 0; i < oyuncuSayisi;i++) {
    	
        double oyuncuPuani = 0.00;

        if (oyuncular[i].oynananMacSayisi > 0) {
        	
            double verim = oyuncular[i].toplamGol + oyuncular[i].toplamAsist;
            double rating = verim / (double)oyuncular[i].oynananMacSayisi;

            if (rating > 0) {
            	
				oyuncuPuani = (rating / maxRating) * 100;
				
				 oyuncular[i].oyuncuRating =sigmoid_puan(oyuncuPuani);
						
            }
        } 
		
		else {
            oyuncular[i].oyuncuRating = 0.0;
        }
    }
    dosyayaOyuncuYaz();
}





int* oyuncuGelismisIstatistikHesapla(int skor, int golAtanlarFormaNo[]) {
	
    static int formaVeGol[2];
    int* temizDizi = (int*)malloc(skor * sizeof(int));
    int temizSkor = 0,k,i,l;

    // DEBUG: Orijinal diziyi yazdýr
    printf("[DEBUG] Gol atanlar: ");
    for (k = 0; k < skor; k++) {
        printf("%d ", golAtanlarFormaNo[k]);
    }
    printf("\n");

    // Sýfýr olmayanlarý filtrele
    for (i = 0; i < skor; i++) {
        if (golAtanlarFormaNo[i] != 0) {
            temizDizi[temizSkor++] = golAtanlarFormaNo[i];
        }
    }

    if (temizSkor == 0) {
        formaVeGol[0] = 0;
        formaVeGol[1] = 0;
        free(temizDizi);
        return formaVeGol;
    }

  
    int max_count = 0;
int most_frequent_forma = 0;
int current_count;

for (i = 0; i < temizSkor; i++) {
    current_count = 1;
    for (l = i + 1; l < temizSkor; l++) {
        if (temizDizi[i] == temizDizi[l]) {
            current_count++;
        }
    }
    if (current_count > max_count) {
        max_count = current_count;
        most_frequent_forma = temizDizi[i];
    }
}

formaVeGol[0] = most_frequent_forma;
formaVeGol[1] = max_count;

  //  printf("[DEBUG] En çok gol atan forma no: %d - Gol sayýsý: %d\n", formaVeGol[0], formaVeGol[1]);

    free(temizDizi);
    return formaVeGol;
}




 int* birMactaEncokGolAtaniBul() {
	
    static int tut1[2] = {0, 0}; // Static yaparak dönüþ deðerinin yerel deðiþken olmamasýný saðlarýz.
    int maxGol = 0;
    int formaNo = 0;
    int i;
    
    // encokGolatanlar dizisi 20 elemanlý (10 maç * 2 bilgi)
    // Her çift indekste (0, 2, 4...) forma no, her tek indekste (1, 3, 5...) gol sayýsý var.
    for (i = 0; i < 20; i += 2) {
        // Þu anki maçtaki gol sayýsýný kontrol et
        if (encokGolatanlar[i+1] > maxGol) {
            maxGol = encokGolatanlar[i+1];
            formaNo = encokGolatanlar[i];
        }
    }
    
    tut1[0] = formaNo;
    tut1[1] = maxGol;
    
    return tut1;
}  
 





void oyuncuIstatistikleriGoster () {
	
	int i,j,k;
	
	int ratingTut[oyuncuSayisi];
	
	dosyadanOyuncuOku();
	oyuncuRatingHesapla();
	
	for(i=0;i<oyuncuSayisi;i++) {
		
	ratingTut[i] = i;	
		
	}
	
	for (i = 0; i < oyuncuSayisi - 1; i++) {
		
        for (j = 0; j < oyuncuSayisi - i - 1; j++) {
        	
            if (oyuncular[ratingTut[j]].oyuncuRating < oyuncular[ratingTut[j + 1]].oyuncuRating ||
    (oyuncular[ratingTut[j]].oyuncuRating == oyuncular[ratingTut[j + 1]].oyuncuRating &&
     strcmp(oyuncular[ratingTut[j]].oyuncuAd, oyuncular[ratingTut[j + 1]].oyuncuAd) > 0))    {
     	
                int temp = ratingTut[j];
                ratingTut[j] = ratingTut[j + 1];
                ratingTut[j + 1] = temp;
            }
        }
    }
	
	printf("\n\n		|----------------------------Temel oyuncu istatistikleri----------------------------|\n\n\n");
	
	printf("\n%-8s %-30s %-5s %-6s %-12s %-7s\n\n", "FormaNo", "Oyuncu Adi", "Gol", "Asist", "Oynanan Mac", "Rating");
	
	for (j=0;j<oyuncuSayisi;j++) {
		
		int idx = ratingTut[j];
		
				printf("%-8d %-30s %-5d %-6d %-12d %-7.2lf\n",oyuncular[idx].formaNo,oyuncular[idx].oyuncuAd,oyuncular[idx].toplamGol,oyuncular[idx].toplamAsist,oyuncular[idx].oynananMacSayisi,oyuncular[idx].oyuncuRating);	
	}
	
	printf("\n\n	      |----------------------------Bir macta en cok gol atan oyuncu----------------------------|\n\n\n");
	
  dosyadanEncokgolataniOku ();
	
	for (i=0;i<oyuncuSayisi;i++) {
		
		if (tut[0] == oyuncular[i].formaNo && oyuncular[i].oynananMacSayisi != 0) {
			printf ("				     %s		%s	     %s\n\n","Forma No","Oyuncu Adi","Toplam Gol");
			printf ("					%d		%s		%d\n\n",tut[0],oyuncular[i].oyuncuAd,tut[1]);
		}
	}	
}





int ligIstatistikleriHesapla (int bizimtakimGol,int rakipTakimGol,int rakipNosu) {
	
	int i;
		

	// BÝZLE OYNANAN MACLARÝN ÝSTATÝSTÝKLERÝ
	
	rakipler[rakipNosu-1].rakipNo = rakipNosu;
	rakipler[rakipNosu-1].atilanGol += rakipTakimGol;
	rakipler[rakipNosu-1].yenilenGol += bizimtakimGol;
	rakipler[rakipNosu-1].averaj += ( rakipler[rakipNosu-1].atilanGol - rakipler[rakipNosu-1].yenilenGol );
	rakipler[rakipNosu-1].oynananMac += rakipler[rakipNosu-1].oynananMac +1;
	
	
	// PUAN HESAPLAMA.
	
	if (rakipler[rakipNosu-1].atilanGol > rakipler[rakipNosu-1].yenilenGol) {
		
		rakipler[rakipNosu-1].galibiyet = rakipler[rakipNosu-1].galibiyet +1;
		rakipler[rakipNosu-1].toplamPuan = rakipler[rakipNosu-1].toplamPuan + 3;
	}
	
	if (rakipler[rakipNosu-1].yenilenGol > rakipler[rakipNosu-1].atilanGol) {
		
		rakipler[rakipNosu-1].maglubiyet = rakipler[rakipNosu-1].maglubiyet +1;
		rakipler[rakipNosu-1].toplamPuan = rakipler[rakipNosu-1].toplamPuan + 0;
	}
	
	if (rakipler[rakipNosu-1].atilanGol == rakipler[rakipNosu-1].yenilenGol) {
		
		rakipler[rakipNosu-1].beraberlik = rakipler[rakipNosu-1].beraberlik +1;
		rakipler[rakipNosu-1].toplamPuan = rakipler[rakipNosu-1].toplamPuan + 1;
	}
}


// SÝMÜLASYON

void ligIstatistikleriHesapla_1 ()  {
	
	int i,j,k;
	
	
	srand (time(NULL));
	
	
	
	// Rakiplere rating ve adini atama
	
	for (i=0;i<10;i++) {
		
		// rakipler[i].rakipAdi = takimlar[i];
		strcpy(rakipler[i].rakipAdi,takimlar[i]);
		rakipler[i].ratingler = takimlarRating[i];
	}
	
	// Simülasyon
	
	for(i=0;i<10;i++) {
		
		for (j= i + 1;j<10;j++) {
			
			int toplamGuc = rakipler[i].ratingler + rakipler[j].ratingler;
			int golSayisi = (rand () % 6) +1;
			int takim1Gol = 0;
			int takim2Gol = 0;
			
			for (k=0;k<golSayisi;k++) {
				
				int sans = rand () % toplamGuc;
				
				if (rakipler[i].ratingler > sans) {
					
					takim1Gol ++;
				}
				else {
					
					takim2Gol ++;
				}
			}
			
			rakipler[i].oynananMac++;
			rakipler[j].oynananMac++;
			
			if (takim1Gol > takim2Gol) {
				
				rakipler[i].galibiyet ++;
				rakipler[j].maglubiyet ++;
				
				rakipler[i].atilanGol += takim1Gol;
				rakipler[i].yenilenGol += takim2Gol;
				rakipler[i].averaj += takim1Gol - takim2Gol;
				
				rakipler[j].atilanGol += takim2Gol;
				rakipler[j].yenilenGol += takim1Gol;
				rakipler[j].averaj += takim2Gol - takim1Gol;
				
				rakipler[i].toplamPuan = rakipler[i].toplamPuan + 3;
			}
			
			if (takim1Gol == takim2Gol) {
				
				rakipler[i].beraberlik ++;
				rakipler[j].beraberlik ++;
				
				rakipler[i].atilanGol += takim1Gol;
				rakipler[i].yenilenGol += takim2Gol;
				rakipler[j].atilanGol += takim2Gol;
				rakipler[j].yenilenGol += takim1Gol;
				
				rakipler[i].toplamPuan = rakipler[i].toplamPuan +1;
				rakipler[j].toplamPuan = rakipler[j].toplamPuan +1;
			}
			
			if (takim1Gol < takim2Gol) {
				
				rakipler[j].galibiyet ++;
				rakipler[i].maglubiyet ++;
				
				rakipler[j].atilanGol += takim2Gol;
				rakipler[j].yenilenGol += takim1Gol;
				rakipler[j].averaj += takim2Gol - takim1Gol;
				
				rakipler[i].atilanGol +=  takim1Gol;
				rakipler[i].yenilenGol += takim2Gol;
				rakipler[i].averaj += takim1Gol - takim2Gol;
				
				rakipler[j].toplamPuan = rakipler[j].toplamPuan + 3;
			}
		}
	}
}



 void bizimTakimiDahilEt () {
	
	int* tut = takimistatistikHesapla (&toplamPerformansPuani,&atilanGollerinDakikaOrtalamasi);
	
	strcpy(rakipler[10].rakipAdi, takimAdi);
rakipler[10].rakipNo = 11;  // biz olduðumuzu ayýrt etmek için özel no
rakipler[10].oynananMac = 10;
rakipler[10].galibiyet = bizimki.galibiyet;
rakipler[10].beraberlik = bizimki.beraberlik;
rakipler[10].maglubiyet = bizimki.maglubiyet;
rakipler[10].atilanGol = tut[0];
rakipler[10].yenilenGol = tut[1];
rakipler[10].averaj = tut[0] - tut[1];
rakipler[10].toplamPuan = tut[2];
	
}




int ligKiyasla(const void *a, const void *b) {
    struct rakip *r1 = (struct rakip *)a;
    struct rakip *r2 = (struct rakip *)b;

    // 1. TOPLAM PUAN karþýlaþtýrmasý
    if (r2->toplamPuan != r1->toplamPuan)
        return r2->toplamPuan - r1->toplamPuan;

    // 2. AVERAJ karþýlaþtýrmasý
    if (r2->averaj != r1->averaj)
        return r2->averaj - r1->averaj;

    // 3. ATILAN GOL karþýlaþtýrmasý
    if (r2->atilanGol != r1->atilanGol)
        return r2->atilanGol - r1->atilanGol;

    // 4. (Opsiyonel) RATING karþýlaþtýrmasý
    if (r2->ratingler != r1->ratingler)
        return r2->ratingler - r1->ratingler;

    // 5. (Son çare) Alfabeye göre
    return strcmp(r1->rakipAdi, r2->rakipAdi);
}



void ligIstatistikleriniGoster () {
	
	int i,tut = 11;
	
	bizimTakimiDahilEt();
    dosyadanTakimlariOku ();
	
	qsort(rakipler, 11, sizeof(struct rakip), ligKiyasla);
	
	printf("\n\n\n%-3s %-20s		 %-3s  %-3s  %-3s  %-3s %-4s  %-4s  %-4s  %-4s\n", "No", "Takim", "OM", "G", "B", "M", "AG", "YG", "AV", "PUAN");
	
	for(i=0;i<11;i++) {
		
	printf("\n%d %-25s 		 %02d  %02d   %02d   %02d   %02d    %02d    %03d     %02d\n\n\n",rakipler[i].rakipNo,rakipler[i].rakipAdi,rakipler[i].oynananMac,rakipler[i].galibiyet,rakipler[i].beraberlik,rakipler[i].maglubiyet,rakipler[i].atilanGol,rakipler[i].yenilenGol,rakipler[i].averaj,rakipler[i].toplamPuan);	
	}
	
}



//------------------------------------------------------------Dosyaya Yazma--------------------------------------------------------------------



void dosyayaOyuncuYaz() {
	
	int i;
	
	FILE *dosyayaYaz = fopen ("oyuncular.txt","w");
	
	if (dosyayaYaz == NULL) {
		printf("\nDosya acilirken hata\n");
		return;
	}
	
	for (i=0;i<oyuncuSayisi;i++) {
		
		fprintf(dosyayaYaz,"%d;%s;%d;%d;%d;%.2f\n",oyuncular[i].formaNo,oyuncular[i].oyuncuAd,oyuncular[i].toplamGol,oyuncular[i].toplamAsist,oyuncular[i].oynananMacSayisi,oyuncular[i].oyuncuRating);
		
	}
	fclose(dosyayaYaz);
}




void dosyayaTakimlariYaz () {
	
	int i;
	
	FILE *dosyayaYaz2 = fopen("takimlar.txt", "w");
	
	if (dosyayaYaz2 == NULL) {
		
    printf("Dosya açýlamadý.\n");
    return;
  }

	for (i = 0; i < 10; i++) {
		
    fprintf(dosyayaYaz2, "%s;%d\n", takimlar[i],takimlarRating[i]);
  }
fclose(dosyayaYaz2);
}




void dosyayaTakimlariYaz1 () {
	
	int i;
	
	FILE *dosyayaYaz4 = fopen("takimlar1.txt", "w");
	
	if (dosyayaYaz4 == NULL) {
		
    printf("Dosya açýlamadý.\n");
    return;
  }

	for (i = 0; i < 10; i++) {
		
    fprintf(dosyayaYaz4, "%s\n", takimlar[i]);
  }
fclose(dosyayaYaz4);
}




void dosyayaEvdeplasmanYaz () {
	
	int i;
	
	FILE *dosyayaYaz1 = fopen ("fikstur.txt","w");
	
	if (dosyayaYaz1 == NULL) {
		printf("\nDosya acilirken hata\n");
		return;
	}
	
	fprintf(dosyayaYaz1,"%s;%d",takimAdi,evDeplasman);
	
	fclose(dosyayaYaz1);
}




void dosyayaEvdeplasmanYaz1 () {
	
	int i;
	
	FILE *dosyayaYaz5 = fopen ("fikstur1.txt","w");
	
	if (dosyayaYaz5 == NULL) {
		printf("\nDosya acilirken hata\n");
		return;
	}
	
	fprintf(dosyayaYaz5,"%s;%d",takimAdi,evDeplasman);
	
	fclose(dosyayaYaz5);
}




void dosyayaMacYaz() {
	
	int i,j;
	
 if (macSayisi <= 0) {
        printf("Kayit yok,dosya yazilmadi.\n");
        return;
    }
	
	FILE *dosyayaYaz3 = fopen ("maclar.txt","w");
	
	if (dosyayaYaz3 == NULL) {
		printf("\nDosya acilirken hata\n");
		return;
	}
			
		for (i=0;i < macSayisi;i++) {
			
			fprintf(dosyayaYaz3,"%d;%d;",maclar[i].takimGolu,maclar[i].rakipGolu);
		
		fprintf(dosyayaYaz3,"%d;%s;%d;",maclar[i].macNo,maclar[i].macTarihi,maclar[i].asistSayisi);
		
		// gol dakikalari
		   for (j=0;j<maclar[i].takimGolu;j++) {
		   	
		   	fprintf(dosyayaYaz3,"%d",maclar[i].golDakikalari[j]);
		   	
		   	if (j != maclar[i].takimGolu-1) {
		   		
		   		fprintf(dosyayaYaz3,",");
			   }
		   } 
		     fprintf(dosyayaYaz3,";");
		     
		   // asist dakikalari
		   for (j=0;j< maclar[i].asistSayisi;j++) {
		   	
		   	fprintf(dosyayaYaz3,"%d",maclar[i].asistDakikalari[j]);
		   	
		   	if (j != maclar[i].asistSayisi-1) {
		   		
		   		fprintf(dosyayaYaz3,",");
			   }
		   }
		   fprintf(dosyayaYaz3,"\n");
		}
		
	fclose(dosyayaYaz3);
}




void dosyayaEncokGolAtanYaz () {
	
	FILE *dosyayaYaz6 = fopen("encokgolatan.txt","w");
	
	if (dosyayaYaz6 == NULL) {
		printf("\nDosya açýlýrken hata\n");
		return;
	}

	int* tut2 = birMactaEncokGolAtaniBul();  // fonksiyon çaðrýsý

	fprintf(dosyayaYaz6, "%d;%d\n", tut2[0], tut2[1]);
	
	fclose(dosyayaYaz6);
}




void dosyayaRakipYaz(struct rakip rakipler[], int sayi) {
	
	int i;
	
    FILE *dosya = fopen("rakipler.txt", "w");

    if (dosya == NULL) {
        printf("Dosya yazma hatasi!\n");
        return;
    }

    for (i = 0; i < sayi; i++) {
        fprintf(dosya, "%s;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d\n",
                rakipler[i].rakipAdi,
                rakipler[i].rakipNo,
                rakipler[i].oynananMac,
                rakipler[i].galibiyet,
                rakipler[i].beraberlik,
                rakipler[i].maglubiyet,
                rakipler[i].atilanGol,
                rakipler[i].yenilenGol,
                rakipler[i].averaj,
                rakipler[i].toplamPuan,
                rakipler[i].ratingler
        );
    }

    fclose(dosya);
}


void dosyayaBizimkiYaz() {
    FILE *dosya = fopen("bizimki_istatistik.txt", "w");
    if (dosya == NULL) {
        printf("Hata: Istatistikler dosyaya yazilamadi.\n");
        return;
    }
    // bizimki struct'ýnýn içeriðini dosyaya yazar
    fprintf(dosya, "%d %d %d %d %d %d %d %d\n",
            bizimki.oynananMac, bizimki.galibiyet, bizimki.beraberlik,
            bizimki.maglubiyet, bizimki.atilanGol, bizimki.yenilenGol,
            bizimki.averaj, bizimki.toplamPuan);

    fclose(dosya);
}



//-------------------------------------------------------------Dosyadan Okuma------------------------------------------------------------------



void dosyadanOyuncuOku() {
	
	FILE *bellegeYaz = fopen("oyuncular.txt","r");
	
	if (bellegeYaz == NULL) {
		printf("Dosya acilirken hata");
		return;
	}
	
	oyuncuSayisi = 0;
	
	while (fscanf(bellegeYaz,"%d;%49[^;];%d;%d;%d;%f\n",&oyuncular[oyuncuSayisi].formaNo,oyuncular[oyuncuSayisi].oyuncuAd,&oyuncular[oyuncuSayisi].toplamGol,&oyuncular[oyuncuSayisi].toplamAsist,&oyuncular[oyuncuSayisi].oynananMacSayisi,&oyuncular[oyuncuSayisi].oyuncuRating) == 6) {
		
		oyuncuSayisi ++;
		
		if (oyuncuSayisi >= MAX_OYUNCU) { 
            break;
       }
	}
	fclose(bellegeYaz);
}




void dosyadanTakimlariOku () {
    int i;
    char satir[100];

    FILE *bellegeYaz2 = fopen("takimlar.txt", "r");
    if (bellegeYaz2 == NULL) {
        printf("Dosya açýlamadý.\n");
        return;
    }

    for (i = 0; i < 10; i++) {
        if (fgets(satir, sizeof(satir), bellegeYaz2) == NULL) {
            printf("Dosyadan okuma hatasý veya dosya erken bitti.\n");
            break;
        }

        // '\n' karakterini temizle
        int len = strlen(satir);
        if (len > 0 && satir[len - 1] == '\n') {
            satir[len - 1] = '\0';
        }

        // satýrý parçala: isim ; rating
        char *parca = strtok(satir, ";");
        if (parca != NULL) {
            strcpy(takimlar[i], parca); // takým ismi

            parca = strtok(NULL, ";");
            if (parca != NULL) {
                takimlarRating[i] = atoi(parca); // rating sayýya çevrilerek alýnýr
            }
        }
    }

    fclose(bellegeYaz2);
}




void dosyadanTakimlariOku1 () {
		
	int i;
	
		FILE *bellegeYaz4 = fopen("takimlar1.txt", "r");
		
		 if (bellegeYaz4 == NULL) {
		 	
    		printf("Dosya açýlamadý.\n");
           return;
         }

			for (i = 0; i < 10; i++) {
				
    			if (fgets(takimlar[i], sizeof(takimlar[i]), bellegeYaz4) == NULL) {
    
                    printf("Dosyadan okuma hatasi veya erken son.\n");
               break;
    		}
    		
    		int len = strlen(takimlar[i]);
    
    if (len > 0 && takimlar[i][len-1] == '\n') {
    	
        takimlar[i][len-1] = '\0';
      }
   }
   fclose(bellegeYaz4); 
}




void dosyadanEvdeplasmanOku () {
	
	int i;
	
	FILE *bellegeYaz1 = fopen ("fikstur.txt","r");
	
	if (bellegeYaz1 == NULL) {
		printf("\nDosya acilirken hata\n");
		return;
	}
	
	fscanf(bellegeYaz1,"%15[^;];%d",takimAdi,&evDeplasman);
	
	fclose(bellegeYaz1);
}



void dosyadanEvdeplasmanOku1 () {
	
	int i;
	
	FILE *bellegeYaz5 = fopen ("fikstur1.txt","r");
	
	if (bellegeYaz5 == NULL) {
		printf("\nDosya acilirken hata\n");
		return;
	}
	
	fscanf(bellegeYaz5,"%15[^;];%d",takimAdi,&evDeplasman);
	
	fclose(bellegeYaz5);
}



void dosyadanMacOku() {
	
    FILE *bellegeYaz3 = fopen("maclar.txt", "r");
    if (bellegeYaz3 == NULL) {
        printf("\nDosya açýlamadý!\n");
        return;
    }

    int i = 0;
    while (i < MAX_MAC) {
    	
  int k;  	
    	for (k = 0; k < MAX_GOL_ASIST; k++) {
    maclar[i].golDakikalari[k] = 0;
}

for (k = 0; k < MAX_GOL_ASIST; k++) {
    maclar[i].asistDakikalari[k] = 0;
}
    	
        int okunan = fscanf(bellegeYaz3, "%d;%d;%d;%[^;];%d;",
                            &maclar[i].takimGolu,
                            &maclar[i].rakipGolu ,                 
                            &maclar[i].macNo,
                            maclar[i].macTarihi,
                            &maclar[i].asistSayisi);

        if (okunan != 5) {
            break; // Dosya bitti veya hata
        }
    int j;
        for (j = 0; j < maclar[i].takimGolu; j++) {
            fscanf(bellegeYaz3, "%d", &maclar[i].golDakikalari[j]);
            if (j < maclar[i].takimGolu - 1)
                fscanf(bellegeYaz3, ",");
        }
        fscanf(bellegeYaz3, ";");

        for (j = 0; j < maclar[i].asistSayisi; j++) {
            fscanf(bellegeYaz3, "%d", &maclar[i].asistDakikalari[j]);
            if (j < maclar[i].asistSayisi - 1)
                fscanf(bellegeYaz3, ",");
        }
        
        int c = fgetc(bellegeYaz3);
        
		if (c != '\n' && c != EOF) {
    // Satýr sonu deðilse fazladan karakter var, atla
    while (c != '\n' && c != EOF) {
        c = fgetc(bellegeYaz3);
    }
  }
        i++;
}

    fclose(bellegeYaz3);
    macSayisi = i;
    printf("%d mac basariyla okundu.\n", i);
}



void dosyadanEncokgolataniOku ()  {
	
	FILE *bellegeYaz6 = fopen("encokgolatan.txt", "r");
	
    if (bellegeYaz6 == NULL) {
        printf("\nDosya açýlamadý!\n");
        return;
    }
    
    fscanf(bellegeYaz6,"%d;%d",&tut[0],&tut[1]);
    
    fclose (bellegeYaz6);
}




void dosyadanRakipOku(struct rakip rakipler[], int *sayi) {
    FILE *dosya = fopen("rakipler.txt", "r");

    if (dosya == NULL) {
        printf("Dosya okuma hatasi!\n");
        return;
    }

    int i = 0;
    while (fscanf(dosya, "%[^;];%d;%d;%d;%d;%d;%d;%d;%d;%d;%d\n",
                  rakipler[i].rakipAdi,
                  &rakipler[i].rakipNo,
                  &rakipler[i].oynananMac,
                  &rakipler[i].galibiyet,
                  &rakipler[i].beraberlik,
                  &rakipler[i].maglubiyet,
                  &rakipler[i].atilanGol,
                  &rakipler[i].yenilenGol,
                  &rakipler[i].averaj,
                  &rakipler[i].toplamPuan,
                  &rakipler[i].ratingler) == 11) {
        i++;
    }

    *sayi = i;
    fclose(dosya);
}


void dosyadanBizimkiOku() {
    FILE *dosya = fopen("bizimki_istatistik.txt", "r");
    if (dosya == NULL) {
        // Dosya yoksa veya okunamýyorsa, istatistikleri sýfýrlar.
        // Bu, yeni bir lig baþlatýrken veya ilk kez çalýþtýrýrken faydalýdýr.
        printf("Onceki istatistikler bulunamadi. Yeni lig baslatiliyor.\n");
        bizimki.oynananMac = 0;
        bizimki.galibiyet = 0;
        bizimki.beraberlik = 0;
        bizimki.maglubiyet = 0;
        bizimki.atilanGol = 0;
        bizimki.yenilenGol = 0;
        bizimki.averaj = 0;
        bizimki.toplamPuan = 0;
        return;
    }
    // bizimki struct'ýnýn içeriðini dosyadan okur
    fscanf(dosya, "%d %d %d %d %d %d %d %d",
           &bizimki.oynananMac, &bizimki.galibiyet, &bizimki.beraberlik,
           &bizimki.maglubiyet, &bizimki.atilanGol, &bizimki.yenilenGol,
           &bizimki.averaj, &bizimki.toplamPuan);

    fclose(dosya);
}


//-------------------------------------------------------------MAÝN-----------------------------------------------------------------------------





int main ()  {
	
	int secim;
	int rakipSayisi = 0;
		
	dosyadanOyuncuOku();
    dosyadanTakimlariOku ();
	dosyadanEvdeplasmanOku ();
	dosyadanMacOku();
	dosyadanEncokgolataniOku ();	 
    dosyadanRakipOku(rakipler, &rakipSayisi);
    dosyadanBizimkiOku();
	
	
	do {
		
		secim = menu ();
		
		switch (secim) {
			
			case 0:
				
					break;		
			case 1:
				
				takimIsmiAl_Guncelle();
				
					break;
			case 2:
				
				oyuncuEkle();
				
					break;
			case 3:
				
				oyuncuSil();
				
					break;
			case 4:
				
				oyuncuGuncelle();
				
					break;
			case 5:
				
				oyuncuListele();
				
					break;
			case 6:
				
				oyuncuIstatistikSifirla ();
				
					break;
			case 7:
				
				fiksturOlustur();
				
					break;
			case 8:
				
				fiksturGoster ();
				
					break;
			case 9:
				
				skorGirisiYap();
				
					break;
			case 10:
				
				macSonucListele();
				
					break;
			case 11:
				
				takimIstatistikGoster ();
				
					break;
			case 12:
				
				oyuncuIstatistikleriGoster ();
				
					break;
			case 13:
				
				ligIstatistikleriniGoster ();
				
					break;			
			default :
			
			
					break;
			
		}	
		
	}while(secim != 0);
	
	dosyayaOyuncuYaz();
	dosyayaTakimlariYaz ();
	dosyayaEvdeplasmanYaz ();
	dosyayaMacYaz();
	dosyayaEncokGolAtanYaz ();
		
	return 0;
}
