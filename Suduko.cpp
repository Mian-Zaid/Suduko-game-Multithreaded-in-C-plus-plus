#include <iostream> 
#include <pthread.h> 
#include <fstream>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <mutex>
#include <cstdio>
#include <cstring>
#include <cstdlib>
using namespace std;
#define UNASSIGNED 0
#define N 9

bool status=false;

pthread_mutex_t mutex_1;   //mutux variable

// Array to store invalid ENTRIES
int arrofIndexes[9][9]={0};

pthread_t thread_array[12]={0};  //array of thraeds


// func to raed matrix from file..
void readFile(int output[9][9], string path){
	
	ifstream infile(path);
	string tempStr;
	int tempInt=0;
	int k=0;
	int count=0;
	while (!infile.eof() && count<9)
	{
		getline (infile, tempStr);
		int j=0;
		for (int i=0; i<tempStr.length()-1 && j<9 ; i++)
		{
			if (tempStr[i]!=' ')
			{
				output[k][j]=tempStr[i]-48;
				++j;
			}

		}
		++k;
		++count;
	}

}

// int Suduko[9][9];

// given array..
int Suduko[9][9]=
				{{6,2,5,4,3,9,1,8,1},
				 {5,5,9,7,2,7,2,3,3},
				 {8,3,6,6,1,4,2,9,7},
				 {1,4,3,8,6,5,7,2,9},
				 {1,5,8,2,4,7,3,9,1},
				 {7,6,2,3,9,1,2,5,2},
				 {3,7,1,9,5,6,7,4,2},
				 {4,9,6,8,8,2,5,7,3},
				 {2,8,5,4,7,3,9,1,6}};


///////=== FUNC to GET INVALID INDEXIS AND AVLUES in ALL ROWS=======////////////


void getIndeciesRow(int value,int OneDArr[],int size,int i,int arrofIndexes[][9]){
	
	for(int j=0;j<size;++j){
		if(OneDArr[j]==value || OneDArr[j]<1 || OneDArr[j]>9){
			arrofIndexes[i][j]=value;
			cout<<"\nThraed ID : "<<pthread_self()<<"\t"<<"Error value : Suduko["<<i<<"]["<<j<<"] = "<<value<<endl;
		}
	}
	
}

///////=== FUNC to GET INVALID INDEXIS AND AVLUES in ALL COLS=======////////////


void getIndeciesCol(int value,int OneDArr[],int size,int i,int arrofIndexes[][9]){
	for(int j=0;j<size;++j){
		if(OneDArr[j]==value || OneDArr[j]<1 || OneDArr[j]>9){
			arrofIndexes[j][i]=value;
			cout<<"\nThraed ID : "<<pthread_self()<<"\t"<<"Error value : Suduko["<<j<<"]["<<i<<"] = "<<value<<endl;
		}
	}
	
}

///////=== FUNC to GET INVALID INDEXIS AND AVLUES in GRID_1 to GRID_3=======////////////


void getIndeciesGrid_1(int value,int OneDArr[],int size,int arrofIndexes[][9]){
	
	for(int j=0;j<size;++j){
		if(j>=0 and j<3){
			if((OneDArr[j]==value || OneDArr[j]<1 || OneDArr[j]>9) and j==0){
				
				arrofIndexes[0][0]=value;
				cout<<"\nThraed ID : "<<pthread_self()<<"\t"<<"Error value : Suduko[0][0] = "<<value<<endl;
			}
			else if((OneDArr[j]==value || OneDArr[j]<1 || OneDArr[j]>9) and j==1){
				
				arrofIndexes[0][1]=value;
				cout<<"\nThraed ID : "<<pthread_self()<<"\t"<<"Error value : Suduko[0][1] = "<<value<<endl;
			}
			else if((OneDArr[j]==value || OneDArr[j]<1 || OneDArr[j]>9) and j==2){
				
				arrofIndexes[0][2]=value;
				cout<<"\nThraed ID : "<<pthread_self()<<"\t"<<"Error value : Suduko[0][2] = "<<value<<endl;
			}
		}else if(j>=3 and j<6){
			if((OneDArr[j]==value || OneDArr[j]<1 || OneDArr[j]>9) and j==3){
				
				arrofIndexes[1][0]=value;
				cout<<"\nThraed ID : "<<pthread_self()<<"\t"<<"Error value : Suduko[1][0] = "<<value<<endl;
			}
			else if((OneDArr[j]==value || OneDArr[j]<1 || OneDArr[j]>9) and j==4){
				
				arrofIndexes[1][1]=value;
				cout<<"\nThraed ID : "<<pthread_self()<<"\t"<<"Error value : Suduko[1][1] = "<<value<<endl;
			}
			else if((OneDArr[j]==value || OneDArr[j]<1 || OneDArr[j]>9) and j==5){
				
				arrofIndexes[1][2]=value;
				cout<<"\nThraed ID : "<<pthread_self()<<"\t"<<"Error value : Suduko[1][2] = "<<value<<endl;
			}
		}else if(j>=6 and j<9){
			if((OneDArr[j]==value || OneDArr[j]<1 || OneDArr[j]>9) and j==6){
				
				arrofIndexes[2][0]=value;
				cout<<"\nThraed ID : "<<pthread_self()<<"\t"<<"Error value : Suduko[2][0] = "<<value<<endl;
			}
			else if((OneDArr[j]==value || OneDArr[j]<1 || OneDArr[j]>9) and j==7){
				
				arrofIndexes[2][1]=value;
				cout<<"\nThraed ID : "<<pthread_self()<<"\t"<<"Error value : Suduko[2][1] = "<<value<<endl;
			}
			else if((OneDArr[j]==value || OneDArr[j]<1 || OneDArr[j]>9) and j==8){
				
				arrofIndexes[2][2]=value;
				cout<<"\nThraed ID : "<<pthread_self()<<"\t"<<"Error value : Suduko[2][2] = "<<value<<endl;
			}
		}
		
	}

}



