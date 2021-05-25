#include <stdlib.h>
#include <string.h>
#include"dialog.h"
#include "Graph.h"
#include <stdio.h>

int Add_Ver(int x, int y, Graph** gr, int num) {
	if ((*gr)->graph == NULL) {
		(*gr)->graph = (Ver*)calloc(1, sizeof(Ver));
		(*gr)->graph[0].num = num;
		(*gr)->graph[0].x = x;
		(*gr)->graph[0].y = y;
		(*gr)->v_size++;
		return 0;
	}
	for (int i = 0; i < (*gr)->v_size; i++) {
		if ((*gr)->graph[i].num == num || ((*gr)->graph[i].x == x && (*gr)->graph[i].y == y)) {
			return -1;
		}
	}
	if ((*gr)->graph != NULL) {
		(*gr)->graph = (Ver*)realloc(((*gr)->graph), (1 + (*gr)->v_size) * sizeof(Ver));
		(*gr)->graph[(*gr)->v_size].num = num;
		(*gr)->graph[(*gr)->v_size].x = x;
		(*gr)->graph[(*gr)->v_size].y = y;
		(*gr)->graph[(*gr)->v_size].color = 0;
		(*gr)->graph[(*gr)->v_size].edges = NULL;
		(*gr)->v_size++;
		return 0;
	}
}

int Add_Edge(int from, int to, Graph** gr) {
	int flag = 0;
	Ed* help;
	Ver* help_v = NULL;
	for (int i = 0; i < (*gr)->v_size; i++) {
		if ((*gr)->graph[i].num == to) {
			flag = 1;
			help_v = &((*gr)->graph[i]);
		}
	}
	if (flag == 0) { return -1; }
	flag = 0;
	for (int i = 0; i < (*gr)->v_size; i++) {
		if ((*gr)->graph[i].num == from) {
			help = (*gr)->graph[i].edges;
			if (help == NULL) {
				flag = 1;
				help = (Ed*)calloc(1, sizeof(Ed));
			}
			while (help->next != NULL) {
				if (help->fr == &((*gr)->graph[i]) && help->to == help_v) { return -1; }
				help = help->next;
			}
			if (help->fr == &((*gr)->graph[i]) && help->to == help_v) { return -1; }
			if (flag == 0) {
				help->next = (Ed*)calloc(1, sizeof(Ed));
				help = help->next;
			}
			help->fr = &((*gr)->graph[i]);
			help->to = help_v;
			if (flag == 1) { (*gr)->graph[i].edges = help; }
			(*gr)->e_size++;
			return 0;
		}
	}
	if (flag == 0) { return -1; }
}

void free_Graph(Graph* gr) {
	Ed* help;
	Ed* help1;
	for (int i = 0; i < gr->v_size; i++) {
		help = gr->graph[i].edges;
		while (help != NULL) {
			help1 = help;
			help = help->next;
			free(help1);
		}
	}
	free(gr->graph);
	free(gr);
}

