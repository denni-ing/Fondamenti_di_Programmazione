#ifndef MYLIB_H
#define MYLIB_H

int load_elem(FILE *fpin, elem Element[], int n);
void print_table(elem Element[], int n);
float scan_request(const char *composto, elem Element[], int n, int l);
float scan_table(const char *atom_name, elem Element[]);

#endif