void getIndeciesGrid_2(int value,int OneDArr[],int size,int arrofIndexes[][9]){
	

	for(int j=0;j<size;++j){
		if(j>=0 and j<3){
			if((OneDArr[j]==value || OneDArr[j]<1 || OneDArr[j]>9) and j==0){
				
				arrofIndexes[0][3]=value;
				cout<<"\nThraed ID : "<<pthread_self()<<"\t"<<"Error value : Suduko[0][3] = "<<value<<endl;
			}
			else if((OneDArr[j]==value || OneDArr[j]<1 || OneDArr[j]>9) and j==1){
				
				arrofIndexes[0][4]=value;
				cout<<"\nThraed ID : "<<pthread_self()<<"\t"<<"Error value : Suduko[0][4] = "<<value<<endl;
			}
			else if((OneDArr[j]==value || OneDArr[j]<1 || OneDArr[j]>9) and j==2){
				
				arrofIndexes[0][5]=value;
				cout<<"\nThraed ID : "<<pthread_self()<<"\t"<<"Error value : Suduko[0][5] = "<<value<<endl;
			}
		}else if(j>=3 and j<6){
			if((OneDArr[j]==value || OneDArr[j]<1 || OneDArr[j]>9) and j==3){
				
				arrofIndexes[1][3]=value;
				cout<<"\nThraed ID : "<<pthread_self()<<"\t"<<"Error value : Suduko[1][3] = "<<value<<endl;
			}
			else if((OneDArr[j]==value || OneDArr[j]<1 || OneDArr[j]>9) and j==4){
				
				arrofIndexes[1][4]=value;
				cout<<"\nThraed ID : "<<pthread_self()<<"\t"<<"Error value : Suduko[1][4] = "<<value<<endl;
			}
			else if((OneDArr[j]==value || OneDArr[j]<1 || OneDArr[j]>9) and j==5){
				
				arrofIndexes[1][5]=value;
				cout<<"\nThraed ID : "<<pthread_self()<<"\t"<<"Error value : Suduko[1][5] = "<<value<<endl;
			}
		}else if(j>=6 and j<9){
			if((OneDArr[j]==value || OneDArr[j]<1 || OneDArr[j]>9) and j==6){
				
				arrofIndexes[2][3]=value;
				cout<<"\nThraed ID : "<<pthread_self()<<"\t"<<"Error value : Suduko[2][3] = "<<value<<endl;
			}
			else if((OneDArr[j]==value || OneDArr[j]<1 || OneDArr[j]>9) and j==7){
				
				arrofIndexes[2][4]=value;
				cout<<"\nThraed ID : "<<pthread_self()<<"\t"<<"Error value : Suduko[2][4] = "<<value<<endl;
			}
			else if((OneDArr[j]==value || OneDArr[j]<1 || OneDArr[j]>9) and j==8){
				
				arrofIndexes[2][5]=value;
				cout<<"\nThraed ID : "<<pthread_self()<<"\t"<<"Error value : Suduko[2][5] = "<<value<<endl;
			}
		}
		
	}
	
}



void getIndeciesGrid_3(int value,int OneDArr[],int size,int arrofIndexes[][9]){
	
	for(int j=0;j<size;++j){
		if(j>=0 and j<3){
			if((OneDArr[j]==value || OneDArr[j]<1 || OneDArr[j]>9) and j==0){
				
				arrofIndexes[0][6]=value;
				cout<<"\nThraed ID : "<<pthread_self()<<"\t"<<"Error value : Suduko[0][6] = "<<value<<endl;
			}
			else if((OneDArr[j]==value || OneDArr[j]<1 || OneDArr[j]>9) and j==1){
				
				arrofIndexes[0][7]=value;
				cout<<"\nThraed ID : "<<pthread_self()<<"\t"<<"Error value : Suduko[0][7] = "<<value<<endl;
			}
			else if((OneDArr[j]==value || OneDArr[j]<1 || OneDArr[j]>9) and j==2){
				
				arrofIndexes[0][8]=value;
				cout<<"\nThraed ID : "<<pthread_self()<<"\t"<<"Error value : Suduko[0][8] = "<<value<<endl;
			}
		}else if(j>=3 and j<6){
			if((OneDArr[j]==value || OneDArr[j]<1 || OneDArr[j]>9) and j==3){
				
				arrofIndexes[1][6]=value;
				cout<<"\nThraed ID : "<<pthread_self()<<"\t"<<"Error value : Suduko[1][6] = "<<value<<endl;
			}
			else if((OneDArr[j]==value || OneDArr[j]<1 || OneDArr[j]>9) and j==4){
				
				arrofIndexes[1][7]=value;
				cout<<"\nThraed ID : "<<pthread_self()<<"\t"<<"Error value : Suduko[1][7] = "<<value<<endl;
			}
			else if((OneDArr[j]==value || OneDArr[j]<1 || OneDArr[j]>9) and j==5){
				
				arrofIndexes[1][8]=value;
				cout<<"\nThraed ID : "<<pthread_self()<<"\t"<<"Error value : Suduko[1][8] = "<<value<<endl;
			}
		}else if(j>=6 and j<9){
			if((OneDArr[j]==value || OneDArr[j]<1 || OneDArr[j]>9) and j==6){
				
				arrofIndexes[2][6]=value;
				cout<<"\nThraed ID : "<<pthread_self()<<"\t"<<"Error value : Suduko[2][6] = "<<value<<endl;
			}
			else if((OneDArr[j]==value || OneDArr[j]<1 || OneDArr[j]>9) and j==7){
				
				arrofIndexes[2][7]=value;
				cout<<"\nThraed ID : "<<pthread_self()<<"\t"<<"Error value : Suduko[2][7] = "<<value<<endl;
			}
			else if((OneDArr[j]==value || OneDArr[j]<1 || OneDArr[j]>9) and j==8){
				
				arrofIndexes[2][8]=value;
				cout<<"\nThraed ID : "<<pthread_self()<<"\t"<<"Error value : Suduko[2][8] = "<<value<<endl;
			}
		}
		
	}
	
}


///////=== FUNC to GET INVALID INDEXIS AND AVLUES in GRID_4 to GRID_6=======////////////



void getIndeciesGrid_4(int value,int OneDArr[],int size,int arrofIndexes[][9]){
	

	for(int j=0;j<size;++j){
		if(j>=0 and j<3){
			if((OneDArr[j]==value || OneDArr[j]<1 || OneDArr[j]>9) and j==0){
				
				arrofIndexes[3][0]=value;
				cout<<"\nThraed ID : "<<pthread_self()<<"\t"<<"Error value : Suduko[3][0] = "<<value<<endl;
			}
			else if((OneDArr[j]==value || OneDArr[j]<1 || OneDArr[j]>9) and j==1){
				
				arrofIndexes[3][1]=value;
				cout<<"\nThraed ID : "<<pthread_self()<<"\t"<<"Error value : Suduko[3][1] = "<<value<<endl;
			}
			else if((OneDArr[j]==value || OneDArr[j]<1 || OneDArr[j]>9) and j==2){
				
				arrofIndexes[3][2]=value;
				cout<<"\nThraed ID : "<<pthread_self()<<"\t"<<"Error value : Suduko[3][2] = "<<value<<endl;
			}
		}else if(j>=3 and j<6){
			if((OneDArr[j]==value || OneDArr[j]<1 || OneDArr[j]>9) and j==3){
				
				arrofIndexes[4][0]=value;
				cout<<"\nThraed ID : "<<pthread_self()<<"\t"<<"Error value : Suduko[4][0] = "<<value<<endl;
			}
			else if((OneDArr[j]==value || OneDArr[j]<1 || OneDArr[j]>9) and j==4){
				
				arrofIndexes[4][1]=value;
				cout<<"\nThraed ID : "<<pthread_self()<<"\t"<<"Error value : Suduko[4][1] = "<<value<<endl;
			}
			else if((OneDArr[j]==value || OneDArr[j]<1 || OneDArr[j]>9) and j==5){
				
				arrofIndexes[4][2]=value;
				cout<<"\nThraed ID : "<<pthread_self()<<"\t"<<"Error value : Suduko[4][2] = "<<value<<endl;
			}
		}else if(j>=6 and j<9){
			if((OneDArr[j]==value || OneDArr[j]<1 || OneDArr[j]>9) and j==6){
				
				arrofIndexes[5][0]=value;
				cout<<"\nThraed ID : "<<pthread_self()<<"\t"<<"Error value : Suduko[5][0] = "<<value<<endl;
			}
			else if((OneDArr[j]==value || OneDArr[j]<1 || OneDArr[j]>9) and j==7){
				
				arrofIndexes[5][1]=value;
				cout<<"\nThraed ID : "<<pthread_self()<<"\t"<<"Error value : Suduko[5][1] = "<<value<<endl;
			}
			else if((OneDArr[j]==value || OneDArr[j]<1 || OneDArr[j]>9) and j==8){
				
				arrofIndexes[5][2]=value;
				cout<<"\nThraed ID : "<<pthread_self()<<"\t"<<"Error value : Suduko[5][2] = "<<value<<endl;
			}
		}
		
	}


}



