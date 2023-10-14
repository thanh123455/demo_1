// Bai 4, chuong 5 : DO THI
#include <stdio.h>
#include <iostream>
#include <fstream>
using namespace std;

#define MAX 20
int A[MAX][MAX]; // mang 2 chieu
int n; // so dinh cua do thi
char vertex[MAX]; // ten dinh

/// DSLK s? d?ng cho STACK va QUEUE
struct Node {
	int info;
	Node *link;
};
Node *sp;
Node *front, *rear;

/// STACK
void InitStack() {
	sp = NULL;
}
int isEmptyS()
{
	if(sp==NULL)
		return 1;
	return 0;
}
void PushS(int x) 
{
	Node *p = new Node;
	p->info = x;
	p->link = sp;
	sp = p;
}
int PopS(int &x) 
{
	if (sp != NULL) {
		Node *p = sp;
		x = p->info;
		sp = p->link;
		delete p;
		return 1;
	}
	return 0;
}
/// end STACK

/// QUEUE
void InitQueue() {
	front = NULL;
	rear = NULL;
}
int isEmptyQ() {
	if (front == NULL)
		return 1;
	return 0;
}
void PushQ(int x) 
{
	Node *p = new Node;
	p->info = x;
	p->link = NULL;
	if (rear == NULL)
		front = p;
	else
		rear->link = p;

	rear = p;
}
int PopQ(int &x) 
{
	if (front !=NULL) {
		Node *p = front;
		front = p->link;
		x = p->info;
		if (front == NULL) {
			rear = NULL;
		}
		delete p;
		return 1;
	}
	return 0;
}
/// end QUEUE

void InitGraph()
{
	n=0;
}

// Cau 4.1 Nhap MTK bang tay
void inputGraph()
{
	cout<<"nhap so dinh do thi n: "; 
	cin>>n;
	for(int i=0;i<n;i++)
	{
		cout<<"Nhap ten dinh: ";
		cin>>vertex[i];
		cout<<"nhap vao dong thu "<<i+1<<":   ";
		for(int j=0;j<n;j++)
			cin>>A[i][j];
	}
}

// Nhap MTK tu file txt
void inputGraphFromText()
{
	string line;
	//ifstream myfile ("mtk1.txt");
	ifstream myfile ("bfs_dfs_slide_th_b10.txt");	
	//ifstream myfile ("dothi_2_bfs_dfs_27_doan.txt");	
	//dothi_2_bfs_dfs_slide
	if (myfile.is_open())
	{
		myfile>>n;
		for(int i=0;i<n;i++)
			myfile>>vertex[i];
		for(int i=0;i<n;i++)
		{		
			for(int j=0;j<n;j++)
				myfile>>A[i][j];
		}
	}
}

// Cau 4.2 Xuat MTK
void outputGraph()
{
	for(int i=0;i<n;i++)
	{
	for(int j=0;j<n;j++)
		cout<<A[i][j]<<"  ";
	cout<<endl;
	}
}

void output(int a[], int n)
{
	for(int i=0;i<n;i++)
		cout<<vertex[a[i]]<<"  ";
}

// Cau 4.3 Duyet BFS (QUEUE)
int C[100]; //luu tru dinh chua xet, 1 la chua xet, 0 la da xet
int bfs[100];  // luu ds ptu da duyet
int nbfs=0;  // chi so luu dinh da xet
void InitC()
{
	for(int i=0; i<n; i++) // n la so dinh cua do thi
		C[i]=1;
}
void BFS(int v) // v la dinh bat dau
{
	int w, p;
	PushQ(v);
	C[v]=0;
	while(front!=NULL)
	{
		PopQ(p);
		bfs[nbfs]=p;
		nbfs++;
		for(w=0; w<n; w++)
			if(C[w] && A[p][w]==1)
			{
				PushQ(w);
				C[w]=0;
			}
	}
}

// Cau 4.4 Duyet DFS (STACK)
int dfs[100]; //luu danh sach ptu da duyet, mang ket qua
int ndfs=0; //chi so luu dinh da xet
void DFS(int s)
{       
    PushS(s); 
   	dfs[ndfs]=s;
    ndfs++;
   	C[s]=0;  // dinh s da xet roi
    int v=-1, u=s;  
    while(isEmptyS()==0)
    {
		if(v==n) //so luong dinh co bang so luong dinh dc xet hay ko
		// chua du thi minh lay 1 ptu ra
			PopS(u);
     	for(v=0;v<n;v++) // cac dinh ke voi u ma chua dc xet dua vao stack
			if(A[u][v]!=0 && C[v]==1)  // ke la khac 0 va dinh do chua dc xet ( chua dc liet ke vao stack)
			{
				PushS(u); //de lat hoi back lai 
  				PushS(v);
				dfs[ndfs]=v;
				ndfs++;
				C[v] = 0;
				u=v;
				break;  // co 1 dua ke thi break
			}
     }
}

//Cau 4.5 Tim su dung BFS
void Search_by_BFS(int x, int v) // v là d?nh b?t d?u
{
	int w, p;
	PushQ(v);
	C[v]=0;
	while(front!=NULL)
	{
		PopQ(p);
		if (x == p) 
		{
			cout<<"Tim thay x="<<x<<endl;
			return;
		}
		for(w=0; w<n; w++)
			if(C[w] && A[p][w]==1)
			{
				PushQ(w);
				C[w]=0;
			}
	}
}

int main()
{
	int a[MAX];	
	int b[MAX];
	int choice, sp, sp_b, x, i;
	system("cls");
	cout<<" ---------  BAI TAP 4 , CHUONG 5 , DO THI -------"<<endl;
	cout<<"1. Khoi tao MA TRAN KE rong"<<endl;
	cout<<"2. Nhap MA TRAN KE tu file text"<<endl;
	cout<<"3. Nhap MA TRAN KE "<<endl;	
	cout<<"4. Xuat MA TRAN KE "<<endl;	
	cout<<"5. Duyet do thi theo chieu rong BFS - MTK "<<endl;
	cout<<"6. Duyet do thi theo chieu sau DFS - MTK"<<endl;
	cout<<"7. Tim dinh co gia tri x theo BFS"<<endl;	
	cout<<"8. Thoat"<<endl;
	do
    {
		cout<<"\nVui long chon so de thuc hien: ";
		cin >> choice;
		switch(choice)
		{
			case 1:
				InitGraph();
				cout << "Ban vua khoi tao MA TRAN KE rong thanh cong!\n";
				break;
			case 2: 				
				inputGraphFromText(); 	
				cout << "Ban vua nhap MA TRAN KE tu file: \n";
				outputGraph();
                break;
			 case 3: 				
				inputGraph(); 				
                break;
			 case 4: 				
				outputGraph(); 				
                break;
			 case 5:
				 InitQueue();
				 InitC();
				 cout << "Vui long nhap dinh xuat phat: ";
				 cin>>x;
				 BFS(x);
				 cout<<"Thu tu dinh sau khi duyet BFS: "<<endl;
				 output(bfs,n);	
				 break;
			case 6: 		
				InitStack();
				InitC();
				cout << "Vui long nhap dinh xuat phat: ";
				cin>>x;
				ndfs =0;
				DFS(x);				
				cout<<"Thu tu dinh sau khi duyet DFS: "<<endl;
				output(dfs,n);
                break;	
			case 7: 				
                cout << "Vui long nhap gia tri x can tim: ";
				cin>>x;
				Search_by_BFS(x,0);
                break;
			case 8: 				
                cout << "Goodbye .....!" <<endl;
                break;
            default: 
                break;
		}
	}
	while(choice!=8);
	system("pause");
	return 0;
}
