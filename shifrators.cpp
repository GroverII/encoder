#include <iostream>
#include <cstdlib>
#include <fstream>
#include<time.h>
using namespace std;


void ReturnEnc(char mas[], int n){
	//open file
	ofstream file1;
	file1.open("Encr_text.txt");
	if(!file1){cout<<"Nav!"; system("pause>nul"); exit(1);}
	for(int i=0; i<n; i++) file1<<mas[i];
	file1.close();
}

void one_two_three_Enc(char mas[], int s1, int s2, int s3, int n){
	int b=0;
	bool isNULL;
	for(int i=0; i<n; i++){
		isNULL=false;
		b=(int)mas[i];
		if(s1<94){
			//cout<<endl<<i+1<<") s1 - "<<s1<<"\nmas[i]+s1 - "<<(int)mas[i]+s1;
			//check if symbol not out of range
			if(b>31 && b<127)
				mas[i]=mas[i]+s1;
			else {
				mas[i]=NULL;
				isNULL=true;
			}
			s1++;
		}
		//if needed drum scrolling
		else {
			//cout<<endl<<i+1<<") s1 - "<<s1<<"\nmas[i]+s1 - "<<(int)mas[i]+s1;
			if(b>31 && b<127)
				mas[i]=mas[i]+s1;
			else {
				mas[i]=NULL;
				isNULL=true;
			}
			s1=0;
			if(s2<94) s2++;
			//if needed drum scrolling
			else{
				s2=0;
				if(s3<94) s3++;
				//if needed drum scrolling
				else s3=0;
			}
		}
		if(s2<94){
			//if((int)mas[i]-s2<0) cout<<endl<<"s2 - "<<s2<<"\nmas[i]-s2+255 - "<<(int)mas[i]-s2+256;
			//else cout<<endl<<"s2 - "<<s2<<"\nmas[i]-s2 - "<<(int)mas[i]-s2;
			//check out of range
			if(mas[i]-s2<0) mas[i]=mas[i]-s2+256;
			else mas[i]=mas[i]-s2;
			s2++;
		}
		//if needed drum scrolling
		else {
			//if((int)mas[i]-s2<0) cout<<endl<<"s2 - "<<s2<<"\nmas[i]-s2+255 - "<<(int)mas[i]-s2+256;
			//else cout<<endl<<"s2 - "<<s2<<"\nmas[i]-s2 - "<<(int)mas[i]-s2;
			//check out of range
			if(mas[i]-s2<0) mas[i]=mas[i]-s2+256;
			else mas[i]=mas[i]-s2;
			s2=0;
			if(s3<94) s3++;
			//if needed drum scrolling
			else {
				s1=0;
				s3=0;
			}
		}
		if(s3<94){
			//if((int)mas[i]-s3>255)cout<<endl<<"s3 - "<<s3<<"\nmas[i]+s3 - "<<(int)mas[i]+s3-256<<endl;
			//else cout<<endl<<"s3 - "<<s3<<"\nmas[i]+s3 - "<<(int)mas[i]+s3<<endl;
			//check out of range
			if(mas[i]+s3>255) mas[i]=mas[i]-256+s3;
			else mas[i]=mas[i]+s3;	
			s3++;
		}
		//if needed drum scrolling
		else {
			//if((int)mas[i]-s3>255)cout<<endl<<"s3 - "<<s3<<"\nmas[i]+s3 - "<<(int)mas[i]+s3-256<<endl;
			//else cout<<endl<<"s3 - "<<s3<<"\nmas[i]+s3 - "<<(int)mas[i]+s3<<endl;
			//check out of range
			if(mas[i]+s3>255) mas[i]=mas[i]-256+s3;
			else mas[i]=mas[i]+s3;
			s1=0;
			s2=0;
			s3=0;
		}
	}
	cout<<endl<<s1<<" - s1"<<endl<<s2<<" - s2"<<endl<<s3<<" - s3"<<endl;
	for(int i=0; i<n; i++)cout<<mas[i];
	//write code into new file
	ReturnEnc( mas, n);
}

void StartOfEnc(char mas[], int n){
	//make key(current date)
	ofstream file1;
	file1.open("Key.txt");
	if(!file1){cout<<"Nav!"; system("pause>nul"); exit(1);}
	time_t now = time(0);
   	tm *ltm = localtime(&now);
	file1<<ltm->tm_mday<<"/"<<1+ltm->tm_mon<<"/";
	if((1900+ltm->tm_year)%100==0)file1<<1;
	else file1<<(1900+ltm->tm_year)%100;
	file1.close();
	//needed key=day*month*2previous numbers of year(if 00 -> *1)
	int s=ltm->tm_mday*(1+ltm->tm_mon);
	if((1900+ltm->tm_year)%100!=0)s=s*((1900+ltm->tm_year)%100);
	cout<<endl<<s<<endl;
	int s1=0, s2=0, s3=0;
	//get keys
	while(s>0){
		if(s1<94) {
			s1++;
		}
		else if(s1==94 && s2<94){
			s1=0;
			s2++;
		} 
		else if(s1==94 && s2==94 && s3<94){
			s1=0;
			s2=0;
			s3++;
		}
		else{
			s1=0;
			s2=0;
			s3=0;
		}
		s--;
	}
	cout<<s1<<" - s1"<<endl<<s2<<" - s2"<<endl<<s3<<" - s3"<<endl;
	//start of encription	
	one_two_three_Enc(mas, s1, s2, s3, n);
}

