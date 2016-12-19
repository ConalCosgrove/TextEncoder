
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
//Structure Definitions
struct huffNode{
    int freq;
    int is_leaf;
    unsigned char c;
        struct{
            struct huffNode * left;
            struct huffNode * right;
        } compound;
    

};

struct bitfile{
    
    unsigned char buffer;
    int bufferPointer;
    FILE  * outputFile;
};



//Function Declarations
struct huffNode ** build_huffman_tree(int * freqs,int nFreqs);

struct huffNode * remove_smallest(struct huffNode ** list,int size);

void setToZero(int * intArray);

void setToOne(int * intArray);

void printTree(struct huffNode * x,struct huffNode * xPrev);

void writeOut(struct huffNode ** huffTree);

void walk_tree(struct huffNode * root, unsigned char * encoding,int depth,unsigned char ** encodings);

void bitfile_write(struct bitfile * b,int x);

void encode_file(FILE * in,struct bitfile * out,unsigned char ** encodings);

void write_encoding(struct bitfile * out,unsigned char * encoding);

struct huffNode * tree_run(int x,struct huffNode * root);

int get_length(unsigned char * x);

//main function
int main(int argc, char *argv[]){

<<<<<<< HEAD
=======

>>>>>>> 98a005e964fb15e67a901c11e7a1ab78b68d2492
//Configuring File Folder Paths for Input
    
    char configPath[100] = "./training_files/";
    strcat(configPath,argv[2]);
    

    
    char inPath[100] = "./files_to_encode/";
    strcat(inPath,argv[3]);
    

    
    char encPath[100] = "./encodings/";
    strcat(encPath,argv[3]);

    
    char outPath[50] = "./encodings/";
    strcat(outPath,argv[4]);

    
    char path[100] = "./decodings/";
    strcat(path,argv[4]);
    

    
    printf("File paths configured\n");
    
//Declaring input files and output file 
    FILE * config;
    FILE * encodedFile;
    FILE * inputFile;


//Creating array of int's which will contain each ASCII character's frequency
    int * charFreqs = malloc(sizeof(int)*256);

//Checking input for incorrect number of parameters
    if(argc != 5){

<<<<<<< HEAD
	
=======
	//zeroBits(b);
	//binaryPrintBuffer(b);
>>>>>>> 98a005e964fb15e67a901c11e7a1ab78b68d2492
        printf("Error, please type:\n \"./huffman <encode/decode> <training_filename.txt> 			<input_file.txt> <output_file_name.txt> \" \n");
        exit(1);
    }
    else if( (strcmp(argv[1],"encode") != 0) && (strcmp(argv[1],"decode") != 0) ){
        printf("Error, please type either \"encode\" or \"decode\" as the first parameter\n");
        exit(1);
    }
    else{
        //Print Program's Parameters and File Names
        printf("Encode or Decode? - %s\n",argv[1]);
        printf("Training File: %s\n",argv[2]);
        printf("Input File : %s\n",argv[3]);
        printf("Output File Name: %s\n",argv[4]);
        
        //Set all character frequencies to zero
        setToZero(charFreqs);
	
        //open training file
        config = fopen(configPath,"r");
        //test if training file is found
        if(!config){
            printf("Error, training file - %s could not be found\n",argv[2]);
            exit(1);
        }
        //create buffer to hold one char of training file at a time
        unsigned char *buffer = malloc(sizeof(unsigned char)*2);

        //scan through all characters in training file and update the character frequencies accordingly
        while(!feof(config)){
            fscanf(config,"%c",buffer);
            buffer[1] = '\0';
            int characterIndex = buffer[0];
            
            charFreqs[characterIndex]++;
            
        }
        
        //set all frequency values that == 0 to 1
        setToOne(charFreqs);
        
    }
    fclose(config);
    
    //build huffman tree using character frequencies of training file
    struct huffNode ** tree = build_huffman_tree(charFreqs,256);
    printf("Huffman Tree Built\n");
    
    //create array of strings to hold each character's encoding
    unsigned char **encodings;
    encodings = malloc(sizeof(unsigned char*)*256);
    
    //populates string array with encoding of ASCII character at its corresponding address
    for(int i = 0; i < 256;i++){
        encodings[i] = malloc(sizeof(unsigned char)*30);
    }
    
    unsigned char enc[256];
    walk_tree(tree[0],enc,0,encodings);
    printf("Encodings Generated\n");
    
    /*printf("Dec  ASCII    Encoding\n");
    for(int i = 0;i<256;i++){
       printf("%-5d%-10c%-25s\n",i,i,encodings[i]);
    }*/
    
    //checks if in encoding mode or decoding mode
    if(strcmp(argv[1],"encode") == 0){
	
        inputFile = fopen(inPath,"r");
        if(!inputFile){
            printf("Error, input file - %s could not be found\n",argv[3]);
            return 1;
        }
        
        //sets up bitfile to write encodings to output file
        struct bitfile * bitWriter = malloc(sizeof(struct bitfile));
        bitWriter->buffer = 0;
        bitWriter->bufferPointer = 0;
        bitWriter->outputFile = fopen(outPath,"w");
        //encodes file
        encode_file(inputFile,bitWriter,encodings);
	
        
    }else if(strcmp(argv[1],"decode") == 0){
        
        inputFile = fopen(encPath,"r");

        FILE * fileOut;
	
	
        fileOut = fopen(path,"w");
        
        if(!inputFile){
            printf("Error, input file - %s could not be found\n",argv[3]);
            return 1;
        }
        //create character buffer
        unsigned char c;
        
        //set c equal to first character in file
        c = fgetc(inputFile);
        
        //create new pointer to root node of huffman tree
        struct huffNode * node;
        node = tree[0];
        
        int ind = 0;
        
        
        //while there are characters left in file
        while(!feof(inputFile)){
            
            
            for(int i = 0; i < 8; i++){                        //for each bit in the character
                int x = c >> (7 - i);                          //starting from the leftmost
                x = x&0x1;                                     //removing the rest of the bits
                //printf("%d",x);
                node = tree_run(x,node);//walks huffman tree depending on whether bit value is 1 or 0
                
                if(node->is_leaf == 1){
                                                    //if a leaf node is found the character
                    printf("%c",node->c);           //is written to the file and the node is
                    fputc(node->c,fileOut);         // reset to the root node of the tree
                    node = tree[0];
                    
                }
             
            }
            c = fgetc(inputFile);                   // get the next character
        }
        printf("File decoded!\n");
        
        
    }else{
        printf("Error. Please type either encode or decode after ./huffman\n");
    }
    printf("Program Finished\n");
return 0;
}

