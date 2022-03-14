#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static long numprints = 0;

typedef struct diff {
    long offset;
    unsigned char orig_value;
    unsigned char new_value;
}diff;


typedef struct node node;
struct node{
    diff *diff_data;
    node *next;
};

void list_print(node* diff_list, FILE* output, int k, long diff_num){
    struct node *temp = diff_list;
    if(temp != NULL){
        list_print(temp->next, output, k, diff_num);
        if (k == 1 && numprints < diff_num){
            fprintf(output, "byte %ld %02hhX %02hhX \n", temp->diff_data->offset,temp->diff_data->orig_value,temp->diff_data->new_value);
            numprints++;
        }
        else if (k != 1){
            fprintf(output, "byte %ld %02hhX %02hhX \n", temp->diff_data->offset,temp->diff_data->orig_value,temp->diff_data->new_value);
        }
    }
}

node* list_append(node* diff_list, diff* data){
    struct node* to_return;
    to_return = malloc(sizeof(node));
    to_return->diff_data = data;
    to_return->next = diff_list;
    return to_return;
}

void list_free(node *diff_list){
    struct node *temp = diff_list;
    struct node *next;
    if (diff_list != NULL){
        free(temp->diff_data);
        next = temp->next;
        free(temp);
        list_free(next);
    }
}

int main(int argc, char **argv) {

    /* open two files for reading*/
    FILE* origf;
    FILE* newf;
    FILE* output = stdout;
    long diff_num;
    int t = 0;
    long total = 0;
    int k = 0;
    int i;
    int r = 0;
    long to_change = -1;

    for(i = 1; i<argc; i++){
        if (strcmp(argv[i], "-r") == 0){
            r = 1;
            if (argv[i+1] != NULL && argv[i+1][0] != '-'){
                to_change = (long) atoi(argv[++i]);
            }
        }
        else if (strcmp(argv[i], "-o") == 0){
            output = fopen(argv[++i], "r");
        }
        else if (strcmp(argv[i], "-t") == 0){
            t = 1;
        }
        else if (strcmp(argv[i], "-k") == 0){
            k = 1;
            diff_num = (long) atoi(argv[++i]);
        }
        else{
            origf = fopen(argv[i++], "r");
            newf = fopen(argv[i], "r+");
        }
    }

    /*Move pointers to end of the binary files, get both sizes and return to the beginning*/
    fseek(origf,0,SEEK_END);
    fseek(newf,0,SEEK_END);

    long orig_length = ftell(origf);
    long new_length = ftell(newf);

    fseek(origf,0,SEEK_SET);
    fseek(newf,0,SEEK_SET);

    long min;
    if (orig_length < new_length){
        min = orig_length;
    }
    else{
        min = new_length;
    }

    unsigned char a,b;
    long q;
    diff *difference;
    struct node* head = NULL;
    
    for(q = 0; q < min; q++){
        fread(&a, 1, 1, origf);
        fread(&b, 1, 1, newf);

        if (a != b){
            if (r == 1 && to_change>0){
                fseek(newf, q, SEEK_SET);
                fputc(a, newf);
                to_change--;
            }
            else if (r == 1 && to_change==-1){
                fseek(newf, q, SEEK_SET);
                fputc(a, newf);
            }
            difference = malloc(sizeof(diff));
            difference->offset = q;
            difference->orig_value = a;
            difference->new_value = b;
            head = list_append(head, difference);
            total++;

        }
    }


    if (t == 1){
        fprintf(output, "There are %ld differences\n", total);
    }
    else{
        list_print(head, output, k, diff_num);
    }

    list_free(head);

    fclose(origf);
    fclose(newf);

    if (output != stdout){
        fclose(output);
    }

    return 0;
}