void getIndeciesGrid_5(int value,int OneDArr[],int size,int arrofIndexes[][9]){
	

	for(int j=0;j<size;++j){
		if(j>=0 and j<3){
			if((OneDArr[j]==value || OneDArr[j]<1 || OneDArr[j]>9) and j==0){
				
				arrofIndexes[3][3]=value;
				cout<<"\nThraed ID : "<<pthread_self()<<"\t"<<"Error value : Suduko[3][3] = "<<value<<endl;
			}
			else if((OneDArr[j]==value || OneDArr[j]<1 || OneDArr[j]>9) and j==1){
				
				arrofIndexes[3][4]=value;
				cout<<"\nThraed ID : "<<pthread_self()<<"\t"<<"Error value : Suduko[3][4] = "<<value<<endl;
			}
			else if((OneDArr[j]==value || OneDArr[j]<1 || OneDArr[j]>9) and j==2){
				
				arrofIndexes[3][5]=value;
				cout<<"\nThraed ID : "<<pthread_self()<<"\t"<<"Error value : Suduko[3][5] = "<<value<<endl;
			}
		}else if(j>=3 and j<6){
			if((OneDArr[j]==value || OneDArr[j]<1 || OneDArr[j]>9) and j==3){
				
				arrofIndexes[4][3]=value;
				cout<<"\nThraed ID : "<<pthread_self()<<"\t"<<"Error value : Suduko[4][3] = "<<value<<endl;
			}
			else if((OneDArr[j]==value || OneDArr[j]<1 || OneDArr[j]>9) and j==4){
				
				arrofIndexes[4][4]=value;
				cout<<"\nThraed ID : "<<pthread_self()<<"\t"<<"Error value : Suduko[4][4] = "<<value<<endl;
			}
			else if((OneDArr[j]==value || OneDArr[j]<1 || OneDArr[j]>9) and j==5){
				
				arrofIndexes[4][5]=value;
				cout<<"\nThraed ID : "<<pthread_self()<<"\t"<<"Error value : Suduko[4][5] = "<<value<<endl;
			}
		}else if(j>=6 and j<9){
			if((OneDArr[j]==value || OneDArr[j]<1 || OneDArr[j]>9) and j==6){
				
				arrofIndexes[5][3]=value;
				cout<<"\nThraed ID : "<<pthread_self()<<"\t"<<"Error value : Suduko[5][3] = "<<value<<endl;
			}
			else if((OneDArr[j]==value || OneDArr[j]<1 || OneDArr[j]>9) and j==7){
				
				arrofIndexes[5][4]=value;
				cout<<"\nThraed ID : "<<pthread_self()<<"\t"<<"Error value : Suduko[5][4] = "<<value<<endl;
			}
			else if((OneDArr[j]==value || OneDArr[j]<1 || OneDArr[j]>9) and j==8){
				
				arrofIndexes[5][5]=value;
				cout<<"\nThraed ID : "<<pthread_self()<<"\t"<<"Error value : Suduko[5][5] = "<<value<<endl;
			}
		}
		
	}
	
}



void getIndeciesGrid_6(int value,int OneDArr[],int size,int arrofIndexes[][9]){


	for(int j=0;j<size;++j){
		if(j>=0 and j<3){
			if((OneDArr[j]==value || OneDArr[j]<1 || OneDArr[j]>9) and j==0){
				
				arrofIndexes[3][6]=value;
				cout<<"\nThraed ID : "<<pthread_self()<<"\t"<<"Error value : Suduko[3][6] = "<<value<<endl;
			}
			else if((OneDArr[j]==value || OneDArr[j]<1 || OneDArr[j]>9) and j==1){
				
				arrofIndexes[3][7]=value;
				cout<<"\nThraed ID : "<<pthread_self()<<"\t"<<"Error value : Suduko[3][7] = "<<value<<endl;
			}
			else if((OneDArr[j]==value || OneDArr[j]<1 || OneDArr[j]>9) and j==2){
				
				arrofIndexes[3][8]=value;
				cout<<"\nThraed ID : "<<pthread_self()<<"\t"<<"Error value : Suduko[3][8] = "<<value<<endl;
			}
		}else if(j>=3 and j<6){
			if((OneDArr[j]==value || OneDArr[j]<1 || OneDArr[j]>9) and j==3){
				
				arrofIndexes[4][6]=value;
				cout<<"\nThraed ID : "<<pthread_self()<<"\t"<<"Error value : Suduko[4][6] = "<<value<<endl;
			}
			else if((OneDArr[j]==value || OneDArr[j]<1 || OneDArr[j]>9) and j==4){
				
				arrofIndexes[4][7]=value;
				cout<<"\nThraed ID : "<<pthread_self()<<"\t"<<"Error value : Suduko[4][7] = "<<value<<endl;
			}
			else if((OneDArr[j]==value || OneDArr[j]<1 || OneDArr[j]>9) and j==5){
				
				arrofIndexes[4][8]=value;
				cout<<"\nThraed ID : "<<pthread_self()<<"\t"<<"Error value : Suduko[4][8] = "<<value<<endl;
			}
		}else if(j>=6 and j<9){
			if((OneDArr[j]==value || OneDArr[j]<1 || OneDArr[j]>9) and j==6){
				
				arrofIndexes[5][6]=value;
				cout<<"\nThraed ID : "<<pthread_self()<<"\t"<<"Error value : Suduko[5][6] = "<<value<<endl;
			}
			else if((OneDArr[j]==value || OneDArr[j]<1 || OneDArr[j]>9) and j==7){
				
				arrofIndexes[5][7]=value;
				cout<<"\nThraed ID : "<<pthread_self()<<"\t"<<"Error value : Suduko[5][7] = "<<value<<endl;
			}
			else if((OneDArr[j]==value || OneDArr[j]<1 || OneDArr[j]>9) and j==8){
				
				arrofIndexes[5][8]=value;
				cout<<"\nThraed ID : "<<pthread_self()<<"\t"<<"Error value : Suduko[5][8] = "<<value<<endl;
			}
		}
		
	}

	
}



