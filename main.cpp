
#include <windows.h>
#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <cstdlib>
#include <ctime>
#include <string.h>
#include<iomanip>
#include <fstream>
#include <Math.h>
using namespace std;
//node
struct SINHVIENDK{
	// khong trung
	char MASV[12];
	float DIEM;
	SINHVIENDK *next = NULL;
};
typedef struct{
	int soluong = 0;
	SINHVIENDK *pFirst=NULL;
	SINHVIENDK *pLast=NULL;
} DSDANGKY;

typedef struct{
	char MAMH[10];
	char TENMH[1000];
	// so tin chi li thuyet
	float STCLT=0;
	// so tin chi thuc hanh
	float STCTH=0;
} MONHOC;

typedef struct{
  int soluong=0;
  MONHOC *monhoc[300];
} DSMONHOC;

typedef struct {
	// khong trung
	// data
	int MALOPTC;
	char MAMH[10];
	char NIENKHOA[50];
	unsigned int HOCKY;
	unsigned int NHOM;
	unsigned int MAX,MIN;
	// danh sach dang ky
	DSDANGKY *dssv=NULL;
}LOP;
// node
struct SINHVIEN{
	// data
	char MASV[12];
	char HO[1000];
	char TEN[1000];
	char PHAI[1000];
	char MALOP[15];
	char SDT[10];
	int NAM;
	// con tro den phan tu tiep theo
	struct SINHVIEN *next = NULL;
};
// quan ly dslk don
struct DSSINHVIEN{
	int soLuong = 0;
	// con tro node dau tien
	SINHVIEN *pFirst = NULL;
	// con tro node cuoi cung
	SINHVIEN *pLast = NULL;
};

// cay nhi phan tim kiem
struct dslop{
	// data
	LOP lop;
	struct dslop *left = NULL;
	struct dslop *right = NULL;
} ;
typedef struct dslop *DSLOP;

//method

DSLOP search(DSLOP,int);
void InHoa(char ch[]);
// file
void LuuLTC(DSLOP);
void LuuSV(DSSINHVIEN listSV);
void LuuMH(DSMONHOC &listMH);
//xuat
void XuatMH(DSMONHOC listMH);
void XuatLTC(DSLOP);
void XuatSV(DSSINHVIEN listSV);
void XuatLTCTheoDK(DSLOP root,DSMONHOC listMH, char nienKhoa[],int hocKy,int &check);
void XuatSVTheoDK(DSSINHVIEN listSV, char maLop[]);
void XuatSVDK(LOP lop,DSSINHVIEN listSV, char tenMon[], char nienKhoa[], int hocKy, char nhom[]);

// graphics method
void swap(MONHOC *&temp1,MONHOC *&temp2){
	MONHOC *temp3;
	temp3 = temp1;
	temp1 = temp2;
	temp2 = temp3;	
}
void gotoxy(int x, int y)
{
    static HANDLE h = NULL;  
    if(!h)
        h = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD c = { x, y };  
    SetConsoleCursorPosition(h,c);
}
void HinhVuong(int x1,int y1, int x2, int y2){
	for(int i=x1;i<=x2; i++){
		gotoxy(i,y1);
		cout << "-";
	}
	for(int i=y1;i<=y2; i++){
		gotoxy(x1,i);
		cout << "-";
	}
		for(int i=x1;i<=x2; i++){
		gotoxy(i,y2);
		cout << "-";
	}
	for(int i=y1;i<=y2; i++){
		gotoxy(x2,i);
		cout << "-";
	}	
}
void xoa(char *a, int q)
{
            int n = strlen(a), i;
            for (i = q; i <= n; i++)
            {
                        a[i] = a[i + 1];
            }
            n--;
}
void XoaKhoangTrangThua(char *ch){
	    int i, n=strlen(ch);
        for (i = 0; i < n; i++)
        {
            if (ch[0] == 32)
            	{
                    xoa(ch, 0);
                    n--;
                }
            if (ch[n-1] == 32)
                {
                	xoa(ch, n-1);
              		n--;
                }
            if (ch[i] == 32 && ch[i + 1] == 32)
            {
           			xoa(ch, i);
           			i--;
            		n--;
            }
        }
}
int confirm(){
	char ch[2];
	fflush(stdin);
	cout << "Ban Co Chac Chan (Y/N): ";
	gets(ch);
	InHoa(ch);
	
	if(strcmp(ch,"Y") == 0) return 1;
	return 0;
}
// CHECKS METHOD
int KiemTraKiTu(char text[]){
	// chu 65-90
	// so 47-58 
	// "ABCD"
	for(int i=0; i<strlen(text); i++){
		if( ((int) text[i] < 65 || (int)text[i] > 90) ) {
			
			if (((int)text[i] > 47 && (int)text[i] < 58)) continue;
			
			if((int)text[i] == 32) continue;
			
			return 0; 
		}
	}
	return 1;
}
// kiem tra xem mltc da ton tai ??
DSLOP KiemTraMLTC(DSLOP lop, int mltc){
	if(search(lop,mltc) == NULL ) return NULL;
	return search(lop,mltc);
}
int KiemTraTrungLTC(DSLOP root, LOP *temp){
	if(root != NULL)    
	   {
	      KiemTraTrungLTC(root->left,temp);
	      KiemTraTrungLTC(root->right,temp);
	      if (root->lop.HOCKY == temp->HOCKY && strcmp(root->lop.MAMH,temp->MAMH) == 0 && strcmp(root->lop.NIENKHOA,temp->NIENKHOA) ==0 && 
		  root->lop.NHOM == temp->NHOM) return 0; 
	   }
	   return 1;
}
int KiemTraKhoangTrang(char ch[]){
	if (strlen(ch) == 0) return 0;
	
	for (int i=0; i< strlen(ch); i++){
		// ma ascii cua khoan trang = 32
		if( (int) ch[i] == 32) return 0;
	}
	
	return 1;
}
int KiemTraSo(char so[]){
	for (int i=0; i< strlen(so); i++){
		if( (int) so[i] == 46 ) continue;
		if (so[i] < 48 or so[i]>57) return 0;
	}
	return 1;
}
void KiemTraLop(DSLOP root, LOP *&lop, char mmh[], char nienKhoa[], int hocKy, int nhom){
	//NLR
	if(root != NULL)    
	   {	
	   	  if (root->lop.HOCKY == hocKy && strcmp(root->lop.MAMH,mmh) == 0 && strcmp(root->lop.NIENKHOA,nienKhoa) ==0 && 
		  	root->lop.NHOM == nhom) {
				lop = &root->lop;
				return;
		  } 
	      KiemTraLop(root->left,lop,mmh,nienKhoa,hocKy,nhom);
	      KiemTraLop(root->right,lop,mmh,nienKhoa,hocKy,nhom);
	      
	   }
}
MONHOC* KiemTraMH(DSMONHOC &listMH, char maMH[]){
	for (int i=0; i< listMH.soluong; i++){
		if( strcmp(listMH.monhoc[i]->MAMH, maMH)  == 0) {
			return listMH.monhoc[i];
		}
	}
	return NULL;
}
SINHVIEN *KiemTraSV(DSSINHVIEN listSV,char maSV[]){
	if(listSV.pFirst == NULL) return NULL;	
	for(SINHVIEN *i = listSV.pFirst; i!=NULL; i=i->next){
		if(strcmp(i->MASV,maSV) == 0) return i;
	}
	return NULL;
}
int KiemTraDaDangKyLTC(DSDANGKY *listDK, char msv[]){
	
	for(SINHVIENDK *k = listDK->pFirst; k!=NULL; k=k->next){
		if(strcmp(k->MASV,msv) == 0) return 0;
	}
	return 1;
	

}
void KiemTraSVDaDangKyLTC(DSLOP root, int &check, char msv[]){
	// NLR
	if(root!=NULL){
		if(check == 0) return;
		for(SINHVIENDK *k = root->lop.dssv->pFirst; k!=NULL; k=k->next){
				if(strcmp(k->MASV,msv) == 0) {
					check = 0;
					return;
				}
		}
		KiemTraSVDaDangKyLTC(root->left,check,msv);
		KiemTraSVDaDangKyLTC(root->right,check,msv);
	}
}
// cac ham can thiet
void InHoa(char ch[]){
	for (int i=0; i< strlen(ch); i++){
		ch[i] = toupper(ch[i]);
	}
}
char  *toChar(int number)
    {
        int n = log10(number) + 1;
        int i;
      	char *numberArray = new char;
        for ( i = 0; i < n; ++i, number /= 10 )
        {
            numberArray[i] = number % 10;
        }
        return numberArray;
}

// tao danh sach lop TC la cay nhi phan AVL

