#ifndef GRAPH_H
#define GRAPH_H
#include<stdio.h>
typedef struct Find Find;
typedef struct Ed Ed;
typedef struct Ver Ver;
typedef struct MD MD;
typedef struct Ed {
	Ed* next;
	Ver* fr;
	Ver* to;
}Ed;
int t;
typedef struct Ver {
	int num;
	int x;
	int y;
	Ed* edges;
	int color;
	Ver* prev;
}Ver;
typedef struct Graph {
	int e_size;
	int v_size;
	Ver* graph;
}Graph;
typedef struct Find {
	Ver* cur;
	Find* prev;
	int d;
	int f;
}Find;
typedef struct MD {
	int num_fr;
	int num_to;
	int d1;
	int next;
}MD;
int Add_Ver(int x, int y, Graph** gr, int num);
void free_Graph(Graph* gr);
int Add_Edge(int from, int to, Graph** gr);
int Del_ed(int from, int to, Graph** gr);
int Del_Ver(int num, Graph** gr);
void ch_ed(Graph** gr, int num, Ver* ch);
void load(Graph* gr, char* fname);
void save(Graph* gr, char* fname);
void* DFS(Graph* gr, int from, int to);
void* DFS_cur(Find* u, int to);
void free_find(Find* a);
void* BF_Find(Graph* gr, int from, int to);
void* Uorshall(Graph* gr, int* d, int fr, int to, int* flag, int* flag1, MD*** matr);
void* findmatr(MD** a, int size, int* fr, int* to);
void* random(int n);
int prov(MD*** matr, int fr, int to);
int dop_1(Graph* gr, FILE* output);
void* load_txt();


#endif