Del_ed(int from, int to, Graph** gr) {
	int flag = 0;
	Ed* help;
	Ed* prev = NULL;
	Ver* help_v = NULL;
	for (int i = 0; i < (*gr)->v_size; i++) {
		if ((*gr)->graph[i].num == to) {
			flag = 1;
			help_v = &((*gr)->graph[i]);
		}
	}
	if (flag == 0) { return -1; }
	flag = 0;
	for (int i = 0; i < (*gr)->v_size; i++) {
		if ((*gr)->graph[i].num == from) {
			help = (*gr)->graph[i].edges;
			while (help->next != NULL) {
				if (help->fr == &((*gr)->graph[i]) && help->to == help_v) {
					flag = 1;
					break;
				}
				prev = help;
				help = help->next;
			}
			if (help->fr == &((*gr)->graph[i]) && help->to == help_v) { flag = 1; }
			if (flag == 1) {
				if (prev != NULL) {
					prev->next = help->next;
					free(help);
					(*gr)->e_size--;
					return 0;
				}
				else {
					(*gr)->graph[i].edges = help->next;
					free(help);
					(*gr)->e_size--;
					return 0;
				}
			}
		}
	}
	return -1;
}
int Del_Ver(int num, Graph** gr) {
	int flag = 0;
	Ver* help_v = NULL;
	Ed* help;
	Ed* help1;
	if ((*gr)->v_size == 1) {
		help = (*gr)->graph[0].edges;
		while (help != NULL) {
			help1 = help;
			help = help->next;
			free(help1);
		}
		free((*gr)->graph);
		(*gr)->v_size--;
		(*gr)->e_size = 0;
		(*gr)->graph = NULL;
		return;
	}
	int a = (*gr)->graph[(*gr)->v_size - 1].num;
	for (int i = 0; i < (*gr)->v_size; i++) {
		if ((*gr)->graph[i].num == num) {
			flag = 1;
			help_v = &(*gr)->graph[i];
		}
		Del_ed((*gr)->graph[i].num, num, gr);
	}
	if (flag == 0) { return; }
	ch_ed(gr, a, help_v);
	for (int i = 0; i < (*gr)->v_size; i++) {
		if ((*gr)->graph[i].num == num) {
			help = (*gr)->graph[i].edges;
			while (help != NULL) {
				help1 = help;
				help = help->next;
				free(help1);
				(*gr)->e_size--;
			}
			(*gr)->graph[i].num = (*gr)->graph[(*gr)->v_size - 1].num;
			(*gr)->graph[i].x = (*gr)->graph[(*gr)->v_size - 1].x;
			(*gr)->graph[i].y = (*gr)->graph[(*gr)->v_size - 1].y;
			(*gr)->graph[i].edges = (*gr)->graph[(*gr)->v_size - 1].edges;
			(*gr)->graph = (Ver*)realloc(((*gr)->graph), ((*gr)->v_size - 1) * sizeof(Ver));
			(*gr)->v_size--;

		}
	}
}
void ch_ed(Graph** gr, int num, Ver* ch) {
	for (int i = 0; i < (*gr)->v_size; i++) {
		Ed* help = (*gr)->graph[i].edges;
		while (help != NULL) {
			if (help->to->num == num) {
				help->to = ch;
			}
			if (help->fr->num == num) {
				help->fr = ch;
			}
			help = help->next;
		}
	}
}

void load(Graph* gr, char* fname) {
	int x, y, num, from, to;
	int e_size;
	int v_size;
	FILE* f;
	void* a = fopen_s(&f, fname, "r+b");
	if (a != NULL) { return; }

	fread(&v_size, sizeof(int), 1, f);
	fread(&e_size, sizeof(int), 1, f);
	for (int i = 0; i < v_size; i++) {
		fread(&num, sizeof(int), 1, f);
		fread(&x, sizeof(int), 1, f);
		fread(&y, sizeof(int), 1, f);
		Add_Ver(x, y, &gr, num);
	}
	for (int i = 0; i < e_size; i++) {
		fread(&from, sizeof(int), 1, f);
		fread(&to, sizeof(int), 1, f);
		Add_Edge(from, to, &gr);
	}
	fclose(f);
}


void save(Graph* gr, char* fname) {
	FILE* f;
	fopen_s(&f, fname, "w+b");
	fwrite(&(gr->v_size), sizeof(int), 1, f);
	fwrite(&(gr->e_size), sizeof(int), 1, f);
	for (int i = 0; i < gr->v_size; i++) {
		fwrite(&(gr->graph[i].num), sizeof(int), 1, f);
		fwrite(&(gr->graph[i].x), sizeof(int), 1, f);
		fwrite(&(gr->graph[i].y), sizeof(int), 1, f);
	}
	Ed* help;
	for (int i = 0; i < gr->v_size; i++) {
		help = gr->graph[i].edges;
		while (help != NULL) {
			fwrite(&(help->fr->num), sizeof(int), 1, f);
			fwrite(&(help->to->num), sizeof(int), 1, f);
			help = help->next;
		}
	}
	fclose(f);
}