DSLOP rp;
void  remove_case_3 (DSLOP  &r )
{
  if (r->left != NULL)
     remove_case_3 (r->left);
   //den day r la nut cuc trai cua cay con ben phai co nut goc la rp}
    else 
	{
   	 	//Chep noi dung cua r sang rp ";
  		rp->lop =r->lop;	//  de lat nua free(rp)
  		rp = r;           	
  		r = rp->right;
	  }
}
void  xoaLTC(DSLOP &p,int mltc)
{
	if (p == NULL)  cout << "Khong tim thay";
	else
	  if (mltc < p->lop.MALOPTC)  {
	  	xoaLTC (p->left, mltc);
	  }
	  else if (mltc > p->lop.MALOPTC){
	  		xoaLTC ( p->right, mltc);
	  }
		  
	       else   	
	       { 
			  rp = p;
			
              if (rp->right == NULL)  p = rp->left; 
			
			  else 	if (rp->left == NULL) p = rp->right;  // p là nut co cay con ben phai
			  else remove_case_3 (rp->right);
		 delete rp;
	       }
}


  

  
void Create_AVLTree(DSLOP &p,LOP lop)  
{  
    if(p == NULL)    // nút p hi?n t?i s? là nút lá
   {
     p = new dslop;
     p->lop = lop;
     p->left = NULL;     p->right = NULL;  
   }
   else
    if(lop.MALOPTC < p->lop.MALOPTC )
      Create_AVLTree(p->left, lop);
    else if(lop.MALOPTC > p->lop.MALOPTC ) Create_AVLTree(p->right, lop);

}  

