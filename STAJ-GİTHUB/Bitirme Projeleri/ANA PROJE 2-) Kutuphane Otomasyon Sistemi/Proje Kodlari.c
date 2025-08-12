#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<locale.h>
#include<ctype.h>
#include<time.h>



//-------------------------------------------------------struct Fonksiyonlari;-----------------------------------------------------------------



struct kitap {      // Kitap Bilgileri
	int kitapID;
	char kitapAdi[50];
	char yazarAdi[50];
	int kitapYili;
	int kitapAdeti;
	int kitapDurum;  // 1: M�sait 2: stokta yok;
};



struct uye {        // Uye bilgileri
	int uyeID;
	char uyeAdi[50];
	char uyeSoyadi[50];
	char uyeTel[50];
	char dogumTarihi[50];
	int alinankitapSayisi; 
};


struct odunc {
    int oduncID;
    int uyeID;
    int kitapID;
    char alisTarihi[30];       // �rn: "2025-07-18"
    char iadeTarihi[30];      // �rn: "2025-07-25"
    char iadeEdilmeTarihi[30];
	int iadeDurumu;          // 0 = kitab� ald�, 1 = kitap iade edildi
};


struct kitap kitaplar[100];
int kitapsayisi=0;
struct uye uyeler[50];
int uyesayisi=0;
struct odunc oduncler[500];
int oduncsayisi=0;



void dosyaYazma_kitap();
void dosyaYazma_uye();
void dosyaYazma_oduncIslemleri();
void kitapListele ();
int kitapKodu_kontrol (int kitapID1);




// ----------------------------------------G�venli Giri� ve Benzersizlik Fonksiyonlari;--------------------------------------------------------




void trim(char *s) {
    char *baslangic = s; // Stringin okunacak k�sm�n�n ba�lang�c�n� g�steren i�aret�i
    char *hedef = s;     // Temizlenmi� stringin yaz�laca�� konumu g�steren i�aret�i
    int oncekiKarakterBosluktu = 1; // Bir �nceki kopyalanan karakterin bo�luk olup olmad���n� tutar.
                                    // Ba�lang��ta 1, ��nk� stringin ba��ndaki bo�luklar� atlamak istiyoruz.

    // 1. Ad�m: Stringi karakter karakter tarayarak bo�luklar� temizle ve normalle�tir.
    // 'baslangic' i�aret�isi string boyunca ilerler.
    while (*baslangic != '\0') { // Stringin sonuna gelene kadar d�ng�y� s�rd�r.
        if (isspace((unsigned char)*baslangic)) { // E�er mevcut karakter bo�luksa...
            // E�er bir �nceki kopyalad���m�z karakter bo�luk DE��LSE,
            // (yani yeni bir kelimenin ard�ndan gelen ilk bo�luksa),
            // bu bo�lu�u hedef konuma kopyala. Aksi takdirde (birden fazla bo�luk varsa), atla.
            if (oncekiKarakterBosluktu == 0) {
                *hedef = ' '; // Tek bir bo�luk kopyala
                hedef++;
                oncekiKarakterBosluktu = 1; // Art�k bir �nceki karakter bo�luk oldu
            }
            // else: Birden fazla bo�luk var, bu bo�lu�u atla (kopyalama)
        } else { // E�er mevcut karakter bo�luk de�ilse (yani bir harf, rakam vb. ise)...
            *hedef = *baslangic; // Karakteri do�rudan hedef konuma kopyala
            hedef++;
            oncekiKarakterBosluktu = 0; // Bir �nceki karakter art�k bo�luk de�il
        }
        baslangic++; // Okuma i�aret�isini bir sonraki karaktere ta��
    }

    // 2. Ad�m: Temizlenmi� stringi null karakteri ile sonland�r.
    *hedef = '\0';

    // 3. Ad�m: Sondaki gereksiz bo�lu�u sil (e�er varsa).
    // E�er stringin sonunda bo�luk kalm��sa (�rn: "Merhaba D�nya "),
    // bu bo�lu�u silmek i�in null karakteri bir geri kayd�r�r�z.
    // Bu durum, stringin en sonuna tek bir bo�luk kopyalanm��sa olu�abilir.
    if (hedef > s && isspace((unsigned char)*(hedef - 1))) {
        *(hedef - 1) = '\0';
    }
}




void bosluk_sil(char *str) {
    int i, j = 0;
    char temp[50]; // yeterli uzunlukta ge�ici bir dizi

    for (i = 0; str[i] != '\0'; i++) {
        if (str[i] != ' ') {
            temp[j++] = str[i];
        }
    }

    temp[j] = '\0';  // null karakteri ekle

    strcpy(str, temp);  // temizlenmi�i orijinal diziye kopyala
}






void scanf_Temizle() {  // Scanf fonksiyonun buffer temizli�i.Bo�luklu veri girilince di�er verilere yazmamas� i�in vs.
	int c;
	
	while ((c = getchar()) != '\n' && c != EOF); // \n ve EOF (hata) g�rmedi�i s�rece okur.E�er hatal�ysa at�yor.EOF veya \n olursa d�ng�den ��kar.Bu noktada giri� tamponu, sonraki giri� i�lemleri i�in temizlenmi� olur.
}




int guvenli_Int () {      // Girilecek int de�erin kontroll� girilmesi sa�lan�r.Bir int de�eri girilmesi gerekiyorsa bu fonksiyon �a��r�l�r.
	
char input[100];          // Kullan�c�n�n girece�i veriyi burada tutar
    int sayi;                 // Sonu� olarak d�nd�r�lecek say�
    char *sonKarakter;        // Say�dan sonra kalan karakterleri kontrol eder

    while (1) {
        if (fgets(input, sizeof(input), stdin) == NULL) {
            printf("Giris hatasi. Tekrar deneyin:\n");
            continue; // Tekrar ba�a d�n, kullan�c�dan tekrar iste
        }

        // Sat�r sonunu temizle
        size_t len = strlen(input);
        if (len > 0 && input[len - 1] == '\n')  {
            input[len - 1] = '\0';
            len--;
        }
        else
            scanf_Temizle();  // Fazla karakterleri temizle (�rne�in kullan�c� 100'den fazla �ey girdiyse)

// Bo� string girilmesini engellemek i�in:
        if (len == 0) {
            printf("Bos girdi kabul edilmez. Lutfen tekrar deneyin:\n");
            continue;
        }

        // Stringi say�ya �eviriyoruz
        sayi = (int)strtol(input, &sonKarakter, 10);

        // E�er t�m string sadece say�ysa, sonKarakter stringin sonunda olur
        if (*sonKarakter == '\0') {
        	
        	// Burada negatif kontrol� yap�l�r
            if (sayi < 0) {
                printf("\nNegatif sayi giremezsiniz. Lutfen pozitif bir sayi girin:\n");
                continue;
            }
            return sayi;
		}
            
        // Hatal� giri� varsa buras� �al���r
        printf("\nGecersiz sayi girdiniz. Lutfen sadece rakam kullanin:\n");
    }	
} 