///////=== FUNC to GET INVALID INDEXIS AND AVLUES in GRID_7 to GRID_9=======////////////





void getIndeciesGrid_7(int value,int OneDArr[],int size,int arrofIndexes[][9]){
	

	for(int j=0;j<size;++j){
		if(j>=0 and j<3){
			if((OneDArr[j]==value || OneDArr[j]<1 || OneDArr[j]>9) and j==0){
				
				arrofIndexes[6][0]=value;
				cout<<"\nThraed ID : "<<pthread_self()<<"\t"<<"Error value : Suduko[6][0] = "<<value<<endl;
			}
			else if((OneDArr[j]==value || OneDArr[j]<1 || OneDArr[j]>9) and j==1){
				
				arrofIndexes[6][1]=value;
				cout<<"\nThraed ID : "<<pthread_self()<<"\t"<<"Error value : Suduko[6][1] = "<<value<<endl;
			}
			else if((OneDArr[j]==value || OneDArr[j]<1 || OneDArr[j]>9) and j==2){
				
				arrofIndexes[6][2]=value;
				cout<<"\nThraed ID : "<<pthread_self()<<"\t"<<"Error value : Suduko[6][2] = "<<value<<endl;
			}
		}else if(j>=3 and j<6){
			if((OneDArr[j]==value || OneDArr[j]<1 || OneDArr[j]>9) and j==3){
				
				arrofIndexes[7][0]=value;
				cout<<"\nThraed ID : "<<pthread_self()<<"\t"<<"Error value : Suduko[7][0] = "<<value<<endl;
			}
			else if((OneDArr[j]==value || OneDArr[j]<1 || OneDArr[j]>9) and j==4){
				
				arrofIndexes[7][1]=value;
				cout<<"\nThraed ID : "<<pthread_self()<<"\t"<<"Error value : Suduko[7][1] = "<<value<<endl;
			}
			else if((OneDArr[j]==value || OneDArr[j]<1 || OneDArr[j]>9) and j==5){
				
				arrofIndexes[7][2]=value;
				cout<<"\nThraed ID : "<<pthread_self()<<"\t"<<"Error value : Suduko[7][2] = "<<value<<endl;
			}
		}else if(j>=6 and j<9){
			if((OneDArr[j]==value || OneDArr[j]<1 || OneDArr[j]>9) and j==6){
				
				arrofIndexes[8][0]=value;
				cout<<"\nThraed ID : "<<pthread_self()<<"\t"<<"Error value : Suduko[8][0] = "<<value<<endl;
			}
			else if((OneDArr[j]==value || OneDArr[j]<1 || OneDArr[j]>9) and j==7){
				
				arrofIndexes[8][1]=value;
				cout<<"\nThraed ID : "<<pthread_self()<<"\t"<<"Error value : Suduko[8][1] = "<<value<<endl;
			}
			else if((OneDArr[j]==value || OneDArr[j]<1 || OneDArr[j]>9) and j==8){
				
				arrofIndexes[8][2]=value;
				cout<<"\nThraed ID : "<<pthread_self()<<"\t"<<"Error value : Suduko[8][2] = "<<value<<endl;
			}
		}
		
	}


}



void getIndeciesGrid_8(int value,int OneDArr[],int size,int arrofIndexes[][9]){
	

	for(int j=0;j<size;++j){
		if(j>=0 and j<3){
			if((OneDArr[j]==value || OneDArr[j]<1 || OneDArr[j]>9) and j==0){
				
				arrofIndexes[6][3]=value;
				cout<<"\nThraed ID : "<<pthread_self()<<"\t"<<"Error value : Suduko[6][3] = "<<value<<endl;
			}
			else if((OneDArr[j]==value || OneDArr[j]<1 || OneDArr[j]>9) and j==1){
				
				arrofIndexes[6][4]=value;
				cout<<"\nThraed ID : "<<pthread_self()<<"\t"<<"Error value : Suduko[6][4] = "<<value<<endl;
			}
			else if((OneDArr[j]==value || OneDArr[j]<1 || OneDArr[j]>9) and j==2){
				
				arrofIndexes[6][5]=value;
				cout<<"\nThraed ID : "<<pthread_self()<<"\t"<<"Error value : Suduko[6][5] = "<<value<<endl;
			}
		}else if(j>=3 and j<6){
			if((OneDArr[j]==value || OneDArr[j]<1 || OneDArr[j]>9) and j==3){
				
				arrofIndexes[7][3]=value;
				cout<<"\nThraed ID : "<<pthread_self()<<"\t"<<"Error value : Suduko[7][3] = "<<value<<endl;
			}
			else if((OneDArr[j]==value || OneDArr[j]<1 || OneDArr[j]>9) and j==4){
				
				arrofIndexes[7][4]=value;
				cout<<"\nThraed ID : "<<pthread_self()<<"\t"<<"Error value : Suduko[7][4] = "<<value<<endl;
			}
			else if((OneDArr[j]==value || OneDArr[j]<1 || OneDArr[j]>9) and j==5){
				
				arrofIndexes[7][5]=value;
				cout<<"\nThraed ID : "<<pthread_self()<<"\t"<<"Error value : Suduko[7][5] = "<<value<<endl;
			}
		}else if(j>=6 and j<9){
			if((OneDArr[j]==value || OneDArr[j]<1 || OneDArr[j]>9) and j==6){
				
				arrofIndexes[8][3]=value;
				cout<<"\nThraed ID : "<<pthread_self()<<"\t"<<"Error value : Suduko[8][3] = "<<value<<endl;
			}
			else if((OneDArr[j]==value || OneDArr[j]<1 || OneDArr[j]>9) and j==7){
				
				arrofIndexes[8][4]=value;
				cout<<"\nThraed ID : "<<pthread_self()<<"\t"<<"Error value : Suduko[8][4] = "<<value<<endl;
			}
			else if((OneDArr[j]==value || OneDArr[j]<1 || OneDArr[j]>9) and j==8){
				
				arrofIndexes[8][5]=value;
				cout<<"\nThraed ID : "<<pthread_self()<<"\t"<<"Error value : Suduko[8][5] = "<<value<<endl;
			}
		}
		
	}

}



