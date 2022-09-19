#if defined _queue_included_ 
    #endinput
#endif
#define _queue_included_

// ------------------------------------- //
//              Definition               //
// ------------------------------------- //

#define Queue:%0<%1,%2> \
        Queue@%0[%1], Queue@idx_%0[%2 + 1] = {-1, ...}, Queue@front_%0 = -1, Queue@back_%0 = -1, Queue@count_%0[2], Queue@size_%0 = %1

#define QueueArray:%0[%1]<%2,%3> /*1d array support*/ \
        Queue@%0[%1][%2], Queue@idx_%0[%1][%3 + 1], Queue@front_%0[%1] = {-1, ...}, Queue@back_%0[%1] = {-1, ...}, Queue@count_%0[%1][2], Queue@size_%0[%1] = {%2, ...}

/*
    e.g: 

        new Queue:queue<100, 1000>;

        * for 1D arrays use

        new QueueArray:queue[100]<100, 1000>;

        100 = size of the queue.
        1000 = maximum value which can be inserted in queue.
*/

// ------------------------------------- //
//        Foreach Implementation         //
// ------------------------------------- //

#define Queue_Foreach(new%0:<%1>) \
        Queue@count_%1[1] = 0; \
        if(Queue@count_%1[0]) for(new Q_Foreach@idx = Queue@front_%1, %0 = Queue@%1[Q_Foreach@idx]; Queue@count_%1[1] < Queue@count_%1[0]; Q_Foreach@idx = (Q_Foreach@idx + 1) % Queue@size_%1, %0 = Queue@%1[Q_Foreach@idx], ++Queue@count_%1[1])
/*
    e.g: 

        Queue_Foreach(new val : <queue>) 
        {
            
        }

        Loop through an queue elements.
*/

// ------------------------------------- //
//              Functions                //
// ------------------------------------- //

#define Queue_IsFull(%0) \
        (Queue@count_%0[0] == Queue@size_%0)

/* ---------------------------------------------------------------- */
/*  Queue_IsFull(queue)                                             */
/*                                                                  */
/*  Check if the queue is full.                                     */
/*                                                                  */
/*                                                                  */
/*  Returns true if the queue is full, otherwise false.             */
/* ---------------------------------------------------------------- */

#define Queue_IsEmpty(%0) \
        (!Queue@count_%0[0])

/* ---------------------------------------------------------------- */
/*  Queue_IsEmpty(queue)                                            */
/*                                                                  */
/*  Check if the queue is empty.                                    */
/*                                                                  */
/*                                                                  */
/*  Returns true if the queue is empty, otherwise false.            */
/* ---------------------------------------------------------------- */

#define Queue_Count(%0) \
        Queue@count_%0[0]

/* ---------------------------------------------------------------- */
/*  Queue_Count(queue)                                              */
/*                                                                  */
/*  Returns the count of the elements from the queue.               */
/* ---------------------------------------------------------------- */

#define Queue_GetBackValue(%0) \
        _Queue_GetBackValue(Queue@%0, Queue@back_%0)

stock _Queue_GetBackValue(const queue[], back) 
    return back != -1 ? queue[back] : -1;

/* ---------------------------------------------------------------- */
/*  Queue_GetBackValue(queue)                                       */
/*                                                                  */
/*  Get the back (last) value from the queue.                       */
/*                                                                  */
/*                                                                  */
/*  Returns the back (last) value from the queue, otherwise -1.     */
/* ---------------------------------------------------------------- */

#define Queue_GetFrontValue(%0) \
        _Queue_GetFrontValue(Queue@%0, Queue@front_%0)

stock _Queue_GetFrontValue(const queue[], front) 
    return front != -1 ? queue[front] : -1;

/* ---------------------------------------------------------------- */
/*  Queue_GetFrontValue(queue)                                      */
/*                                                                  */
/*  Get the front (first) value from the queue.                     */
/*                                                                  */
/*                                                                  */
/*  Returns the front (first) value from the queue, otherwise -1.   */
/* ---------------------------------------------------------------- */

#define Queue_InsertValue(%0,%1) \
        _Queue_InsertValue(Queue@%0, Queue@idx_%0, Queue@front_%0, Queue@back_%0, Queue@count_%0[0], Queue@size_%0, _, %1)

stock bool:_Queue_InsertValue(queue[], indexes[], &front, &back, &count, size_queue, size_indexes = sizeof indexes, value) {
    if(count == size_queue || (value < 0 || value >= size_indexes) || indexes[value] != -1)
        return false;

    if(front == -1) 
        front = 0;

    back = (back + 1) % size_queue;
    queue[back] = value;
    indexes[value] = back;

    count ++;
    return true;
}

/* ---------------------------------------------------------------- */
/*  Queue_InsertValue(queue, value)                                 */
/*                                                                  */
/*  Insert an value in queue.                                       */
/*                                                                  */
/*                                                                  */
/*  Returns true for success, otherwise false.                      */
/* ---------------------------------------------------------------- */

#define Queue_RemoveValue(%0,%1) \
        _Queue_RemoveValue(Queue@%0, Queue@idx_%0, Queue@size_%0, _, Queue@front_%0, Queue@back_%0, Queue@count_%0[0], %1) 