DSLOP search(DSLOP root, int mltc)
{
   DSLOP p = NULL;
   p = root;
   while(p != NULL && mltc!=p->lop.MALOPTC)
     if(mltc < p->lop.MALOPTC)
         p = p->left;
      else
         p = p->right;
	return(p); 
}
void Posorder(DSLOP root)
{
	
   if(root != NULL)    
	   {
	      Posorder(root->left);
	      Posorder(root->right);
		  cout << right << setw(9) << root->lop.MALOPTC << "|";
		  cout << right << setw(14) << root->lop.MAMH << "|";
	      cout << right << setw(15) << root->lop.HOCKY << "|";
		  cout << right << setw(16) << root->lop.NIENKHOA << "|";
		  cout << right << setw(11) << root->lop.NHOM << "|";
		  cout << right << setw(13) << root->lop.MIN << "|";
		  cout << right << setw(12) << root->lop.MAX << "|" << endl;
	   }
}
void DuyetTheoDK(DSLOP root,DSMONHOC listMH, char nienKhoa[],int hocKy,int &check)
{
   if(root != NULL)    
	   {
		  DuyetTheoDK(root->left, listMH,nienKhoa,hocKy,check);
	      DuyetTheoDK(root->right, listMH,nienKhoa,hocKy,check);
	      if(strcmp(root->lop.NIENKHOA,nienKhoa) == 0 && root->lop.HOCKY == hocKy){
	      	  check = 1;
	      	  cout << right << setw(15) << root->lop.MALOPTC << "|";
			  cout << right << setw(15) << KiemTraMH(listMH, root->lop.MAMH)->MAMH << "|";
			  cout << right << setw(40) << KiemTraMH(listMH, root->lop.MAMH)->TENMH << "|";
		      cout << right << setw(20) << KiemTraMH(listMH, root->lop.MAMH)->STCLT << "|";
			  cout << right << setw(20) << KiemTraMH(listMH, root->lop.MAMH)->STCTH << "|" << endl;		  
		  }
	   }
}
// tu dong sinh ma lop tin chi
int SinhMLTC(DSLOP root){
	// ham sinh ngay nhien
	// sinh tu 0 - randmax, dinh nghia san trong thu vien <cstdlib>
	srand(time(NULL));
	int number = rand();
	// kiem tra xem MLTC co ton tai chua
	while( (search(root,number) != NULL) || number==0) {
			number = rand();
	}
	return number;
}
// a
// mo lop tin chi (LTC)
void ThemLTC(DSLOP &root,DSMONHOC listMH, char nienKhoa[], int hocKy){
	while(1){
	char min[1000],max[1000],nhom[1000];
	
	system("cls");
	XuatMH(listMH);
	LOP tempLop; 
	tempLop.dssv = new DSDANGKY;
	tempLop.HOCKY = hocKy;
	strcpy(tempLop.NIENKHOA,nienKhoa);
	// tao MLTC: tu dong sinh
	 tempLop.MALOPTC = SinhMLTC(root);
	// nhap MMH
	mmh:
	cout << "Nhap MMH: ";
	fflush(stdin);
	gets(tempLop.MAMH);
	InHoa(tempLop.MAMH);
	if(strlen(tempLop.MAMH) == 0) return;
	if(KiemTraKhoangTrang(tempLop.MAMH) == 0 || KiemTraKiTu(tempLop.MAMH) == 0){
		cout << "*Khong duoc bo trong hoac chua khoang trang, chi chua chu va so!!" << endl;
		goto mmh;
	}
	if (KiemTraMH(listMH,tempLop.MAMH) == NULL){
		cout << "*Ma mon hoc khong ton tai!!" << endl;
		goto mmh;
	}
	//nhom
	nhom:
	cout << "Nhap nhom: ";
	fflush(stdin);
	cin >> nhom;
	if(KiemTraSo(nhom) == 0){
		cout << "*Phai la so!!!" << endl;
		goto nhom;
	}
	tempLop.NHOM = atoi(nhom);
	// kiem tra trung lich hoc:
	if (KiemTraTrungLTC(root,&tempLop) == 0){
		cout << "*Lich hoc da ton tai!!" << endl;
		goto mmh;
	}
	// so SV min
	min:
	cout << "Nhap So Luong SV toi thieu (MIN): ";
	fflush(stdin);
	gets(min);
	if(KiemTraSo(min) == 0){
		cout << "Khong phai la so! Vui long nhap lai.." << endl;
		goto min;
	}
	tempLop.MIN = atoi(min);
	// so SV max
	max:
	cout << "Nhap So Luong SV toi da (MAX): ";
	fflush(stdin);
	gets(max);
	if(KiemTraSo(max) == 0){
		cout << "Khong phai la so! Vui long nhap lai.." << endl;
		goto max;
	}
	tempLop.MAX = atoi(max);
	Create_AVLTree(root,tempLop);
	LuuLTC(root);
}
}
// xoa lop tin chi
void XoaLTC(DSLOP &root,int mltc){
	if (KiemTraMLTC(root,mltc) == 0 ){
		cout << "Ma lop tin chi khong ton tai!!!";
		return;
	}
	xoaLTC(root,mltc);
	cout << "DA XOA THANH CONG 1 LTC!!";
}
void SuaLTC(DSLOP &root,DSMONHOC listMH){
	LOP *tempLop = new LOP;
	char mltc[1000];
	mltc:
	cout << "Nhap Ma Lop Tin Chi: ";
	fflush(stdin);
	gets(mltc);
	if (strlen(mltc) == 0) return;
	if(KiemTraMLTC(root,atoi(mltc)) == NULL){
		cout << "*Ma lop tin chi khong ton tai!!!" << endl;
		goto mltc;
	}
	
	char min[1000],max[1000],nhom[1000];
	DSLOP temp = search(root,atoi(mltc));
	// tao mot bien tam de lay gia tri
	*tempLop = temp->lop;
	 mmh:
	// nhap MMH
	cout << "Nhap MMH: ";
	fflush(stdin);
	gets(tempLop->MAMH);
	InHoa(tempLop->MAMH);
	// giu gia tri cu
	if (strlen(tempLop->MAMH) == 0) strcpy(tempLop->MAMH,temp->lop.MAMH);
	if(KiemTraKhoangTrang(tempLop->MAMH) == 0 || KiemTraKiTu(tempLop->MAMH) == 0){
		cout << "Khong duoc bo trong hoac chua khoang trang, chi chua chu va so!!" << endl;
		goto mmh;
	}
	if (KiemTraMH(listMH,tempLop->MAMH) == NULL){
		cout << "*Khong ton tai!" << endl;
		goto mmh;
	}
	
	//nhom
	nhom:
	cout << "Nhap Nhom: ";
	fflush(stdin);
	gets(nhom);
	if (strlen(nhom) == 0){
		tempLop->NHOM = temp->lop.NHOM;
	} else {
		if(KiemTraSo(nhom) == 0){
			cout << "*Phai la so!!!" << endl;
			goto nhom;
		}
		tempLop->NHOM = atoi(nhom);
		// kiem tra xem co co bi trung lich khong
		if (KiemTraTrungLTC(root,tempLop) == 0){
			cout << "*Lich bi trung!";
			goto mltc;
		}
	}
	// so SV min
	min:
	cout << "Nhap So Luong SV toi thieu (MIN): ";
	fflush(stdin);
	gets(min);
	if(strlen(min) == 0){
		tempLop->MIN = temp->lop.MIN;
	} else {
		if(KiemTraSo(min) == 0){
			cout << "*Khong phai la so! Vui long nhap lai.." << endl;
			goto min;
		}
		tempLop->MIN = atoi(min);
	}
	// so SV max
	max:
	cout << "Nhap So Luong SV toi da (MAX): ";
	fflush(stdin);
	gets(max);
	if (strlen(max) == 0){
		tempLop->MAX = temp->lop.MAX;
	} else {
	if(KiemTraSo(max) == 0){
		cout << "*Khong phai la so! Vui long nhap lai.." << endl;
		goto max;
		}
		tempLop->MAX = atoi(max);
	}
	// cap nhat bang cach xoa xong them lai
//	KiemTraMLTC(root,tempLop.MALOPTC)->lop = tempLop;
	temp->lop = *tempLop;
}
// b
void InDanhSachSVCuaLTC(DSLOP root, DSMONHOC listMH, DSSINHVIEN listSV){
	char mmh[10], nienKhoa[50];
	char hocKy[10],nhom[10],diem[10];
	LOP *tempLop = NULL;
	int i=0;

	cout <<"\t\t\tMENU NHAP DIEM" << endl;
	
	cout << "Nien Khoa: ";
	fflush(stdin);
	gets(nienKhoa);
	InHoa(nienKhoa);
	if(strlen(nienKhoa) == 0) return;
	
	cout << "Hoc Ky: ";
	fflush(stdin);
	gets(hocKy);
	InHoa(hocKy);
	if(strlen(hocKy) == 0) return;
	
	cout << "Nhom: ";
	fflush(stdin);
	gets(nhom);
	InHoa(nhom);
	if(strlen(nhom) == 0) return;
	
	cout << "Ma Mon Hoc: ";
	fflush(stdin);
	gets(mmh);
	InHoa(mmh);
	if(strlen(mmh) == 0) return;	
	// tim kiem trong danh sach lop tc lay ra danh sach sv trung khop voi dieu kien tren
	KiemTraLop(root,tempLop,mmh,nienKhoa,atoi(hocKy),atoi(nhom));
	if(tempLop == NULL ) {
		cout << "ERROR: Du Lieu Khong Ton tai...";
		Sleep(1000);
		return;
	}
	
	XuatSVDK(*tempLop,listSV, KiemTraMH(listMH,tempLop->MAMH)->TENMH, nienKhoa, atoi(hocKy), nhom);
	
	cout << "Nhan (ENTER) de thoat...";
	fflush(stdin);
	gets(mmh);	
}
//c
void ThemNodeSV(DSSINHVIEN &listSV,SINHVIEN *sinhVien){
	SINHVIEN *temp;
	SINHVIEN *i;
	
	// chuan hoa
	XoaKhoangTrangThua(sinhVien->HO);
	XoaKhoangTrangThua(sinhVien->TEN);
	XoaKhoangTrangThua(sinhVien->MALOP);
	XoaKhoangTrangThua(sinhVien->MASV);
	XoaKhoangTrangThua(sinhVien->SDT);
	// neu dsach rong
	if (listSV.pFirst == NULL){
		listSV.soLuong++;
		listSV.pFirst = sinhVien;
		listSV.pLast = sinhVien;
		return;
	} 
	// tim vi tri can them  &&
	string ch1="";
	string ch2="";
	for(i = listSV.pFirst; i!=NULL ; temp=i, i=i->next){
		// ch1: sv can them
		ch1 = sinhVien->MALOP;
		ch1 = ch1 + sinhVien->MASV;
		//ch2: sv mang	
		ch2 = i->MALOP;
		ch2 = ch2 + i->MASV;
		if(strcmp(ch1.c_str(),ch2.c_str()) < 0) break;
	}
	// them dau
	if( i == listSV.pFirst){
		sinhVien->next = listSV.pFirst;
		listSV.pFirst = sinhVien;
		listSV.soLuong++;
		return;
	} else
	// them cuoi
	if (i == NULL){
		listSV.pLast->next = sinhVien;
		listSV.pLast = sinhVien;
		listSV.soLuong++;
		return;
	}
	listSV.soLuong++;
	temp->next = sinhVien;
	sinhVien->next = i;
	LuuSV(listSV);
}
void XoaNodeSV(DSSINHVIEN &listSV,char maSV[]){
	SINHVIEN *t;
	// kiem tra sinh vien da dang ky mon hoc

	if(strcmp(listSV.pFirst->MASV,maSV) == 0){
		SINHVIEN *temp = listSV.pFirst;
		listSV.pFirst = listSV.pFirst->next;
		delete temp;
	} else
	for (SINHVIEN *i = listSV.pFirst; i!= NULL;t=i, i=i->next){
		if ( strcmp(i->MASV,maSV) == 0){
			t->next = i->next;
			if (i == listSV.pLast) listSV.pLast = t;
			delete i;
			break;
		}
	}
	
	listSV.soLuong--;
	LuuSV(listSV);
}
void SuaNodeSV(DSSINHVIEN &listSV, SINHVIEN *sv,char maSV[]){
	XoaNodeSV(listSV,maSV);
	ThemNodeSV(listSV,sv);
	LuuSV(listSV);
}
void ThemSV(DSSINHVIEN &listSV,char maLop[]){
	while(1){
		// bien sinh vien can them
		SINHVIEN *sinhVien = new SINHVIEN;
		// gan maLop vao ma lop cua sinhVien
		strcpy(sinhVien->MALOP,maLop);
		
		system("cls");
		XuatSVTheoDK(listSV,sinhVien->MALOP); 
		// nhap msv can them
		masv: 
		cout << "Ma SV: ";
		fflush(stdin);
		gets(sinhVien->MASV);
		InHoa(sinhVien->MASV);
		
		if ( strlen(sinhVien->MASV) == 0) return;
		if (KiemTraKiTu(sinhVien->MASV) == 0){
			cout << "ERROR: Khong duoc chua ki tu dac biet!" << endl;
			goto masv;
		}
		
		if(KiemTraKhoangTrang(sinhVien->MASV) == 0 || strlen(sinhVien->MASV) > 12){
			cout << "ERROR: Khong duoc chua khoang trang va do dai khong qua 12 ki tu!" << endl;
			goto masv;
		}
		if( KiemTraSV(listSV,sinhVien->MASV) != NULL){
			cout << "ERROR: MSV da ton tai!" << endl;
			goto masv;
		}
		
		// ho
		ho:
		cout << "Nhap Ho: ";
		fflush(stdin);
		gets(sinhVien->HO);
		InHoa(sinhVien->HO);
		if ( strlen(sinhVien->HO) == 0) return;
		if (KiemTraKiTu(sinhVien->HO) == 0){
			cout << "ERROR: Khong duoc chua ki tu dac biet!" << endl;
			goto ho;
		}
		
		// ten
		ten:
		cout << "Nhap Ten: ";
		fflush(stdin);
		gets(sinhVien->TEN); 
		InHoa(sinhVien->TEN);
		if ( strlen(sinhVien->TEN) == 0) return;
		if (KiemTraKiTu(sinhVien->TEN) == 0){
			cout << "ERROR: Khong duoc chua ki tu dac biet!" << endl;
			goto ten;
		}
		// phai
		phai:
		cout << "Phai (NAM/NU):";
		gets(sinhVien->PHAI);
		InHoa(sinhVien->PHAI);
		if ( strlen(sinhVien->PHAI) == 0) return;
		if ( strcmp(sinhVien->PHAI,"NAM") !=0 && strcmp(sinhVien->PHAI,"NU") !=0){
			cout << "ERROR: Sai cu phap!!!" << endl;
			goto phai;
		}
		//sdt
		sdt:
		cout <<"SDT: ";
		fflush(stdin);
		gets(sinhVien->SDT);
		if (strlen(sinhVien->SDT) == 0) return;
		if(KiemTraSo(sinhVien->SDT) == 0){
			cout << "ERROR: SDT phai la so!!" << endl;
			goto sdt;
		}	
		if (KiemTraKhoangTrang(sinhVien->SDT) == 0 || strlen(sinhVien->SDT) != 10 || atoi(sinhVien->SDT) == 0){
			cout << "ERROR: Sai cu phap" << endl;
			goto sdt;
		}
		//nam nhap hoc
		char number[5];
		number:
		cout << "Nam nhap hoc: ";
		gets(number);
		if ( strlen(number) == 0) return;
		if(KiemTraSo(number) == 0 || atoi(number) < 2014 || KiemTraKhoangTrang(number) == 0 || strlen(number) > 4){
			cout << "ERROR: Nam khong dung, moi nhap lai: " << endl;
			goto number;
		} else sinhVien->NAM = atoi(number);
		
		ThemNodeSV(listSV,sinhVien);
		
	}

}
void SuaSV(DSSINHVIEN &listSV){
	SINHVIEN *sinhVien = new SINHVIEN;
	// lop
	lop:
	cout << "Nhap Ma Lop: ";
	fflush(stdin);
	gets(sinhVien->MALOP);
	InHoa(sinhVien->MALOP);
	if (KiemTraKiTu(sinhVien->MALOP) == 0){
		cout << "ERROR: Khong duoc chua ki tu dac biet!" << endl;
		goto lop;
	}
	
	if(KiemTraKhoangTrang(sinhVien->MALOP) == 0 || strlen(sinhVien->MALOP) > 15 || strlen(sinhVien->MALOP) == 0){
		cout << "ERROR: Khong duoc chua khoang trang va do dai khong qua 15 ki tu!" << endl;
		goto lop;
	}
	
	while(1){
	system("cls");
	XuatSVTheoDK(listSV,sinhVien->MALOP);
	// msv can sua
	maSV_test:
	char maSV[12];
	cout << "MSV: ";
	fflush(stdin);
	gets(maSV);
	InHoa(maSV);
	if(strlen(maSV) == 0) return;
	if (KiemTraSV(listSV,maSV) == NULL){
			cout << "ERROR: Ma sinh vien khong ton tai";
			goto maSV_test;
	}
		system("cls");
		XuatSVTheoDK(listSV,sinhVien->MALOP);
		cout << "===Sua Thong Tin===" << endl;
		maSV:
		cout << "MSV: " << maSV << endl;
		strcpy(sinhVien->MASV,maSV);

		// ho
		ho:
		cout << "Nhap Ho: ";
		fflush(stdin);
		gets(sinhVien->HO);
		InHoa(sinhVien->HO);
		if(strlen(sinhVien->HO) == 0) return;
		if (KiemTraKiTu(sinhVien->HO) == 0){
			cout << "ERROR: Khong duoc chua ki tu dac biet!" << endl;
			goto ho;
		}
		// ten
		ten:
		cout << "Nhap Ten: ";
		fflush(stdin);
		gets(sinhVien->TEN);
		InHoa(sinhVien->TEN);
		if(strlen(sinhVien->TEN) == 0 ) return;
		if (KiemTraKiTu(sinhVien->TEN) == 0){
			cout << "ERROR: Khong duoc chua ki tu dac biet!" << endl;
			goto ten;
		}
		if( strlen(sinhVien->TEN) == 0){
			cout << "*Khong duoc bo trong" << endl;
			goto ten;
		}
		// phai
		phai:
		cout << "Phai (NAM/NU):";
		fflush(stdin);
		gets(sinhVien->PHAI);
		InHoa(sinhVien->PHAI);
	
		if(strlen(sinhVien->PHAI) == 0 ) return;
		if ( strcmp(sinhVien->PHAI,"NAM") !=0 && strcmp(sinhVien->PHAI,"NU") !=0){
			cout << "ERROR: Sai cu phap!!!" << endl;
			goto phai;
		}
		//sdt
		sdt:
		cout <<"SDT: ";
		gets(sinhVien->SDT);
		if(strlen(sinhVien->SDT) == 0 ) return;
		if(KiemTraSo(sinhVien->SDT) == 0){
			cout << "*SDT phai la so!!" << endl;
			goto sdt;
		}
		if (KiemTraKhoangTrang(sinhVien->SDT) == 0){
			cout << "SDT khong duoc chua khoang trang!" << endl;
			goto sdt;
		}
		//nam nhap hoc
		char number[5];
		number:
		cout << "Nam nhap hoc: ";
		gets(number);
		if(strlen(number) == 0 ) return;
		if(KiemTraSo(number) == 0 || atoi(number) < 2014 || KiemTraKhoangTrang(number) == 0 || strlen(number) > 4){
			cout << "ERROR: Nam khong dung, moi nhap lai: " << endl;
			goto number;
		}
		sinhVien->NAM = atoi(number);	
		SuaNodeSV(listSV,sinhVien,maSV);
}
}
// e
void ThemMH(DSMONHOC &listMH, MONHOC *monHoc){ 
	listMH.monhoc[listMH.soluong] = new MONHOC();
	XoaKhoangTrangThua(monHoc->TENMH);
	XoaKhoangTrangThua(monHoc->MAMH);
	listMH.monhoc[listMH.soluong] = monHoc;
	listMH.soluong++;
} 
void XoaMH(DSMONHOC &listMH, char maMH[]){   
	for(int i=0; i < listMH.soluong; i++){ 		
		if ( strcmp(listMH.monhoc[i]->MAMH, maMH) == 0){
			delete listMH.monhoc[i];
		
			for(i; i< listMH.soluong;i++){
				listMH.monhoc[i] = listMH.monhoc[i+1];
			}	
			listMH.soluong--;
			LuuMH(listMH);
			return;
		}
	}
}
void SuaMH(DSMONHOC &listMH, MONHOC *monHoc){
	for(int i=0; i< listMH.soluong; i++){
		if (strcmp(listMH.monhoc[i]->MAMH,monHoc->MAMH) == 0){
			listMH.monhoc[i] = monHoc;
			LuuMH(listMH);
			return;
		}
	}
}

