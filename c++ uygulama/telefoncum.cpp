#include<iostream>
#include<string>
#include<windows.h>
#include<locale.h>
#include<fstream>
#include<conio.h>
#include<ctime>
using namespace std;
int sec,i,tel_iter,stokadet,silkontrol,satiskontrol,durum,satis,fiyat,sirala;
string telmarka,telmodel,telfiyat,tel_id="0",datetime;
string siltel_id;
char Date[17];

void tel_stokekle();
void tel_stoksil();
void tel_guncelle();
void tel_satis();
void stokgoster();
void gotoxy(int x,int y)
{
COORD pos={x,y};
SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
}

void Anamenu(){
system("color B");
gotoxy(40,3);
cout<<"TELEFON SATIÞ PROGRAMI"<<endl;
for (int y=3;y<20;y++)
{
gotoxy(25,y);
cout<<"|";
gotoxy(74,y);
cout<<"|";
}
for(int x=25;x<=74;x++)
{
gotoxy(x,20);
cout<<"=";
}
}
void menu(){
	system("CLS");
 Anamenu();
 string Item[6];
Item[0]="[1] Yeni Telefon Ekle";
Item[1]="[2] Telefonlarý Listele";
Item[2]="[3] Telefonlarý Güncelle";
Item[3]="[4] Telefon Markasý Sil";
Item[4]="[5] Satýþ Yap";
Item[5]="[6] Çýkýþ";

for (int menu=0;menu<=5;menu++)
{
gotoxy(35,6+menu*2);
cout<<Item[menu];
}
gotoxy(15,22);
cout<<"Ýþlem seçiniz:[ ]";
gotoxy(30,22);
sec=getch()-48;
switch(sec){
		case 1:
		system("cls"); 
		tel_stokekle();
		break;
		case 2:
			system("cls"); 
			stokgoster();
			cout<<endl<<"Menuye dönmek için bir tuþa basýnýz";
			getch();
			menu();
		break;
		case 3:
		system("cls");
       tel_guncelle();
		break;
		case 4:
		system("cls");
		tel_stoksil();
		break;
		case 5:
		system("cls");
		tel_satis();
		break;
		case 6:
		exit(1);
		break;
	
		
}
}
void dateprint(string s1,string s2){
	
	time_t date = time(NULL);
	struct tm *date_info = localtime(&date);
	strftime(Date, sizeof(Date), "%d-%m-%Y %H:%M", date_info);
	datetime=Date;
	ofstream writefile("satislog.txt",ios::out|ios::app);
 	writefile<<"\n"<<tel_id<<" id'li"<<" markasý "<<telmarka<<" olan "<<telmodel<<" modeli "<<s1<<" fiyatýnda "<<datetime<<" Tarihinde "<<s2<<" adet satilmistir";
  	writefile.close();
}

void sonidbul(){
	ifstream dosyaoku("dosya.txt",ios::app | ios::out); 
	while (!dosyaoku.eof()){
	dosyaoku>>tel_id>>telmarka>>telmodel>>telfiyat>>stokadet;
	}
	tel_iter=stoi(tel_id);
}

void tel_stoksil(){
	stokgoster();
	string tel_id;
	cout<<endl<<"Silmek istediðiniz id:";
	cin>>siltel_id;
	cin.ignore();
	ifstream dosyaoku("dosya.txt",ios::app | ios::out); 
	ofstream dosya("yeni.txt",ios::app | ios::out);
    while (!dosyaoku.eof()){
    dosyaoku>>tel_id>>telmarka>>telmodel>>telfiyat>>stokadet;
    if(tel_id==siltel_id){
    silkontrol=1;
    cout<<tel_id<<" "<<telmarka<<" "<<telmodel<<" "<<telfiyat<<" "<<stokadet<<"-Silindi!";
    }
	else{
    	dosya<<"\n"<<tel_id<<" "<<telmarka<<" "<<telmodel<<" "<<telfiyat<<" "<<stokadet;
	}
	}
if(silkontrol==0)
cout<<"Bu id ye ait telefon bulunmamaktadir";
dosya.close();
dosyaoku.close();
remove("dosya.txt");
rename("yeni.txt","dosya.txt");
cout<<endl<<"Menuye dönmek için bir tuþa basýnýz ";
getch();
menu();
}

void tuslama(){
	durum=getch();
    	switch(durum){
    		case '1':
    		cout<<endl<<"Yeni Fiyat:";
    	    cin>>telfiyat;
    	    cout<<endl<<"Fiyat Güncellendi";
			break;
			case '2':
			cout<<endl<<"Yeni Stok Adeti:";
    	    cin>>stokadet;
    	    cout<<endl<<"Stok Güncellendi";
			break;
			default:
			cout<<endl<<"Yanlýþ seçim 1 veya 2 seçin"<<endl;
			tuslama();
			break;
    	}
}