struct huffNode ** build_huffman_tree(int * freqs,int nFreqs){
    
    struct huffNode ** list;
    list = malloc(sizeof(struct huffNode *)*256);
    int i;
    
    printf("Frequency List Created\n");
    
    for(i = 0; i < nFreqs; i++){
        list[i] = malloc(sizeof(struct huffNode));
        list[i] -> freq= freqs[i];
        list[i] -> is_leaf = 1;
        list[i] -> c = i;
    }
    
    printf("Frequency List Populated\n");
    
    
    //building tree
    int arraySize = nFreqs;
    
    for(i = 0;i<nFreqs - 1;i++){
        //printf("For loop start\n");
        
        struct huffNode * smallest1 = malloc(sizeof(struct huffNode));
        struct huffNode * smallest2 = malloc(sizeof(struct huffNode));
        struct huffNode * compound = malloc(sizeof(struct huffNode));
        
        //printf("Structs Created - %d \n",i);
        
        smallest1 = remove_smallest(list,arraySize);
        arraySize--;
        smallest2 = remove_smallest(list,arraySize);
        
        //printf("Smallest Removed - %d\n",i);
        //printf("Smallest one - %c  Freq - %d \n Smallest two - %c  Freq - %d\n",smallest1->c,smallest1->freq,smallest2->c,smallest2->freq);
        //combine smallest two nodes into new compound nodes
        compound = malloc(sizeof(struct huffNode));
        compound -> freq = (smallest1 -> freq) + (smallest2 -> freq);
        compound -> is_leaf = 0;
        compound -> compound.left = smallest1;
        compound -> compound.right = smallest2;
        compound -> c = smallest2 -> c;
        list[arraySize - 1] = compound;
	
    }
    
