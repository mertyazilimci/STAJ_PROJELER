#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

void menu () {
	
	printf("----------------------------------------\nSiparis & Stok Takibi Sistemi\n\n\n1.Musteri ekle.\n2.Urun ekle\n3.Urun sil\n4.Siparis ver\n5.Stoklari goster\n6.Stok guncelle\n7.Siparis gecmisi\n8.Musteri listesi\n9.Musteri sil\n10.Cikis\n\n\nLutfen secim yapiniz.\n");	
}

 struct musteri {
 	char ad[20];
 	char soyad[20];
 	int musteriID;
 };
 
 struct urun {
 	int urunID;
 	char urunadi[20];
 	int urunadedi;
 	int urunfiyati; 	
 };
 
 struct siparis {
 	char musteri_Adi[20];
 	char musteri_Soyadi[20];
 	int musteri_IDsi;
 	
 	char urun_Isim[20];
 	int urun_Fiyat;
 	int urun_Adet;
 	int urun_ID1;
 	int urun_Toplam;
 	struct tm yerelzaman;
 	char tarihSaat[50]; // dosyaya yazýp okumak için
 };
 
 

// Bu fonksiyonu çaðýrdýðýnda string olarak tarih ve saati verir
void tarihSaatAl(char* buffer, int bufferSize) {
    time_t simdi = time(NULL);
    struct tm *zamanBilgisi = localtime(&simdi);
    strftime(buffer, bufferSize, "%d-%m-%Y %H:%M:%S", zamanBilgisi);
}

 
 
  void siparismodulu (struct urun *a,int urunsayisi,struct musteri *b,int toplam_fiyat,struct siparis *siparisler,int *sip_sayisi,int *siparis_IDsi1,int *mevcut_siparis_sayisi) {
 	int siparisID;
 	int secim1;
 	int mustID;
 	int dongu;
 	int siparisAdet;
    int k;
    int yeniden;
    char tarihsaatStr [100];
    int sonuccc;
 	
 	printf("\n\n%-22s | %-6s| %-6s| %-6s","Urun Adi","Fiyat","Adet","ID\n----------------------------------------------");
 	
           for (k = 0; k < urunsayisi; k++) {
    printf("\n%d-) %-20s %05d	%05d	%05d",k+1,a[k].urunadi, a[k].urunfiyati, a[k].urunadedi, a[k].urunID);
}

 
// printf("\n\nLutfen musteri ID giriniz.\n");
// scanf("%d",&mustID);

while (1) {
    printf("\n\nLutfen musteri ID giriniz.\n");
    sonuccc = scanf("%d", &mustID);
    if (sonuccc != 1) {
        printf("\nGecersiz ID girdiniz! Lutfen sadece tam sayi giriniz.\n");
        while (getchar() != '\n'); // Buffer temizle
    } else {
        while (getchar() != '\n'); // Satýr sonundaki fazla karakterleri temizle
        break; // Geçerli giriþ alýndý
    }
}

// int musteribulundu=0;
     for(dongu=0;dongu<5;dongu++) {
		
if(mustID == b[dongu].musteriID) {
	printf("\n				     %s	    %s   %s\n                                  |---------------------|","Ad","Soyad","ID");
	printf("\nMusteri bulundu.Musteri bilgileri: %s  %s  %d",b[dongu].ad,b[dongu].soyad,b[dongu].musteriID);
//	musteribulundu=1;
	break;
}


 /* else if(!musteribulundu){

printf("\nMusteri bulunamadi.\n");
	break;
} */

  else if(dongu==4 && mustID != b[dongu].musteriID){

printf("\nMusteri bulunamadi.\n");
	break;
} 

}

if (mustID == b[dongu].musteriID) {
	
printf("\n\n\nUrunlerimiz listelenmistir.Lutfen siparis vermek istediginiz urunu seciniz.\n");

scanf("%d",&secim1);

if (secim1 < 1 || secim1 > urunsayisi) {
    printf("Gecersiz urun secimi.\n");
    return;
}


printf("Kac adet istiyorsunuz.\n");
scanf("%d",&siparisAdet);

if(siparisAdet>a[secim1-1].urunadedi) {
	printf("\nStok yetersiz.\n\n");
}
else {
	toplam_fiyat= a[secim1-1].urunfiyati*siparisAdet;
	
int uretilen_ID;
int benzersiz=0;
int l;
int denemeSayisi = 0;
 
while (!benzersiz && denemeSayisi < 1000) {
    uretilen_ID = rand() % 9000 + 1000;
    benzersiz = 1; // þimdilik benzersiz say
    for (l = 0; l < *mevcut_siparis_sayisi; l++) {
        if (siparis_IDsi1[l] == uretilen_ID) {
            benzersiz = 0; // ayný ID bulundu
            break;
        }
    }
    denemeSayisi++;
}

if (!benzersiz) {
    printf("Benzersiz siparis ID bulunamadi. Lutfen daha sonra tekrar deneyin.\n");
    return;
}

siparis_IDsi1[*mevcut_siparis_sayisi] = uretilen_ID;
(*mevcut_siparis_sayisi)++;
	
	time_t zaman = time(NULL);
siparisler[*sip_sayisi].yerelzaman = *localtime(&zaman);
tarihSaatAl(siparisler[*sip_sayisi].tarihSaat, sizeof(siparisler[*sip_sayisi].tarihSaat));
	
	FILE *siparisbilgisi = fopen("Siparisler.txt","a");
	fprintf(siparisbilgisi,"%-20s %-20s %04d %-20s %05d %05d %05d %05d %05d %s\n",b[dongu].ad,b[dongu].soyad,b[dongu].musteriID,a[secim1-1].urunadi,a[secim1-1].urunfiyati,siparisAdet,a[secim1-1].urunID,toplam_fiyat,uretilen_ID,siparisler[*sip_sayisi].tarihSaat);
	fclose(siparisbilgisi);
	
	strcpy(siparisler[*sip_sayisi].musteri_Adi, b[dongu].ad);
strcpy(siparisler[*sip_sayisi].musteri_Soyadi, b[dongu].soyad);
siparisler[*sip_sayisi].musteri_IDsi = b[dongu].musteriID;
strcpy(siparisler[*sip_sayisi].urun_Isim, a[secim1-1].urunadi);
siparisler[*sip_sayisi].urun_Fiyat = a[secim1-1].urunfiyati;
siparisler[*sip_sayisi].urun_Adet = siparisAdet;
siparisler[*sip_sayisi].urun_ID1 = a[secim1-1].urunID;
siparisler[*sip_sayisi].urun_Toplam = toplam_fiyat;
(*sip_sayisi)++;
	
		
	a[secim1-1].urunadedi -= siparisAdet;
	
	FILE *urunAdetdus = fopen("Urunler.txt","w");
	
	for (yeniden=0;yeniden<urunsayisi;yeniden++) {
		
		fprintf(urunAdetdus,"%-20s %05d %05d %05d\n",a[yeniden].urunadi,a[yeniden].urunfiyati,a[yeniden].urunadedi,a[yeniden].urunID);
	}
	fclose(urunAdetdus);
		
}	
	
}

	 } 
	 
	 