void guvenli_String (char *buffer,int bufferSize) {     // Girilecek stringin kontroll� girilmesi sa�lan�r.Bir string de�eri girilmesi gerekiyorsa bu fonksiyon �a��r�l�r.
	
while (1) {
	
	if (fgets(buffer, bufferSize, stdin) == NULL) {
        printf("Giris hatasi veya dosya sonu. Programdan cikiliyor...\n");
        exit(1); // Hata durumunda program� sonland�rabilirsin
    }
    
    size_t len= strlen(buffer); 
    if(len > 0 && buffer[len-1] == '\n') {
    	buffer[len-1] = '\0';
    	len--;
	}
	else {
		
		scanf_Temizle();
	}
	
	// E�er bo� string ise tekrar sor
        if (len == 0) {
            printf("Bos girdi kabul edilmez. Lutfen tekrar deneyin:\n");
            continue;
        }

        // Ge�erli girdi, ��k
        break;
}
}




int kitapKodu_kontrol (int kitapID1) {     // 5 haneli kitap kodunun uygun girilmesini sa�lar.
	
	if (kitapID1 < 10000  ||  kitapID1 > 99999) {
		    return 0;
		  }
	else {
		return 1;
	}
}




int kitapKodu_benzersizlik (int kitapID1) {     // 5 haneli kitap kodunun benzersiz olmas�n� sa�lar.
	int kitapbenzersizlik;
	
	for(kitapbenzersizlik = 0;kitapbenzersizlik < kitapsayisi ; kitapbenzersizlik++) {
		
		if(kitaplar[kitapbenzersizlik].kitapID == kitapID1) {
	    		return 0;
		}
	}
	   return 1;
}




int uyeKodu_kontrol (int uyeID1)  {    // 4 haneli �ye kodunun uygunlu�unu kontrol eder.
	
	if (uyeID1 < 1000  ||  uyeID1 > 9999) {
		    return 0;      // Yanlis 
		  }
	else {
		return 1;       // Dogru
	}
	
}





int uyeKodu_benzersizlik (int uyeID1)  {    // 4 haneli �ye kodunun benzersizli�ini kontrol eder.
	
	int uyebenzersizlik;
	
	for(uyebenzersizlik = 0;uyebenzersizlik < uyesayisi ; uyebenzersizlik++) {
		
		if(uyeler[uyebenzersizlik].uyeID == uyeID1) {
	    		return 0;
		}
	}
	   return 1;
	
}


int uyeNumara_kontrol (char numara[]) {

int uzunluktut,i;	
	
	uzunluktut = strlen(numara);
	
	if (uzunluktut != 11) {
		return 0;
	}
	
	if (numara[0] != '0') {
		return 0;
	}
	
	for (i = 0;i < 11;i++) {
		
	if (numara[i] < '0' || numara[i] > '9') {
		return 0;
	}  
	}
	
	return 1;
}




//--------------------------------------------------------Genel Menu Fonksiyonu;---------------------------------------------------------------




int menu () {    // Men� ekran�
int secim;
	
	printf("-------------------------------------------------------------------------------------------------------\nKutuphane Otomasyonu Sistemi\n\n\n1.Kitap Ekle\n2.Kitap Sil\n3.Kitap Listele\n4.Kitap Ara\n5.Kitap Guncelle\n6.Uye Ekle\n7.Uye Sil\n8.Uye Ara\n9.Uye Listele\n10.Kitap Odunc Al\n11.Kitap Iade Et\n12.Odunc Kayitlarini Listele\n13.Cikis\n\n\n-------------------------------------------------------------------------------------------------------\nLutfen Secim Yapiniz:\n");
	
    secim = guvenli_Int ();
								return secim;    
}






//-------------------------------------------------------Kitap Y�netim Fonksiyonlari;----------------------------------------------------------


void kitapEkle ( ) {   // Kitap Ekle

int kitapID1;

if(kitapsayisi < 100) {
		

	while (1) {
		
		printf("\nEklemek istediginiz kitaba ait 5 haneli kodu giriniz\n");
	  		    kitapID1 = guvenli_Int ();
	  		    
	  		    if(kitapKodu_kontrol (kitapID1) == 1 && kitapKodu_benzersizlik(kitapID1) == 1) {
	  	kitaplar[kitapsayisi].kitapID = kitapID1;
	  		    	printf("\nKitabin adini giriniz.\n");
				  		guvenli_String(kitaplar[kitapsayisi].kitapAdi,sizeof(kitaplar[kitapsayisi].kitapAdi));
				  		trim(kitaplar[kitapsayisi].kitapAdi);
					printf("\nYazarin adini giriniz.\n");
					         guvenli_String(kitaplar[kitapsayisi].yazarAdi,sizeof(kitaplar[kitapsayisi].yazarAdi));
					         trim(kitaplar[kitapsayisi].yazarAdi);
					         printf("\nKitabin basim yilini giriniz.\n");
					         		kitaplar[kitapsayisi].kitapYili = guvenli_Int();
					         					printf("\nKitap adetini giriniz.\n");
					         						kitaplar[kitapsayisi].kitapAdeti = guvenli_Int ();
					         						
													 if (kitaplar[kitapsayisi].kitapAdeti == 0) {
													 	
													 	kitaplar[kitapsayisi].kitapDurum = 2;
													 	
													 }	
													 else {
													 	
													 	kitaplar[kitapsayisi].kitapDurum = 1;
													 } 
		       				
					         		kitapsayisi++;
					         		
					        printf("\nKitap basariyla eklendi.\n"); 		
															dosyaYazma_kitap();				         		
					    break;     		
				  }
				  else {
				  			printf("\nHatali giris veya ID benzersiz degil.\n");
				  }
	}
	
			
}
else {
	printf ("Kutuphane dolu.\n");
}
}