void getIndeciesGrid_9(int value,int OneDArr[],int size,int arrofIndexes[][9]){
	

	for(int j=0;j<size;++j){
		if(j>=0 and j<3){
			if((OneDArr[j]==value || OneDArr[j]<1 || OneDArr[j]>9) and j==0){
				
				arrofIndexes[6][6]=value;
				cout<<"\nThraed ID : "<<pthread_self()<<"\t"<<"Error value : Suduko[6][6] = "<<value<<endl;
			}
			else if((OneDArr[j]==value || OneDArr[j]<1 || OneDArr[j]>9) and j==1){
				
				arrofIndexes[6][7]=value;
				cout<<"\nThraed ID : "<<pthread_self()<<"\t"<<"Error value : Suduko[6][7] = "<<value<<endl;
			}
			else if((OneDArr[j]==value || OneDArr[j]<1 || OneDArr[j]>9) and j==2){
				
				arrofIndexes[6][8]=value;
				cout<<"\nThraed ID : "<<pthread_self()<<"\t"<<"Error value : Suduko[6][8] = "<<value<<endl;
			}
		}else if(j>=3 and j<6){
			if((OneDArr[j]==value || OneDArr[j]<1 || OneDArr[j]>9) and j==3){
				
				arrofIndexes[7][6]=value;
				cout<<"\nThraed ID : "<<pthread_self()<<"\t"<<"Error value : Suduko[7][6] = "<<value<<endl;
			}
			else if((OneDArr[j]==value || OneDArr[j]<1 || OneDArr[j]>9) and j==4){
				
				arrofIndexes[7][7]=value;
				cout<<"\nThraed ID : "<<pthread_self()<<"\t"<<"Error value : Suduko[7][7] = "<<value<<endl;
			}
			else if((OneDArr[j]==value || OneDArr[j]<1 || OneDArr[j]>9) and j==5){
				
				arrofIndexes[7][8]=value;
				cout<<"\nThraed ID : "<<pthread_self()<<"\t"<<"Error value : Suduko[7][8] = "<<value<<endl;
			}
		}else if(j>=6 and j<9){
			if((OneDArr[j]==value || OneDArr[j]<1 || OneDArr[j]>9) and j==6){
				
				arrofIndexes[8][6]=value;
				cout<<"\nThraed ID : "<<pthread_self()<<"\t"<<"Error value : Suduko[8][6] = "<<value<<endl;
			}
			else if((OneDArr[j]==value || OneDArr[j]<1 || OneDArr[j]>9) and j==7){
				
				arrofIndexes[8][7]=value;
				cout<<"\nThraed ID : "<<pthread_self()<<"\t"<<"Error value : Suduko[8][7] = "<<value<<endl;
			}
			else if((OneDArr[j]==value || OneDArr[j]<1 || OneDArr[j]>9) and j==8){
				
				arrofIndexes[8][8]=value;
				cout<<"\nThraed ID : "<<pthread_self()<<"\t"<<"Error value : Suduko[8][8] = "<<value<<endl;
			}
		}
		
	}

	
}



////////////////////====FUNC TO CEHCK VALUES IN RANGE (1-9)====//////////////////////////

bool checkInRange(int arr[],int size){
	int var=0;
	for(int i=0;i<size;++i){
		if(arr[i]>=1 and arr[i]<=9){
			var++;
		}
	}
	if(var==size){
		cout<<"\nin range of 1 and 9"<<endl;
		return true;
	}

	cout<<"\nnot in range"<<endl;
	return false;
}

///////////////====== FUNC to CHECK REPEAT VALUES in ALL ROWS=======////////////////////


void findRepeat_Row(int arr[],int size,int i){


	// if(checkInRange(arr,9)==true){
		cout<<"elements are consecutive\n\n";
		int temp[9]={0};
		for(int j=0;j<9;++j){
			if(temp[arr[j]-1]==0){
				temp[arr[j]-1]=1;
			}else{
				
	          	int value=arr[j];
	          	getIndeciesRow(value,arr,size,i,arrofIndexes);
			}
			
		}
	// }
}

///////////////====== FUNC to CHECK REPEAT VALUES in ALL COLS=======////////////////////


void findRepeat_Col(int arr[],int size,int i){

	

	// if(checkInRange(arr,9)==true){
		cout<<"elements are consecutive\n\n";
		int temp[9]={0};
		for(int j=0;j<9;++j){
			if(temp[arr[j]-1]==0){
				temp[arr[j]-1]=1;
			}else{
				
	          	int value=arr[j];
	          	getIndeciesCol(value,arr,size,i,arrofIndexes);
			}
			
		}
	// }

	
}

///////////====== FUNC to CHECK REPEAT VALUES in GRID_1 to GRID_3=======///////////////


void findRepeat_Grid_1(int arr[],int size){
	// if(checkInRange(arr,9)==true){
		cout<<"elements are consecutive\n\n";
		int temp[9]={0};
		for(int j=0;j<9;++j){
			if(temp[arr[j]-1]==0){
				temp[arr[j]-1]=1;
			}else{
         		int value=-1;
          		
	          	if(j>=0 and j<3){
	          		
	          		value=arr[j];
	          		getIndeciesGrid_1(value,arr,size,arrofIndexes);
	          	}else if(j>=3 and j<6){
	          		
	          		value=arr[j];
	          		getIndeciesGrid_1(value,arr,size,arrofIndexes);
	          	}else if(j>=6 and j<9){
	          		
	          		value=arr[j];
	          		getIndeciesGrid_1(value,arr,size,arrofIndexes);
	          	}
			}
			
		}
	// }
}




void findRepeat_Grid_2(int arr[],int size){
	// if(checkInRange(arr,9)==true){
		cout<<"elements are consecutive\n\n";
		int temp[9]={0};
		for(int j=0;j<9;++j){
			if(temp[arr[j]-1]==0){
				temp[arr[j]-1]=1;
			}else{
         		int value=-1;
          		
	          	if(j>=0 and j<3){
	          		
	          		value=arr[j];
	          		getIndeciesGrid_2(value,arr,size,arrofIndexes);
	          	}else if(j>=3 and j<6){
	          		
	          		value=arr[j];
	          		getIndeciesGrid_2(value,arr,size,arrofIndexes);
	          	}else if(j>=6 and j<9){
	          		
	          		value=arr[j];
	          		getIndeciesGrid_2(value,arr,size,arrofIndexes);
	          	}
			}
			
		}
	// }
}



void findRepeat_Grid_3(int arr[],int size){
	// if(checkInRange(arr,9)==true){
		cout<<"elements are consecutive\n\n";
		int temp[9]={0};
		for(int j=0;j<9;++j){
			if(temp[arr[j]-1]==0){
				temp[arr[j]-1]=1;
			}else{
         		int value=-1;
          		
	          	if(j>=0 and j<3){
	          		
	          		value=arr[j];
	          		getIndeciesGrid_3(value,arr,size,arrofIndexes);
	          	}else if(j>=3 and j<6){
	          		
	          		value=arr[j];
	          		getIndeciesGrid_3(value,arr,size,arrofIndexes);
	          	}else if(j>=6 and j<9){
	          		
	          		value=arr[j];
	          		getIndeciesGrid_3(value,arr,size,arrofIndexes);
	          	}
			}
			
		}
	// }
}

