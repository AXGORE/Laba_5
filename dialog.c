#include<stdio.h>
#include<stdlib.h>
#include"dialog.h"
#include"Graph.h"
#include<string.h>



void Get_int(int* a) {
	int x;
	do {
		do {
			x = scanf("%d", a);
			if (x == 0) {
				printf("%s\n", "Error, try again ");
				scanf("%*s");
			}
			if (x == -1) { *a = -1; return; }
		} while (x == 0);
		if (*a < 1) {
			printf("%s\n", "Error, try again ");
			scanf("%*s");
		}
	} while (*a < 1);
}

int dialog(int* x, int* y, int* num) {
	char* options[] = { "1.Add Ver","2.Add Edge","3.Delete Edge", "4.Delete Ver","5.Find ver","6.Show tree","7.Exit" };
	int flag, vsp, n;
	printf("Choose one option:\n");
	for (int i = 0; i < 7; i++) {
		printf("%s\n", options[i]);
	}
	do {
		Get_int(&vsp);
		if (vsp > 7) { printf("%s\n", "Error, try again "); }
	} while (vsp > 7);
	if (vsp == -1) { return 7; }
	printf("\n");
	if (vsp == 1) {
		printf("Enter num -->\n");
	    Get_int(num);
		if (*num == -1) { return 7; }
		printf("Enter x -->\n");
		flag = Get_key(x);
		if (flag == -1) { return 7; }
		printf("Enter y -->\n");
		flag = Get_key(y);
		if (flag == -1) { return 7; }
		return 1;
	}
	if (vsp == 2) {
		printf("Enter from -->\n");
		flag = Get_key(x);
		if (flag == -1) { return 7; }
		printf("Enter to -->\n");
		flag = Get_key(y);
		if (flag == -1) { return 7; }
		return 2;
	}
	if (vsp == 3) {

		printf("Enter from -->\n");
		flag = Get_key(x);
		if (flag == -1) { return 7; }
		printf("Enter to -->\n");
		flag = Get_key(y);
		if (flag == -1) { return 7; }
		return 3;
	}

	if (vsp == 4) {
		printf("Enter num -->\n");
		while (getchar() != '\n');
		flag = Get_key(num);
		if (flag == -1) { return 7; }
		return 4;
	}
	if (vsp == 5) {
		printf("Enter from -->\n");
		flag = Get_key(x);
		if (flag == -1) { return 7; }
		printf("Enter to -->\n");
		flag = Get_key(y);
		if (flag == -1) { return 7; }
		return 5;
	}
	if (vsp == 6) {
		return 6;
	}
	if (vsp == 7) {
		return 7;
	}
}
void Error() {
	printf("\nCan't add vertex with rhis name\n");
}
int Get_key(int* a) {
	int x;
	do {
		x = scanf("%d", a);
		if (x == 0) {
			printf("%s\n", "Error, try again ");
			scanf("%*s");
		}
		if (x == -1) { return -1; }
	} while (x == 0);
}
void Show_Graph(Graph* gr) {
	Ed* help;
	for (int i = 0; i < gr->v_size; i++) {
		printf("\nnum: %d \n X --> %d Y --> %d\n", gr->graph[i].num, gr->graph[i].x, gr->graph[i].y);
		help = gr->graph[i].edges;
		printf("Edges:\n");
		while (help != NULL) {
			printf("%d ---> %d\n",help->fr->num,help->to->num);
			help = help->next;
		}
	}
}
char* Get_str() {
	int a = 1, size = 80;
	char help_str[81];
	int n = 1;
	char* osn_str;
	osn_str = (char*)calloc(1, sizeof(char));
	while (1 == 1) {
		n = scanf("%80[^\n]s", &help_str);
		if (n == -1) { return NULL; }
		if (n == 0) { return osn_str; }
		//size += 80;
		osn_str = (char*)realloc(osn_str, (size + a) * sizeof(char));
		strcpy((osn_str)+(a - 1), help_str);
		a += 80;
	}
}

void show_way(Find* a) {
	if (a->prev != NULL) {
		show_way(a->prev);
	}
	printf("%d --> ", a->cur->num);
}

void show_ver(Find* a) {
	Ed* help;
	printf("\nnum: %d \n X --> %d Y --> %d\n", a->cur->num, a->cur->x, a->cur->y);
	help = a->cur->edges;
	printf("Edges:\n");
	while (help != NULL) {
		printf("%d ---> %d\n", help->fr->num, help->to->num);
		help = help->next;
	}
}