void kitapSil () {   // Kitap Sil
	
int kitapsilgezici;
	  int bulundu=0;
	int kitapsilinecek;
	
	       if(kitapsayisi == 0) {
	       			printf("\nSilinecek kitap yok.\n");
	       	return;
		   }
		   
		while (bulundu == 0) {
	          bulundu =0;
	              kitapListele ();
			printf("\nSilmek istediginiz kitabin 5 haneli ID'sini giriniz.Cikmak icin 0 tuslayiniz.\n");
				kitapsilinecek	=	guvenli_Int ();
	if(kitapsilinecek == 0) {
		return;
	}
			if(kitapKodu_kontrol (kitapsilinecek) == 1) {
				
				for(kitapsilgezici = 0;kitapsilgezici < kitapsayisi;kitapsilgezici++) {
					
			if(kitaplar[kitapsilgezici].kitapID == kitapsilinecek) {
				 	 // kitap silinecek.
				 	 int i;
				 	 for(i=kitapsilgezici;i<kitapsayisi-1;i++) {
				 	 	kitaplar[i] = kitaplar[i+1];
					  }
				printf("\nKitap basairyla silindi.\n"); 	
					 bulundu =1;
			kitapsayisi--;		 
			        dosyaYazma_kitap();
				 	 break;
			}
	}
	if(bulundu == 0) {
		
printf("\nEslesme bulinamadi.\n");
         continue;		 
	}
  }	
  else {
  	 printf("\nLutfen 5 haneli bir kod giriniz.\n");
  	    continue;
  }
 }
}





void kitapGuncelle () {   // Kitap G�ncelle


	int kitapguncelledongu,guncellemekod,guncellemecik=1,kitaptut=0,guncellemeyenikod,guncelleatla;
	
	
	
	if (kitapsayisi == 0) {
		
		printf("\nGuncellenecek kitap yok.\n");
	return;	
	}
	
	while (guncellemecik == 1) {
		printf("\nGuncellemek istediginiz kitabin ID numarasini giriniz.Cikmak icin 0 tuslayiniz.\n");
		guncellemekod = guvenli_Int ();
		
		if(guncellemekod == 0) {
			return;
		}
		kitapKodu_kontrol (guncellemekod);
		
		if (kitapKodu_kontrol (guncellemekod) == 0) {
			
			printf("Lutfen 5 haneli bir ID giriniz.\n");
			continue;
		}
			
			for (kitapguncelledongu = 0;kitapguncelledongu < kitapsayisi;kitapguncelledongu++) {
				
				if (guncellemekod == kitaplar[kitapguncelledongu].kitapID) {
					printf("\nEslesme bulundu.\n");
					kitaptut = guncellemekod;
					break;
				}	
			}
			  if (kitaptut != guncellemekod) {
			  	printf ("\nKitap bulunamadi.\n");
			  	continue;
			  }
			  	printf("\nKitap bilgileri:\n\n%05d %-49s %-49s %04d %03d %02d\n\n",kitaplar[kitapguncelledongu].kitapID,kitaplar[kitapguncelledongu].kitapAdi,kitaplar[kitapguncelledongu].yazarAdi,kitaplar[kitapguncelledongu].kitapYili,kitaplar[kitapguncelledongu].kitapAdeti,kitaplar[kitapguncelledongu].kitapDurum);
			  	guncellemecik = 0;
			  	
		while (1) {
			
			printf("Yeni ID kodunu giriniz.Cikis icin 0 tuslayiniz.\n");
			  	guncellemeyenikod = guvenli_Int ();
			
			 if (guncellemeyenikod == 0) {
			 	return;
			 } 	
			 
		kitapKodu_kontrol (guncellemeyenikod);
		
		if (kitapKodu_kontrol (guncellemeyenikod) == 0) {
			
			printf("\nLutfen 5 haneli bir ID giriniz.\n");
			continue;
		}
		
		if (guncellemeyenikod == guncellemekod)	  {
			
			printf("\nKitap adi guncellemek istiyorsaniz herhangi bir rakam giriniz.Atlamak icin 0 tuslayiniz.\n");
			
			guncelleatla = guvenli_Int ();
			
			if (guncelleatla != 0) {
				
				printf("\nKitabin adini giriniz.\n");
				guvenli_String (kitaplar[kitapguncelledongu].kitapAdi,sizeof(kitaplar[kitapguncelledongu].kitapAdi));
	   trim(kitaplar[kitapguncelledongu].kitapAdi);
				
			}
			
			printf("\nYazar adi guncellemek icin herhangi bir rakam giriniz.Atlamak icin 0 tuslayiniz.\n");
			
			guncelleatla = guvenli_Int ();
			
			if (guncelleatla != 0) {
				
				printf("\nYazarin adini giriniz.\n");
	   guvenli_String (kitaplar[kitapguncelledongu].yazarAdi,sizeof(kitaplar[kitapguncelledongu].yazarAdi));
	   trim(kitaplar[kitapguncelledongu].yazarAdi);
				
			}
			
			printf("\nYayim yilini guncellemek icin herhangi bir rakam giriniz.Atlamak icin 0 tuslayiniz.\n");
			
			guncelleatla = guvenli_Int ();
			
			if (guncelleatla != 0) {
				
				printf("\nYayim yilini giriniz.\n");
	   kitaplar[kitapguncelledongu].kitapYili = guvenli_Int ();
				
			}
			
	   printf("\nKitap adetini guncellemek icin herhangi bir rakam giriniz.Atlamak icin 0 tuslayiniz.\n");
			
			guncelleatla = guvenli_Int ();
			
			if (guncelleatla != 0) {
				
				printf ("\nKitap adetini giriniz.\n");
	   kitaplar[kitapguncelledongu].kitapAdeti = guvenli_Int ();
	   
	   if (kitaplar[kitapguncelledongu].kitapAdeti == 0) {	 
	   	
		 	kitaplar[kitapguncelledongu].kitapDurum = 2;
			 		 	
		 }
		 
		 else {
		 	
		 	kitaplar[kitapguncelledongu].kitapDurum = 1;
		 }
		 
		 		
			}
	   break;	
		}
		
	kitapKodu_benzersizlik (guncellemeyenikod);
	
	if (kitapKodu_benzersizlik (guncellemeyenikod) == 0) {
		printf ("\nLutfen benzersiz bir ID giriniz.\n");
		continue;
	}
	
			  kitaplar[kitapguncelledongu].kitapID = guncellemeyenikod;
	
	printf("Kitap adi guncellemek istiyorsaniz herhangi bir rakam giriniz.Atlamak icin 0 tuslayiniz.\n");
			
			guncelleatla = guvenli_Int ();
			
			if (guncelleatla != 0) {
				
				printf("Kitabin adini giriniz.\n");
				guvenli_String (kitaplar[kitapguncelledongu].kitapAdi,sizeof(kitaplar[kitapguncelledongu].kitapAdi));
	   trim(kitaplar[kitapguncelledongu].kitapAdi);
				
			}
	   
	   printf("\nYazar adi guncellemek icin herhangi bir rakam giriniz.Atlamak icin 0 tuslayiniz.\n");
			
			guncelleatla = guvenli_Int ();
			
			if (guncelleatla != 0) {
				
				printf("\nYazarin adini giriniz.\n");
	   guvenli_String (kitaplar[kitapguncelledongu].yazarAdi,sizeof(kitaplar[kitapguncelledongu].yazarAdi));
	   trim(kitaplar[kitapguncelledongu].yazarAdi);
				
			}
			
			printf("\nYayim yilini guncellemek icin herhangi bir rakam giriniz.Atlamak icin 0 tuslayiniz.\n");
			
			guncelleatla = guvenli_Int ();
			
			if (guncelleatla != 0) {
				
				printf("\nYayim yilini giriniz.\n");
	   kitaplar[kitapguncelledongu].kitapYili = guvenli_Int ();
				
			}
			
	   printf("\nKitap adetini guncellemek icin herhangi bir rakam giriniz.Atlamak icin 0 tuslayiniz.\n");
			
			guncelleatla = guvenli_Int ();
			
			if (guncelleatla != 0) {
				
				printf ("\nKitap adetini giriniz.\n");
	   kitaplar[kitapguncelledongu].kitapAdeti = guvenli_Int ();
	   
	   if (kitaplar[kitapguncelledongu].kitapAdeti == 0) {	 
	   	
		 	kitaplar[kitapguncelledongu].kitapDurum = 2;
			 		 	
		 }
		 
		 else {
		 	
		 	kitaplar[kitapguncelledongu].kitapDurum = 1;
		 }
		 				
			}
			
			break;
		}	  	
			 
	}
	
	dosyaYazma_kitap ();
}





