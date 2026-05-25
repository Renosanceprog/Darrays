#include <iostream>
#include <stdio.h>
#include <malloc.h>
#include <stdexcept>

class darray
{
private:
    int  capacity;
    int  count;
    int* head;
public:
    darray(){
        capacity = 1;
        count = 0;
        head  = (int*)malloc(capacity * sizeof(int));
    }
    ~darray(){
        free(head);
    }

    int* start(){
        return head;
    }

    void append(int num){
        if (count >= capacity){
            capacity *= 2;
            head = (int*)realloc(head, capacity * sizeof(int));
        }

        head[count] = num;
        count++;
    }

    void clear(){
        count = 0;
        capacity = 1;
        head = (int*)realloc(head, capacity * sizeof(int));
    }

    void extend(darray array){
        if ((count + array.count) > capacity)
        {
            capacity = (count + array.count) * 2;
            head = (int*)realloc(head, capacity * sizeof(int));
        }
        int newcount = count + array.count;
        int j = 0;
        for (int i = count; i < newcount; i++) {head[i] = array.head[j]; j++;}
        count = newcount;
    }

    int pop(){
        if (count == 0) throw std::invalid_argument("array is empty");
        int item = head[count-1];
        count--;

        if ((capacity >= count * 2) && (capacity > 2)){
            capacity /= 2;
            head = (int*)realloc(head, capacity * sizeof(int));
        }
        return item;
    }

    int pop(int index){
        if (count == 0) throw std::invalid_argument("array is empty");
        int item = head[index];
        for (size_t i = index; i < count-1; i++) head[i] = head[i+1];
        count--;

        if ((capacity >= count * 2) && (capacity > 2)){
            capacity /= 2;
            head = (int*)realloc(head, capacity * sizeof(int));
        }
        return item;
    }

    void debugprint(){
        printf("darray stats: count = %d, max capacity = %d, sizeof(head) = %3u bytes | [", count, capacity, capacity*sizeof(head));
        for (size_t i = 0; i < count; i++)
        {
            printf("%d", head[i]);
            if (i < count - 1) printf(", ");
        }
        printf("]\n");
    }
};



int main(){    
    darray nums;
    darray nums2;
    nums.pop();
    nums2.debugprint();
    nums.debugprint();
    // nums.extend(nums2);
    nums.debugprint();
}