// list menu
void MenuLTC(DSLOP &root,DSMONHOC &listMH){
	while(1){
		start:
		char chon[10];
		system("cls");
		XuatLTC(root);
		cout << "Cap Nhat Danh Sach Lop Tin Chi: " << endl;
		cout << "1. Them Lop Tin Chi" << endl;
		cout << "2. Xoa Lop Tin Chi" << endl;
		cout << "3. Sua Lop Tin Chi" << endl;
		cout << "LuaChon (1/2/3): ";
		fflush(stdin);
		gets(chon);	
		
		switch(atoi(chon)){
			system("cls");
			XuatLTC(root);
			case 1:{		
				case_1:
				char nienkhoa[50],hocKy[50];
				cout << "--THEM LOP TIN CHI--" << endl;
				cout << "Nien Khoa: ";
				fflush(stdin);
				gets(nienkhoa);
				InHoa(nienkhoa);
				if(strlen(nienkhoa) == 0) break;
				if(KiemTraKhoangTrang(nienkhoa) == 0) {
					cout << "*Khong chua khoang trang hoac bo trong!!" << endl;
					goto case_1;
				}
				cout << "Hoc Ky: ";
				fflush(stdin);
				gets(hocKy);
				if(strlen(hocKy)== 0) break;
				ThemLTC(root,listMH,nienkhoa,atoi(hocKy));
				break;
			}
			case 2:{
				int mltc;
				cout << "--XOA LOP TIN CHI--" << endl;
				cout << "Nhap Ma Lop Tin Chi Can Xoa: ";
				cin >> mltc;
				if(mltc == 0) break;
				char ch[2];
	
				if  (confirm() == 0) return; 
				xoaLTC(root,mltc);
				Sleep(1000);
				LuuLTC(root);
				break;
			}
			case 3:{
				cout << "--SUA LOP TIN CHI--" << endl;
				SuaLTC(root,listMH);
				LuuLTC(root);
				break;
			}
			case 0:{	
				return;
			}
	
		}	
	}
}
//g
void DangKyTC(DSDANGKY *dsdk,char maSV[],float diem){
	SINHVIENDK *data = new SINHVIENDK;
	strcpy(data->MASV,maSV);
	data->DIEM = diem;
	SINHVIENDK *i = dsdk->pFirst;
	SINHVIENDK *t;
	dsdk->soluong++;
	
	if (dsdk->pFirst == NULL){
		dsdk->pFirst = data;
		dsdk->pLast = data;
		return;
	}
	
	// tu chay tim t va i
	for(i ; i!=NULL && strcmp(i->MASV,data->MASV) < 0;t=i, i=i->next);
	
	if (i == NULL){
		dsdk->pLast->next = data;
		dsdk->pLast = data;
	} else if (i == dsdk->pFirst){
		data->next = dsdk->pFirst;
		dsdk->pFirst = data;
	}
	 else {
		data->next = t->next;
		t->next = data;
	}
}

