#ifndef INDEX_H
#define INDEX_H

#include <stdio.h>
#include <stdbool.h>

#define INDEX_BOOKS "index/books.txt"
#define INDEX_CODE "index/code.dat"

enum color { RED, BLACK, DOUBLE_BLACK };

//structs

typedef struct books{
    
    int key;
    char *title;
    char *author;
    int year;
    
}Book;


typedef struct index{
    
    int key; // refers to the book key
    int code;
    
} Index;


typedef Index values;


typedef struct rb{
    
    values *value;
    enum color color;
    struct rb *left, *right, *father;
    
}Rb;


typedef struct table{
    
    FILE *book_file;
    Rb *index;
    
}Table;
    
//creation of files

bool initialize_table (Table *table);
void close (Table *table);
void add_book (Book *book, Table *table);
Book *search_book (Table *table, int key);

//books

Book *read_book ();
void remove_character (char *string);
void save_file (char *name, Rb *tree);
void save_tree (Rb *tree, FILE *file_name);
void load_file (char *name, Rb **tree);
char *get_value (char *string);

//tree

void initialize_tree (Rb **root);
void add_node (Rb **root, values *value);
void fix_node (Rb **root, Rb *node);

//tree helper functions

enum color color (Rb *node);
void pre_order (Rb *tree);
int is_root (Rb *node);
int is_left_soon (Rb *node);
int is_right_soon (Rb *node);
Rb *brother (Rb *node);
Rb *uncle (Rb *node);

//rotations

void single_rl (Rb **root, Rb *pivot);
void single_rr (Rb **root, Rb *pivot);
void double_rl (Rb **root, Rb *pivot);
void double_rr (Rb **root, Rb *pivot);

#endif