stock bool:_Queue_RemoveValue(queue[], indexes[], size_queue, size_indexes = sizeof indexes, &front, &back, &count, value) {
    if(!count || (value < 0 || value >= size_indexes) || indexes[value] == -1) 
        return false;

    if(front == back)
        front = back = -1;

    else if(front == indexes[value]) 
        front = (front + 1) % size_queue;
    
    else if(back == indexes[value]) 
        back = (back - 1) % size_queue;

    else {
        for(new i = indexes[value]; i != back; i = (i + 1) % size_queue) {
            queue[i] = queue[(i + 1) % size_queue];
            indexes[queue[i]] = i;
        }   

        back = (back - 1) % size_queue;   
    }

    indexes[value] = -1;
    
    count --;

    return true;
}

/* ---------------------------------------------------------------- */
/*  Queue_RemoveValue(queue, value)                                 */
/*                                                                  */
/*  Remove an element from the queue.                               */
/*                                                                  */
/*                                                                  */
/*  Returns true for success, otherwise false.                      */
/* ---------------------------------------------------------------- */

#define Queue_RemoveFrontValue(%0) \
        _Queue_RemoveFrontValue(Queue@%0, Queue@idx_%0, Queue@front_%0, Queue@back_%0, Queue@count_%0[0], Queue@size_%0)

stock _Queue_RemoveFrontValue(const queue[], indexes[], &front, &back, &count, size) {
    if(!count) 
        return -1;

    new const value = queue[front];

    indexes[value] = -1;

    count --;

    if(front == back)
        front = back = -1;

    else 
        front = (front + 1) % size;

    return value;
}

/* ---------------------------------------------------------------- */
/*  Queue_RemoveFrontValue(queue)                                   */
/*                                                                  */
/*  Remove the front (first) value from the queue.                  */
/*                                                                  */
/*                                                                  */
/*  Returns the removed value, otherwise -1 if function failed.     */
/* ---------------------------------------------------------------- */

#define Queue_Clear(%0) \
        _Queue_Clear(Queue@%0, Queue@idx_%0, Queue@size_%0, Queue@count_%0[0], Queue@front_%0, Queue@back_%0)

stock bool:_Queue_Clear(const queue[], indexes[], size_queue, &count, &front, &back)  {
    if(count) { 
        for(new idx = front;; idx = (idx + 1) % size_queue) {
            indexes[queue[idx]] = -1;
            
            if(idx == back)
                break;
        }
 
        count = 0;
        front = back = -1; 
        return true;
    }
    return false;
}

/* ---------------------------------------------------------------- */
/*  Queue_Clear(queue)                                              */
/*                                                                  */
/*  Clear the queue.                                                */
/*                                                                  */
/*                                                                  */
/*  Returns true for success, otherwise false.                      */
/* ---------------------------------------------------------------- */

#define Queue_GetValuePos(%0,%1) \
        _Queue_GetValuePos(Queue@idx_%0, _, Queue@size_%0, Queue@front_%0, Queue@back_%0, Queue@count_%0[0], %1)

stock _Queue_GetValuePos(const indexes[], size_indexes = sizeof indexes, size_queue, front, back, count, value) {
    if(!count || (value < 0 || value >= size_indexes) || indexes[value] == -1)
        return -1;

    if(back < front && indexes[value] <= back)
        return size_queue + (indexes[value] - front + 1);

    return indexes[value] - front + 1;
}

/* ---------------------------------------------------------------- */
/*  Queue_GetValuePos(queue, value)                                 */
/*                                                                  */
/*  Get the position of an element from the queue.                  */
/*                                                                  */
/*                                                                  */
/*  Returns the position of the element, otherwise -1.              */
/* ---------------------------------------------------------------- */

#define Queue_Contains(%0,%1) \
        _Queue_Contains(Queue@idx_%0, _, Queue@count_%0[0], %1)

stock bool:_Queue_Contains(const indexes[], size_indexes = sizeof indexes, count, value) 
    return (count && (value >= 0 && value < size_indexes) && indexes[value] != -1);

/* ---------------------------------------------------------------- */
/*  Queue_Contains(queue, value)                                    */
/*                                                                  */
/*  Check if an value exists in the queue.                          */
/*                                                                  */
/*                                                                  */
/*  Returns true if value exists, otherwise false.                  */
/* ---------------------------------------------------------------- */

#define Queue_Init(%0) \
        _Queue_Init(Queue@idx_%0, _, _) 

stock _Queue_Init(indexes[][], size_1 = sizeof indexes, size_2 = sizeof indexes[]) {
    for(new i = 0; i < size_1; ++i) {
        for(new idx = 0; idx < size_2; ++idx)
            indexes[i][idx] = -1;  
    }
    return 1;
}

/* ---------------------------------------------------------------- */
/*  Queue_Init(queue)                                               */
/*                                                                  */
/*  Initialise an queue array.                                      */
/*                                                                  */
/*  IMPORTANT! Use it only ONCE before first use of an queue        */
/*  array to work properly.                                         */
/* ---------------------------------------------------------------- */