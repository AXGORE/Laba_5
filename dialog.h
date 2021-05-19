#ifndef DIALOG_H
#define DIALOG_H

typedef struct Graph Graph;
typedef struct Find Find;
void Get_int(int* a); 
int dialog(int* x, int* y, int* num);
int Get_key(int* a);
void Error();
void Show_Graph(Graph* gr);
char* Get_str();
void show_way(Find* a);
void show_ver(Find* a);







#endif // !DIALOG_H
