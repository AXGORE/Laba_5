#include <stdlib.h>
#include <string.h>
#include"dialog.h"
#include "Graph.h"
#define __CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW



int main() {
	char* fname;
	Graph* gr = (Graph*)calloc(1, sizeof(Graph));
	int x, y, num,a,n;
	//_crtBreakAlloc = 96;
	printf("\nEnter File name-->\n");
	fname = Get_str();
	while (getchar() != '\n');
	load(gr,fname);
	do{
	a = dialog(&x, &y, &num);
	if (a == 1) {
		n = Add_Ver(x, y,&gr,num);
		if (n == -1) { Error(); }
	}
	if (a == 2) {
		n = Add_Edge(x,y,&gr);
		if (n == -1) { Error(); }
	}
	if (a == 3) {
		n = Del_ed(x, y, &gr);
		if (n == -1) { Error(); }
	}
	if (a == 4) {
		Del_Ver(num, &gr);
	}
	if (a == 5) {
		Find* i=DFS(gr, x, y);
		if (i == NULL) { Error(); }
		else {
			show_ver(i);
			printf("\nway: ");
			show_way(i);
			printf("\n");
			free_find(i);
		}
	}
	if (a == 6) {
		Show_Graph(gr);
	}
    } while (a != 7);
	save(gr,fname);
	free_Graph(gr);
	free(fname);
	_CrtDumpMemoryLeaks();
    return 0;
}




