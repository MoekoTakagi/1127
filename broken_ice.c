/*
冬の寒いある日，JOI太郎君は広場にはった薄氷を割って遊ぶことにした．
広場は長方形で， 東西方向に m 個， 南北方向に n 個， つまり， m × n の区画に区切られている．
また， 薄氷が有る区画と無い区画がある． JOI太郎君は，次のルールにしたがって，薄氷を割りながら区画を移動することにした．

薄氷があるどの区画からも薄氷を割り始めることができる．
東西南北のいずれかの方向に隣接し， まだ割られていない薄氷のある区画に移動できる．
移動した先の区画の薄氷をかならず割る．
JOI太郎君が薄氷を割りながら移動できる区画数の最大値を求めるプログラムを作成する
ただし， 1 ≦ m ≦ 90，1 ≦ n ≦ 90 である． 与えられる入力データでは， 移動方法は20万通りを超えない．

入力はn+2行ある
1 行目には整数 m が書かれている．
2 行目には整数 n が書かれている．
3 行目から n+2 行目までの各行には、0 もしくは 1 が， 
空白で区切られて m 個書かれており， 各区画に薄氷があるか否かを表している． 
北から i 番目，西からj番目の区画を (i,j) と記述することにすると (1 ≦ i ≦ n, 1 ≦ j ≦ m)， 
第 i+2 行目の j 番目の値は， 区画 (i,j) に薄氷が存在する場合は 1 となり， 区画 (i,j) に薄氷が存在しない場合は 0 となる．

出力は移動できる区画数の最大値と改行を書き出す

深さ優先探索で再帰を用いる

*/
#include <stdio.h>
#include <stdbool.h>

#define MAX 10000 //
#define c 4

int depth_first_search(int i); //深さ優先探索
void break_ice(int i); //薄氷を割る
void make_ice(int i); //薄氷を作る
int search_next_ice(int i, int j); //次に移動できる薄氷があるかどうか
int is_this_correct(); //正解かどうか
void print_state(); //現在の氷の状態を表示する

static int m, n;
static int counter;
static int max_c;
static int max = 0;
static int node[MAX];
static bool done[MAX];

int main(){
	int i, j;
	scanf("%d%d", &m, &n);
	for(i = 0; i < m*n; i++){
		scanf("%d", &node[i]);
		
	}
//	printf("\n");
	for(i = 0; i < m*n; i++){
		counter = 0;
		max_c = 0;
	//	printf("%d番目でサーチ\n", i);
		depth_first_search(i);
	//	printf("戻ったステートは\n");
	//	print_state();
//		printf("%d\n", max_c);
		if(max < max_c) max = max_c;
	}
	printf("%d\n", max+1);
}

int depth_first_search(int i){
	int x, j = 0;
	if(node[i]){
		break_ice(i); //i番目の氷を割る
	//	printf("%d番目の薄氷を割る\n", i);
		while(j < c){ //i番目に薄氷があったら
			if((x = search_next_ice(i, j)) >= 0){ //次に移動できるとき
	//			printf("%d番目の薄氷を割って、次は%d番目\n", i, j);
			//	counter++;
				depth_first_search(x); //次の薄氷を探索
			}


			j++;
		}
		make_ice(i); //iに氷を作る
	}
	if(max_c < counter) max_c = counter;
//	printf("カウンタは%d\n", counter);
//	counter = 0;
//	print_state();

//	printf("マックスカウンタは%d\n", max_c);
	
	return 1;
}

int search_next_ice(int i, int j){
	if(j == 0 && i % m != 0){
		if(node[i-1]) return i-1; //左に移動
	}
	else if(j == 1 && i % m != m-1){
		if(node[i+1]) return i+1; //右に移動
	}
	else if(j == 2 && i >= m){
		if(node[i-m]) return i-m; //上に移動
	}
	else if(j == 3 && i < m*(n-1)){
		if(node[i+m]) return i+m; //下に移動
	}
	return -1; //指定された方向に移動出来ない	
}



void break_ice(int i){
	counter++;
	node[i] = false;
}

void make_ice(int i){
	counter--;
	node[i] = true;
}

int is_this_correct(){
	int i, j, k;
	for(j = 0; j < n; j++){
		for(i = 0; i < n; i++){
			k = i*n+j; //添字
			if(j == 0 && node[k] == true){ //一番左の列に関して、右上・右下に竜があるか
				if(node[k-n+1] == true || node[k+n+1] == true) return 0;
			}else if(j == n-1 && node[k] == true){ //一番右の列に関して、左上・左下に竜があるか
				if(node[k-n-1] == true || node[k+n-1] == true) return 0;
			}else if(node[k] == true){ //それ以外の列に関して、右上・右下・左上・左下に竜があるか
				if(node[k-n-1] == true || node[k+n-1] == true || node[k-n+1] == true || node[k+n+1] == true) return 0;
			}
		}
	}
	return 1; //途中で戻らなければ正解
}

void print_state(){
	int i, j;
	for(i = 0; i < n; i++){
		for(j = 0; j < m; j++){
			printf("%d ", node[i*m+j]);
		}
		printf("\n");
	}
	printf("\n");
}
