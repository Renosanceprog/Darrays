#include <iostream>
#include <stdio.h>
#include <malloc.h>

class darray
{
private:
    int  capacity;
    int  darr_count;
    int* head;
public:
//=== CONSTRUCTORS & DECONSTRUCTOR =========================================
    template <size_t N>
    darray(int (&arr)[N]){
        darr_count = N;
        capacity = N;
        head  = (int*)malloc(capacity * sizeof(int));
        for (size_t i = 0; i < darr_count; i++) head[i] = arr[i];
    }
    darray(const darray &other){
        darr_count = other.darr_count;
        capacity = other.capacity;
        head = (int*)malloc(capacity * sizeof(int));
        for (size_t i = 0; i < darr_count; i++) head[i] = other.head[i];
    }
    darray& operator=(const darray& other){
        if (this == &other) return *this;
        free(head);
        darr_count = other.darr_count;
        capacity = other.capacity;
        head = (int*)malloc(capacity * sizeof(int));
        for (size_t i = 0; i < darr_count; i++) head[i] = other.head[i];
        return *this;
    }
    darray(){
        capacity = 1;
        darr_count = 0;
        head  = (int*)malloc(capacity * sizeof(int));
    }
    ~darray(){
        free(head);
    }

//=== APPEND =============================================================
    void append(int num){
        if (darr_count >= capacity){
            capacity *= 2;
            head = (int*)realloc(head, capacity * sizeof(int));
        }
        
        head[darr_count] = num;
        darr_count++;
    }

//=== CLEAR ==============================================================
    void clear(){
        darr_count = 0;
        capacity = 1;
        head = (int*)realloc(head, capacity * sizeof(int));
    }

//== COPY ================================================================
    darray copy(){
        darray n;
        for (size_t i = 0; i < darr_count; i++) n.append(head[i]);
        return n;
    }

//== COUNT ===============================================================
    size_t count(int item){
        size_t occurs = 0;
        for (size_t i = 0; i < darr_count; i++) if (head[i] == item) occurs++;
        return occurs;
    }

//=== EXTEND =============================================================
    void extend(const darray& array){
        if ((darr_count + array.darr_count) > capacity)
        {
            capacity = (darr_count + array.darr_count) * 2;
            head = (int*)realloc(head, capacity * sizeof(int));
        }
        int newcount = darr_count + array.darr_count;
        int j = 0;
        for (int i = darr_count; i < newcount; i++) {head[i] = array.head[j]; j++;}
        darr_count = newcount;
    }

//== INDEX ================================================================
    size_t index(int item){
        size_t arr_index = 0;
        for (size_t i = 0; i < darr_count; i++) if (head[i] == item) {arr_index = i; break;}
        return arr_index;
    }

//== INSERT ===============================================================
    void insert(int index, int item){
        if (index < 0) index = darr_count + index;
        if (index < 0) index = 0;
        if (index > darr_count-1) {append(item); return;}
        if (darr_count >= capacity){
            capacity *= 2;
            head = (int*)realloc(head, capacity * sizeof(int));
        }
        for (size_t i = darr_count; i > index; i--) head[i] = head[i-1];
        head[index] = item;
        darr_count++;
    }

//=== REMOVE =============================================================
    void remove(int item){
        bool notfound = true;
        for (size_t i = 0; i < darr_count; i++)
        {
            if (head[i] == item)
            {
                notfound = false;
                for (size_t j = i; j < darr_count-1; j++) head[j] = head[j+1];
                break;
            }
        }
        if (notfound) {std::cout<<"item is not in darray"<<std::endl; return;}
        darr_count--;
        if ((capacity >= darr_count * 2) && (capacity > 2)){
            capacity /= 2;
            head = (int*)realloc(head, capacity * sizeof(int));
        }
    }
//=== POP ================================================================
    int pop(){
        if (darr_count == 0) {std::cout<<"array is empty"<<std::endl; return -1;}
        int item = head[darr_count-1];
        darr_count--;
        
        if ((capacity >= darr_count * 2) && (capacity > 2)){
            capacity /= 2;
            head = (int*)realloc(head, capacity * sizeof(int));
        }
        return item;
    }
    
    int pop(int index){
        if (darr_count == 0) {std::cout<<"array is empty"<<std::endl; return -1;}
        if (index > darr_count-1) {std::cout<<"index is out of bounds"<<std::endl; return -1;}
        if (index < 0) index = darr_count + index;
        if (index < 0) {std::cout<<"index is out of bounds"<<std::endl; return -1;}
        int item = head[index];
        for (size_t i = index; i < darr_count-1; i++) head[i] = head[i+1];
        darr_count--;
        
        if ((capacity >= darr_count * 2) && (capacity > 2)){
            capacity /= 2;
            head = (int*)realloc(head, capacity * sizeof(int));
        }
        return item;
    }
//=== REVERSE ============================================================
void reverse(){
    int p1 = 0;
    int p2 = darr_count-1;
    if (darr_count < 2) return;
    while (p1 != p2+1)
    {
        int temp = head[p1];
        head[p1] = head[p2];
        head[p2] = temp;

        p1++;
        p2--;
    }
}

//=== self implementations ========================================
    int* start(){
        return head;
    }
    
    void debugprint(){
        printf("darray stats: darr_count = %d, max capacity = %d, sizeof(head) = %3u bytes | [", darr_count, capacity, capacity*sizeof(head));
        for (size_t i = 0; i < darr_count; i++)
        {
            printf("%d", head[i]);
            if (i < darr_count - 1) printf(", ");
        }
        printf("]\n");
    }
};

int main(){   
    int digits[] = {1,2};
    darray nums(digits);
    nums.debugprint();
    nums.reverse();
    nums.debugprint();
    printf("exit succesfully...");
}