#include <stdlib.h>
#include <string.h>
#include<stdio.h>
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
	FILE* file;
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
		file = fopen("output.txt", "w+b");
		fprintf(file, "digraph G{\n");
		dop_1(gr, file);
		fprintf(file, "\n}\n");
		fclose(file);
	}
	if (a == 7) {
		Ver* m = BF_Find(gr, x, y);
		if (m == NULL) { Error(); }
		else{
			show_ver_v(m);
			printf("\nway: ");
			show_way_v(m);
			printf("\n");
	    }
	}
	if (a == 8) {
		int c=-1, d=-1,e=-2,flag=-1,flag1=-2;
		for (int j = 0; j < gr->v_size; j++) {
			if (gr->graph[j].num == x) { c = j; }
			if (gr->graph[j].num == y) { d = j; }
		}
		MD** k = NULL;
		for (int j = 0; j < 3; j++) {
			if (c == -1 || d == -1) {
				Error();
				break;
			}
			Uorshall(gr,&e,c,d,&flag,&flag1,&k);
			int h=showmatr(k,c,d);
			if (h == -1) {
				printf("\nNo more ways\n");
				break;
			}
		}
		if (k != NULL) {
			for (int j = 0; j < gr->v_size; j++) { free(k[j]); }
			free(k);
		}
	}
	if (a == 10) {
		free_Graph(gr);
		gr = random(x);
	}
	if (a == 11) {
		DFS_Timing();
	}
	if (a == 12) {
		BF_Timing();
	}
	if (a == 13) {
		free_Graph(gr);
		gr = load_txt();
	}
    } while (a != 9);
	save(gr,fname);
	free_Graph(gr);
	free(fname);
	_CrtDumpMemoryLeaks();
    return 0;
}