///////////====== FUNC to CHECK REPEAT VALUES in GRID_4 to GRID_6=======///////////////



void findRepeat_Grid_4(int arr[],int size){
	// if(checkInRange(arr,9)==true){
		cout<<"elements are consecutive\n\n";
		int temp[9]={0};
		for(int j=0;j<9;++j){
			if(temp[arr[j]-1]==0){
				temp[arr[j]-1]=1;
			}else{
         		int value=-1;
          		
	          	if(j>=0 and j<3){
	          		
	          		value=arr[j];
	          		getIndeciesGrid_4(value,arr,size,arrofIndexes);
	          	}else if(j>=3 and j<6){
	          		
	          		value=arr[j];
	          		getIndeciesGrid_4(value,arr,size,arrofIndexes);
	          	}else if(j>=6 and j<9){
	          		
	          		value=arr[j];
	          		getIndeciesGrid_4(value,arr,size,arrofIndexes);
	          	}
			}
			
		}
	// }
}




void findRepeat_Grid_5(int arr[],int size){
	// if(checkInRange(arr,9)==true){
		cout<<"elements are consecutive\n\n";
		int temp[9]={0};
		for(int j=0;j<9;++j){
			if(temp[arr[j]-1]==0){
				temp[arr[j]-1]=1;
			}else{
         		int value=-1;
          		
	          	if(j>=0 and j<3){
	          		
	          		value=arr[j];
	          		getIndeciesGrid_5(value,arr,size,arrofIndexes);
	          	}else if(j>=3 and j<6){
	          		
	          		value=arr[j];
	          		getIndeciesGrid_5(value,arr,size,arrofIndexes);
	          	}else if(j>=6 and j<9){
	          		
	          		value=arr[j];
	          		getIndeciesGrid_5(value,arr,size,arrofIndexes);
	          	}
			}
			
		}
	// }
}



void findRepeat_Grid_6(int arr[],int size){
	// if(checkInRange(arr,9)==true){
		cout<<"elements are consecutive\n\n";
		int temp[9]={0};
		for(int j=0;j<9;++j){
			if(temp[arr[j]-1]==0){
				temp[arr[j]-1]=1;
			}else{
         		int value=-1;
          		
	          	if(j>=0 and j<3){
	          		
	          		value=arr[j];
	          		getIndeciesGrid_6(value,arr,size,arrofIndexes);
	          	}else if(j>=3 and j<6){
	          		
	          		value=arr[j];
	          		getIndeciesGrid_6(value,arr,size,arrofIndexes);
	          	}else if(j>=6 and j<9){
	          		
	          		value=arr[j];
	          		getIndeciesGrid_6(value,arr,size,arrofIndexes);
	          	}
			}
			
		}
	// }
}


///////////====== FUNC to CHECK REPEAT VALUES in GRID_7 to GRID_9=======///////////////



void findRepeat_Grid_7(int arr[],int size){
	// if(checkInRange(arr,9)==true){
		cout<<"elements are consecutive\n\n";
		int temp[9]={0};
		for(int j=0;j<9;++j){
			if(temp[arr[j]-1]==0){
				temp[arr[j]-1]=1;
			}else{
         		int value=-1;
          		
	          	if(j>=0 and j<3){
	          		
	          		value=arr[j];
	          		getIndeciesGrid_7(value,arr,size,arrofIndexes);
	          	}else if(j>=3 and j<6){
	          		
	          		value=arr[j];
	          		getIndeciesGrid_7(value,arr,size,arrofIndexes);
	          	}else if(j>=6 and j<9){
	          		
	          		value=arr[j];
	          		getIndeciesGrid_7(value,arr,size,arrofIndexes);
	          	}
			}
			
		}
	// }
}




void findRepeat_Grid_8(int arr[],int size){
	// if(checkInRange(arr,9)==true){
		cout<<"elements are consecutive\n\n";
		int temp[9]={0};
		for(int j=0;j<9;++j){
			if(temp[arr[j]-1]==0){
				temp[arr[j]-1]=1;
			}else{
         		int value=-1;
          		
	          	if(j>=0 and j<3){
	          		
	          		value=arr[j];
	          		getIndeciesGrid_8(value,arr,size,arrofIndexes);
	          	}else if(j>=3 and j<6){
	          		
	          		value=arr[j];
	          		getIndeciesGrid_8(value,arr,size,arrofIndexes);
	          	}else if(j>=6 and j<9){
	          		
	          		value=arr[j];
	          		getIndeciesGrid_8(value,arr,size,arrofIndexes);
	          	}
			}
			
		}
	// }
}



void findRepeat_Grid_9(int arr[],int size){
	// if(checkInRange(arr,9)==true){
		cout<<"elements are consecutive\n\n";
		int temp[9]={0};
		for(int j=0;j<9;++j){
			if(temp[arr[j]-1]==0){
				temp[arr[j]-1]=1;
			}else{
         		int value=-1;
          		
	          	if(j>=0 and j<3){
	          		
	          		value=arr[j];
	          		getIndeciesGrid_9(value,arr,size,arrofIndexes);
	          	}else if(j>=3 and j<6){
	          		
	          		value=arr[j];
	          		getIndeciesGrid_9(value,arr,size,arrofIndexes);
	          	}else if(j>=6 and j<9){
	          		
	          		value=arr[j];
	          		getIndeciesGrid_9(value,arr,size,arrofIndexes);
	          	}
			}
			
		}
	// }
}

// \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\ 

///////////////////////======THREAD FUNC for ROW THREAD=======//////////////////////


void *row_thraed(void *args){
	int var=16;
	while(var!=0){
		var=pthread_mutex_trylock (&mutex_1);
	}
	pthread_t t_id=pthread_self();
	

	printf("\nThraed ID : %ld mutux error : %d\n",t_id,var);

	cout<<"Row Thraed started\n";

	int n=9;
	int temp[9]={-1};
	
	for(int i=0;i<n;++i){
		for(int j=0;j<n;++j){
			cout<<Suduko[i][j]<<' ';
			temp[j]=Suduko[i][j];
		} 
	    findRepeat_Row(temp, n,i);
	}

	

	cout<<"Row Thraed Ending\n";

	pthread_mutex_unlock (&mutex_1);
	pthread_exit(NULL);
}

///////////////////////======THREAD FUNC for COL THREAD=======//////////////////////

void *col_thraed(void *args){

	int var=16;
	while(var!=0){
		var=pthread_mutex_trylock (&mutex_1);
	}
	pthread_t t_id=pthread_self();
	

	printf("\nThraed ID : %ld mutux error : %d\n",t_id,var);

	cout<<"Col Thraed started\n";

	
	int n=9;
	int temp[9]={-1};
	
	for(int i=0;i<n;++i){
		for(int j=0;j<n;++j){
			cout<<Suduko[j][i]<<' ';
			temp[j]=Suduko[j][i];
		} 
	    findRepeat_Col(temp, n,i);
	}

	cout<<"Col Thraed Ending\n";

	pthread_mutex_unlock (&mutex_1);
	pthread_exit(NULL);
}