void* DFS(Graph* gr, int from, int to) {
	Find* help = NULL;
	t = 0;
	for (int i = 0; i < gr->v_size; i++) {
		gr->graph[i].color = 0;
	}
	int flag = 1;
	for (int i = 0; i < gr->v_size; i++) {
		if (from == gr->graph[i].num) {
			help = (Find*)calloc(1, sizeof(Find));
			help->cur = &(gr->graph[i]);
			flag = 0;
			break;
		}
	}
	if (flag == 1) { return NULL; }
	void* a = DFS_cur(help, to);
	if (a == NULL) { free(help); }
	return a;
}


void* DFS_cur(Find* u, int to) {
	void* a = NULL;
	Find* help1;
	u->cur->color = 1;
	t++;
	u->d = t;
	Ed* help = u->cur->edges;
	while (help != NULL) {
		help1 = (Find*)calloc(1, sizeof(Find));
		help1->cur = help->to;
		help1->prev = u;
		if (help1->cur->num == to) { return help1; }
		if (help1->cur->color == 0) {
			a = DFS_cur(help1, to);
			if (a != NULL) { return a; }

		}
		free(help1);
		help = help->next;
	}
	u->cur->color = 2;
	t++;
	u->f = t;
	return a;
}

void free_find(Find* a) {
	if (a->prev != NULL) {
		free_find(a->prev);
	}
	free(a);
}

void* BF_Find(Graph* gr, int from, int to) {
	int flag = 0;
	Ed* help;
	for (int i = 0; i < gr->v_size; i++) {
		gr->graph[i].prev = NULL;
		if (from == gr->graph[i].num) {
			gr->graph[i].color = 0;
		}
		else {
			gr->graph[i].color = -1;
		}
	}
	for (int i = 1; i < gr->v_size; i++) {
		for (int j = 0; j < gr->v_size; j++) {
			if (gr->graph[j].color != -1) {
				help = gr->graph[j].edges;
				while (help != NULL) {
					if (help->to->color == -1 || help->to->color > help->fr->color + 1) {
						help->to->color = help->fr->color + 1;
						help->to->prev = help->fr;
					}
					help = help->next;
				}
			}
		}
	}
	for (int i = 0; i < gr->v_size; i++) {
		if (to == gr->graph[i].num && gr->graph[i].prev != NULL) {
			return &(gr->graph[i]);
		}
	}
	return NULL;
}


void* Uorshall(Graph* gr, int* d, int fr, int to, int* flag, int* flag1, MD*** matr) {
	int h = -1;

	if ((*matr) == NULL) {
		(*matr) = (MD**)calloc(gr->v_size, sizeof(MD*));
		for (int i = 0; i < gr->v_size; i++) {
			gr->graph[i].color = i;
			(*matr)[i] = (MD*)calloc(gr->v_size, sizeof(MD));

		}
		for (int i = 0; i < gr->v_size; i++) {
			for (int j = 0; j < gr->v_size; j++) {
				(*matr)[i][j].num_fr = gr->graph[i].num;
				(*matr)[i][j].num_to = gr->graph[j].num;
				(*matr)[i][j].next = -1;
			}
		}
	}
	for (int i = 0; i < gr->v_size; i++) {
		Ed* help = gr->graph[i].edges;
		while (help != NULL) {
			(*matr)[i][help->to->color].d1 = 1;
			(*matr)[i][help->to->color].next = help->to->color;
			if (fr == i && to == help->to->color && *flag == -2) {
				(*matr)[i][help->to->color].d1 = 0;
				(*matr)[i][help->to->color].next = -1;
			}
			else if (fr == i && to == help->to->color) {
				*flag = -2;
				return matr;
			}
			help = help->next;
		}
	}
	(*matr)[fr][to].d1 = 0;
	(*matr)[fr][to].next = -1;
	for (int i = 0; i < gr->v_size; i++) {
		int h1 = 0;
		for (int j = 0; j < gr->v_size; j++) {
			if (h1 == 1) { break; }
			for (int k = 0; k < gr->v_size; k++) {
				if ((i == *d || i == *flag1) && j == fr && k == to) { 
					h1 = 1;
					break;
				}
				if (((*matr)[j][k].d1 > (*matr)[j][i].d1 + (*matr)[i][k].d1 || (*matr)[j][k].d1 == 0) && (*matr)[j][i].d1 != 0 && (*matr)[i][k].d1 != 0) {
					(*matr)[j][k].d1 = (*matr)[j][i].d1 + (*matr)[i][k].d1;
					(*matr)[j][k].next = (*matr)[j][i].next;
					if (j == fr && k == to) {
						h = i;
						if ((*matr)[j][i].next != i) {
							(*matr)[(*matr)[j][i].next][k].next = i;
							//if (prov(matr, fr, to) == -1) {
							//(*matr)[j][k].next == -1;
						   // }
					    }
					}
				}
			}
		}
	}
	*flag1 = *d;
	*d = h;
	return;
}

