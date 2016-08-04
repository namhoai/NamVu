#include<string>			// copyright of Trieu Than
#include<iostream>			// code update: 04/12/2015
#include<fstream>			// truy cap: https://youtu.be/j1U8cK4Gn9I
#include<iomanip>			// de biet them thong tin chi tiet!
#include<vector>
using namespace std;

class Nguoi{
	protected:
		string ten, diachi, sodt;
	public:
		Nguoi(){
			ten = diachi = sodt = "";
		}
		friend istream &operator>>( istream &in, Nguoi &n ){
			cout<< "\nTen: "; in>> n.ten;
			cout<< "\nDia chi: "; in>> n.diachi;
			cout<< "\nsoDT: "; in>>  n.sodt;
		}
		friend ostream &operator<<( ostream &out, Nguoi &n ){
			out<< left << setw(15) << n.ten << setw(15) << n.diachi << setw(15) << n.sodt;
		}
		string getTen(){ 
			return ten; 
		}
};
				
class TV:public Nguoi{
	friend class BPC;
	protected:
		int maTV;
		static int manv;
		float luong;
	public:
		NV(){
			maTV = 0; luong = 0.0;
		}
		friend istream &operator>>( istream &in, TV &tv ){
			Nguoi *nguoi = reinterpret_cast<Nguoi*> (&tv);
			tv.maTV = manv++;
			in>> *nguoi;
			cout<< "\nMuc luong: "; in>> tv.luong;
		}
		friend ostream &operator<<( ostream &out, TV &tv ){
			Nguoi *nguoi = reinterpret_cast<Nguoi*> (&tv);
			out<< left << setw(10) << tv.maTV;
			out<< *nguoi;
			out<< tv.luong << endl;
		}
		void ghiTV(){
			ofstream ofs("TV.DAT", ios::app);
			ofs.write(reinterpret_cast<const char*>(this),sizeof(TV)); ofs.close();
		}
		void docTV( istream &ifs ){ ifs.read(reinterpret_cast<char*>(this), sizeof(TV)); }
		int getMaTV(){ return maTV; }
		float getLuong(){ return luong; }
};
			// copyright 2015/12/04
class VT{
	friend class BPC;
	protected:
		int maVT;
		static int mavt;
		string tenvt;
		float thuong;
	public:
		VT(){
			thuong = 0; maVT =  0; tenvt = "";
		}
		friend istream &operator>>( istream &in, VT &v ){
			v.maVT = mavt++;
			cout<< "\nTen VT: "; in>> v.tenvt;
			cout<< "\nThuong: "; in>> v.thuong;
		}
		friend ostream &operator<<( ostream &out, VT &v ){
			out<< left << setw(10) << v.maVT << setw(15)<< v.tenvt << setw(12)<< v.thuong;
		}
		void docVT( fstream &ifs ){ ifs.read(reinterpret_cast<char*>(this),sizeof(VT)); }
		void ghiVT(){
			ofstream ofs( "VT.DAT", ios::app );
			ofs.write(reinterpret_cast<const char*>(this),sizeof(VT)); ofs.close();
		}
		int getMaVT(){ return maVT; }
		float getThuong(){ return thuong; }
		string getTenVT(){ return tenvt; }
};
					
class BPC{
	protected:
		TV tv;
		VT vt[3];
		vector<int> songay;
		int sl, tong;
	public:
		BPC(){ sl = 0; tong = 0; }
		void nhapB( TV tv1, VT v[100], int n ){				
			tv= tv1;
			int ok, kt, ma, ng; 
			cout<<"\nThong tin cua TV " << tv.getTen()<<" :";
			do{
				cout<<"\nNhap so vi tri: "; cin>>sl;
			} while( sl > 3 ||sl < 0 );
			for( int i = 0; i < sl; i++ ){
				do{
					ok = kt = 0;
					cout<<"\nNhap ma Vi tri: "; cin>> ma;
					if( ma < 100 || ( ma > v[n-1].getMaVT()) ) ok = 1;
					for( int j = 0; j< n; j++ ) 
						if( ma == v[j].getMaVT() ) vt[i] = v[j];
					for(int k = 0; k < i; k++ )
						if( vt[k].getMaVT() == ma ) kt = 1;
				} while( ok || kt );
				cout<< "\nNgay lam viec: "; cin>> ng; songay.push_back(ng);
				tong += ng;
			}
		}
		void xuatB(){
			cout<< left << setw(10) << "Ma NV: " << setw(15) <<"Ten NV" 
					<< setw(15) << "Dia chi" << setw(15)
					<< "So DT" << setw(12) << "Muc luong" << endl;
			cout<<tv;
			cout<<"So luong vi tri: " << sl << endl;
			cout<< left << setw(10) << "Ma VT" << setw(15) << "Ten VT" << setw(12) << "Thuong"
				<< setw(10) << "So ngay" << endl;
			for( int i = 0; i < sl; i++ )
				cout<< vt[i] << songay[i] << endl;
		}
		void ghiB(){
			ofstream ofs0( "PC.DAT", ios::app );
			ofs0.write(reinterpret_cast<char*>(this),sizeof(BPC)); ofs0.clear();ofs0.close();
		}
		void docB(fstream &ifs){ ifs.read(reinterpret_cast<char*>(this),sizeof(BPC)); }
		void sapxep( BPC b[], int n ){
			int lc = 0;
			do{
				cout<< "\n___LUA CHON___\n" << "\n1: Sap xep theo ten. \n2: sap xep theo thong so ngay."
					<< "\n0: Tro lai Menu. \nBan chon ? "; cin>> lc;
				switch( lc ){
					case 1:{ system( "cls" );
						for( int i = 0; i < n; i++ )
							for(int j = 1 + i; j < n; j++ )
								if( b[i].tv.getTen() > b[j].tv.getTen() ) swap( b[i], b[j] );
						cout<< "\nThong tin sau sap xep: \n";
						for( int i = 0; i < n; i++ ) b[i].xuatB(), cout<< endl;
						break;
					}
					case 2:{ system("cls");
						for( int i = 0; i < n; i++ )
							for( int j = 1 + i; j < n; j++ )
								if( b[i].tong < b[j].tong ) swap( b[i], b[j] );
						cout<<"\nThong tin sau sap xep: \n";
						for( int i = 0; i < n; i++ ) b[i].xuatB(), cout << endl;
						break;
					}
					case 0: system( "cls" ); break;
				}
			} while( lc != 0 );
		}
		void TinhTien( BPC b[], int n ){
	 		int lc = 0;
			cout<< left << setw(10) << "Ma TV" << setw(15) << "Ten TV" 
				<< setw(10) << "SL" << setw(12) << "Tong tien" << endl;
			for( int i = 0; i < n; i++ ){
				float phi = 0.1*b[i].tv.getLuong();
				for( int j = 0; j < b[i].sl; j++ )
					phi += b[i].vt[j].getThuong();
				cout<< left << setw(10) << b[i].tv.getMaTV() << setw(15) << b[i].tv.getTen() << setw(10)
					<< b[i].sl << setw(12) << phi << endl;
			}	
			cout<< endl;
		}
};
int TV::manv = 100;
int VT::mavt = 100;
					// caution: code chi mang tinh tham khao!
