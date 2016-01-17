/*
将棋の駒の飛車は，上下方向，左右方向に升目があいている限りどこへでも移動できる。
特に，空いているその先に敵の駒があれば，その位置に進んでその駒を取ることができる。
さらに，飛車は，成ると竜となり，左右斜め前および左右斜め後の４つの升目にある敵の駒も取ることができるようになる。
将棋の駒に取って取ることのできる位置にある（敵の）駒を当たりの駒という。

正整数 n について n×n の升目をもつ盤を考え，その上にn個の竜を，
互いに当たりにならないように配置することを考え，可能な配置の総数を出力するプログラムを作る。

入力で升目nを受け取り、可能な配置の総数を出力する。
再帰を用いて深さ優先探索を行う。

b.1/17 自分で作成。
c. 全ての入力に対して成り立つ。
*/

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX 100 //jが置かれているかどうか

int depth_first_search(int i); //深さ優先探索
void set_dragon(int i, int j); //竜を置く
void remove_dragon(int i, int j); //竜を除く
int is_this_correct(); //正解かどうか
void print_state(); //現在の駒の状態を表示する

static int n;
static int isj[MAX] = {0};
static int counter = 0;
static bool node[MAX];

int main(){
	scanf("%d", &n);
	depth_first_search(0);
	printf("%d\n", counter);
}

int depth_first_search(int i){
	if(i >= n){
	//	print_state();
		if(is_this_correct() == 1) counter++; //1なら正解、0なら不正解
		return 1;
	}

	int j = 0;
	while(j < n){
		if(isj[j] == 0){ //j列に竜が置かれていなければ
			set_dragon(i, j); //(i, j)に竜を置く
			depth_first_search(i+1); //次の行で探索
			remove_dragon(i, j); //(i, j)の竜を除く
		}
		j++;
	}
	return 1;
}

void set_dragon(int i, int j){
	node[i*n+j] = true;
	isj[j] = 1;
}

void remove_dragon(int i, int j){
	node[i*n+j] = false;
	isj[j] = 0;
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
		for(j = 0; j < n; j++){
			printf("%d ", node[i*n+j]);
		}
		printf("\n");
	}
	printf("\n");
}
