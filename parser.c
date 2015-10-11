#include "parser.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void advance_after(int* offset,char* string,char* html){
    char* ptr = string;
    while(1){
        if ( html[*offset] == *ptr){
            ptr++;
            if ( *ptr == '\0'){
                (*offset)++;
                break;
            }
        }
        else {
            ptr = string;
        }
        (*offset)++;
    }
}

void parse_ordres_boursorama(char* html){
    int offset = 0;
    
    int found = 0;
    int parser_state = 0;
    
    /*
    while( found == 0 ){
        offset++;
        switch(parser_state){
            case 0:
                if ( html[offset] == '>')
                    parser_state = 1;
                break;
            case 1:
                if ( html[offset] == 'A')
                    parser_state = 2;
                else
                    parser_state = 0;
                break;
            case 2:
                if ( html[offset] == 'c')
                    parser_state = 3;
                else
                    parser_state = 0;
                break;
            case 3:
                if ( html[offset] == 'h')
                    parser_state = 4;
                else
                    parser_state = 0;
                break;
            case 4:
                if ( html[offset] == 'a')
                    parser_state = 5;
                else
                    parser_state = 0;
                break;
            case 5:
                if ( html[offset] == 't')
                    found = 1;
                else
                    parser_state = 0;
                break;
            default:
                break;
        }
        
    }*/
    
    advance_after(&offset,">Achat",html);
    advance_after(&offset,"<td",html);
    advance_after(&offset,"<td",html);
    
    advance_after(&offset,">",html);
    advance_after(&offset,">",html);
    int start = offset;
    advance_after(&offset,"<",html);
    int stop = offset - 1;

    
    char* quantite_ordre = strndup(html+start,stop-start);
    printf("quantite ordres %d\n",atoi(quantite_ordre));
    free(quantite_ordre);
}