// save & load
void LuuMH(DSMONHOC &listMH){
	ofstream xuatFile;
	xuatFile.open("MONHOC.txt", ios::out);
	xuatFile << listMH.soluong << endl;
	for(int i = 0; i < listMH.soluong; i++){
		xuatFile << listMH.monhoc[i]->MAMH << endl;
		xuatFile << listMH.monhoc[i]->TENMH << endl;
		xuatFile << listMH.monhoc[i]->STCTH << endl;
		xuatFile << listMH.monhoc[i]->STCLT << endl;
	}
	xuatFile.close();
}
void DocMH(DSMONHOC &listMH){
	ifstream docFile;
	docFile.open("MONHOC.txt", ios::in);

	docFile >> listMH.soluong;
	string tempString; 
	for(int i = 0; i < listMH.soluong; i++){
		listMH.monhoc[i] = new MONHOC;
		docFile >> listMH.monhoc[i]->MAMH;
		getline(docFile, tempString);
		getline(docFile, tempString);
		strcpy(listMH.monhoc[i]->TENMH,tempString.c_str());
		docFile >>  listMH.monhoc[i]->STCTH;
		docFile >>  listMH.monhoc[i]->STCLT;
	}
	docFile.close();
}

void LuuSV(DSSINHVIEN listSV){
	ofstream xuatFile;
	xuatFile.open("SINHVIEN.txt", ios::out);
	xuatFile << listSV.soLuong << endl;
	for(SINHVIEN *i = listSV.pFirst; i != NULL; i=i->next){
		xuatFile << i->MALOP << endl;
		xuatFile << i->MASV << endl;
		xuatFile << i->HO << endl;
		xuatFile << i->TEN << endl;
		xuatFile << i->SDT << endl;
		xuatFile << i->PHAI << endl;
		xuatFile << i->NAM << endl;
	}
	xuatFile.close();
}
void DocSV(DSSINHVIEN &listSV){
	ifstream docFile;
	docFile.open("SINHVIEN.txt", ios::out);
	int solg = 0;
	docFile >> solg;
	string temp;
	for(int j=1; j <= solg; j++){
		SINHVIEN *i = new SINHVIEN;
		docFile >>  i->MALOP;
		docFile >>  i->MASV;
		getline(docFile>>ws,temp);
		strcpy(i->HO,temp.c_str());
		getline(docFile>>ws,temp);
		strcpy(i->TEN,temp.c_str());
		docFile >>  i->SDT;
		docFile >>  i->PHAI;
		docFile >>  i->NAM;		
		ThemNodeSV(listSV,i);
	}
	docFile.close();
}
void LuuSVDK(LOP lop){
	ofstream luu;
	char fileName[1000] ;
	// int -> char
	sprintf(fileName,"%d", lop.MALOPTC);
	strcat(fileName,".txt");
	luu.open(fileName, ios::out);
	luu << lop.dssv->soluong << endl;
	for(SINHVIENDK *i = lop.dssv->pFirst; i!= NULL; i=i->next){
		luu << i->MASV << endl;
		luu << i->DIEM << endl;
	}
	luu.close();
}
void DocSVDK(LOP lop,DSDANGKY *dsdk){
	ifstream doc;
	char fileName[1000];
	fileName,sprintf(fileName,"%d", lop.MALOPTC);
	strcat(fileName,".txt");
	doc.open(fileName, ios::in);
	char maSV[12];
	float diem;
	int n;
	doc >> n;
	if(doc.fail()) return;
	for(int i=1; i<=n; i++){
		SINHVIENDK temp;
		doc >> temp.MASV;
		doc >> temp.DIEM;
		DangKyTC(dsdk,temp.MASV,temp.DIEM);
	}
	doc.close();
}

void tempLuuLTC(ofstream &luuFile, DSLOP root){	 
	 if(root != NULL)    
	   {
	      tempLuuLTC(luuFile,root->left);
	      tempLuuLTC(luuFile,root->right);
	      luuFile << root->lop.MALOPTC << endl;
	 	  luuFile << root->lop.MAMH << endl;
	 	  luuFile << root->lop.NHOM << endl;
	 	  luuFile << root->lop.HOCKY << endl;
	 	  luuFile << root->lop.NIENKHOA << endl;
	   	  luuFile << root->lop.MAX << endl;
	 	  luuFile << root->lop.MIN << endl;
		//LuuSVDK(root->lop.dssv,root->lop);
	   } 
}
void LuuLTC(DSLOP root){
	ofstream luuFile;
	remove("LOP.txt");
	luuFile.open("LOP.txt",ios::out |ios::app);
	tempLuuLTC(luuFile,root);
	luuFile.close();
}

