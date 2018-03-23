#include "SDL_Plotter.h"
#include <cstdlib>
#include <algorithm>

using namespace std;

SDL_Plotter *g;
int *data;
const int SPEED = 0;
bool TRACE = false;

void plotData();

void RandomizeData();
//************************************************************
// description: Sorts the data by swapping the data until all data is in the
//              correct location.
// return: None
// precondition: the array data exists and is valid
// postcondition: the array is sorted
//
//************************************************************
void BubbleSort();

//************************************************************
// description: Sorts the data by searching the data for the next element
//              and sorting it.
// return: None
// precondition: the array data exists and is valid
// postcondition: the array is sorted and data is drawn to the screen
//
//************************************************************
void SelectionSort();

//************************************************************
// description: Sorts the data by inserting each element into the correct
//              sorted spot.
// return: None
// precondition: the array data exists and is valid
// postcondition: the array is sorted and data is drawn to the screen
//
//************************************************************
void InsertionSort();

//************************************************************
// description: Sorts the data by creating a heap and removing the top element
//              then reheaping with the remaining data and repeating
// return: None
// precondition: the array data exists and is valid
// postcondition: the array is sorted and data is drawn to the screen
//
//************************************************************
void HeapSort();


//************************************************************
// description: Sorts the data by recursively dividing the data in half
//              and recursively sorting the subsets
// return: None
// precondition: the array data exists and is valid
// postcondition: the array is sorted and data is drawn to the screen
//
//************************************************************
void QuickSort(int,int);


//************************************************************
// description: Sorts the data by recursively dividing the data in half and
//              sorting the subsets
// return: None
// precondition: the array data exists and is valid
// postcondition: the array is sorted and data is drawn to the screen
//
//************************************************************
void MergeSort(int left, int right);

//
// Sorting Visualization Driver
//


int main(int argc, char **argv) {
    g = new SDL_Plotter(500,500);
    data = new int[g->getCol()];


    for(int i =0; i < g->getCol(); i++){
        data[i] = rand()%g->getCol();
    }

    while(!g->getQuit()){

        if(g->kbhit()){
            switch(g->getKey()){
                case 'B': BubbleSort();
                    break;
                case 'R': RandomizeData();
                    break;
                case 'S': SelectionSort();
                    break;
                case 'I': InsertionSort();;
                    break;
                case 'H': HeapSort();
                    break;
                case 'Q': QuickSort(0, g->getCol());
                    break;
                case 'M': MergeSort(0, g->getCol());
                    break;
                case 'T': TRACE = !TRACE;
                    break;
                case 'C': g->clear();
                    break;
                case 'X': g->setQuit(true);
                    break;
            }
        }
        plotData();
    }

}




void BubbleSort(){
    for(int i = 0; i < g->getCol()-1; i++){
        for(int j = 0; j < g->getCol()-1-i; j++){
            if(data[j] > data[j+1]){
                swap(data[j], data[j+1]);
            }
        }
        plotData();
    }
}

void SelectionSort(){
    int least;
    for ( int i = 0; i < g->getCol() - 1; i++ ){
        least = i;
        for ( int j = 1 + i; j < g->getCol() - 1; j++){
            if ( data[j] < data[least] ){
                least = j;
            }
        }

        swap( data[i], data[least]);
        plotData();
    }
}

void InsertionSort(){
    for (int i = 1; i < g->getCol(); i++)
    {
        int current = data[i];
        int position = i - 1;

        while (position >= 0 and data[position] > current){
            data[position + 1] = data[position];
            position -= 1;
        }
        data[position + 1] = current;

        plotData();
    }
}

void HeapSort() {
    for ( int i = 0; i < g->getCol() - 1; i++ ){
        make_heap( data, data + (g->getCol() - 1 - i)) ;
        swap( data[0], data[(g->getCol() - 1) - i] );
        plotData();
    }

}

int partition( int left, int right ){
    int pivotValue = data[left];
    int pivotPosition = left;

    for ( int pos = left + 1; pos <= right; pos++ ){
        if ( data[pos] < pivotValue ){
            swap( data[pivotPosition + 1], data[pos] );
            swap( data[pivotPosition], data[pivotPosition + 1] );

            pivotPosition ++;
        }
    }

    return pivotPosition;
}

void QuickSort( int left, int right ){
    if ( left < right ){
        int p = partition( left, right );

        QuickSort( left, p - 1 );
        QuickSort( p + 1, right );

        plotData();
    }
}

// SHE DONT WORK
void Merge( int left, int right, int part ){
    int sizeL = part - left + 1;
    int sizeR = right - part;
    int leftArr[sizeL];
    int rightArr[sizeR];

    for ( int i = 0; i < sizeL; i++ ){
        leftArr[i] = data[i];
    }

    for ( int i = 0; i < sizeR; i++ ){
        rightArr[i] = data[part + 1 + i];
    }

    int leftPos = 0;
    int rightPos = 0;
    int mainPos = 0;

    while ( leftPos < sizeL and rightPos < sizeR ){
        if ( leftArr[leftPos] <= rightArr[rightPos] ){
            data[mainPos] = leftArr[leftPos];
            leftPos++;
        }
        else{
            data[mainPos] = rightArr[rightPos];
            rightPos++;
        }
        mainPos++;
    }

    while ( leftPos < sizeL ){
        data[mainPos] = leftArr[leftPos];
        leftPos++;
        mainPos++;
    }

    while ( rightPos < sizeR ){
        data[mainPos] = rightArr[rightPos];
        rightPos++;
        mainPos++;
    }

}
// SHE DOESNT WORK
void MergeSort(int left, int right){
    if (left < right) {
        int part = left + (right - left) / 2;

        MergeSort(left, part);
        MergeSort(part + 1, right);

        Merge(left, right, part);
    }

}

void RandomizeData(){
    g->clear();
    for(int i =0; i < g->getCol(); i++){
        data[i] = rand()%g->getCol();
    }
    plotData();
}

// main draw function, gets called over and over, as fast as possible
void plotData(){
    if(!TRACE) g->clear();
    for(int i = 0; i < g->getCol();i++){
        g->plotPixel(i,data[i],0,0,0);

        if(i + 1 < g->getCol()) g->plotPixel(i+1,data[i],0,0,0);
        if(i - 1 >= 0) g->plotPixel(i-1,data[i],0,0,0);
        if(data[i] + 1 < g->getCol()) g->plotPixel(i,data[i]+1,0,0,0);
        if(data[i] - 1 >= 0)g->plotPixel(i,data[i]-1,0,0,0);
    }
    g->update();
    g->Sleep(SPEED);
}