void stok_goster (struct urun *b,int urun_sayisi)  {
	int s_o;
	printf("\n\nMevcut stoklar asagida listelenmistir.\n\n%-20s| %-6s   | %-6s	| %-6s\n----------------------------------------\n","Urun Adi","Fiyat","Adet","ID");
	for (s_o=0;s_o<urun_sayisi && s_o<10;s_o++) {
		
			printf("%-20s %05d	%05d	%05d\n",b[s_o].urunadi,b[s_o].urunfiyati,b[s_o].urunadedi,b[s_o].urunID);
		
	}	
}


   void siparis_gecmisi (struct siparis *siptut,int *sip_sayisi,int siparis_IDsi[50]) {
  	int y;
  	printf("\n");
  	for(y=0;y<*sip_sayisi;y++) {
  		
  	printf("%-20s %-20s %04d %-20s %05d %05d %05d %05d %s\n",siptut[y].musteri_Adi,siptut[y].musteri_Soyadi,siptut[y].musteri_IDsi,siptut[y].urun_Isim,siptut[y].urun_Fiyat,siptut[y].urun_Adet,siptut[y].urun_Toplam,siparis_IDsi[y],siptut[y].tarihSaat);	
	  } 
	  printf("\n");	
  } 
  
  
  void musteri_listele (struct musteri *listesi,int *must_sayisi) {
  	int m;
  	
  	for(m=0;m<*must_sayisi;m++) {
  		
  		printf("%-20s %-20s %05d\n",listesi[m].ad,listesi[m].soyad,listesi[m].musteriID);
  		
	  } 	
  }
	 
	 
	 void musteri_sil (int *must_sayisi1,struct musteri *sil_musteri) {
  		int sil,n,o,sonuc4;
		  int bulundu = 0;	
  	//	scanf("%d",&sil);
  	while (1) {
    printf("\nSilmek istediginiz musterinin ID'sini giriniz.\n");
    sonuc4 = scanf("%d", &sil);
    if (sonuc4 != 1) {
        printf("\nGecersiz ID girdiniz! Lutfen sadece tam sayi giriniz.\n");
        while (getchar() != '\n'); // Buffer temizle
    } else {
        while (getchar() != '\n'); // Satýr sonundaki fazla karakterleri temizle
        break; // Geçerli giriþ alýndý
    }
}
  	
  			FILE *musteriyi_sil = fopen("Musteriler.txt","w");
  			
  			for (n = 0; n < *must_sayisi1; n++) {
  				
    if (sil_musteri[n].musteriID != sil) {
        fprintf(musteriyi_sil, "%-20s %-20s %04d\n",
            sil_musteri[n].ad,
            sil_musteri[n].soyad,
            sil_musteri[n].musteriID);
    }
    else {
		  	// Diziden de sil
            for (o = n; o < *must_sayisi1 - 1; o++) {
                sil_musteri[o] = sil_musteri[o + 1];
            }
            (*must_sayisi1)--; // sayýyý bir azalt
            bulundu = 1;
            n--; // kaydýrma yaptýðýmýz için indeksi bir geri al
		  }
}
		  fclose(musteriyi_sil);
		  if (bulundu) {
        printf("Musteri basariyla silindi.\n");
    } else {
        printf("Musteri ID bulunamadi.\n");
    }		  
	  }
	  
	  
	  void urun_sil (int *urunsil_sayi,struct urun *urunsil_tut) {
	  	int urunSil,p,r,bulundu1=0;
	  	printf("Lutfen silmek istediginiz Urunun ID'sini giriniz.\n");
	  	scanf("%d",&urunSil);
	  	
	  	FILE *urun_Sil = fopen("Urunler.txt","w");
	  	
	  	for (p=0; p<*urunsil_sayi;p++){
	  		if(urunsil_tut[p].urunID != urunSil) {
	  			
	  			fprintf(urun_Sil,"%-20s %05d %05d %05d\n",urunsil_tut[p].urunadi,urunsil_tut[p].urunfiyati,urunsil_tut[p].urunadedi,urunsil_tut[p].urunID);
			  }
			  else {
			    for(r=p;r<*urunsil_sayi-1;r++) {
			    		urunsil_tut[r] = urunsil_tut[r+1];
				}
				(*urunsil_sayi)--;
				bulundu1=1;
				p--;
			  }
		  }
		  fclose(urun_Sil);
		  if (bulundu1){
		  	printf("Urun basariyla silindi.\n");
		  }
		  else {
        printf("\nUrun ID bulunamadi.\n");
    }		  
	  }
	  
	  void stok_guncelle (struct urun *stokGuncelle,int *stokUzun) {
	  	
		  int stokguncelle,t,bulundu2=0;
		  printf("Lutfen stok guncellemesi yapmak istediginiz urunun ID'sini giriniz.\n");
	  	scanf("%d",&stokguncelle);
	  	
	  	FILE *stokguncelle_dosya = fopen("Urunler.txt","w");
	  	if (stokguncelle_dosya == NULL) {
    printf("Dosya acilamadi.\n");
    return;
}
	  	for(t=0;t<*stokUzun;t++) {
	  		if(stokGuncelle[t].urunID==stokguncelle) {
	  			printf("Stok adeti giriniz.\n");
	  			scanf("%d",&stokGuncelle[t].urunadedi);
			  bulundu2=1;
			  }
			  fprintf(stokguncelle_dosya,"%-20s %05d %05d %05d\n",stokGuncelle[t].urunadi,stokGuncelle[t].urunfiyati,stokGuncelle[t].urunadedi,stokGuncelle[t].urunID);
		  } 
		  	if(bulundu2){
		  		printf("Stok basariyla guncellendi.\n");
			  }
			  else{
			  	printf("Stok guncelleme basarisiz.\n");
			  }
	  }
	  
	  
	  void inputTemizle() {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}