void kitapAra () {    // Kitap Ara
	int kitaparadongu1,kitaparadongu2,aramasec,aramacikis=1,aramaId;
	char aramaAd[50];
	
	while (aramacikis==1) {
		   
		printf("\n1.Isime gore arama\n2.Koda gore arama\n\nHangi arama turunde arama yapmak istiyorsunuz?.Cikis icin 0 tuslayiniz.\n");
	   aramasec = guvenli_Int ();
	   
	   if (aramasec == 0) {
	   	return;
	   }
	   
	  else if(aramasec != 1 && aramasec != 2) {
	   	printf("\nLutfen 1 veya 2 tuslayiniz.\n");
	   	continue ;
	   }
	   else if(aramasec == 1) {
printf("\nLutfen aramak istediginiz kitabin adini giriniz.\n");
     guvenli_String (aramaAd,sizeof(aramaAd));
     								trim(aramaAd);
     for (kitaparadongu1 = 0;kitaparadongu1 < kitapsayisi; kitaparadongu1++){
     	
     	if (_stricmp(aramaAd,kitaplar[kitaparadongu1].kitapAdi) == 0) {
     						 		
     		printf("\n%05d %-49s %-49s %05d %03d %02d\n",kitaplar[kitaparadongu1].kitapID,kitaplar[kitaparadongu1].kitapAdi,kitaplar[kitaparadongu1].yazarAdi,kitaplar[kitaparadongu1].kitapYili,kitaplar[kitaparadongu1].kitapAdeti,kitaplar[kitaparadongu1].kitapDurum);
     		 aramacikis = 0;
     				
		 }  
 	 }
 	 if (aramacikis == 1){
 	 	
 	 	printf("\nEslesme basarisiz.\n");
 	 	continue ;
	  }
	  else if (aramacikis == 0) {
	  	 printf("\nEslesme basarili.\n");
	  	 break;
	  }
	   }
	   else if (aramasec == 2) {
	   	
			printf("\nLutfen aramak istediginiz kitabin kodunu giriniz.\n");
				   	aramaId = guvenli_Int ();
				   	 kitapKodu_kontrol (aramaId);
				   	 
				  if(kitapKodu_kontrol (aramaId) == 0) {
				  	printf("\nLutfen 5 haneli bir kod giriniz.\n");
				  	continue;
				  } 	 
				  
			for (kitaparadongu2 = 0;kitaparadongu2 < kitapsayisi;kitaparadongu2++) {
				
				if(aramaId == kitaplar[kitaparadongu2].kitapID) {
						
					printf("\n%05d %-49s %-49s %05d %03d %02d\n",kitaplar[kitaparadongu2].kitapID,kitaplar[kitaparadongu2].kitapAdi,kitaplar[kitaparadongu2].yazarAdi,kitaplar[kitaparadongu2].kitapYili,kitaplar[kitaparadongu2].kitapAdeti,kitaplar[kitaparadongu2].kitapDurum);	
				aramacikis = 0;	
					break;
				}
			}	   
			if (aramacikis == 1){
 	 	
 	 	printf("\nEslesme basarisiz.\n");
 	 	continue ;
	  }	
	  else if (aramacikis == 0) {
	    	printf("\nEslesme basarili.\n");
	    	break;
	  }
	   }	
	}	
}




void kitapListele () {   //Kitap Listele
	int kitaplistedongu;
				printf("\n");
					printf("%-5s %45s %30s\t\t %-5s %-5s%7s\n\n", "ID", "Kitap Adi", "Yazar Adi", "Yil", "Adet", "Durum");
	for (kitaplistedongu = 0;kitaplistedongu < kitapsayisi;kitaplistedongu++) {
		printf("%05d %45s %30s\t\t%05d\t%03d\t%02d\n",kitaplar[kitaplistedongu].kitapID,kitaplar[kitaplistedongu].kitapAdi,kitaplar[kitaplistedongu].yazarAdi,kitaplar[kitaplistedongu].kitapYili,kitaplar[kitaplistedongu].kitapAdeti,kitaplar[kitaplistedongu].kitapDurum);
	}
		printf("\n\nKitaplarimiz Listelenmistir.\n");
}




//-------------------------------------------------------�ye Y�netim Fonksiyonlari;----------------------------------------------------------