void Encr(){
	ifstream file1;
	char mas[1000];
	int n;
	file1.open("Text.txt");
	if(!file1){cout<<"Nav!"; system("pause>nul"); exit(1);}
	//get inf and size of inf
	while(!file1.eof()){
	file1.getline(mas,1000,'\n');
	n=file1.gcount();
	//start enctiption
	StartOfEnc(mas, n);
	}
	file1.close();
}

char* StartDecr(char* mas, int* sn, int n){
	int s=sn[0]*sn[1]*sn[2];
	int s1=0, s2=0, s3=0, b=0;
	//get start position
	while(s>0){
		if(s1<94) {
			s1++;
		}
		else if(s1==94 && s2<94){
			s1=0;
			s2++;
		} 
		else if(s1==94 && s2==94 && s3<94){
			s1=0;
			s2=0;
			s3++;
		}
		else{
			s1=0;
			s2=0;
			s3=0;
		}
		s--;
	}
	cout<<endl<<"s1 - "<<s1<<endl<<"s2 - "<<s2<<endl<<"s3 - "<<s3<<endl;
	//start decription
	for(int i=0; i<n; i++){
		if(s1<94){
			//check for out of range needless
			mas[i]=mas[i]-s1;
			s1++;
		}	
		else {
			//check for out of range needless
			mas[i]=mas[i]-s1;
			s1=0;
			if(s2<94) s2++;
			else {
				s2=0;
				if(s3<94) s3++;
				else s3=0;
			}
		}
		if(s2<94){
			//check if out of range
			if(mas[i]+s2>255) mas[i]=mas[i]-256+s2;
			else mas[i]=mas[i]+s2;
			s2++;
		}
		else {
			//check if out of range
			if(mas[i]+s2>255) mas[i]=mas[i]-256+s2;
			else mas[i]=mas[i]+s2;
			s2=0;
			if(s3<94) s3++;
			else {
				s1=0;
				s3=0;
			}
				
		}
		if(s3<94){
			//check if out of range
			if(mas[i]-s3<0) mas[i]=mas[i]+256-s3;
			else mas[i]=mas[i]-s3;	
			s3++;
		}
		else {
			//check if out of range
			if(mas[i]-s3<0) mas[i]=mas[i]+256-s3;
			else mas[i]=mas[i]-s3;
			s1=0;
			s2=0;
			s3=0;
		}
	}
	cout<<endl<<"s1 - "<<s1<<endl<<"s2 - "<<s2<<endl<<"s3 - "<<s3<<endl;
	return mas;
}

void ReturnText(char* mas, int* sn, int n){
	//decription
	mas=StartDecr(mas, sn, n);
	ofstream file1;
	file1.open("NewText.txt");
	if(!file1){cout<<"Nav!"; system("pause>nul"); exit(1);}
	//add decripted information to new file
	for(int i=0; i<n; i++) file1<<mas[i];
	for(int i=0; i<n; i++)cout<<mas[i];
	file1.close();
}

void ReturnKey(char s[], int m, char mas[], int n){
	int i=0, sn[3];
	string apv;
	//day get
	while(s[i]!='/' && s[i]>='0' && s[i]<='9'){
			apv+=s[i];
			i++;
	}
	i++;
	if(!apv.empty())sn[0]=stoi(apv);
	else sn[0]=1;
	apv="";
	//month get
	while(s[i]!='/' && s[i]>='0' && s[i]<='9'){
			apv+=s[i];
			i++;
	}
	i++;
	if(!apv.empty())sn[1]=stoi(apv);
	else sn[1]=1;
	;
	apv="";
	//year get
	while(s[i]>='0' && s[i]<='9' && i<m){
			apv+=s[i];
			i++;
	}
	if(!apv.empty())sn[2]=stoi(apv);
	else sn[2]=1;
	//if year ends of 00
	if(s[2]==0) s[2]=1;
	apv="";
	//start decription
	ReturnText(mas, sn, n);
}

void GetKey(char* mas, int n){
	ifstream file1;
	file1.open("Key.txt");
	if(!file1){cout<<"Nav!"; system("pause>nul"); exit(1);}
	//there will be only 9 symbols
	char s[9];
	int m;
	while(!file1.eof()){
		file1.getline(s,9, '\n');
		m=file1.gcount();
		//transform Key to needed format
		ReturnKey(s, m, mas, n);
	}
}

void Decr(){
	//open and get info
	ifstream file1;
	char mas[1000];
	int n;
	file1.open("Encr_text.txt");
	if(!file1){cout<<"Nav!"; system("pause>nul"); exit(1);}
	//get inf and size of inf
	while(!file1.eof()){
	file1.getline(mas,1000, '\n');
	n=file1.gcount();
	//get key-start
	GetKey(mas, n);
	}
	file1.close();
}


int main(){
bool menu=true;
int i;
while(menu){
	system("pause>nul");
	system("cls");
	cout<<"MENU: ";
	cout<<"\n_________________________________\n\t1.\tEncryption\t|\n\t2.\tDecryption\t|\n\t3.\tExit\t\t|\n________________________________|\n";
	cin>>i;
	switch(i)
	{
		case(1):
			//encript text
			Encr();
			break;
		case(2):
			//decript code
			Decr();
			break;
		case(3):
			//exit
			menu=false;
		default:break;
	}
}
return 0;
}