//////////////////////////////Thread FUNCTIONS GRID_1 to GRID_3////////////////////

void *Grid_1_thraed(void *args){
	int var=16;
	while(var!=0){
		var=pthread_mutex_trylock (&mutex_1);
	}
	pthread_t t_id=pthread_self();


	printf("\nThraed ID : %ld mutux error : %d\n",t_id,var);

	cout<<"Grid_1 Thraed started\n";

	

	int temp[9]={-1};
	
	for(int i=0,k=0;i<3;++i){
		for(int j=0;j<3;++j,++k){
			cout<<Suduko[i][j]<<' ';

			temp[k]=Suduko[i][j];
		}
		cout<<endl;
	}

	int n = sizeof(temp); 
    findRepeat_Grid_1(temp,n);
		cout<<endl;

		

	cout<<"Grid_1 Thraed Ending\n";
	pthread_mutex_unlock (&mutex_1);
	pthread_exit(NULL);
}


void *Grid_2_thraed(void *args){
	int var=16;
	while(var!=0){
		var=pthread_mutex_trylock (&mutex_1);
	}
	pthread_t t_id=pthread_self();
	

	printf("\nThraed ID : %ld mutux error : %d\n",t_id,var);
	cout<<"Grid_2 Thraed started\n";

	

	
	int temp[9]={-1};
	
	for(int i=0,k=0;i<3;++i){
		for(int j=3;j<6;++j,++k){
			cout<<Suduko[i][j]<<' ';

			temp[k]=Suduko[i][j];
		}
		cout<<endl;
	}

	int n = sizeof(temp); 
    findRepeat_Grid_2(temp,n);
		cout<<endl;

		

	cout<<"Grid_2 Thraed Ending\n";
	pthread_mutex_unlock (&mutex_1);
	pthread_exit(NULL);
}

void *Grid_3_thraed(void *args){
	int var=16;
	while(var!=0){
		var=pthread_mutex_trylock (&mutex_1);
	}
	pthread_t t_id=pthread_self();


	printf("\nThraed ID : %ld mutux error : %d\n",t_id,var);

	cout<<"Grid_3 Thraed started\n";

	

	
	int temp[9]={-1};
	
	for(int i=0,k=0;i<3;++i){
		for(int j=6;j<9;++j,++k){
			cout<<Suduko[i][j]<<' ';

			temp[k]=Suduko[i][j];
		}
		cout<<endl;
	}

	int n = sizeof(temp); 
    findRepeat_Grid_3(temp,n);
		cout<<endl;


		

	cout<<"Grid_3 Thraed Ending\n";
	pthread_mutex_unlock (&mutex_1);
	pthread_exit(NULL);
}

/////////////////////////////Thread FUNCTIONS GRID_4 to GRID_6///////////////////////



void *Grid_4_thraed(void *args){
	int var=16;
	while(var!=0){
		var=pthread_mutex_trylock (&mutex_1);
	}
	pthread_t t_id=pthread_self();
	

	printf("\nThraed ID : %ld mutux error : %d\n",t_id,var);

	cout<<"Grid_4 Thraed started\n";



	int temp[9]={-1};
	
	for(int i=3,k=0;i<6;++i){
		for(int j=0;j<3;++j,++k){
			cout<<Suduko[i][j]<<' ';

			temp[k]=Suduko[i][j];
		}
		cout<<endl;
	}

	int n = sizeof(temp); 
    findRepeat_Grid_4(temp,n);
		cout<<endl;




	cout<<"Grid_4 Thraed Ending\n";
	pthread_mutex_unlock (&mutex_1);
	pthread_exit(NULL);
}


void *Grid_5_thraed(void *args){
	int var=16;
	while(var!=0){
		var=pthread_mutex_trylock (&mutex_1);
	}
	pthread_t t_id=pthread_self();
	

	printf("\nThraed ID : %ld mutux error : %d\n",t_id,var);

	cout<<"Grid_5 Thraed started\n";



	int temp[9]={-1};
	
	for(int i=3,k=0;i<6;++i){
		for(int j=3;j<6;++j,++k){
			cout<<Suduko[i][j]<<' ';

			temp[k]=Suduko[i][j];
		}
		cout<<endl;
	}

	int n = sizeof(temp); 
    findRepeat_Grid_5(temp,n);
		cout<<endl;




	cout<<"Grid_5 Thraed Ending\n";
	pthread_mutex_unlock (&mutex_1);
	pthread_exit(NULL);
}

void *Grid_6_thraed(void *args){
	int var=16;
	while(var!=0){
		var=pthread_mutex_trylock (&mutex_1);
	}
	pthread_t t_id=pthread_self();
	

	printf("\nThraed ID : %ld mutux error : %d\n",t_id,var);

	cout<<"Grid_6 Thraed started\n";

	


	int temp[9]={-1};
	
	for(int i=3,k=0;i<6;++i){
		for(int j=6;j<9;++j,++k){
			cout<<Suduko[i][j]<<' ';

			temp[k]=Suduko[i][j];
		}
		cout<<endl;
	}

	int n = sizeof(temp); 
    findRepeat_Grid_6(temp,n);
		cout<<endl;



	cout<<"Grid_6 Thraed Ending\n";
	pthread_mutex_unlock (&mutex_1);
	pthread_exit(NULL);
}
//////////////////////////////Thread FUNCTIONS GRID_7 to GRID_9////////////////////////


void *Grid_7_thraed(void *args){
	int var=16;
	while(var!=0){
		var=pthread_mutex_trylock (&mutex_1);
	}
	pthread_t t_id=pthread_self();
	

	printf("\nThraed ID : %ld mutux error : %d\n",t_id,var);

	cout<<"Grid_7 Thraed started\n";



	int temp[9]={-1};
	
	for(int i=6,k=0;i<9;++i){
		for(int j=0;j<3;++j,++k){
			cout<<Suduko[i][j]<<' ';

			temp[k]=Suduko[i][j];
		}
		cout<<endl;
	}

	int n = sizeof(temp); 
    findRepeat_Grid_7(temp,n);
		cout<<endl;



	cout<<"Grid_7 Thraed Ending\n";
	pthread_mutex_unlock (&mutex_1);
	pthread_exit(NULL);
}


void *Grid_8_thraed(void *args){
	int var=16;
	while(var!=0){
		var=pthread_mutex_trylock (&mutex_1);
	}
	pthread_t t_id=pthread_self();
	

	printf("\nThraed ID : %ld mutux error : %d\n",t_id,var);

	cout<<"Grid_8 Thraed started\n";



	
	int temp[9]={-1};
	
	for(int i=6,k=0;i<9;++i){
		for(int j=3;j<6;++j,++k){
			cout<<Suduko[i][j]<<' ';

			temp[k]=Suduko[i][j];
		}
		cout<<endl;
	}

	int n = sizeof(temp); 
    findRepeat_Grid_8(temp,n);
		cout<<endl;



	cout<<"Grid_8 Thraed Ending\n";
	pthread_mutex_unlock (&mutex_1);
	pthread_exit(NULL);
}

