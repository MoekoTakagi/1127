/*
将棋の駒の飛車は，上下方向，左右方向に升目があいている限りどこへでも移動できる。
特に，空いているその先に敵の駒があれば，その位置に進んでその駒を取ることができる。
さらに，飛車は，成ると竜となり，左右斜め前および左右斜め後の４つの升目にある敵の駒も取ることができるようになる。
将棋の駒に取って取ることのできる位置にある（敵の）駒を当たりの駒という。

正整数 n について n×n の升目をもつ盤を考え，その上にn個の竜を，
互いに当たりにならないように配置することを考え，可能な配置の総数を出力するプログラムを作る。
入力で升目nを受け取り、可能な配置の総数を出力する。

再帰を用いて深さ優先探索を行う。
縦にも横にも，どこまでも“当たり”となるというのが飛車の特性であるから、
どの行，どの列にも1個の飛車しか置くことができないので、各行に順に1個の飛車をおいていく。
それまでに置いた飛車がどの列に置かれているかを記録しておいて，それらの列を除いた残りの列に飛車を置く。
各行で飛車を置き、次の行で再帰呼出しによりまた上記の探索を行い飛車を置く。
ある段階で試行のしようがなくなると上の段階に戻る。
つまり再帰呼び出しから戻ってきたら，置いた飛車を取り除いて次の列に対して探索する。
また、升目の最大行数を超えたら、飛車が互いに当たらないようにすべての行に置けたことになるので、
竜に成るか、つまり斜め方向に一升ずつ当たりがないかチェックし再帰を終え上の段階に戻る。
*/

#include <stdio.h>
#include <stdbool.h>

#define MAX 100

int depth_first_search(int i); //深さ優先探索
void set_dragon(int i, int j); //飛車を置く
void remove_dragon(int i, int j); //飛車を除く
bool promoted_dragon(); //当たりの駒がなければ竜に成る
void print_state(); //現在の駒の状態を表示する

static int n;
static int counter = 0;
static bool isj[MAX];
static bool node[MAX];

int main(){
	scanf("%d", &n);
	depth_first_search(0);
	printf("%d\n", counter);
}

int depth_first_search(int i){
	int j = 0;
	if(i >= n && promoted_dragon()) return 1;
	while(j < n){
		if(!isj[j]){ //j列に飛車が置かれていなければ
			set_dragon(i, j); //(i, j)に飛車を置く
			depth_first_search(i+1); //次の行で探索
			remove_dragon(i, j); //(i, j)の飛車を除く
		}
		j++;
	}
	return 1;
}

void set_dragon(int i, int j){
	node[i*n+j] = true;
	isj[j] = true;
}

void remove_dragon(int i, int j){
	node[i*n+j] = false;
	isj[j] = false;
}

bool promoted_dragon(){
	int i, j, k;
	for(j = 0; j < n; j++){
		for(i = 0; i < n; i++){
			k = i*n+j; //添字
			if(j == 0 && node[k]){ //一番左の列に関して、右上・右下に飛車があるか
				if(node[k-n+1] || node[k+n+1]) return false;
			}else if(j == n-1 && node[k]){ //一番右の列に関して、左上・左下に飛車があるか
				if(node[k-n-1] || node[k+n-1]) return false;
			}else if(node[k]){ //それ以外の列に関して、右上・右下・左上・左下に飛車があるか
				if(node[k-n-1] || node[k+n-1] || node[k-n+1] || node[k+n+1]) return false;
			}
		}
	}
	counter++;
	return true; //途中で戻らなければ竜に成る
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