// Kullanýcýdan güvenli bir þekilde tamsayý giriþi almak için
int getSafeIntegerInput() {
    int value;
    int result;
    while (1) {
        result = scanf("%d", &value);
        if (result != 1) {
            printf("\nGecersiz giris! Lutfen sadece tam sayi giriniz.\n");
            while (getchar() != '\n'); // Input buffer'ý temizle
        } else {
            while (getchar() != '\n'); // Satýr sonundaki fazla karakterleri temizle
            break;
        }
    }
    return value;
}


// ID'nin benzersiz olup olmadýðýný kontrol eden yardýmcý fonksiyon
// Bu fonksiyonu ana dosyanýn üst kýsýmlarýna, main'den önce tanýmlamalýsýn.
int isCustomerIDUnique(const struct musteri *musteriler, int musteriSayisi, int newID) {
	int k;
    for ( k = 0; k < musteriSayisi; k++) {
        if (musteriler[k].musteriID == newID) {
            return 0; // Benzersiz deðil
        }
    }
    return 1; // Benzersiz
}


int main()  {
		srand(time(NULL));
	struct musteri  musteriler[5];
	int secim;
	int i=0,j=0,x=0;
	int toplam_tutar=0;
	int *xp;
	int kontrol_ID=0;
	int urun_kontrol_ID;
	int uretilenID;
	 	int siparis_IDsi[50];
	 	int *sipID_tut = siparis_IDsi;
	 	int mevcut_siparis_sayisi = 0;
	 	int sonucc;
	 	int sadeceRakam = 1,i1;
	 	int basamak = 0;
	
	struct urun  urunler[10];
	struct urun *urunp= urunler;
	
	struct siparis siparisler[50];
	struct siparis *siparisp= siparisler;

FILE *musteriokuma = fopen("Musteriler.txt","r");

if (musteriokuma != NULL){
	
	while(fscanf(musteriokuma,"%19s %19s %d",musteriler[i].ad,musteriler[i].soyad,&musteriler[i].musteriID)==3){
	i++;
	if(i>=5) break;	
	}
	fclose(musteriokuma);
}

FILE *urunokuma = fopen("Urunler.txt","r");

if (urunokuma != NULL){
	
	while(fscanf(urunokuma,"%s %d %d %d",urunler[j].urunadi,&urunler[j].urunfiyati,&urunler[j].urunadedi,&urunler[j].urunID)==4){
	j++;
	if(j>=10) break;	
	}
	fclose(urunokuma);
}


FILE *siparisokuma = fopen("Siparisler.txt","r");

if (siparisokuma != NULL){
    while (x < 50) {
        int sonuc = fscanf(siparisokuma, "%19s %19s %d %19s %d %d %d %d %d %[^\n]",
                           siparisler[x].musteri_Adi,
                           siparisler[x].musteri_Soyadi,
                           &siparisler[x].musteri_IDsi,
                           siparisler[x].urun_Isim,
                           &siparisler[x].urun_Fiyat,
                           &siparisler[x].urun_Adet,
                           &siparisler[x].urun_ID1,
                           &siparisler[x].urun_Toplam,
                           &uretilenID,
						   siparisler[x].tarihSaat);
						   
						   
        if (sonuc == EOF) {
            break; // Dosya sonuna geldik
        }

        if (sonuc != 10) {
            printf("Dosya okuma hatasi! Satir formati bozuk olabilir.\n");
            break;
        }

        siparis_IDsi[x] = uretilenID;
        mevcut_siparis_sayisi++;
        x++;
    }
    fclose(siparisokuma);
    
    xp = &x;
}




  /* FILE *siparisokuma = fopen("Siparisler.txt","r");

if (siparisokuma != NULL){
	
	while(x<50 && fscanf(siparisokuma,"%19s %19s %d %19s %d %d %d %d",siparisler[x].musteri_Adi,siparisler[x].musteri_Soyadi,siparisler[x].musteri_IDsi,siparisler[x].urun_Isim,siparisler[x].urun_Fiyat,siparisler[x].urun_Adet,siparisler[x].urun_ID1,siparisler[x].urun_Toplam)==8){
	
	if(fscanf(siparisokuma,"%19s %19s %d %19s %d %d %d %d",siparisler[x].musteri_Adi,siparisler[x].musteri_Soyadi,siparisler[x].musteri_IDsi,siparisler[x].urun_Isim,siparisler[x].urun_Fiyat,siparisler[x].urun_Adet,siparisler[x].urun_ID1,siparisler[x].urun_Toplam)!=8) {
	printf("Dosya okuma hatasý! Satýr formatý bozuk olabilir.\n");
    break;
	}
	
	x++;
	if(x>=50) break;	
	}
	fclose(siparisokuma);
}   */
	
	do {

while (1) {
	menu();
   // printf("Bir sayi giriniz: ");
    sonucc = scanf("%d",&secim);
   
    if (sonucc != 1) {  // scanf 1 döndürmezse, geçerli int deðil demek
 //    inputTemizle();
	    printf("\nGecersiz sayi girdiniz! Lutfen sadece tam sayi giriniz.\n");
        while(getchar() != '\n');   // buffer temizleme, yanlýþ giriþten kurtulmak için
    } else {
        break;  // geçerli sayý okundu, çýk döngüden
    }
}
// sayi artýk integer ve güvenli
// printf("Girdiginiz sayi: %d\n",secim);

	/*	menu();
	
	scanf("%d",&secim); */
	
	switch (secim) {
		
		case 1:
			if (i<5) {
			printf("\nLutfen musterinin bilgilerini giriniz.\n\n");
			printf("\nMusteri adini giriniz.\n");
			scanf("%19s",musteriler[i].ad);
			while (getchar() != '\n');
			printf("\nMusteri Soyadini giriniz.\n");
			scanf("%19s",musteriler[i].soyad);
			while (getchar() != '\n');
			
			int tempID; // Geçici bir ID deðiþkeni kullanýyoruz
                    do {
                        printf("\nMusteriye ait 4 haneli ID olusturunuz.\n");
                        tempID = getSafeIntegerInput(); // Güvenli tamsayý giriþi

                        if (tempID < 1000 || tempID > 9999) {
                            printf("\nLutfen 4 haneli bir sayi giriniz. (Orn: 1234)\n");
                        } else if (!isCustomerIDUnique(musteriler, i, tempID)) {
                            // isCustomerIDUnique fonksiyonunu çaðýrarak benzersizliði kontrol ediyoruz
                            printf("\nBu ID kullanilamaz. Lutfen farkli bir ID seciniz.\n");
                        } else {
                            musteriler[i].musteriID = tempID; // Geçerli ve benzersiz ID'yi atýyoruz
                            break; // Döngüden çýkýyoruz
                        }
                    } while (1); // Geçerli bir ID alana kadar döngü devam eder
					
						
						
				
			FILE *filep = fopen("Musteriler.txt","a");
			
			fprintf(filep, "%-20s %-20s %04d\n", musteriler[i].ad, musteriler[i].soyad, musteriler[i].musteriID);

			fclose(filep);
			printf("\nMusteri basariyla kaydedildi.\n");
			i++;
		}
		else {
			printf("\nMusteri kontenjani dolu.\n");
		}
				                   break;	 
			case 2:
				if (j<10) {

				printf("\nLutfen eklemek istediginiz urunun bilgilerini giriniz.\n\n");
			printf("\nUrunun adini giriniz.\n");
			scanf("%19s",urunler[j].urunadi);
			while (getchar() != '\n');
			printf("\nUrunun fiyatini giriniz.\n");
			urunler[j].urunfiyati = getSafeIntegerInput();
			while (urunler[j].urunfiyati <= 0) {
            printf("\nUrun fiyati sifirdan buyuk olmalidir. Lutfen tekrar giriniz.\n");
            urunler[j].urunfiyati = getSafeIntegerInput();
        }
			printf("\nUrun adedini giriniz.\n");
			urunler[j].urunadedi = getSafeIntegerInput();
			while (urunler[j].urunadedi <= 0) {
            printf("\nUrun adedi sifirdan buyuk olmalidir. Lutfen tekrar giriniz.\n");
            urunler[j].urunadedi = getSafeIntegerInput();
        }
			printf("\nLutfen 4 haneli urun ID giriniz.\n");
			do {	
		don1:
			urunler[j].urunID = getSafeIntegerInput();
			
		if (urunler[j].urunID < 1000 || urunler[j].urunID > 9999) {
            printf("\nLutfen 4 haneli bir sayi giriniz.\n");
        }
}while (urunler[j].urunID < 1000 || urunler[j].urunID > 9999);
			
			for (urun_kontrol_ID=0;urun_kontrol_ID<j;urun_kontrol_ID++){			
			if (urunler[j].urunID == urunler[urun_kontrol_ID].urunID){
				printf("\nID kullanilamaz.Lutfen farkli bir ID seciniz.\n");
				goto don1;
			}
		}
			
			FILE *filep1 = fopen("Urunler.txt","a");
			
			fprintf(filep1,"%-20s %-010d %-010d %-010d\n",urunler[j].urunadi,urunler[j].urunfiyati,urunler[j].urunadedi,urunler[j].urunID);
			fclose(filep1);
			
			printf("\nUrun basariyla kaydedildi.\n");
			j++;
		}
		else {
			printf("\nStok dolu.\n");
		}
					               break;
				 	case 3: 
				 	      
				 	      stok_goster(urunler,j);
						printf("\n");
						   urun_sil(&j,urunler);
						   
						   break;         
			     	case 4:
					
					siparismodulu(urunp,j,musteriler,toplam_tutar,siparisler,xp,sipID_tut,&mevcut_siparis_sayisi);
					
						           break;
					case 5:
						
						stok_goster(urunler,j);
						printf("\n");
						
							       break;
					case 6:
						stok_goster(urunler,j);
						printf("\n");
						stok_guncelle(urunler,&j);
						
						break;
					case 7:
							
							siparis_gecmisi(siparisp,xp,sipID_tut);
							
								   break;
					case 8:
								printf("----------------------------------------\n\n\n");
					 			musteri_listele(musteriler,&i);
					 			printf("\n\nMusteriler Listelenmistir.\n");
					 			
					               break;
					case 9:
					 
		       				printf("----------------------------------------\n\n\n");
					 			musteri_listele(musteriler,&i);
					 	//		printf("\n\nMusteriler Listelenmistir.Silmek istediginiz musterinin ID'sini giriniz.\n");	
								  		
										  musteri_sil(&i,musteriler);	
							    	break;	
					case 10:
					
					printf("\nBasariyla Cikis Yapildi.\n");
							    	break;		   			
					default:
						
		break;
	}
} while (secim != 10);
	
	
	return 0;
}