void menu(){
	fstream f( "TV.DAT", ios::out ); fstream f1( "VT.DAT", ios::out );
	fstream f2( "PC.DAT", ios::out ); 
	int sotv = 0, sovt = 0, sobpc = 0, lc = 0, slvt = 0, slb = 0;
	TV tv1, tv[100]; VT vt1[100], vt[100]; BPC bpc1[100], bpc[100], bss;
	do{
		cout<< "\n_____CAC LUA CHON____\n" << "\n1: y 1. \n2: y 2. \n3; y 3. \n4: y 4. \n5: y 5."
			<< "\n0: Thoat. \nBan chon ? "; cin>> lc;
		switch( lc ){
			case 0: exit(0);
			case 1: {
				system( "cls" ); int n; cout<< "\nNhap so luong TV muon them: "; cin>> n;
				for( int i = sotv; i < sotv + n; i++ ){
					cout<< "\nNhap thong tin TV thu " << i + 1 << ": ";
					cin>> tv[i]; tv[i].ghiTV( );
				} sotv += n; system( "cls" );
				cout<< "\n__THONG TIN TRONG FILE__\n";
				cout<< left << setw( 10 ) << "Ma NV: " << setw( 15 ) << "Ten NV" 
					<< setw(15) << "Dia chi" << setw( 15 )
					<< "So DT" << setw( 12 ) << "Muc luong" << endl;
				ifstream ifs( "TV.DAT",ios::in | ios::binary );
				if( !ifs ) { cout<< "\nFile could not be opened!"; exit(1); }	
				while( ifs ){
					tv1.docTV( ifs ); if(!ifs.eof()) cout<< tv1;
				} ifs.close();
				break;
			}
			case 2: {
				system( "cls" ); int n; cout<< "\nNhap so luong VT muon them: "; cin>> n;
				for( int i = sovt; i < sovt + n; i++ ){
					cout<< "\nNhap thong tin VT thu " << i + 1 <<": ";
					cin>> vt[i]; vt[i].ghiVT( );
				} sovt += n; system( "cls" );
				cout<< "\n__THONG TIN TRONG FILE__\n";
				cout<< left << setw(10) << "Ma VT" << setw(15) << "Ten VT" << setw(12) << "Thuong" 
					<< endl;
				fstream ifs1( "VT.DAT", ios::in );
				if( !ifs1 ) { cout<<"\nFile could not be opened!"; exit(1); }
				while(ifs1){
					vt1[slvt].docVT( ifs1 );
					if( !ifs1.eof() ) cout<< vt1[slvt] << endl; slvt++;
				} ifs1.close(); slvt--;
				break;
			}
			case 3: { system("cls");
				for( int i = sobpc; i < sotv; i++ ){
					cout<< "\nNhap thong tin VT thu " << i + 1 <<": ";
					bpc[i].nhapB(tv[i], vt1, slvt); bpc[i].ghiB( );
				} sobpc = sotv; system("cls");
				cout<< "\n__THONG TIN TRONG FILE__\n";
				fstream ifs2( "PC.DAT", ios::in );
				if(!ifs2){ cout<< "\nFile could not be opened!"; exit(1); }
				while(ifs2){
					bpc1[slb].docB(ifs2);
					if(!ifs2.eof()) bpc1[slb].xuatB(); slb++;
				} ifs2.close(); slb--;
				break;
			}
			case 4: system("cls"); bss.sapxep( bpc1, slb ); break;
			case 5: system("cls"); bss.TinhTien( bpc1, slb ); break;
		}
	} while( lc != 0 );
}
int main(){
	menu();
	return 0;
}						// chuc cac ban thi tot!
