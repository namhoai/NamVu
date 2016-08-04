#include<iostream>			// copyright of Trieu Than
#include<string>			// code update: 05/12/2015
#include<fstream>			// truy cap: https://youtu.be/IbLooG9lo_k
#include<vector>			// de biet them thong tin chi tiet.
#include<iomanip>
using namespace std;

class Nguoi{
	protected:
		string ten, diachi, sodt;
	public:
		Nguoi(){
			ten = diachi = sodt = "";
		}
		friend istream& operator>>(istream &in, Nguoi &n ){
			cout<<"\nTen: "; in>>n.ten;
			cout<<"\nDia chi: "; in>>n.diachi;
			cout<<"\nSo DT: "; in>>n.sodt;
		}
		friend ostream& operator<<(ostream &out, Nguoi &n ){
			out<<"Ten: " <<n.ten <<"\nDia Chi: " <<n.diachi<<"\n So DT: " <<n.sodt;
		}
};

class NV: public Nguoi{
	friend class BDS;
	protected:
		int maNV;
		string ngayhd;
		static int manv;
	public:
		NV(){
			ngayhd = ""; maNV = 0;
		}
		friend istream& operator>>(istream &in, NV &nv ){
			nv.maNV = manv++;
			Nguoi *n = reinterpret_cast<Nguoi*>(&nv);
			in>>*n;
			cout<<"\nNgay hop dong: "; in>>nv.ngayhd;
		}
		friend ostream& operator<<(ostream &out, NV &nv ){
			Nguoi *n = reinterpret_cast<Nguoi*>(&nv);
			out<<"Ma NV: " <<nv.maNV <<endl;
			out<< *n;
			out<<"\nNgay HD: " <<nv.ngayhd <<endl;
		}
		void ghiNV(){
			ofstream ofs("NV.DAT",ios::app);
			ofs.write(reinterpret_cast<const char*>(this),sizeof(NV)); ofs.close();
		}
		void docNV( fstream &ifs ){
			ifs.read(reinterpret_cast<char*>(this), sizeof(NV));
		}
};
int NV::manv = 1000;
class MH{
	friend class BDS;
	protected:
		static int mamh;
		int nhom, maMH, soluong;
		string tenmh;
		float giaban;
	public:
		MH(){
			maMH = nhom = soluong = 0;
			tenmh = ""; giaban = 0.0;
		}
		friend istream& operator>>(istream &in, MH &mh ){
			mh.maMH = mamh++;
			cout<<"\nTen MH: "; in>> mh.tenmh;
			do{ cout<<"\nNhom MH: \n1: DT. \n2: Dl. \n3: MT. \n4: TBVP. \n"; in>> mh.nhom;
			} while( mh.nhom < 1 || mh.nhom > 4 );
			cout<<"\nGia Ban: " ; in>>mh.giaban;
			cout<<"\nSo Luong: "; in>>mh.soluong;
		}
		friend ostream& operator<<(ostream &out, MH &mh ){
			cout<< left << setw(10) <<mh.maMH << setw(15) << mh.tenmh << setw(12);
			if( mh.nhom == 1 ) out<<"DT";
			if( mh.nhom == 2 ) out<<"Dl";
			if( mh.nhom == 3 ) out<<"MT";
			if( mh.nhom == 4 ) out<<"TBVP";
			out<<setw(10) << mh.giaban << setw(10) <<mh.soluong<<endl; 
		}
		void ghiMH(){
			ofstream ofs("MH.DAT",ios::app);
			ofs.write(reinterpret_cast<const char*>(this),sizeof(MH)); ofs.close();
		}
		void docMH( fstream &ifs ){
			ifs.read(reinterpret_cast<char*>(this), sizeof(MH));
		}
};
int MH::mamh = 1000;
							// code chi mang tinh tham khao!