void tel_guncelle(){
	stokgoster();
	int count=0;
	string tel_kontrol;
	ifstream dosyaoku("dosya.txt");
	ofstream dosya("yeni.txt");
	cout<<endl<<"Güncellemek istediðiniz id:";
	cin>>tel_kontrol;
	cin.ignore();
    while(!dosyaoku.eof())
    {
    dosyaoku>>tel_id>>telmarka>>telmodel>>telfiyat>>stokadet;
    if(tel_kontrol==tel_id)
    {
    	cout<<endl<<"Güncellemek istediðiniz kategoriyi seçin";
    	cout<<endl<<"Fiyat-1"<<"   "<<"Stok Adet-2"<<endl;
    	tuslama();
    	
    count=1;
	}
      dosya<<"\n"<<tel_id<<" "<<telmarka<<" "<<telmodel<<" "<<telfiyat<<" "<<stokadet;
	}
	if(count==0)
	cout<<"Bu sayýyla eþleþen id yoktur";
	dosya.close();
	dosyaoku.close();
	remove("dosya.txt");
	rename("yeni.txt","dosya.txt");
	cout<<endl<<"Menuye donmek icin bir tuþa basýnýz ";
	getch();
	menu();
}

void tel_stokekle(){
	    cout<<endl<<"Telefon Markasý:";
	    cin>>telmarka;
	    cout<<"Telefon Modeli:";
	    cin>>telmodel;
	    cout<<"Telefon Fiyatý:";
	    cin>>telfiyat;
	    cout<<"Telefon Stok Adet:";
	    cin>>stokadet;
	    cin.ignore();
        ofstream dosya("dosya.txt",ios::app| ios::out);
        dosya<<"\n"<<to_string(tel_iter+1)<<" "<<telmarka<<" "<<telmodel<<" "<<telfiyat<<" "<<stokadet;
        dosya.close();
        ++tel_iter;
        cout<<"Menuye donmek icin bir tuþa basýnýz ";
    	getch();
		menu();
}

void tel_satis(){
	stokgoster();
	string tel_satis;
	ifstream dosyaoku("dosya.txt");
	ofstream dosya("yeni.txt");
	cout<<endl<<"Satmak istediðiniz telefon id:";
	cin>>tel_satis;
	cin.ignore();
    while(!dosyaoku.eof())
    {
    dosyaoku>>tel_id>>telmarka>>telmodel>>telfiyat>>stokadet;
    if(tel_satis==tel_id)
    {
    	satiskontrol=1;
    	cout<<"Kaç adet satýlacak:";
    	cin>>satis;
    	
    	if(stokadet-satis<0) cout<<"Yeterli stok yoktur";
    	
		else{
	    stokadet-=satis;
	    fiyat=stoi(telfiyat)*satis;
    	gotoxy(0,tel_iter+5);	cout<<"Id";
    	gotoxy(0,tel_iter+6);	cout<<tel_id;
    	
    	gotoxy(15,tel_iter+5);	cout<<"Marka";
    	gotoxy(15,tel_iter+6);	cout<<telmarka;
    	
    	gotoxy(30,tel_iter+5);	cout<<"Model";
    	gotoxy(30,tel_iter+6);	cout<<telmodel;
    	
    	gotoxy(45,tel_iter+5);	cout<<"Toplam Borç";
    	gotoxy(45,tel_iter+6);	cout<<fiyat;
    	
    	gotoxy(60,tel_iter+5);	cout<<"Adet";
    	gotoxy(60,tel_iter+6);	cout<<satis<<"    Adet Satýldý";
    	dateprint(to_string(fiyat),to_string(satis));
    }
    }
    	dosya<<"\n"<<tel_id<<" "<<telmarka<<" "<<telmodel<<" "<<telfiyat<<" "<<stokadet;
}
if(satiskontrol==0)
cout<<"Bu sayýyla eþleþen id yoktur";
dosya.close();
dosyaoku.close();
remove("dosya.txt");
rename("yeni.txt","dosya.txt");
cout<<endl<<endl<<endl<<"Menuye dönmek için bir tuþa basýnýz ";
getch();
menu();
}

void stokgoster(){
	sirala=2;
	ifstream dosyaoku("dosya.txt");
	gotoxy(0,1);	cout<<"Id";
	gotoxy(15,1);	cout<<"Marka";
	gotoxy(30,1);	cout<<"Model";
	gotoxy(45,1);	cout<<"Tane Fiyat";
	gotoxy(60,1);	cout<<"Adet";
	while(!dosyaoku.eof())
    {
    dosyaoku>>tel_id>>telmarka>>telmodel>>telfiyat>>stokadet;
    
    	gotoxy(0,sirala);	cout<<tel_id;
    	
    	gotoxy(15,sirala);	cout<<telmarka;
    	
    	gotoxy(30,sirala);	cout<<telmodel;
    	
    	gotoxy(45,sirala);	cout<<telfiyat;
    	
    	gotoxy(60,sirala);	cout<<stokadet;
    	cout<<endl;
    	sirala++;
	}
	dosyaoku.close();
}

int main(){
	sonidbul();
	setlocale(LC_ALL,"Turkish");
	menu();

}