void DocLTC(DSLOP &root){
	LOP *tempLOP = new LOP;
	ifstream docFile;
	docFile.open("LOP.txt",ios::in);
	do {
		 docFile >> tempLOP->MALOPTC;
	 	 docFile >>  tempLOP->MAMH ;
	 	 docFile >>  tempLOP->NHOM;
	 	 docFile >>  tempLOP->HOCKY;
	 	 docFile >>  tempLOP->NIENKHOA ;
	   	 docFile >>  tempLOP->MAX ;
	     docFile >>  tempLOP->MIN;
	     tempLOP->dssv = new DSDANGKY;
	      Create_AVLTree(root,*tempLOP);
	     DocSVDK(*tempLOP,tempLOP->dssv);
	}  while(!docFile.eof());
	docFile.close();
}
void MenuMH(DSMONHOC &listMH){
	while(1){
		start:
		system("cls");
		XuatMH(listMH);
		char chon[10];
		cout << "Cap Nhat Danh Sach Mon Hoc: " << endl;
		cout << "1. Them Mon Hoc" << endl;
		cout << "2. Xoa Mon Hoc" << endl;
		cout << "3. Sua Mon Hoc" << endl;
		cout << "LuaChon (1/2/3): ";
		fflush(stdin);
		gets(chon);	
		
		switch(atoi(chon)){
			case 1:{
				system("cls");
				XuatMH(listMH);
				mmh_case1:
				// bien
				MONHOC *tempMH = new MONHOC;
				cout<< "--THEM MON HOC--" << endl;
				cout << "Ma Mon Hoc: ";
				fflush(stdin);
				gets(tempMH->MAMH);
				InHoa(tempMH->MAMH);
				
				if(strlen(tempMH->MAMH) == 0) break;
					
				if( KiemTraKhoangTrang(tempMH->MAMH) == 0 ){
					cout << "ERROR: Khong Chua Khong Trang!!" << endl;
					goto mmh_case1;
				}
				
				if( KiemTraKiTu(tempMH->MAMH) == 0 || strlen(tempMH->MAMH) > 10 ){
					cout << "ERROR: Sai Cu Phap! Moi Nhap Lai" << endl;
					goto mmh_case1;
				}
				
				if(KiemTraMH(listMH,tempMH->MAMH) !=NULL ){
					cout << "ERROR: Ma Mon Hoc Bi Trung" << endl;
					goto mmh_case1;	
				}
				
				mon:
				cout << "Ten Mon: ";
				fflush(stdin);
				gets(tempMH->TENMH);
				InHoa(tempMH->TENMH);
			
				if(strlen(tempMH->TENMH) == 0) break;
				if( KiemTraKiTu(tempMH->TENMH) == 0 ){
					cout << "ERROR: Sai Cu Phap! Moi Nhap Lai" << endl;
					goto mon;
				}
				char stclt[5],stcth[5];
				stclt_case1:
				cout << "So Tin Chi Li Thuyet: ";
				gets(stclt);
				
				if(strlen(stclt) == 0) break;
				
				if(KiemTraSo(stclt) == 0) {
					cout << "ERROR: Sai Cu Phap!!";
					goto stclt_case1;
				}
				tempMH->STCLT = atoi(stclt);
				
				stcth_case1:
				cout << "So Tin Chi Thuc Hanh: ";
				gets(stcth);
				
				if(strlen(stcth) == 0) break;
				
				if(KiemTraSo(stcth) == 0) {
					cout << "ERROR: Sai Cu Phap!!";
					goto stcth_case1;
				}
				tempMH->STCTH = atoi(stcth);
				
				ThemMH(listMH,tempMH);
				LuuMH(listMH);
				break;
			}
			case 2:{
				system("cls");
				XuatMH(listMH);
				mmh_case2:
				char maMH[10];
				cout<< "--XOA MON HOC--" << endl;
				cout << "Ma Mon Hoc: ";
				fflush(stdin);
				gets(maMH);
				InHoa(maMH);
				
				if(strlen(maMH) == 0) break;
				
				if( KiemTraKiTu(maMH) == 0  || strlen(maMH) > 10){
					cout << "ERROR: Sai cu phap! Moi nhap lai" << endl;
					goto mmh_case2;	
				}
				if (KiemTraMH(listMH,maMH) == NULL){
					cout << "ERROR: Ma mon hoc khong ton tai!" << endl; 
					Sleep(1000);
					break;
				}
				char ch[2];
				if  (confirm() == 0) return;
				XoaMH(listMH,maMH);
				cout << "Xoa Thanh Cong !!!";
				Sleep(1000);
				break;
			}
			case 3:{
				system("cls");
				XuatMH(listMH);
				char maMH[50],tenMH[300], stclt[50],stcth[50];
				//object hoc can sua
				MONHOC *monHoc = new MONHOC;
				mmh_case3:
				cout<< "--Sua MON HOC--" << endl;
				cout << "Ma Mon Hoc: ";
				fflush(stdin);
				gets(maMH);
				InHoa(maMH);
				if(strlen(maMH) == 0) break;
				
				if( KiemTraMH(listMH,maMH) == NULL ){
					cout << "ERROR: Ma Mon Hoc Khong Ton Tai!!!";
					break;	
				}
				// lay mon hoc can sua ///
				*monHoc = *KiemTraMH(listMH,maMH);
				
				cout << "Thong Tin Sua" << endl;
				mon_case3:
				cout << "Ten Mon: ";
				fflush(stdin);
				gets(tenMH);
				InHoa(tenMH);
				if(strlen(tenMH) == 0) {
					break;
				} else {
					if( KiemTraKiTu(tenMH) == 0){
						cout << "ERROR: Sai Cu Phap! Moi Nhap Lai" << endl;
						goto mon_case3;
					}
					strcpy(monHoc->TENMH,tenMH);
				}
				stclt: 
				cout << "So Tin Chi Li Thuyet: ";
				fflush(stdin);
				gets(stclt);
				if(strlen(stclt) == 0) {
					break;
				} else{
					if(KiemTraSo(stclt) == 0){
						cout <<"ERROR: Sai Cu Phap!Nhap lai...";
						goto stclt;
					}
					monHoc->STCLT = atoi(stclt);
				}
				stcth:
				cout << "So Tin Chi Thuc Hanh: ";
				fflush(stdin);
				gets(stcth);		
				if(strlen(stcth) == 0) {
					break;
				} else{
					if(KiemTraSo(stcth) == 0){
						cout <<"ERROR: Sai Cu Phap!Nhap lai...";
						goto stcth;
					}
					monHoc->STCTH = atoi(stcth);
				}
				SuaMH(listMH,monHoc);
				break;
			}
			case 0:{
				return;
			}
		}
	}
} 
//c
void MenuSV(DSSINHVIEN &listSV, DSLOP &root){
	start:
	// lap lai lien tuc cac cau lenh trong {}
	while(1){
		char chon[10];
		// cau lenh xoa man hinh
		system("cls");
		// cau lenh xuat danh sach
		XuatSV(listSV);
		// menu
		cout << "Cap Nhat Danh Sach Sinh Vien: " << endl;
		cout << "1. Them Sinh Vien" << endl;
		cout << "2. Xoa Sinh Vien" << endl;
		cout << "3. Sua Sinh Vien" << endl;
		cout << "LuaChon (1/2/3): ";
		// ng dung nhap lua chon
		fflush(stdin);
		gets(chon);	
		// atoi doi "chon" ra so de so sanh voi case
		switch(atoi(chon)){
			case 1:{
				// lop
				lop:
				// yeu cau ng dung nhap ma lop
				char maLop[15];
				cout << "Nhap Ma Lop: ";
				fflush(stdin);
				gets(maLop);
				InHoa(maLop);
				
				// break: dung lai switch
				// strlen: lay ra do dai cua bien bien trong dau ngoac tron
				if ( strlen(maLop) == 0) break;
			
				if(KiemTraKiTu(maLop) == 0){
					cout << "ERROR: Khong duoc chua ki tu dac biet!" << endl;
					goto lop;
				}
				
				if(KiemTraKhoangTrang(maLop) == 0 || strlen(maLop) > 15 ){
					cout << "ERROR: Khong duoc chua khoang trang va do dai khong qua 15 ki tu!" << endl;
					goto lop;
				}
				ThemSV(listSV,maLop);
				break;
			}
			case 2:{
				back:
				char maSV[12];
				fflush(stdin);
				cout << "Nhap MA Sinh Vien Can Xoa: ";
				gets(maSV);
				InHoa(maSV);
				if(KiemTraSV(listSV,maSV) == NULL){
					cout << "ERROR: Ma sinh vien khong ton tai!" << endl;
					Sleep(1000);
					break;
				}
				int check = 1;
				//char ch[2];
				KiemTraSVDaDangKyLTC(root,check,maSV);
				if ( check == 0){
					cout << "Sinh Vien Da Dang Ky Lop Tin Chi. Khong Duoc Xoa....";
					Sleep(1000);
					return;
				}
				if (confirm()  == 0 ) return;
				XoaNodeSV(listSV,maSV);
				cout << "XOA THANH CONG!!" << endl;
				Sleep(1000);
				break;
			}
			case 3:{
				SuaSV(listSV);
				break;
			}
			case 0:{
				return;
			}
		}
	}
}
//g
void MenuDangKyLTC(DSLOP &root,DSSINHVIEN &listSV, DSMONHOC &listMH){
	DSMONHOC tempListMH;
	int check = 0,i=0;
	char mltc[50];
	
	system("cls");
	XuatLTC(root);
	char nienKhoa[50],hocKy[50],msv[12];
	msv:
	cout << "Nhap Ma Sinh Vien: ";
	fflush(stdin);
	gets(msv);
	InHoa(msv);
	if(strlen(msv) == 0) return;
	if(KiemTraSV(listSV,msv) == NULL){
		cout << "ERROR: Sinh vien khong ton tai" << endl;
		goto msv;
	}
	cout << "Nien Khoa: ";
	fflush(stdin);
	gets(nienKhoa);
	InHoa(nienKhoa);
	if(strlen(nienKhoa) == 0) return;
	
	cout << "Hoc Ky: ";
	fflush(stdin);
	gets(hocKy);
	system("cls");
	//check xem co lop tai nien khoa va hoc ky do khong
	XuatLTCTheoDK(root,listMH,nienKhoa,atoi(hocKy),check);
	
	while (check == 1){
		mmh:
		char chon[5]="";
		int maLTC[50];
		system("cls");
		XuatLTCTheoDK(root,listMH,nienKhoa,atoi(hocKy),check);
		cout << endl <<"=====================================================================";
		XuatMH(tempListMH);
		cout << "Luachon(1: Chon/2: Huy/3: Luu): ";
		fflush(stdin);
		gets(chon);
		InHoa(chon);
		if(strlen(chon) == 0) break;
		
		while(atoi(chon) == 1){
			system("cls");	
			XuatLTCTheoDK(root,listMH,nienKhoa,atoi(hocKy),check); cout<< endl;
			cout << "=====================================================================" << endl;
			XuatMH(tempListMH);
			cout << "MLTC: ";
			fflush(stdin);
			gets(mltc);
			if(strlen(mltc) == 0) break;
			if(KiemTraMLTC(root,atoi(mltc)) == NULL){
				system("cls");
				cout << "ERROR: Ma LTC khong ton tai" << endl;
				Sleep(1000);
				continue;
			}
			if(KiemTraMH(tempListMH,KiemTraMLTC(root,atoi(mltc))->lop.MAMH) != NULL){
				system("cls");
				cout << "ERROR: Ma mon hoc da ton tai" << endl;
				Sleep(1000);
				continue;
			}
			if(KiemTraDaDangKyLTC(KiemTraMLTC(root,atoi(mltc))->lop.dssv,msv) == 0){
				system("cls");
				cout << "ERROR: Ma mon hoc da duoc dang ky" << endl;
				Sleep(1000);
				continue;
			}
			MONHOC *tempMH = new MONHOC;
			*tempMH = *KiemTraMH(listMH,KiemTraMLTC(root,atoi(mltc))->lop.MAMH);
			// show mon hoc chon
			ThemMH(tempListMH,tempMH);
			// luu ma ltc da chon
			maLTC[i] = atoi(mltc);
			i++;
		}
		//delete 
		if(atoi(chon) == 2){
			system("cls");	
			XuatLTCTheoDK(root,listMH,nienKhoa,atoi(hocKy),check); cout<< endl;
			XuatMH(tempListMH);
			cout << "MLTC (Can Huy): ";
			fflush(stdin);
			gets(mltc);
			
			if(strlen(mltc) == 0) break;
			
			for(int j=0;j<i; j++){
				if(atoi(mltc) == maLTC[j]){
					// xoa phan hien thi
					XoaMH(tempListMH,KiemTraMLTC(root,atoi(mltc))->lop.MAMH);
					// xoa mang dang ky
					for(int k=j; k<i-1; k++){
						 maLTC[k] = maLTC[k+1];
					}
					i--;
					break;
				}
			}
		}
		// save
		if(atoi(chon) == 3){
			for(int j=0; j<i; j++){
				DangKyTC(KiemTraMLTC(root,maLTC[j])->lop.dssv, msv,-1);
				LuuSVDK(KiemTraMLTC(root,maLTC[j])->lop);
			}
			break;
		}
	}
}
//h
void NhapDiem(DSLOP root, DSMONHOC listMH, DSSINHVIEN listSV){
	char mmh[10], nienKhoa[50];
	char hocKy[10],nhom[10],diem[10];
	LOP *tempLop = NULL;
	int i=0;
	SINHVIENDK *k;
	system("cls");
	
	cout <<"\t\t\tMENU NHAP DIEM" << endl;
	cout << "Nien Khoa: ";
	fflush(stdin);
	gets(nienKhoa);
	InHoa(nienKhoa);
	if(strlen(nienKhoa) == 0) return;
	
	cout << "Hoc Ky: ";
	fflush(stdin);
	gets(hocKy);
	InHoa(hocKy);
	if(strlen(hocKy) == 0) return;
	
	cout << "Nhom: ";
	fflush(stdin);
	gets(nhom);
	InHoa(nhom);
	if(strlen(nhom) == 0) return;
	
	cout << "Ma Mon Hoc: ";
	fflush(stdin);
	gets(mmh);
	InHoa(mmh);
	if(strlen(mmh) == 0) return;	
	
	// tim kiem trong danh sach lop tc lay ra danh sach sv trung khop voi dieu kien tren
	KiemTraLop(root,tempLop,mmh,nienKhoa,atoi(hocKy),atoi(nhom));
	if(tempLop == NULL ) {
		cout << "ERROR: Du Lieu Khong Ton tai...";
		Sleep(1000);
		return;
	}
	
	k = tempLop->dssv->pFirst;
	// nhap diem
	while( k!=NULL){
		XuatSVDK(*tempLop, listSV, KiemTraMH(listMH,tempLop->MAMH)->TENMH, nienKhoa, atoi(hocKy), nhom);
		gotoxy(60,4+i);
		cout << ": ";
		fflush(stdin);
		gets(diem);
		//
		if(strlen(diem) == 0 || KiemTraSo(diem) == 0) return;
		if(atof(diem) < 0 || atof(diem) > 10) continue;
		
		k->DIEM = atof(diem);
		k=k->next;
		i++;
	}
	XuatSVDK(*tempLop,listSV,KiemTraMH(listMH,tempLop->MAMH)->TENMH, nienKhoa, atoi(hocKy), nhom);
	LuuSVDK(*tempLop);
	cout << endl << "Nhap (ENTER) de thoat...";
	gets(mmh);
}
// j
// tinh so tin chi cua lop do
void getMaxTC(DSLOP root, DSSINHVIEN listSV, DSMONHOC listMH, char maLop[],float &n,int &nam){
		if(root != NULL){
		  // tim xem sinh vien thuoc lop can tim co trong list dsdk neu co thi cong tin chi cua cai lop lai
		
	   	  for(SINHVIENDK *k=root->lop.dssv->pFirst; k!=NULL; k=k->next){
	   	  		if( strcmp(KiemTraSV(listSV,k->MASV)->MALOP,maLop) == 0){
	   	  			n = n + KiemTraMH(listMH,root->lop.MAMH)->STCLT + KiemTraMH(listMH,root->lop.MAMH)->STCTH;
	   	  			nam = KiemTraSV(listSV,k->MASV)->NAM;
	   	  			break;
	   	  		}
	   	  }
	      getMaxTC(root->left, listSV, listMH, maLop, n,nam);
	      getMaxTC(root->right,listSV, listMH, maLop, n , nam);
	   }
}

