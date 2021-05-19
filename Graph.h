#ifndef GRAPH_H
#define GRAPH_H
typedef struct Find Find;
typedef struct Ed Ed;
typedef struct Ver Ver;
typedef struct Ed {
	Ed* next;
	Ver* fr;
	Ver* to;
}Ed;
int time;
typedef struct Ver {
	int num;
	int x;
	int y;
	Ed* edges;
	int color;
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



#endif