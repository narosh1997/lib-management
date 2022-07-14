#include"book_bdb.h"
#include<stdio.h>
#include<string.h>
void book_insert(book_t* book){
    char fileName[] = "book.dat";
    FILE* out = fopen(fileName,"ab");
    if(out == NULL){
        printf("FILE ERROR.\n");
        return;
    }
    fwrite(book,1,sizeof(book_t),out);
    fclose(out);
}
void book_readAll(book_t* book, int* countAddr){
    int I=0;
    book_t temp = {};
    
    char fileName[] = "book.dat";
    FILE* in = fopen(fileName,"rb");
    if(in == NULL){
        printf("FILE ERROR.\n");
        return;
    }
    while(fread(&temp,1,sizeof(book_t),in)){
        book[I] = temp;
        I++;
    }
    fclose(in);
    (*countAddr) = I;
}

void book_delete(int id){
	int I=0;
    book_t temp  = {};
    
    char fileName[] = "book.dat";
    char tempFileName[] = "booktemp.dat";
    FILE* in = fopen(fileName,"r");
    FILE* out = fopen(tempFileName,"w");
    if(in == NULL){
        printf("(in)FILE ERROR.\n");
        return;
    }
    if(out == NULL){
        printf("(out)FILE ERROR.\n");
        return;
    }
    while(fread(&temp,1,sizeof(book_t),in)){
    	I++;
        if(temp.bookId != id){        	
        	fwrite(&temp,1,sizeof(book_t),out);
        }        
    }    
    fclose(out);
    fclose(in); 
    remove(fileName);
    rename(tempFileName,fileName);
}
void book_readById(book_t* bookAddr, int bookId){
    int I=0;
    book_t temp  = {};
    
    char fileName[] = "book.dat";
    FILE* in = fopen(fileName,"rb");
    if(in == NULL){
        printf("FILE ERROR.\n");
        return;
    }
    while(fread(&temp,1,sizeof(book_t),in)){
        if(temp.bookId == bookId){
        	(*bookAddr) = temp;
        	break;
        }
        I++;
    }
    fclose(in);
}
void book_update(book_t book){
	int I=0;
    book_t temp = {};
    
    char fileName[] = "book.dat";
    FILE* in = fopen(fileName,"rb+");
    if(in == NULL){
        printf("FILE ERROR.\n");
        return;
    }
    while(fread(&temp,1,sizeof(book_t),in)){
    	I++;
        if(temp.bookId == book.bookId){        	
        	break;
        }        
    }
    if(I > 0){
    	fseek(in,(I-1)*sizeof(book_t),SEEK_SET);
    	fwrite(&book,1,sizeof(book_t),in);
    }
    fclose(in);
}