class BDS{
	protected:
		NV nv;
		vector<MH> mh;
		int sl; static int slb[5];
		vector<int> slbd;
	public:
		BDS(){ sl = 0; }
		void nhapB( NV nv1, MH m[], int n ){
			nv = nv1;int ok, kt, ma, banduoc;
			cout<<"\nThong tin NV "<<nv.ten<<" : ";
			do{
				cout<<"\nNhap so MH ban dc: "; cin>> sl;
			} while( sl < 0|| sl > 5 );
			for(int i = 0; i< sl; i++ ){
				do{ ok = 0, kt = 0;
					cout<<"\nNhap ma MH: "; cin>> ma;
					if(ma < 1000 || (ma > m[n-1].maMH) ) ok = 1;
					for(int j = 0; j< n; j++ )
						if( ma == m[j].maMH) mh.push_back( m[j] );
					for(int k = 0; k < i; k++ )
						if( mh[k].maMH == ma ) kt = 1;
				} while( ok || kt );
				do{ cout<<"\ncon lai: "<<m[i].soluong - slb[i];
					cout<<"\nNhap so luong ban duoc: "; cin>> banduoc;
					slb[i] += banduoc;
				} while( slb[i] < 0 );
				slbd.push_back(banduoc);
			}
		}
		void xuatB(){
			cout<< nv;
			cout<< "\nSo loai MH ban duoc:" <<sl << endl;
			cout<< left << setw(10) << "Ma MH" << setw(15) << " Ten MH" << setw(10) <<" Sl "<< endl;
			for(int i = 0; i< sl; i++ )
				cout<< left<< setw(10)<<mh[i].maMH<<setw(15)<<mh[i].tenmh <<setw(10) <<slbd[i]<< endl;
		}
		void ghiB(){
			fstream ofs("QLBH.DAT",ios::app);
			ofs.write(reinterpret_cast<const char*>(this),sizeof(BDS)); ofs.close();
		}
		void docB( fstream &ifs ){
			ifs.read(reinterpret_cast<char*>(this),sizeof(BDS));
		}
		void sapxep( BDS b[], int n ){
			int lc = 0;
			do{
				cout<< "\n___LUA CHON___\n" << "\n1: Sap xep theo ten NV. "
					<< "\n2: sap xep theo ten MH."
					<< "\n0: Tro lai Menu. \nBan chon ? "; cin>> lc;
				switch( lc ){
					case 1:{ system( "cls" );
						for( int i = 0; i < n; i++ )
							for(int j = 1 + i; j < n; j++ )
								if( b[i].nv.ten > b[j].nv.ten ) swap( b[i], b[j] );
						cout<< "\nThong tin sau sap xep: \n";
						for( int i = 0; i < n; i++ ) b[i].xuatB(), cout<< endl;
						break;
					}
					case 2:{ system("cls");
						for( int i = 0; i < n; i++ )
							for( int j = 0; j < b[i].sl; j++ )
								for(int k = j+1; k <b[i].sl; k++)
								if( b[i].mh[j].tenmh > b[i].mh[k].tenmh ) 
									swap( b[i].mh[j], b[i].mh[k] );
						cout<<"\nThong tin sau sap xep: \n";
						for( int i = 0; i < n; i++ ) b[i].xuatB(), cout << endl;
						break;
					}
					case 0: system( "cls" ); break;
				}
			} while( lc != 0 );
		}		
		void DoanhThu( BDS b[], int n ){
			float phi;
			cout<< left << setw(10) << "Ma NV" << setw(15) << "Ten NV" << setw(15) << "SLMH" 
				<< setw(12) << "DT" <<endl;
				for( int i = 0; i < n; i++ ){
					phi = 0;
					for(int j = 0; j< b[i].sl; j++) phi+= b[i].slbd[j]*b[i].mh[j].giaban;
					cout<< left << setw(10) << b[i].nv.maNV << setw(15) << b[i].nv.ten << setw(15) 
						 << b[i].sl << setw(12) << phi <<endl;
				}
		}
};								// copyright of Trieu Than
int BDS::slb[5] ={0};
void menu(){
	fstream f("NV.DAT",ios::out); 	fstream f1("MH.DAT",ios::out);  fstream f2("QLBH.DAT",ios::out);
	NV nv1[100], nv2[100]; MH mh1[100], mh2[100]; BDS bds1[100], bds2[100], dss;
	int sonv = 0, somh = 0, sobds = 0, lc = 0, solnv = 0, solmh = 0, slbds = 0;
	do{
		cout<<"\n_____CAC LUA CHON_____\n"<<"\n1: y 1. \n2: y 2. \n3: y 3. \n4: y 4. \n5: y 5."
			<<"\n0: Thoat. \nBan chon ? "; cin>>lc;
		switch( lc ){
			case 0: exit(0);
			case 1:{ system("cls");
				int n; cout<<"\nnhap so luong nhan vien: "; cin>> n;
				for( int i = sonv; i< n+sonv; i++){
					cout<<"\nThong tin NV thu " <<i+1 <<" : ";
					cin>>nv1[i]; nv1[i].ghiNV();
				} sonv+= n; system("cls");
				cout<<"\n____THONG TIN TRONG FILE____\n ";
				fstream ifs("NV.DAT",ios::in);
				if(!ifs){ cout<<"\nFile could not be opened!"; exit(1); }
				while(ifs){
					nv2[solnv].docNV(ifs);
					if(!ifs.eof()) cout<< nv2[solnv]; cout<<endl; solnv++;
				} ifs.close(); solnv--;
				break;
			}
			case 2:{ system("cls");
				int n; cout<<"\nnhap so luong MH: "; cin>> n;
				for( int i = somh; i< n+somh; i++){
					cout<<"\nThong tin MH thu " <<i+1 <<" : ";
					cin>> mh1[i]; mh1[i].ghiMH();
				} somh+= n; system("cls");
				cout<<"\n____THONG TIN TRONG FILE____\n";
				cout<< left << setw(10) <<"Ma MH" << setw(15) << "Ten MH" << setw(12) << "Nhom MH"
				<< setw(10) << "Gia Ban" << setw(10) << "SLuong" << endl;
				fstream ifs("MH.DAT",ios::in);
				if(!ifs){ cout<<"\nFile could not be opened!"; exit(1); }
				while(ifs){
					mh2[solmh].docMH(ifs);
					if(!ifs.eof()) cout<< mh2[solmh]; solmh++;
				} ifs.close(); solmh--;
				break;
			}
			case 3:{
				for( int i = sobds; i< sonv; i++){
					bds1[i].nhapB(nv2[i], mh2, solmh ); bds1[i].ghiB();
				} sobds = sonv; system("cls");
				cout<< "\n____THONG TIN TRONG FILE____\n ";
				fstream ifs("QLBH.DAT",ios::in);
				if(!ifs){ cout<<"\nFile could not be opened!"; exit(1); }
				while(ifs){
					bds2[slbds].docB(ifs);
					if(!ifs.eof()) bds2[slbds].xuatB(); cout<<endl; slbds++;
				} ifs.close(); slbds--;
				break;
			}	
			case 4: system("cls"); dss.sapxep( bds2, slbds ); break;
			case 5: system("cls"); dss.DoanhThu( bds2, slbds ); break;
		}
	} while( lc != 0 );
}
					// code chi mang tinh minh hoa !
int main(){
	menu();
	return 0;
}					// ****______chuc cac ban thi tot!______****//