void getDiemSV(DSLOP root, DSSINHVIEN listSV, DSMONHOC listMH, char maSV[], float &diem){
	if(root != NULL){
		  // tim xem sinh vien thuoc lop can tim co trong list dsdk neu co thi cong tin chi cua cai lop lai
	   	  for(SINHVIENDK *k=root->lop.dssv->pFirst; k!=NULL; k=k->next){
	   	  		if( strcmp( KiemTraSV(listSV,k->MASV)->MASV,maSV ) == 0){
	   	  			if( k->DIEM == -1) diem++;
	   	  			diem = diem + (KiemTraMH(listMH,root->lop.MAMH)->STCLT + KiemTraMH(listMH,root->lop.MAMH)->STCTH) * k->DIEM;
	   	  			break;
	   	  		}
	   	  }
	      getDiemSV(root->left,listSV,listMH, maSV, diem);
	      getDiemSV(root->right,listSV,listMH , maSV, diem);
	   }
}
void XuatDiemTB(DSLOP root, DSSINHVIEN listSV,DSMONHOC listMH, char maLop[], int nam){
	int i=1;	
	float solgTC = 0;
	getMaxTC(root,listSV,listMH,maLop,solgTC,nam);
	
	system("cls");
	cout << "\t  BANG THONG KE DIEM TRUNG BINH KHOA HOC" << endl;
	cout << "\t  Lop: " << maLop << "\t  Nam nhap hoc: " << nam << endl;
	cout << right<<setw(5)<< "STT|" << right<<setw(15)<< "MASV|" << right<<setw(15)<< "HO|" <<right<<setw(13)<< "TEN|" <<right<<setw(10)<< " DIEM TB|" << endl;
	cout <<"-----------------------------------------------------------" << endl;

	for(SINHVIEN *k=listSV.pFirst; k!=NULL; k=k->next){
		if(strcmp(k->MALOP,maLop) == 0){
			float diemSV = 0;
			getDiemSV(root, listSV, listMH, k->MASV,diemSV);
			
			cout << right<<setw(4)<< i <<"|" << right<<setw(15)<< k->MASV <<"|" 
			<< right<<setw(14)<< KiemTraSV(listSV,k->MASV)->HO <<"|" <<right<<setw(13)<<KiemTraSV(listSV,k->MASV)->TEN
			<<"|" <<right<<setw(9)<< (float) diemSV/solgTC << "|" << endl;
			i++;
		}
	}
}
void InBangDiemTrungBinh(DSLOP root, DSSINHVIEN listSV,DSMONHOC listMH){
	float n=0;
	char maLop[15];
	LOP lop;
	int nam;
	// nhap maLop
	cout << "Nhap Ma Lop: ";
	fflush(stdin);
	gets(maLop);
	InHoa(maLop);
	
	XuatDiemTB(root,listSV,listMH,maLop, nam);
	

	gets(maLop);
}
void MenuQuanLyThongTin(DSLOP root, DSSINHVIEN listSV,DSMONHOC listMH){
		char chon[10];
		while(1){
			system("cls");
			strcpy(chon,"-1");
			cout << "\t\t\t\t\t\tMENU QUAN LY THONG TIN" << endl;
			cout << "\t\t\t\t\t1. In Danh Sach Sinh Vien Theo Lop Tin Chi"<<endl;
			cout << "\t\t\t\t\t2. In Danh Sach Sinh Vien Theo Lop" << endl;
			cout << "\t\t\t\t\t3. In Bang Diem Theo Lop Tin Chi" << endl;
			cout << "\t\t\t\t\t4. In Danh Danh Sach Mon Hoc" << endl;
			cout << "\t\t\t\t\t5. In Bang Diem Trung Binh Cua Mot Lop Theo Tin Chi" << endl;
			cout << "----------------------------------------------------------------------------------------------------" << endl;
			cout << "Lua chon: ";
			gets(chon);
			switch(atoi(chon)){
				case 1:{
					InDanhSachSVCuaLTC(root,listMH,listSV);
					break;
				}
				case 2:{
					char maLop[10];
					cout << "Nhap Map Lop: ";
					fflush(stdin);
					gets(maLop);
					InHoa(maLop);
					if(strlen(maLop) == 0) break;
					
					XuatSVTheoDK(listSV,maLop);
					cout << "An (ENTER) De Thoat....";
					gets(maLop);
					break;
				}
				case 3:{
					InDanhSachSVCuaLTC(root, listMH, listSV);
					break;
				}
				case 4:{
					char key[10];
					system("cls");
					XuatMH(listMH);
					gets(key);
					break;
				}
				case 5:{
					InBangDiemTrungBinh(root, listSV, listMH);
					break;
				}
			}
		
			if(atoi(chon) == 0) break;
		}
}
void MainMenu(DSSINHVIEN &listSV,DSMONHOC &listMH, DSLOP &root){
	char luachon[2];	
	while(1){	
		system("cls");
		strcpy(luachon,"-1");
		cout << "\t\t\t\tMENU QUAN LY DIEM SINH VIEN THEO HE TIN CHI" << endl;
		cout << "\t\t\t\t\t1. Dang Ky Lop Tin Chi"<<endl;
		cout << "\t\t\t\t\t2. Nhap Diem" << endl;
		cout << "\t\t\t\t\t3. Quan Ly Mon Hoc" << endl;
		cout << "\t\t\t\t\t4. Quan Ly Sinh Vien" << endl;
		cout << "\t\t\t\t\t5. Quan Ly Lop Tin Chi" << endl;
		cout << "\t\t\t\t\t6. Quan Ly Thong Tin" << endl;
		cout << "\t\t\t\t\t0. Thoat" << endl;
		cout << "----------------------------------------------------------------------------------------------------" << endl;
		cout << "Luachon: ";
		gets(luachon);
		switch (atoi(luachon)){
			case 1:{
				MenuDangKyLTC(root,listSV,listMH);
				break;
			}
			case 2:{
				NhapDiem(root,listMH,listSV);
				break;
			}
			case 3:{
				MenuMH(listMH);
				break;
			}
			case 4:{
				MenuSV(listSV,root);
				break;
			}
			case 5:{
				MenuLTC(root,listMH);
				break;
			}
			case 6:{
				MenuQuanLyThongTin(root,listSV,listMH);
				break;
			}
		}
		if(atoi(luachon) == 0) break;
	}
}
// Xuat
void XuatMH(DSMONHOC listMH){
	cout << "\t\t\t\t\t\tDANH SACH MON HOC" << endl;
	cout << right << setw(15) << "MMH" << "|";
	cout << right << setw(40) << "TEN"<< "|";
	cout << right << setw(20) << "LT"<< "|";
	cout << right << setw(20) << "TH"<< "|";
	cout << endl <<"---------------------------------------------------------------------------------------------------" << endl;
	// sort mon hoc
	for(int i=0; i<listMH.soluong-1; i++){
		for(int j=i+1;j<listMH.soluong; j++ ){
			if( strcmp(listMH.monhoc[i]->TENMH,listMH.monhoc[j]->TENMH) > 0 ){
				swap(listMH.monhoc[i],listMH.monhoc[j]);
			}
		}
	}
	
	for (int i=0; i<listMH.soluong; i++){
		cout << right << setw(15) << listMH.monhoc[i]->MAMH << "|";
		cout << right << setw(40) << listMH.monhoc[i]->TENMH << "|";
		cout << right << setw(20) << listMH.monhoc[i]->STCLT<< "|";
		cout << right << setw(20) << listMH.monhoc[i]->STCTH << "|"<< endl;
	}
}
void XuatLTC(DSLOP root){
	cout << "\t\t\t\t\tDANH SACH LOP TIN CHI" << endl;
	cout << right << setw(9) << "MLTC" << "|";
	cout << right << setw(14) << "MAMH" << "|";
	cout << right << setw(15) << "Hoc Ky" << "|";
	cout << right << setw(16) << "Nien Khoa" << "|";
	cout << right << setw(11) << "Nhom" << "|";
	cout << right << setw(13) << "SV Min" << "|";
	cout << right << setw(12) << "SV Max" << "|";
	cout << endl <<"    ----------------------------------------------------------------------------------------------" << endl;
	Posorder(root);
}
void XuatLTCTheoDK(DSLOP root, DSMONHOC listMH, char nienKhoa[],int hocKy,int &check){
	cout << "\t\t\t\t\tDANH SACH MON HOC-HOC KY: " << hocKy << "-NIEN KHOA: " << nienKhoa << endl;
	cout << right << setw(15) << "MLTC" << "|";
	cout << right << setw(15) << "MMH" << "|";
	cout << right << setw(40) << "TEN"<< "|";
	cout << right << setw(20) << "LT"<< "|";
	cout << right << setw(20) << "TH"<< "|";
	cout << endl <<"-----------------------------------------------------------------------------------------------------------" << endl;
	DuyetTheoDK(root,listMH,nienKhoa,hocKy,check);
}
void XuatSV(DSSINHVIEN listSV){
	cout << "\t\t\t\t\tDANH SACH SINH VIEN - " << endl;
	cout << right << setw(13) << "MA LOP" << "|";
	cout << right << setw(9) << "MA SV" << "|";
	cout << right << setw(14) << "HO" << "|";
	cout << right << setw(15) << "TEN" << "|";
	cout << right << setw(16) << "PHAI" << "|";
	cout << right << setw(11) << "SDT" << "|";
	cout << right << setw(12) << "Nam" << "|";
	cout << endl <<"    ----------------------------------------------------------------------------------------------" << endl;
	if(listSV.pLast == NULL) return;
	for(SINHVIEN *i = listSV.pFirst; i!=NULL; i=i->next){
		cout << right << setw(13) <<  i->MALOP << "|";
		cout << right << setw(9)  <<    i->MASV << "|";
		cout << right << setw(14) <<  i->HO << "|";
		cout << right << setw(15) <<  i->TEN << "|";
		cout << right << setw(16) <<  i->PHAI << "|";
		cout << right << setw(11) <<  i->SDT << "|";
		cout << right << setw(12) <<  i->NAM << "|";
		cout << endl <<"    ----------------------------------------------------------------------------------------------" << endl;
	}
}
void XuatSVTheoDK(DSSINHVIEN listSV, char maLop[]){
	cout << "\t\t\t\t\tDANH SACH SINH VIEN - " << maLop<< endl;
	cout << right << setw(13) << "MA LOP" << "|";
	cout << right << setw(9) << "MA SV" << "|";
	cout << right << setw(14) << "HO" << "|";
	cout << right << setw(15) << "TEN" << "|";
	cout << right << setw(16) << "PHAI" << "|";
	cout << right << setw(11) << "SDT" << "|";
	cout << right << setw(12) << "Nam" << "|";
	cout << endl <<"\t----------------------------------------------------------------------------------------------" << endl;
	// kiem tra mang trong
	if(listSV.pLast == NULL) return;
	// kiem tra maLop co ton tai khong ?
	if(strcmp(listSV.pLast->MALOP, maLop) < 0 ) return;

	int check = 0;
	for(SINHVIEN *i = listSV.pFirst; i!=NULL; i=i->next){
		if(strcmp(i->MALOP,maLop) != 0 && check == 1) break;
		if(strcmp(i->MALOP,maLop) != 0) continue;
		check = 1;
		cout << right << setw(13) <<  i->MALOP << "|";
		cout << right << setw(9)  <<   i->MASV << "|";
		cout << right << setw(14) <<  i->HO << "|";
		cout << right << setw(15) <<  i->TEN << "|";
		cout << right << setw(16) <<  i->PHAI << "|";
		cout << right << setw(11) <<  i->SDT << "|";
		cout << right << setw(12) <<  i->NAM << "|";
		cout << endl <<"    ----------------------------------------------------------------------------------------------" << endl;
	}
}
void XuatSVDK(LOP lop, DSSINHVIEN listSV, char tenMon[], char nienKhoa[], int hocKy, char nhom[]){
	system("cls");
	cout << "\t  DANH SACH SINH VIEN -  " << tenMon << endl;
	cout << "\t  Nien Khoa: " << nienKhoa << "  Hoc Ky: " << hocKy << "  Nhom: " << nhom << endl;
	cout << right<<setw(5)<< "STT|" << right<<setw(15)<< "MASV|" << right<<setw(15)<< "HO|" <<right<<setw(13)<< "TEN|" <<right<<setw(10)<< "DIEM|" << endl;
	cout <<"-----------------------------------------------------------" << endl;
	int i=1;	

	for(SINHVIENDK *k=lop.dssv->pFirst; k!=NULL; k=k->next){	
		cout << right<<setw(4)<< i <<"|" << right<<setw(15)<< k->MASV <<"|" 
			<< right<<setw(14)<< KiemTraSV(listSV,k->MASV)->HO <<"|" <<right<<setw(13)<<KiemTraSV(listSV,k->MASV)->TEN
			<<"|" <<right<<setw(9)<< (float) k->DIEM  << "|" << endl;
			i++;	
	}
}
int main(int argc, char *argv[])
{	

	DSLOP root = NULL;
	DSSINHVIEN listSV;
	DSMONHOC listMH;
	
	DocMH(listMH);
	DocLTC(root);
	DocSV(listSV);
	//menu
	MainMenu(listSV,listMH,root);
//	Posorder(root);
	return 0;
}