void uyeEkle () {   // Uye ekle
		
	int uyeekleatla,uyetutint;
	char uyetutchar[50];	
	
	if(uyesayisi == 50) {
		printf("\nUye kontenjani dolu.\n");
		return;
	}
	
	printf("\nEklemek istediginiz uyenin bilgilerini giriniz.\n\n");
	
	while (1) {
				
	printf("\nYeni uyenin 4 haneli ID numarasini giriniz.Cikis icin 0 tuslayiniz.\n");
	
	uyetutint = guvenli_Int ();
	
	if (uyetutint == 0) {
				return;
	}
	
	    	uyeKodu_kontrol (uyetutint);
	    				uyeKodu_benzersizlik (uyetutint);
	    	
	    	if(uyeKodu_kontrol (uyetutint) == 0) {
	    		printf ("\nLutfen 4 haneli bir kod giriniz.\n");
	    		continue;
			}
			
			if(uyeKodu_benzersizlik (uyetutint) == 0) {
				printf("\nKod benzersiz degil.\n");
			continue;	
			}
			
			uyeler[uyesayisi].uyeID = uyetutint;
			
		
				printf("\nYeni uyenin adini giriniz.\n");
				 guvenli_String(uyeler[uyesayisi].uyeAdi,sizeof(uyeler[uyesayisi].uyeAdi));
			trim (uyeler[uyesayisi].uyeAdi);
			
			printf("\nYeni uyenin soyadini giriniz.\n");
				 guvenli_String(uyeler[uyesayisi].uyeSoyadi,sizeof(uyeler[uyesayisi].uyeSoyadi));
			trim (uyeler[uyesayisi].uyeSoyadi);
				
			while (1) {
				
				printf("\nYeni uyenin telefon numarasini giriniz.\n");
				 guvenli_String(uyeler[uyesayisi].uyeTel,sizeof(uyeler[uyesayisi].uyeTel));
			bosluk_sil(uyeler[uyesayisi].uyeTel);
				uyeNumara_kontrol (uyeler[uyesayisi].uyeTel);
				
				
				if (uyeNumara_kontrol (uyeler[uyesayisi].uyeTel) == 0) {
					continue;
				}
				break;
			}	
				  
			printf("\nYeni uyenin dogum tarihini giriniz.\n");
				 guvenli_String(uyeler[uyesayisi].dogumTarihi,sizeof(uyeler[uyesayisi].dogumTarihi));
				trim (uyeler[uyesayisi].dogumTarihi);
		uyesayisi++;
		
		printf("\nUye basariyla eklendi.\n");
		
		break;		
	}
		
   dosyaYazma_uye ();	
					         					
}




void uyeSil () {   // Uye Sil
	
	int uyesilID,i,j,tut;
	int bulundu=1;
	
	if(uyesayisi == 0) {
		printf("Silinecek uye yok.\n");
	return;
	}
	
	while (1) {
		
		printf("\nSilmek istediginiz uyenin ID numarasini giriniz.\n");
		 uyesilID = guvenli_Int ();
		 uyeKodu_kontrol (uyesilID);
		 
		 if(uyeKodu_kontrol (uyesilID) == 0) {
		 	printf("\nLutfen 4 haneli bir kod giriniz.\n");
		 	continue;
		 }
		 
		 bulundu = 1;
		 
		 for (i = 0;i < uyesayisi;i++) {
		 	
		 	if (uyesilID == uyeler[i].uyeID) {
		
		 		for (j = i;j < uyesayisi-1;j++) {
		 			
		 			uyeler[j] = uyeler[j+1];
		 			
				 }
		 		uyesayisi--;
		 		bulundu = 0;
		 		
		 		printf("\nUye basariyla silindi.\n");
                break; 
                
			 }
		 	
		 }
		if (bulundu == 0) {
			
			break;
		}
		
		else { 
              printf("\nUye bulunamadi.\n");
            continue; 
        }
			
	}
	
	dosyaYazma_uye ();
	
}




void uyeAra () {  // Uye Ara
	
	int i,dongucik = 1,secim1,aramakod,j;
	char aramaisim[50],aramasoyad[50];
	
	while (1)  {
		
		printf("\n\n1-)Koda gore arama\n2-)Isime gore arama\n\nHangi arama turunde arama yapmak istediginizi seciniz.\n");
		
		secim1 = guvenli_Int ();
		
		if (secim1 != 1 && secim1 != 2 ) {
			
			printf("\nLutfen 1 veya 2 tuslayiniz.\n");
			
			continue;
		}
		break;
	}
	
	
	
	while (secim1 == 1) {
					
					dongucik = 1;
					
		printf("\nLutfen aramak istediginiz uyeye ait 4 haneli kodu giriniz.Cikmak icin 0 tuslayiniz.\n");
		aramakod = guvenli_Int ();
		
		if (aramakod == 0) {
			return;
		}
		
		if(uyeKodu_kontrol (aramakod) == 0) {
			
			printf("\nLutfen 4 haneli bir kod giriniz.\n");
			
			continue;
		}
		
		
		for (i = 0;i < uyesayisi;i++) {
			
			if (aramakod == uyeler[i].uyeID) {
				
				printf ("\n%04d %-30s %-30s %11s %15s\n",uyeler[i].uyeID,uyeler[i].uyeAdi,uyeler[i].uyeSoyadi,uyeler[i].uyeTel,uyeler[i].dogumTarihi);
				
				dongucik = 0;
			}
			
		}	
		
		if (dongucik == 0) {
			
			printf ("\nEslesme basarili.\n");
			
			return;
			
		}
		
		if (dongucik == 1) {
			
			printf ("\nEslesme basarisiz.\n");
			
			continue ;
		}
		
	}
	
	
	
	
	while (secim1 == 2) {
		
		dongucik = 1;
		
		printf("\nLutfen aramak istediginiz uyenin sadece adini giriniz.Cikmak icin 0 tuslayiniz.\n");
		guvenli_String (aramaisim,sizeof (aramaisim));
		trim (aramaisim);
		
		if (aramaisim[0] == '0') {
			return;
		}
		
		printf("\nLutfen aramak istediginiz uyenin sadece soyadini giriniz.Cikmak icin 0 tuslayiniz.\n");
		guvenli_String (aramasoyad,sizeof (aramasoyad));
		trim (aramasoyad);
		
		if (aramasoyad[0] == '0') {
			return;
		}
		
		for (j = 0;j < uyesayisi;j ++) {
			
			if (_stricmp(aramaisim,uyeler[j].uyeAdi) == 0 && _stricmp(aramasoyad,uyeler[j].uyeSoyadi) == 0) {
				
				printf ("\n%04d %-30s %-30s %11s %15s\n",uyeler[j].uyeID,uyeler[j].uyeAdi,uyeler[j].uyeSoyadi,uyeler[j].uyeTel,uyeler[j].dogumTarihi);
				
				dongucik = 0;
			}
			
		}
		
		if (dongucik == 1) {
			
			printf ("\nEslesme basarisiz.\n");
			
			continue;
		}
		
		if (dongucik == 0) {
			
			printf ("\nEslesme basarili.\n");
			
			return;
		}
		
	}		
	
}




void uyeListele () {   // Uye Listele
	
	int uyeDongu;
	
	printf("\nUyeler:\n\n\n");
	printf("%-5s%-30s %-30s  %-15s%-15s%-10s\n\n", "ID", "Adi", "Soyadi", "Telefon", "Dogum Tarihi", "Alinan Kitap");
	
	for (uyeDongu = 0;uyeDongu < uyesayisi;uyeDongu++) {
		
		printf("%04d %-30s %-30s %-15s %-15s %02d\n",uyeler[uyeDongu].uyeID,uyeler[uyeDongu].uyeAdi,uyeler[uyeDongu].uyeSoyadi,uyeler[uyeDongu].uyeTel,uyeler[uyeDongu].dogumTarihi,uyeler[uyeDongu].alinankitapSayisi);
	}
	
	printf("\n\n\nUyeler listelenmistir.\n");
	
}