    return list;
}

struct huffNode * remove_smallest(struct huffNode ** list,int size){
    
    int smallestIndex = 0;
    
    int i;

    for(i = 0; i < size; i++){
        if(list[i]->freq < list[smallestIndex]->freq){
            smallestIndex = i;
        }
        else if((list[i]->freq == list[smallestIndex]->freq) && (list[i]->c > list[smallestIndex]->c)){
            smallestIndex = i;
        }
    }
    
    //Remove smallest item from array
    struct huffNode * result = malloc(sizeof(struct huffNode));
    result = list[smallestIndex];
    
    list[smallestIndex] = list[size-1];
    list[size-1] = NULL;

    return result;
    
    
}





void setToZero(int * intArray){
    int i;
    for(i = 0;i<256;i++){
        intArray[i] = 0;
    }
    
}

void setToOne(int * intArray){
    int i;
    for(i=0;i<256;i++){
        if(intArray[i] == 0){
            intArray[i] = 1;
        }
    }
}

void walk_tree(struct huffNode * root,unsigned char * encoding,int depth,unsigned char ** encodings){
    if(root->is_leaf == 1){
        encoding[depth] = '\0';
        //printf("Found ASCII %d Char %c\n",root->c,root->c);
        if(root->c >= 0){
            for(int i = 0; i < depth;i++){
                encodings[root->c][i] = encoding[i];
                //printf("%d adding %d %c \n",i,root->c,encoding[i]);
            }
        }
        //printf("%c - %s",root -> c,encoding);
        //printf("\n");
    }else{
        encoding[depth] = '0';
        walk_tree(root->compound.left,encoding,depth+1,encodings);
        encoding[depth] = '1';
        walk_tree(root->compound.right,encoding,depth+1,encodings);
    }
    
}

void bitfile_write(struct bitfile * b,int x){
    assert(x == 0 || x == 1);
    unsigned char temp = b -> buffer;
    unsigned char or = 1;
    


    temp <<= 1;
    if(x == 1){
        temp = temp | or;
    }else{
        
    }
    
    b -> bufferPointer++;
    if(b->bufferPointer > 7){
        b->bufferPointer = 0;
        fputc(temp,b->outputFile);
        //printf("writeout %d\n",x);
        
        //printf("\n");
        b -> buffer = 0;
    }else{
        b -> buffer = temp;
    }
}

void encode_file(FILE * in,struct bitfile * out,unsigned char ** encodings){
    unsigned char c;
    c = fgetc(in);
    
    while(!feof(in)){
        unsigned char * encoding = encodings[c];
        //printf("Found %c - %s\n",c,encoding);
        write_encoding(out,encoding);
        c = fgetc(in);
    }
    const int EOT = 4;
    write_encoding(out,encodings[EOT]);
    printf("File Encoded!\n");
    fclose(in);
    
    
}

void write_encoding(struct bitfile * out,unsigned char * encoding){
    int length = get_length(encoding);
    
    for(int i = 0; i < length;i++){
        int bit;
        assert(encoding[i] == '0' || encoding[i] == '1');
        
        bit = encoding[i] - '0';
        //printf("%d",bit);
        bitfile_write(out,bit);
    }
    //printf("\n");
}

int get_length(unsigned char * x){
    int i;
    for(i = 0; x[i] != '\0'; i++){
        
    }
    return i;
}

struct huffNode * tree_run(int x,struct huffNode * root){
    if(x == 0){
        return root->compound.left;
    }else{
        return root->compound.right;
    }
}

void printTree(struct huffNode * x,struct huffNode * xPrev){

    
    
}
