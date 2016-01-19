/*
冬の寒いある日，JOI太郎君は広場にはった薄氷を割って遊ぶことにした．
広場は長方形で， 東西方向に m 個， 南北方向に n 個， つまり， m × n の区画に区切られている．
また， 薄氷が有る区画と無い区画がある． JOI太郎君は，次のルールにしたがって，薄氷を割りながら区画を移動することにした．
薄氷があるどの区画からも薄氷を割り始めることができる．
東西南北のいずれかの方向に隣接し， まだ割られていない薄氷のある区画に移動できる．
移動した先の区画の薄氷をかならず割る．
JOI太郎君が薄氷を割りながら移動できる区画数の最大値を求めるプログラムを作成する。
ただし， 1 ≦ m ≦ 90，1 ≦ n ≦ 90 である． 与えられる入力データでは， 移動方法は20万通りを超えない．
入力はn+2行ある。
1 行目には整数 m が書かれている．
2 行目には整数 n が書かれている．
3 行目から n+2 行目までの各行には、0 もしくは 1 が， 
空白で区切られて m 個書かれており， 各区画に薄氷があるか否かを表している． 
北から i 番目，西からj番目の区画を (i,j) と記述することにすると (1 ≦ i ≦ n, 1 ≦ j ≦ m)， 
第 i+2 行目の j 番目の値は， 区画 (i,j) に薄氷が存在する場合は 1 となり， 区画 (i,j) に薄氷が存在しない場合は 0 となる．
出力は移動できる区画数の最大値を示す。

input
5
3
1 1 1 0 1
1 1 0 0 0
1 0 0 0 1

output
5

飛車の配置をベースに考え、再帰を用いて深さ優先探索する。
薄氷がある全ての場所から割り始め、その場所に隣接する薄氷があるかどうかを探し、
もしあればその隣の薄氷で再帰呼出しを行い、また薄氷を割りさらに探索を行う。
ある段階でこれ以上薄氷を割れなくなると、カウンタに保存しておいた割った数をチェックして、
もし割った薄氷の数が最大であればそれを一旦max_cに保存しておき上の段階に戻る。
そして再帰呼び出しから戻ってきたら，割った薄氷を元に戻して次の東西南北の方向に対して探索する。
割り始めた地点までつまりmain関数まで再帰呼び出しが戻ってきたら、
今まで探索した地点での割った薄氷の最大値と比較し、
それより大きければmaxに保存し次の地点からまた割り始める。
これを最後の地点まで繰り返す。
*/

#include <stdio.h>
#include <stdbool.h>

#define MAX 10000 //最大区画数
#define c 4 //東西南北への方向

int depth_first_search(int i); //深さ優先探索
void break_ice(int i); //薄氷を割る
void make_ice(int i); //薄氷を作る
int search_next_ice(int i, int j); //次に移動できる薄氷があるかどうか
void print_state(); //現在の氷の状態を表示する

static int m, n;
static int counter, max_c, max = 0;
static int node[MAX];

int main(){
	int i, j;
	scanf("%d%d", &m, &n);
	for(i = 0; i < m*n; i++){
		scanf("%d", &node[i]);	
	}
	for(i = 0; i < m*n; i++){
		counter = 0;
		max_c = 0;
		depth_first_search(i);
		if(max < max_c) max = max_c;
	}
	printf("%d\n", max+1);
}

int depth_first_search(int i){
	int x, j = 0;
	if(node[i]){
		break_ice(i); //i番目の氷を割る
		while(j < c){ //i番目に薄氷があったら
			//東西南北に移動できる薄氷があるとき移動先の薄氷を探索
			if((x = search_next_ice(i, j)) >= 0) depth_first_search(x);
			j++;
		}
		make_ice(i); //iに氷を作る
	}
	if(max_c < counter) max_c = counter;
	return 1;
}

int search_next_ice(int i, int j){
	if(j == 0 && i % m != 0){
		if(node[i-1]) return i-1; //西に移動
	}
	else if(j == 1 && i % m != m-1){
		if(node[i+1]) return i+1; //東に移動
	}
	else if(j == 2 && i >= m){
		if(node[i-m]) return i-m; //北に移動
	}
	else if(j == 3 && i < m*(n-1)){
		if(node[i+m]) return i+m; //南に移動
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
