#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "index.h"

//creation of files

bool initialize_table (Table *table){

    initialize_tree(&table->index);
    table->book_file = fopen("books.txt", "a+");
    load_file("code.dat", &table->index);
    if (table->book_file != NULL) {
        return true;
    } else {
        return false;
    }
}


void close (Table *table){
    fclose(table->book_file);
        save_file("code.dat", table->index);
}


void add_book (Book *book, Table *table){
    
    if(table->book_file != NULL){
        values *new_index = (values *) malloc(sizeof(values));
        new_index->key = book->key;
        
        fseek(table->book_file, 0L, SEEK_END);
        new_index->code = ftell(table->book_file);
        
        fprintf(table->book_file, "CODE|%d\n", book->key);
        fprintf(table->book_file, "TITLE|%s\n", book->title);
        fprintf(table->book_file, "AUTHOR|%s\n", book->author);
        fprintf(table->book_file, "YEAR|%d\n", book->year);
        fprintf(table->book_file, "#\n");
        
        add_node(&table->index, new_index);
    }
}


Book *search_book (Table *table, int key){
    
    if(table->book_file != NULL){
        Rb *node;
        node = table->index;
        
        while(node != NULL){
            if(node->value->key == key){
                Book *s_book = (Book *) malloc(sizeof(Book));
                char *buffer = (char *) malloc(256 * sizeof(char));
                
                fseek(table->book_file, node->value->code, SEEK_SET);
                fgets(buffer, 255, table->book_file);
                
                if(strcmp(buffer, "#\n") != 0){
                    remove_character(buffer);
                    s_book->key = atoi(get_value(buffer));

                    fgets(buffer, 255, table->book_file);
                    remove_character(buffer);
                    s_book->title = strdup(get_value(buffer));

                    fgets(buffer, 255, table->book_file);
                    remove_character(buffer);
                    s_book->author = strdup(get_value(buffer));
                    
                    fgets(buffer, 255, table->book_file);
                    remove_character(buffer);
                    s_book->year = atoi(get_value(buffer));
                }
                
                free(buffer);
                return s_book;
            }
            
            else{
                if(key > node->value->key)
                    node = node->right;
                else
                    node = node->left;
            }
        }
    }
    
    return NULL;
}

//books

Book *read_book (){
    
    Book *new_book = (Book *) malloc(sizeof(Book));
    char *buffer = (char *) malloc(256 * sizeof(char));

    getchar();
    printf("Code: ");
    scanf("%d", &new_book->key);
    //remove_character(new_book->key);
    getchar();
    
    printf("Title: ");
    fgets(buffer, 255, stdin);
    remove_character(buffer);
    new_book->title = strdup(buffer);
    
    printf("Author: ");
    fgets(buffer, 255, stdin);
    remove_character(buffer);
    new_book->author = strdup(buffer);
    
    printf("Year: ");
    //remove_character(new_book->year);
    scanf("%d", &new_book->year);
    
    free(buffer);
    
    return new_book;
}


void remove_character (char *string){
    //printf("%s\n", string);
    string[strlen(string) - 1] = '\0';
    //printf("%s\n", string);
}


void save_file (char *name, Rb *tree){
    FILE *file;
        file = fopen(name, "wb");
        if(file != NULL){
            save_tree(tree, file);
            fclose(file);
        }
}


void save_tree (Rb *tree, FILE *file_name){
    if(tree != NULL){
        fwrite(tree->value, sizeof(values), 1, file_name);
            save_tree(tree->left, file_name);
            save_tree(tree->right, file_name);
    }
}


void load_file(char *nome, Rb **tree) {
    FILE *arq;
    arq = fopen(nome, "rb");
    values * temp;
    if(arq != NULL) {
        temp = (values *) malloc(sizeof(values));

        while(fread(temp, sizeof(values), 1, arq)) {
            add_node(tree, temp);
            temp = (values *) malloc(sizeof(values));
        }
        fclose(arq);
    }
}


char *get_value (char *string) {
    int i = 0, j, k = 0;
    char *value = (char *) malloc(256 * sizeof(char));

    while (string[i] != '|' && string[i] != '\0') {
        i++;
    }

    for (j = i + 1; j < strlen(string); j++, k++) {
        value[k] = string[j];
    }
    value[k] = '\0';
    //printf("v: %s,%s\n", value,string);
    return value;
}

//tree

void initialize_tree (Rb **root){
    *root = NULL;
}


void add_node (Rb **root, values *value){
    Rb *position, *father, *new;
    position = *root;
    father = NULL;
    
    while(position != NULL){
        father = position;
        if(value->key > position->value->key)
            position = position->right;
        else
            position = position->left;
    }
    
    new = (Rb *) malloc(sizeof(Rb));
    new->value = value;
    new->left = NULL;
    new->right = NULL;
    new->father = father;
    new->color = RED;
    
    if(is_root(new))
        *root = new;
    
    else{
        if(value->key > father->value->key)
            father->right = new;
        else
            father->left = new;
    }
    
    fix_node(root, new);
}


