#include <queue>

// ------------------------------------- //
//              Utils                    //
// ------------------------------------- //

#define _@Queue_Print_Values(%0,%1) \
        Queue_Foreach(new i : %0) format(%1, sizeof %1, "%s %d", %1, i); print(%1)

// ------------------------------------- //
//              Tests                    //
// ------------------------------------- //

_@Queue_Test_Foreach() {
    new 
        Queue:queue<10>;

    //Loop through an empty queue.
    Queue_Foreach(new i : queue) {
        #pragma unused i
    }

    //Insert some values.
    new     
        values[5] = {3, 2, 5, 1, 6};

    for(new i = 0; i < sizeof values; ++i) 
        Queue_InsertValue(queue, values[i]);

    //Check if the values are the correct ones.
    new 
        values_count;

    Queue_ForeachEx(new i, idx : queue) {
        if(values[idx] == i) 
            ++values_count;
    }

    if(values_count != 5) {
        new str[64] = "[Queue Tests] Foreach test 1 failed. Elements:";

        _@Queue_Print_Values(queue, str);

        return 1;
    }

    //Insert some values.
    new     
        values_[6] = {1024, 1048, 1072, 1096, 0, 455}, idx_ = 2;

    for(new i = 0; i < (sizeof values_) - 1; ++i) 
        Queue_InsertValue(queue, values_[i]);

    //Remove some values.
    for(new i = 0; i < 7; ++i)
        Queue_RemoveFrontValue(queue);

    //Insert the last value.
    Queue_InsertValue(queue, values_[(sizeof values_) - 1]);

    //Check if the values are the correct ones.
    values_count = 0;

    Queue_Foreach(new i : queue) {
        if(values_[idx_++] == i)
            values_count ++;
    }

    if(values_count != 4) {
        new str[64] = "[Queue Tests] Foreach test 2 failed. Elements:";

        _@Queue_Print_Values(queue, str);

        return 1;
    }

    new str[64] = "[Queue Tests] Foreach test passed. Elements:";

    _@Queue_Print_Values(queue, str);
    return 1;
} 

_@Queue_Test_Functions() {
    new 
        Queue:queue<10>, values_count;

    //
    //  Insert Test
    //
    
    //Insert some values.
    new 
        values[10] = {4, -5, 6, 44, 2, 10, 0, 50};

    for(new i = 0; i < 8; ++i) 
        Queue_InsertValue(queue, values[i]);

    //Check if the values are the correct ones.
    Queue_ForeachEx(new i, idx : queue) {
        if(values[idx] == i)
            values_count ++;
    }

    //Stopping the test if the queue values are not matching.
    if(values_count != 8) {
        new str[128] = "[Queue Tests] Insert test failed. (queue values are not matching) Elements:";
        
        _@Queue_Print_Values(queue, str);

        return 1;
    }

    //
    //  Clear Test
    //

    //Clearing the queue.
    Queue_Clear(queue);

    //Checking if values are still in queue.
    if(Queue_GetFrontValue(queue) != INVALID_QUEUE_VALUE || !Queue_IsEmpty(queue)) 
        return print("[Queue Tests] Clear test failed. (values are still in queue)");

    else Queue_Foreach(new i : queue) 
        return printf("[Queue Tests] Clear test failed. (values are still in queue)", i);

    //
    //  Remove Test
    //

    //Insert some values.
    new 
        values_[10] = {5, 2, 7, 9, 8, 1, 4, 12, 15, 25};

    for(new i = 0; i < 10; ++i) 
        Queue_InsertValue(queue, values_[i]);

    //Remove some values.
    Queue_RemoveValue(queue, 7);
    Queue_RemoveValue(queue, 1);
    Queue_RemoveValue(queue, 12);
    Queue_RemoveValue(queue, 25);
    Queue_RemoveValue(queue, 5);

    //Insert again some values.
    Queue_InsertValue(queue, 33);
    Queue_InsertValue(queue, 35);
    Queue_InsertValue(queue, 32);
    Queue_InsertValue(queue, 30);

    //Remove some values.
    Queue_RemoveValue(queue, 35);
    Queue_RemoveValue(queue, 30);
    Queue_RemoveFrontValue(queue);

    //Trying to remove non-existing values.
    Queue_RemoveValue(queue, 35);
    Queue_RemoveValue(queue, 30);
    Queue_RemoveValue(queue, 25);

    //Insert again some values.
    Queue_InsertValue(queue, 6);
    Queue_InsertValue(queue, 3);
    Queue_InsertValue(queue, 12);
    Queue_InsertValue(queue, 16);

    //Check if the values are the correct ones.
    new 
        values__[10] = {9, 8, 4, 15, 33, 32, 6, 3, 12, 16}, idx_;

    values_count = 0;

    Queue_Foreach(new i : queue) {
        if(values__[idx_++] == i)
            values_count ++;
    }

    if(values_count != 10) {        
        new str[128] = "[Queue Tests] Remove test failed. (values count not matching). Elements:";
        
        _@Queue_Print_Values(queue, str);

        return 1;
    }

    //
    //  Getters/Others Test
    //

    if(!Queue_IsFull(queue) || Queue_IsEmpty(queue) || Queue_Count(queue) != 10 || Queue_GetBackValue(queue) != 16 || Queue_GetFrontValue(queue) != 9 || Queue_GetValuePos(queue, 12) != 9 || !Queue_Contains(queue, 15) || 
        Queue_Contains(queue, 69) || Queue_GetValuePos(queue, 69) != INVALID_QUEUE_VALUE || Queue_GetValuePos(queue, 16) != 10)
        return print("[Queue Tests] Getters/Others test failed.");

    return print("[Queue Tests] Tests ended. 4/4 passed.");
}