void* findmatr(MD** a, int size, int* fr, int* to) {
	MD* x = &a[0][0];
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (a[i][j].d1 < x->d1 && a[i][j].d1 != 0) {
				x = &a[i][j];
				*fr = i;
				*to = j;
			}
		}
	}
	return x;
}

void* random(int n) {
	Graph* gr = (Graph*)calloc(1, sizeof(Graph));
	int x, y, num;
	for (int i = 0; i < n; i++) {
		x = rand() % 5000;
		y = rand() % 5000;
		num = i;
		Add_Ver(x, y, &gr, num);
	}
	num = 2 * n;
	for (int i = 0; i < num; i++) {
		x = rand() % ((gr)->v_size);
		y = rand() % ((gr)->v_size);
		Add_Edge(x, y, &gr);
	}
	return gr;
}
int prov(MD*** matr, int fr, int to) {
	if ((*matr)[fr][to].next == -1) {
		return -1;
	}
	int c = (*matr)[fr][to].num_fr;
	int b = fr;
	while (b != to) {
		b = (*matr)[b][to].next;
		c = (*matr)[b][to].num_fr;
		if (b == fr) { return -1; }
		if ((*matr)[(*matr)[b][to].next][to].next == b && b!= to && (*matr)[b][to].next!=to) {
			return -1;
		}
	}
	return 0;
}

int dop_1(Graph* gr, FILE* output) {
	for (int i = 0; i < gr->v_size; i++) {
		fprintf(output, "\n%d->", gr->graph[i].num);
		Ed* help = gr->graph[i].edges;
		while (help != NULL) {
			fprintf(output, "%d", help->to->num);
			if (help->next != NULL) {
				fprintf(output, ",", help->to->num);
			}
			help = help->next;
		}
	}
	return 0;
}

void* load_txt() {
  Graph* gr = (Graph*)calloc(1, sizeof(Graph));
  FILE* f;
  int flag=0;
  int num, x, y,e=0;
  f = fopen("OL.cnode.txt","r+b");
  char* help = (char*)calloc(255,sizeof(char));
  while (flag == 0) {
	  for (int i = 0; i < 3; i++) {
		  e = fscanf(f,"%s",help);
		  if (e == -1) {
			  flag = 1;
			  break;
		  }
		  if (i == 0) {
			  num = atoi(help);
		  }
		  else if (i == 1) {
			  x = atoi(help);
		  }
		  else if (i == 2) {
			  y = atoi(help);
		  }
	  }
	  if (flag == 0) {
		  Add_Ver(x, y, &gr, num);
	  }
  }
  fclose(f);
  flag = 0;
  f = fopen("OL.cedge.txt","r+b");
  while (flag == 0) {
	  for (int i = 0; i < 4; i++) {
		  e = fscanf(f, "%s", help);
		  if (e == -1) {
			  flag = 1;
			  break;
		  }
		  if (i == 0) {
			  continue;
		  }
		  else if (i == 1) {
			  x = atoi(help);
		  }
		  else if (i == 2) {
			  y = atoi(help);
		  }
		  else if (i == 3) {
			  continue;
		  }
	  }
	  if (flag == 0) {
		  Add_Edge(x,y,&gr);
		  Add_Edge(y,x, &gr);
	  }
  }
  fclose(f);
  free(help);
  return gr;
}