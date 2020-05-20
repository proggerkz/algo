#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 1;
int a[N];
struct segtree
{
	vector<long long> T;
	vector<long long> add;
	void init(int n){
		T.resize(4 * n + 1);
		add.resize(4 * n + 1);
	}
	long long merge(long long x, long long y){
		return x + y;
	}
	void push(int v){
		T[v * 2] += add[v];
		T[v * 2 + 1] += add[v];
		add[v * 2] += add[v];
		add[v * 2 + 1] += add[v];
		add[v] = 0; 
	}
	void buildmin(int v, int tl, int tr){
		if(tl == tr){
			T[v] = a[tl];
		}
		else{
			int tm = tl + tr >> 1;
			buildmin(2 * v, tl, tm);
			buildmin(2 * v + 1, tm + 1, tr);
			T[v] = min(T[v * 2], T[v * 2 + 1]);
		}
	}
	void buildmax(int v, int tl, int tr){
		if(tl == tr) {
			T[v] = a[tl];
		}
		else{
			int tm = tl + tr >> 1;
			buildmax(2 * v, tl, tm);
			buildmax(2 * v + 1, tm + 1, tr);
		}
	}
	void updval(int v, int tl, int tr, int pos, int val){
		if(tl == tr)  T[v] = val;
		else{
			int tm = tl + tr >> 1;
			if(pos <= tm) updval(2 * v, tl, tm, pos, val);
			else updval(2 * v + 1, tm + 1, tr, pos, val);
			T[v] = merge(T[v * 2], T[v * 2 + 1]);
		}
	}
	void updrange(int v, int tl, int tr, int l, int r, long long val){
		if(l <= tl && tr <= r){
			T[v] += val;
			add[v] += val;
			return;
		}
		if(l > tr || r < tl) return;
		push(v);
		int tm = tl + tr >> 1;
		updrange(2 * v, tl, tm, l, r, val);
		updrange(2 * v + 1, tm + 1, tr, l, r, val);
		T[v] = merge(T[v * 2], T[v * 2 + 1]);
	}
	long long get(int v, int tl, int tr, int l, int r){
		if(l <= tl && tr <= r){
			return T[v];
		}
		if(l > tr || r < tl) return 0;
		push(v);
		int tm = tl + tr >> 1;
		return merge(get(2 * v, tl, tm, l, r),
		get(2 * v + 1, tm + 1, tr, l, r));
	}
};