void *Grid_9_thraed(void *args){
	int var=16;
	while(var!=0){
		var=pthread_mutex_trylock (&mutex_1);
	}
	pthread_t t_id=pthread_self();
	
	printf("\nThraed ID : %ld mutux error : %d\n",t_id,var);

	cout<<"Grid_9 Thraed started\n";



	
	int temp[9]={-1};
	
	for(int i=6,k=0;i<9;++i){
		for(int j=6;j<9;++j,++k){
			cout<<Suduko[i][j]<<' ';

			temp[k]=Suduko[i][j];
		}
		cout<<endl;
	}

	int n = sizeof(temp); 
    findRepeat_Grid_9(temp,n);
		cout<<endl;


	cout<<"Grid_9 Thraed Ending\n";
	pthread_mutex_unlock (&mutex_1);

	pthread_exit(NULL);
}
///////////////////////// PHASE 2 /////////////////////////////////////



	// check location containig 0/inavlid value
 
    bool FindUnassignedLocation(int grid[N][N], int &row, int &col){
        for (row = 0; row < N; row++)
            for (col = 0; col < N; col++)
                if (grid[row][col] == UNASSIGNED)
                    return true;
        return false;
    }
 
    // chk repeatition in row

    bool UsedInRow(int grid[N][N], int row, int num){
        for (int col = 0; col < N; col++)
            if (grid[row][col] == num)
                return true;
        return false;
    }

    // chk repition in col..

    bool UsedInCol(int grid[N][N], int col, int num){
        for (int row = 0; row < N; row++)
            if (grid[row][col] == num)
                return true;
        return false;
    }

	// chk repet in grid

    bool UsedInBox(int grid[N][N], int boxStartRow, int boxStartCol, int num){
        for (int row = 0; row < 3; row++)
            for (int col = 0; col < 3; col++)
                if (grid[row+boxStartRow][col+boxStartCol] == num)
                    return true;
        return false;
    }

    // if not present in row ,col an grid then insert into it

    bool isSafe(int grid[N][N], int row, int col, int num){
        return !UsedInRow(grid, row, num) && !UsedInCol(grid, col, num) &&
               !UsedInBox(grid, row - row % 3 , col - col % 3, num);
    }


	// recursive func to enetr valid value on inavlid indexis

    bool SolveSudoku(int grid[N][N]) {
        int row, col;
        if (!FindUnassignedLocation(grid, row, col))
           return true;
        for (int num = 1; num <= 9; num++)
        {
            if (isSafe(grid, row, col, num))
            {
                grid[row][col] = num;
                if (SolveSudoku(grid)){
                	 return true;
                }
             	else
                	grid[row][col] = UNASSIGNED;
            }
        }
        return false;
    }

    

// print grid
    void printGrid(int grid[N][N]){
        for (int row = 0; row < N; row++)
        {
            for (int col = 0; col < N; col++)
                cout<<grid[row][col]<<"  ";
            cout<<endl;
        }
    }



/////////////////////////////////====MIAN FUNCTION====/////////////////////////////

int main(){

	// readFile(Suduko, "read.txt");
	cout<<"starting array \n\n";
	printGrid(Suduko);
	cout<<"\n\n\n";
	pthread_mutex_init (&mutex_1 ,NULL) ;

	cout<<"\nMian thread Started\n";

// ROW THRAED
	pthread_create(&thread_array[0],NULL,row_thraed,NULL);
// COL THREAD
	pthread_create(&thread_array[1],NULL,col_thraed,NULL);
// GRID THREADS
	pthread_create(&thread_array[2],NULL,Grid_1_thraed,NULL);
	pthread_create(&thread_array[3],NULL,Grid_2_thraed,NULL);
	pthread_create(&thread_array[4],NULL,Grid_3_thraed,NULL);
	pthread_create(&thread_array[5],NULL,Grid_4_thraed,NULL);
	pthread_create(&thread_array[6],NULL,Grid_5_thraed,NULL);
	pthread_create(&thread_array[7],NULL,Grid_6_thraed,NULL);
	pthread_create(&thread_array[8],NULL,Grid_7_thraed,NULL);
	pthread_create(&thread_array[9],NULL,Grid_8_thraed,NULL);
	pthread_create(&thread_array[10],NULL,Grid_9_thraed,NULL);
	
// JOIN CALLING
	pthread_join(thread_array[0],NULL);
	pthread_join(thread_array[1],NULL);
	pthread_join(thread_array[2],NULL);
	pthread_join(thread_array[3],NULL);
	pthread_join(thread_array[4],NULL);
	pthread_join(thread_array[5],NULL);
	pthread_join(thread_array[6],NULL);
	pthread_join(thread_array[7],NULL);
	pthread_join(thread_array[8],NULL);
	pthread_join(thread_array[9],NULL);
	pthread_join(thread_array[10],NULL);


// DISPLAY ALL INVALID ENTRIES
	cout<<"\nALL INVALID ENTRIES (Rows,Cols,Grids)\n";
	for(int i=0;i<9;++i){
		for(int j=0;j<9;j++){
			cout<<arrofIndexes[i][j]<<" ";
		}
		cout<<endl;
	}

// CREATIONG TEMP ARRAY AND STORING ORIGINAL TO TTEMP SUDUKO
	int tempSuduko[9][9]={0};

	for(int i=0;i<9;++i){
		for(int j=0;j<9;++j){
			tempSuduko[i][j]=Suduko[i][j];
		}
	}

// SETTING 0 ON ALL INVALID ENTRIES IN TEMP SUDUKO ARRAY
	int counter=0;
	for(int k=0;k<9;k++){
		for(int l=0;l<9;l++){
			if(arrofIndexes[k][l]!=0){
				tempSuduko[k][l]=0;
				counter++;
			}
		}
	}

	cout<<"\nTotal number of invalid ENTRIES are : "<<counter<<endl;


// DISPLAY TEMP SUDUKO
	cout<<"\nTEMP SUDUKO\n";
	for(int i=0;i<9;++i){
		for(int j=0;j<9;j++){
			cout<<tempSuduko[i][j]<<" ";
		}
		cout<<endl;
	}

	
	pthread_mutex_destroy (&mutex_1);

cout<<"\n\n\n Solution to my suduko \n\n";


	// if solution found print final array else no soution exists

	 if (SolveSudoku(tempSuduko)){
	 	printGrid(tempSuduko);
	 }        
     else
        cout<<"No solution exists"<<endl;


	cout<<"\nMain thread Ending\n";
	pthread_exit(NULL);
}