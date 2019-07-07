#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct books{

    long long int ISBN;
    char author[51];
    char title[101];


}book;



int binarySearch(book *array, int size, long long int element, int **position){

    int start = 0 , end = size - 1, mid = 0, value = 0;

    while(start <=  end){
        

        mid = (start + end) / 2 ;

        if(element > array[mid].ISBN){
            start = mid + 1;
            
        }
        else if(element < array[mid].ISBN){
            end = mid - 1;
           
        }
        else{
            value++;
            **position =  mid;
            return value;
        }
        value ++;
        **position = -1;
    }
    value ++;
    return value;
}

int interpolatedSearch(book *array, int size, long long int element){

    int start = 0 , end = size - 1, valueFunction = 0, value = 0;
    
    while(start <=  end){
        value++;
        valueFunction = start + ((array[end].ISBN - array[start].ISBN) ) % (end - start + 1);
        
        if(element > array[valueFunction].ISBN){
            start = valueFunction + 1;
            
        }
        else if(element < array[valueFunction].ISBN){
            end = valueFunction - 1;
            
        }
        else{
            
            return value;
        }
       
    }
    return value;

}


int main(int argc, char const *argv[])
{
    
    FILE* input = fopen(argv[1], "r");
    FILE* output = fopen(argv[2], "w");

    int numbOfBooks = 0, numbOfsearched = 0, valueBinary = 0, valueInterpolated = 0, pointBinary = 0, pointInterpolated = 0, mediaBinary = 0, mediaInterpolated = 0;
    long long int search = 0;
    int *position = (int*)malloc(sizeof(int));
    *position = 0;


    fscanf(input, "%d", &numbOfBooks);

    book *arrayBooks = (book*)malloc(numbOfBooks*sizeof(book));


    for(int i = 0 ; i < numbOfBooks ; i++){
        fscanf(input,"%lld %50[^&]%*c %100[^\n]", &arrayBooks[i].ISBN, arrayBooks[i].author, arrayBooks[i].title);
    }

    
    fscanf(input, "%d", &numbOfsearched);
    
    for(int i = 0 ; i < numbOfsearched ; i++){
        fscanf(input, "%lld", &search);
        

        valueBinary = binarySearch(arrayBooks, numbOfBooks, search, &position);
        valueInterpolated = interpolatedSearch(arrayBooks, numbOfBooks, search);
        
        if(valueInterpolated <= valueBinary){
            
            pointInterpolated++;
        }
        else{
            pointBinary++;
        }

        mediaBinary += valueBinary;
        mediaInterpolated += valueInterpolated;

        if(*position != -1){
            fprintf(output, "[%lld]B=%d,I=%d:Author:%s,Title:%s\n", arrayBooks[*position].ISBN, valueBinary, valueInterpolated, arrayBooks[*position].author, arrayBooks[*position].title);
        }
        else{
            fprintf(output, "[%lld]B=%d,I=%d:ISBN_NOT_FOUND\n", search, valueBinary, valueInterpolated);
        }
        
        *position = 0;
    }
    fprintf(output, "BINARY=%d:%d\n", pointBinary, mediaBinary / numbOfsearched);
    fprintf(output, "INTERPOLATION=%d:%d\n", pointInterpolated, mediaInterpolated / numbOfsearched);
    




    free(position);
    free(arrayBooks);
    fclose(input);
	fclose(output);

    return 0;
}
