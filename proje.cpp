#include <iostream>
#include <fstream>
#include <cstring>
#include <locale.h>

using namespace std;


const int MAX_EKSTRA_SAYISI = 5;
const int MAX_PIZZA_ADI_UZUNLUGU = 20;
const int MAX_AD_UZUNLUGU = 30;
const int MAX_ADRES_UZUNLUGU = 50;
const int MAX_TELEFON_UZUNLUGU = 15;
const int MAX_BOYUT_UZUNLUGU = 10;
const int MAX_ICECEK_UZUNLUGU = 15;

struct Musteri {
    char ad[MAX_AD_UZUNLUGU];
    char adres[MAX_ADRES_UZUNLUGU];
    char telefon[MAX_TELEFON_UZUNLUGU];
};

struct Siparis {
    char pizzaTuru[MAX_PIZZA_ADI_UZUNLUGU];
    char boyut[MAX_BOYUT_UZUNLUGU];
    char icecek[MAX_ICECEK_UZUNLUGU];
    double tutar;
};

void siparisKaydet(const Musteri &musteri, const Siparis &siparis) {
    ofstream dosya("siparisler.txt", ios::app);
    if (dosya.is_open()) {
        dosya << "----------Musteri Bilgileri:-----------\n";
        dosya << "Ad: " << musteri.ad << "\n";
        dosya << "Adres: " << musteri.adres << "\n";
        dosya << "Telefon: " << musteri.telefon << "\n\n";

        dosya << "          Siparis Detaylari:			\n";
        dosya << "Pizza Türü: " << siparis.pizzaTuru << "\n";
        dosya << "Boyut: " << siparis.boyut << "\n";

        dosya << "Içecek: " << siparis.icecek << "\n";
        dosya << "Toplam Tutar: $" << siparis.tutar << "\n";
        dosya << "-----------------------------------------"<< endl;
        dosya << endl;

   

        dosya.close();
        cout << "Siparis dosyaya kaydedildi.\n\n";
    } else {
        cout << "Dosya acilamadi!\n";
    }
}

double siparisTutariHesapla(const Siparis &siparis) {
    double tutar = 10.0;

    if (strcmp(siparis.boyut, "Buyuk") == 0 || strcmp(siparis.boyut, "buyuk") == 0) {
        tutar += 5.0;
    } else if (strcmp(siparis.boyut, "Orta") == 0 || strcmp(siparis.boyut, "orta") == 0) {
        tutar += 3.0;
    } else {
        tutar += 2.0;
    }

    if (strcmp(siparis.icecek, "Kola") == 0 || strcmp(siparis.icecek, "kola") == 0) {
        tutar += 10.0;
    } else if (strcmp(siparis.icecek, "Su") == 0 || strcmp(siparis.icecek, "su" ) == 0) {
        tutar += 5.0;
    } else {
        tutar += 8.0;
    }
    
    if (strcmp(siparis.pizzaTuru, "S") == 0 || strcmp(siparis.pizzaTuru, "s") == 0) {
        tutar += 10.0;
    } else if (strcmp(siparis.pizzaTuru, "K") == 0 || strcmp(siparis.pizzaTuru, "k") == 0) {
        tutar += 5.0;
    } else {
        tutar += 8.0;
    }

    return tutar;
}


void siparisAl(Musteri &musteri, Siparis &siparis) {
    cout << "Ad Soyad: ";
    cin.getline(musteri.ad, MAX_AD_UZUNLUGU);
    cout << "Adres: ";
    cin.getline(musteri.adres, MAX_ADRES_UZUNLUGU);
    cout << "Telefon: ";
    cin.getline(musteri.telefon, MAX_TELEFON_UZUNLUGU);

    cout << "Pizza Türü(Sucuklu= 'S'/ Mantarlý = 'M'/ Karýþýk = 'K'): ";
    cin.getline(siparis.pizzaTuru, MAX_PIZZA_ADI_UZUNLUGU);
    cout << "Boyut (Kucuk/Orta/Buyuk): ";
    cin.getline(siparis.boyut, MAX_BOYUT_UZUNLUGU);

    cout << "Icecek (Su/Kola/Soda): ";
    cin.getline(siparis.icecek, MAX_ICECEK_UZUNLUGU);

    siparis.tutar = siparisTutariHesapla(siparis);
    cout << "Toplam Tutar:"<<siparis.tutar <<  "TL" << endl;
}


void siparisGoster() {
    ifstream dosyaOku("siparisler.txt");
    if (!dosyaOku.is_open()) {
        cout << "Dosya acilamadi!\n";
        return;
    }

    string satir;
    while (getline(dosyaOku, satir)) {
        cout << satir << endl;
    }
    cout<<endl;
    dosyaOku.close();
}

void tumSiparisleriSil() {
    char onay;
    cout << "Tum siparisleri silmek istediginize emin misiniz? (E/H): ";
    cin >> onay;
    cin.ignore();

    if (onay == 'E' || onay == 'e') {
        // Dosyayý temizleme
        ofstream temizleDosya("siparisler.txt", ios::trunc);
        temizleDosya.close();

        cout << "Tum siparisler basariyla silindi!\n\n\n";
    } else {
        cout << "Islem iptal edildi, siparisler silinmedi.\n";
    }
}


void siparisSil() {
    ifstream dosyaOku("siparisler.txt");
    if (!dosyaOku.is_open()) {
        cout << "Dosya acilamadi!\n";
        return;
    }

    cout << "Silinecek Siparisin Indisini Giriniz: ";
    int indis;
    cin >> indis;
    cin.ignore();

    string satir;
    int satirSayac = 0;
    ofstream geciciDosya("gecici_siparisler.txt");

    while (getline(dosyaOku, satir)) {
        if (satirSayac / 8 != indis) {
            geciciDosya << satir << endl;
        }
        satirSayac++;
    }

    dosyaOku.close();
    geciciDosya.close();

    if (remove("siparisler.txt") != 0) {
        cout << "Dosya silinemedi!\n";
        return;
    }

    if (rename("gecici_siparisler.txt", "siparisler.txt") != 0) {
        cout << "Dosya ismi degistirilemedi!\n";
        return;
    }

    cout << "Siparis basariyla silindi.\n";
}



int main() {
	system("cls");
	setlocale(LC_ALL, "Turkish");
    
    Musteri musteri;
    Siparis siparis;
    int secim;
    bool devam = true;
    while(devam) {
    cout << "----Pizzaci Otomasyonu------" << endl;	
    cout << "| 1. Yeni Siparis          |" << endl;
    cout << "| 2. Siparisleri Goruntule |" << endl;
    cout << "| 3. Siparis Sil           |" << endl;
    cout << "| 4. Tum Siparisleri Sil   |" << endl;
    cout << "| 5. Otomasyondan Cik      |" << endl;
    cout << "----------------------------" << endl;
    cout << "Seciminiz: "; cin >> secim;
    cin.ignore();

    switch (secim) {
        case 1: {
        	system("cls");
            siparisAl(musteri, siparis);
            siparisKaydet(musteri, siparis);        	
			break;
		}
        case 2: {
        	system("cls");
            siparisGoster();        	
			break;
		}
        case 3: {
        	system("cls");
            siparisGoster();
            siparisSil();        	
			break;
		}
        case 4 : {
			system("cls");
			tumSiparisleriSil();
			break;
		} 
		case 5 : {
        	system("cls");
        	cout<< "Otomasyondan Çýktýnýz."<<endl;
        	devam = false;
			break;
		}
        default:
            cout << "Gecersiz secim!\n";
    }
}
    return 0;
}


