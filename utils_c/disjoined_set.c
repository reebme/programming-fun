#include <stdio.h>
#include <disjoined_set.h>
/*
 * Disjoined set is represented as an array from 1...|V|
 */
void make_set(int no_vertices, int *ds, int *size){
    // initialize all vertices as roots
    for(int i = 1; i < no_vertices; ++i){
        ds[i] = i;
        size[i] = 1;
    }
}

/*
 * Returns the representative of the set containing element e
 * Does path compression.
 * Recursive.
 */
int find_set(int e, int *ds){
    if(ds[e] != e)
        ds[e] = find_set(ds[e], ds);
    else return ds[e];
}

/*
 * Joins two groups represented by x and y smaller to larger
 */
void link_by_size(int x, int y, int *ds, int *size){
    if(x == y) return;
    if(size[x] > size[y]){
        ds[y] = x;
        size[x] = size[x] + size[y];
    } else {
        ds[x] = y;
        size[y] = size[x] + size[y];
    }
    //if(size[x] < 0) printf("%d %d %d %d\n", x, y, size[x], size[y]);
}

void join(int x, int y, int *ds, int *size){
    link_by_size(find_set(x, ds), find_set(y, ds), ds, size);
}