void fix_node (Rb **root, Rb *node){
    
    while(color(node->father) == RED && color(node) == RED){
        
        //CASE 1:
        
        if(color(uncle(node)) == RED){
            uncle(node)->color = BLACK;
            node->father->color = BLACK;
            node->father->father->color = RED;
            node = node->father->father;
            
            continue;
        }
        
        //CASE 2 - RIGHT:
        
        if(is_left_soon(node) && is_left_soon(node->father)){
            single_rr(root, node->father->father);
            node->father->color = BLACK;
            node->father->right->color = RED;
            
            continue;
        }
        
        //CASE 2 - LEFT:
        
        if(is_right_soon(node) && is_right_soon(node->father)){
            single_rl(root, node->father->father);
            node->father->color = BLACK;
            node->father->left->color = RED;
            
            continue;
        }
        
        //CASE 3 - RIGHT:
        
        if(is_right_soon(node) && is_left_soon(node->father)){
            double_rr(root, node->father->father);
            node->right->color = RED;
            node->left->color = RED;
            node->color = BLACK;
            
            continue;
        }
        
        //CASE 3 - LEFT:
        
        if(is_left_soon(node) && is_right_soon(node->father)){
            double_rl(root, node->father->father);
            node->right->color = RED;
            node->left->color = RED;
            node->color = BLACK;
            
            continue;
        }
        
    }
    
    (*root)->color = BLACK;
}

//tree helper functions

enum color color (Rb *node){
    enum color c;
	if(node==NULL)
		c = BLACK;
	else
		c = node->color;
	return c;
}


int is_root (Rb *node){
    return (node->father == NULL);
}


int is_left_soon (Rb *node){
    return (node->father != NULL && node == node->father->left);
}


int is_right_soon (Rb *node){
    return (node->father != NULL && node == node->father->right);
}


Rb *brother (Rb *node){
    if(is_left_soon(node))
		return node->father->right;
	else
		return node->father->left;
}


Rb *uncle (Rb *node){
    return brother(node->father);
}


void pre_order (Rb *tree){
    if (tree != NULL) {
        printf("[%d]", tree->value->key);
        pre_order(tree->left);
        pre_order(tree->right);
    }
}

//rotations

void single_rl (Rb **root, Rb *pivot){
    
    Rb *u, *t1;
    u = pivot->right;
    t1 = u->left;
    
    int p_is_right_soon = is_right_soon(pivot);
    
    pivot->right = t1;
    
    if(t1 != NULL)
        t1->father = pivot;
    
    u->left = pivot;
    u->father = pivot->father;
    pivot->father = u;
    
    if(is_root(u))
        *root = u;
    
    else{
        if(p_is_right_soon)
            u->father->right = u;
        else
            u->father->left = u;
    }
}


void single_rr (Rb **root, Rb *pivot){
    
    Rb *p, *u, *t1;
    p = pivot;
    u = p->left;
    t1 = u->right;
    
    int p_is_left_soon = is_left_soon(pivot);
    
    p->left = t1;
    
    if(t1 != NULL)
        t1->father = pivot;
    
    u->right = pivot;
    u->father = p->father;
    p->father = u;
    
    if(is_root(u))
        *root = u;
    
    else{
        if(p_is_left_soon)
            u->father->left = u;
        else
            u->father->right = u;
    }
}


void double_rl (Rb **root, Rb *pivot){
    
    Rb *v, *p, *u, *t2, *t3;
    p = pivot;
    u = p->right;
    v = u->left;
    t2 = v->left;
    t3 = v->right;
    
    int p_is_right_soon = is_right_soon(p);
    
    u->left = t3;
    
    if(t3 != NULL)
        t3->father = u;
    
    v->right = u;
    p->right = v;
    p->right = t2;
    
    if(t2 != NULL)
        t2->father = p;
    
    v->left = p;
    v->father = p->father;
    p->father = v;
    u->father = v;
    
    if(is_root(v))
        *root = v;
    
    else{
        if(p_is_right_soon)
            v->father->right = v;
        else
            v->father->left = v;
    }
}


void double_rr (Rb **root, Rb *pivot){
    
    Rb *v, *p, *u, *t2, *t3;
    p = pivot;
    u = p->left;
    v = u->right;
    t2 = v->left;
    t3 = v->right;
    
    int p_is_left_soon = is_left_soon(pivot);
    
    u->right = t2;
    
    if(t2 != NULL)
        t2->father = u;
    
    v->left = u;
    p->left = v;
    p->left = t3;
    
    if(t3 != NULL)
        t3->father = p;
    
    v->right = p;
    v->father = p->father;
    p->father = v;
    u->father = v;
    
    if(is_root(v))
        *root = v;
    
    else{
        if(p_is_left_soon)
            v->father->left = v;
        else
            v->father->right = v;
    }
}