//-------------------------------------------------------�d�n� Alma/�ade Fonksiyonlari;----------------------------------------------------------



void kitapOduncAl() {

int uyekod,i,cikis=1,uyetut,kitapkod,j,cikis1=1,kitaptut,eminlik;


 while (1) {   // Uye bulma 
 	
 	printf ("\nLutfen odunc kitap alacak uyenin 4 haneli kodunu giriniz.Cikmak icin 0 tuslayiniz.\n");
 	uyekod = guvenli_Int ();
 	uyeKodu_kontrol (uyekod);
 	
 	if (uyekod == 0 ) {
 		
 	return;	
 		
	 }
	 
	 
 	if (uyeKodu_kontrol (uyekod) == 0 ) {
 		
 		printf ("\nLutfen 4 haneli bir kod giriniz.\n");
 		
 		continue;
	 }
	 
	 cikis = 1;
	 
	 for ( i = 0 ; i < uyesayisi ; i ++ ) {
	 	
	 	if ( uyekod == uyeler[i].uyeID ) {
	 		
	 		printf ("\n%04d %-30s %-30s %11s %15s\n",uyeler[i].uyeID,uyeler[i].uyeAdi,uyeler[i].uyeSoyadi,uyeler[i].uyeTel,uyeler[i].dogumTarihi);
	 		
	 		uyetut = i;
	 		cikis = 0;
	 		break;
		 }
	 	
	 }
	 
	 if ( cikis == 1 ) {
	 	
	 	printf ("\nUye bulunamadi.\n");
	 	
	 	continue;
	 }
	 
	 if ( cikis == 0 )  {
	 	
	 	printf ("\nUye bulundu.\n");
	 	
	 	break;
	 }
	 
 } 
 
 
 
 while ( cikis == 0 ) { // Kitap bulma
 	
 	if ( uyeler[uyetut].alinankitapSayisi >= 5) {
 		
 		printf ("\nAyni kullanici 5'ten fazla kitap alamaz.\n");
 		return;
 		
	 }
 
 kitapListele ();
 
printf ("\nOdunc almak istediginiz kitabin ID kodunu giriniz.\n");
kitapkod = guvenli_Int ();


if (kitapKodu_kontrol (kitapkod) == 0 ) {
	
	printf ("\nLutfen 5 haneli bir kod giriniz.\n");
	
	continue;	
}

cikis1 = 1;

for (j=0;j < kitapsayisi ; j ++ ) {
	
	if (kitapkod == kitaplar[j].kitapID) {
		
		printf ("\n%05d %-30s %-30s %04d %03d %02d\n",kitaplar[j].kitapID,kitaplar[j].kitapAdi,kitaplar[j].yazarAdi,kitaplar[j].kitapYili,kitaplar[j].kitapAdeti,kitaplar[j].kitapDurum);
		
		kitaptut = j;
		cikis1 = 0;
		break;
	}
	
}

if (cikis1 == 1) {
	
	printf("\nKitap bulunamadi.\n");
		
	continue;
}

if (cikis1 == 0 ) {
	
	printf("\nKitap bulundu.\n");
	
	break;
}

}



while (cikis1 == 0) {    // Odunc islemleri
	
	if ( kitaplar[kitaptut].kitapDurum == 2 ) {
		
		printf ("\nKitap hic kalmadi.Daha sonra tekrar kontrol edebilirsiniz\n");
		
		return;
	}
	
	printf("\nBu kitabi odunc almak istediginizden emin misiniz?\n\n1-)Evet\n2-)Hayir\n");
	eminlik = guvenli_Int ();
	
	if ( eminlik != 1 && eminlik != 2 ) {
		
		printf ("\nLutfen sadece 1 veya 2 rakamini tuslayiniz.\n");
		
		continue;	
	} 
	
	if (eminlik == 2 ) {
		
		printf("\nVazgecildi.\n");
		
		return;
	}
	
	if ( eminlik == 1 ) {
		
		
		oduncler[oduncsayisi].oduncID = oduncsayisi + 1;
		oduncler[oduncsayisi].uyeID = uyeler[uyetut].uyeID;
		oduncler[oduncsayisi].kitapID = kitaplar[kitaptut].kitapID;
		
		// Alma tarihi
		
		time_t t = time(NULL);
        struct tm tm = *localtime(&t);
        sprintf(oduncler[oduncsayisi].alisTarihi, "%02d.%02d  %02d/%02d/%04d",tm.tm_hour,tm.tm_min, tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
        
        
        // �ade tarihi (Al�� tarihinden �rne�in 15 g�n sonras�)
        time_t iade_t = t + (15 * 24 * 60 * 60); // 15 g�n saniye cinsinden
        struct tm iade_tm = *localtime(&iade_t);
        sprintf(oduncler[oduncsayisi].iadeTarihi, "%02d.%02d  %02d/%02d/%04d",iade_tm.tm_hour,iade_tm.tm_min, iade_tm.tm_mday, iade_tm.tm_mon + 1, iade_tm.tm_year + 1900);
		
		
		oduncler[oduncsayisi].iadeDurumu = 0;
		
		uyeler[uyetut].alinankitapSayisi++;
		
		oduncsayisi ++;
		
		kitaplar[kitaptut].kitapAdeti--;   // kitap sayisini 1 azalt
		
		
		
		
		if ( kitaplar[kitaptut].kitapAdeti == 0 ) {   // kitap al�n�nca adet 0 olursa kitap durumunu 0 yap.
			
			kitaplar[kitaptut].kitapDurum = 2;
			
		}
		
		dosyaYazma_kitap ();
		dosyaYazma_oduncIslemleri ();
		dosyaYazma_uye ();
		
		printf ("\nOdunc alma islemi basariyla gerceklestirildi.\n");
		
		return;
	}
	
  }

}



void kitapIadeEt() {
	
	int uyekod,kitapkod,i,cikis=1,odunctut,kitaptut,uyetut;
	
	
	while (cikis == 1)  {
		
		cikis = 1;
		
		printf ("\nKitap iadesi yapacak uyenin ID numarasini giriniz.Cikis icin 0 tuslayiniz.\n");
		
		uyekod = guvenli_Int ();
		
		if (uyekod == 0) {
			return;
		}
		
		if (uyeKodu_kontrol (uyekod) == 0) {
			
			printf ("\nLutfen 4 haneli bir kod giriniz.\n");
					
			continue;
		}
		
		printf ("\nIadesi yapilacak kitabin ID numarasini giriniz.\n");
		
		kitapkod = guvenli_Int ();
		
		if (kitapKodu_kontrol (kitapkod) == 0) {
			
			printf ("\nLutfen 5 haneli bir kod giriniz.\n");
					
			continue;
		}
		
		
		printf("\n %3s \t%4s  \t%5s%20s   %20s \t%2s\n\n", "Odunc ID", "Uye ID", "Kitap ID", "Alis Tarihi", "Teslim Tarihi", "Iade durumu");
		
		for (i=0 ;i < oduncsayisi ; i++) {
			
			if (uyekod == oduncler[i].uyeID && kitapkod == oduncler[i].kitapID && oduncler[i].iadeDurumu == 0) {
				
				printf ("%5d \t\t%4d\t	%5d\t%20s   %20s \t    %02d\n",oduncler[i].oduncID,oduncler[i].uyeID,oduncler[i].kitapID,oduncler[i].alisTarihi,oduncler[i].iadeTarihi,oduncler[i].iadeDurumu);
				
				odunctut = i;
			cikis = 0;	
			}
			
		}
		
		if (cikis == 1) {
			
			printf ("\nEslesme bulinamadi.\n");
			continue;
		}
		
		if (cikis == 0) {
			
			printf ("\nEslesme bulindi.\n");
			break;
		}
					
	}
	
	
	for (i= 0; i < kitapsayisi ; i ++ ) {
		
		if (kitapkod == kitaplar[i].kitapID) {
			
			kitaptut = i;
			break;
		}
		
	}
	
	for (i= 0; i < uyesayisi ; i ++ ) {
		
		if (uyekod == uyeler[i].uyeID) {
			
			uyetut = i;
			break;
		}
		
	}
	
	kitaplar[kitaptut].kitapAdeti ++;
	uyeler[uyetut].alinankitapSayisi --;
	oduncler[odunctut].iadeDurumu = 1;
	
	time_t iadetarih_t = time(NULL);
	struct tm iadetarih_tm = *localtime(&iadetarih_t);
	sprintf(oduncler[odunctut].iadeEdilmeTarihi, "%02d.%02d  %02d/%02d/%04d",iadetarih_tm.tm_hour,iadetarih_tm.tm_min, iadetarih_tm.tm_mday, iadetarih_tm.tm_mon + 1, iadetarih_tm.tm_year + 1900);
	
	struct tm iade_tm = {0};
int saat, dakika, gun, ay, yil;

// iadeTarihi format�n �u: "HH.MM  DD/MM/YYYY" gibi g�z�k�yor
// �rne�in: "14.30  25/07/2025"
// sscanf ile ay�klayabiliriz:

sscanf(oduncler[odunctut].iadeTarihi, "%d.%d  %d/%d/%d", &saat, &dakika, &gun, &ay, &yil);

iade_tm.tm_hour = saat;
iade_tm.tm_min = dakika;
iade_tm.tm_mday = gun;
iade_tm.tm_mon = ay - 1;      // tm_mon 0-11 aras�d�r
iade_tm.tm_year = yil - 1900; // tm_year 1900�den itibaren y�l
iade_tm.tm_sec = 0;
iade_tm.tm_isdst = -1;        // yaz saati uygulamas� bilmiyoruz

time_t iade_time = mktime(&iade_tm);

time_t su_an = time(NULL);

double fark = difftime(iade_time, su_an);

if (fark < 0) {
    printf("\nIade tarihi gecmis! Lutfen cezanizi odeyin.\n");
} else {
    printf("\nIade tarihi gecmemis. Tesekkurler.\n");
}

	
	dosyaYazma_oduncIslemleri ();
	
	printf ("\nIade basarili.\n");
	
	return;
	
}




void oduncGecmisiListele()   {
	
	int i;
	
	printf("\n");
	
	printf(" %3s \t%4s  \t%5s%20s   %20s \t%2s\n\n", "Odunc ID", "Uye ID", "Kitap ID", "Alis Tarihi", "Teslim Tarihi", "Iade durumu");
	
	for (i=0 ; i < oduncsayisi ; i ++) {
		
		printf ("%5d \t\t%4d\t	%5d\t%20s   %20s \t%02d\n",oduncler[i].oduncID,oduncler[i].uyeID,oduncler[i].kitapID,oduncler[i].alisTarihi,oduncler[i].iadeTarihi,oduncler[i].iadeDurumu);
		
	}
	
	printf ("\n\nOdunc gecmisi basariyla listelenmislir.\n");
	
}

						
						

//---------------------------------------Belle�e Y�kleme Fonksiyonlari;------------------------------------------------------------------------
						
						
						

void bellekKayit_kitap () {    // Program ba�lad���nda dosyadaki t�m kitaplari belle�e y�kler.

FILE *kitapDosya = fopen("Kitaplar.txt","r");
	
	if (kitapDosya == NULL) {
		printf("Dosya islemi basarisiz.\n");
		kitapsayisi = 0;
					return;
	}
	 
	 kitapsayisi = 0;   
while  (fscanf(kitapDosya,"%d;%49[^;];%49[^;];%d;%d;%d",&kitaplar[kitapsayisi].kitapID,kitaplar[kitapsayisi].kitapAdi,kitaplar[kitapsayisi].yazarAdi,&kitaplar[kitapsayisi].kitapYili,&kitaplar[kitapsayisi].kitapAdeti,&kitaplar[kitapsayisi].kitapDurum) == 6) {
	
	
	if (kitaplar[kitapsayisi].kitapAdeti == 0) {
            kitaplar[kitapsayisi].kitapDurum = 2;
        } 
		
		else {
            
            kitaplar[kitapsayisi].kitapDurum = 1;
        }
	
	trim(kitaplar[kitapsayisi].kitapAdi); 
        trim(kitaplar[kitapsayisi].yazarAdi); 
        
	kitapsayisi++;
	
	if (kitapsayisi >= 100) { 
            printf("Uyari:Kitap dizisi kapasitesi doldu,tum kitaplar yuklenemedi.\n");
           break;
        }
	
}
	
	fclose(kitapDosya);
}





void bellekKayit_uye () {     // Program ba�lad���nda dosyadaki t�m �yeleri belle�e y�kler.
	
	FILE *uyeDosya = fopen("Uyeler.txt","r");
	
	if (uyeDosya == NULL) {
		printf("Dosya islemi basarisiz.\n");
					return;
	}
	
	uyesayisi = 0;
	
	while  (fscanf(uyeDosya,"%d;%49[^;];%49[^;];%49[^;];%49[^;];%d\n",&uyeler[uyesayisi].uyeID,uyeler[uyesayisi].uyeAdi,uyeler[uyesayisi].uyeSoyadi,uyeler[uyesayisi].uyeTel,uyeler[uyesayisi].dogumTarihi,&uyeler[uyesayisi].alinankitapSayisi) == 6) {

	trim(uyeler[uyesayisi].uyeAdi); 
        trim(uyeler[uyesayisi].uyeSoyadi); 
        
        trim(uyeler[uyesayisi].uyeTel);
    trim(uyeler[uyesayisi].dogumTarihi);
        
	uyesayisi++;
}
	
	fclose(uyeDosya);
}





void bellekKayit_oduncIslemleri () {    // Program ba�lad���nda dosyadaki t�m �d�n� al ve teslim et i�lemlerini belle�e y�kler.
	
	FILE *oduncDosya = fopen("Oduncler.txt","r");
	
	if (oduncDosya == NULL) {
		printf("Dosya islemi basarisiz.\n");
					return;
	}
	
	oduncsayisi = 0;
	
	while ( fscanf (oduncDosya,"%d;%d;%d;%20[^;];%20[^;];%d",&oduncler[oduncsayisi].oduncID,&oduncler[oduncsayisi].uyeID,&oduncler[oduncsayisi].kitapID,oduncler[oduncsayisi].alisTarihi,oduncler[oduncsayisi].iadeTarihi,&oduncler[oduncsayisi].iadeDurumu) == 6 )  {
		
		
		trim(oduncler[oduncsayisi].alisTarihi);
		trim(oduncler[oduncsayisi].iadeTarihi);
		
		if (oduncsayisi >= 500) {
			
			printf("Uyari: Odunc kayit dizisi dolu. Daha fazla veri yuklenemedi.\n");
			break;
		}
		
		oduncsayisi ++;
	}
	
	fclose (oduncDosya);
	
//	printf("Odunc islemleri bellege basariyla yuklendi. Toplam kayit: %d\n", oduncsayisi);
}




//-------------------------------------------Dosyaya Yazma Fonksiyonlari;-----------------------------------------------------------------------





void dosyaYazma_kitap () {                /*Bellekteki t�m kitap verilerini program kapat�l�rken veya �nemli bir de�i�iklikten sonra 
				                                        kitaplar.txt dosyas�na kaydeder. */
int dosyaYazmak;				                                        
				                                        
  FILE *kitapDosyaYaz = fopen("Kitaplar.txt","w");
  
  if (kitapDosyaYaz == NULL) {
        printf("\nHATA: Kitaplar.txt dosyasi yazma icin acilamadi.\n");
        return;
    }
  
  for (dosyaYazmak = 0;dosyaYazmak < kitapsayisi;dosyaYazmak++) {
  	
  	fprintf (kitapDosyaYaz,"%d;%s;%s;%d;%d;%d\n",kitaplar[dosyaYazmak].kitapID,kitaplar[dosyaYazmak].kitapAdi,kitaplar[dosyaYazmak].yazarAdi,kitaplar[dosyaYazmak].kitapYili,kitaplar[dosyaYazmak].kitapAdeti,kitaplar[dosyaYazmak].kitapDurum);
  	
  }	
	fclose(kitapDosyaYaz);
}




void dosyaYazma_uye () {                  /*Bellekteki t�m �ye verilerini uyeler.txt dosyas�na kaydeder.*/
	
	int dosyaYazmak1;
	
	FILE *uyeDosyaYaz = fopen ("Uyeler.txt","w");
	
	if (uyeDosyaYaz == NULL) {
        printf("\nHATA: Uyeler.txt dosyasi yazma icin acilamadi.\n");
        return;
    }
	
	for (dosyaYazmak1 = 0;dosyaYazmak1 < uyesayisi;dosyaYazmak1++) {
  	
  	fprintf (uyeDosyaYaz,"%d;%s;%s;%s;%s;%d\n",uyeler[dosyaYazmak1].uyeID,uyeler[dosyaYazmak1].uyeAdi,uyeler[dosyaYazmak1].uyeSoyadi,uyeler[dosyaYazmak1].uyeTel,uyeler[dosyaYazmak1].dogumTarihi,uyeler[dosyaYazmak1].alinankitapSayisi);
  	
  }	
	fclose(uyeDosyaYaz);
	
}






void dosyaYazma_oduncIslemleri () {        /*Bellekteki t�m �d�n� alma/iade verilerini odunc_islemleri.txt dosyas�na kaydeder.*/
	
	int dosyaYazmak2;
	
	FILE *oduncDosyaYaz = fopen ("Oduncler.txt","w");
	
	if ( oduncDosyaYaz == NULL ) {
        printf("\nHATA: Oduncler.txt dosyasi yazma icin acilamadi.\n");
        return;     // Fonksiyondan ��k
    }
	
	for (dosyaYazmak2 = 0;dosyaYazmak2 < oduncsayisi;dosyaYazmak2++) {
  	
  	fprintf (oduncDosyaYaz,"%d;%d;%d;%s;%s;%d\n",oduncler[dosyaYazmak2].oduncID,oduncler[dosyaYazmak2].uyeID,oduncler[dosyaYazmak2].kitapID,oduncler[dosyaYazmak2].alisTarihi,oduncler[dosyaYazmak2].iadeTarihi,oduncler[dosyaYazmak2].iadeDurumu);
  	
  }	
	fclose(oduncDosyaYaz);
}






int main () {               //  ANA FONKS�YON   
  	setlocale(LC_ALL, ".Turkish");
	  
	  int secim;  
	  	
  	  		bellekKayit_kitap ();
  	  		bellekKayit_uye ();
  	  		bellekKayit_oduncIslemleri();
  	  		
  	  //		printf("Uye sayisi: %d\n", uyesayisi);
  	  	
do {
		secim = menu ();
	
	switch(secim) {
	  	
	  	case 1:
	  		    kitapEkle ();
	break;
	  		case 2:
	  			 
	  			kitapSil ();
		break;  			
	  			case 3:
	  				
	  				kitapListele ();
	  				
	  		break;		
	  				case 4:
	  				
					kitapAra ();
					  	
	  			break;		
	  					case 5:
	  					
	  					 kitapGuncelle ();
						  	
	  				break;		
	  						case 6:
	  						
	  						uyeEkle ();
							  	
	  					break;		
	  							case 7:
	  								
	  						uyeSil ();
	  						
							break;		
	  								case 8:
	  								
									  uyeAra ();	
	  								
								break;	
	  									case 9:
	  										
	  									uyeListele ();
	  									
	  								break;
	  										case 10:
	  										
	  										kitapOduncAl();
											  	
	  									break;	
	  											case 11:
	  												
	  												kitapIadeEt();
	  												
	  										break;	
	  												case 12:
	  													
	  												oduncGecmisiListele();
													  	
	  											break;	
	  													case 13:
	  														
	  										printf("\nCikis Yapildi.\n");				
	  												break;	
	  														default:
	  															
	  															
	  														break;	  	
	  }
	
}while(secim != 13);
				 

	return 0;
}
