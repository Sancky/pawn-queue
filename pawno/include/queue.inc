#if defined _queue_included_ 
    #endinput
#endif
#define _queue_included_

// ------------------------------------- //
//              Constants                //
// ------------------------------------- //

#define INVALID_QUEUE_VALUE -1  

// ------------------------------------- //
//             Macro guards              //
// ------------------------------------- //

#define Queue@%0\32; Queue@
#define Queue@front_%0\32; Queue@front_
#define Queue@back_%0\32; Queue@back_
#define Queue@count_%0\32; Queue@count_
#define Queue@size_%0\32; Queue@size_

// ------------------------------------- //
//              Definition               //
// ------------------------------------- //

#define Queue:%0<%1> \
        Queue@%0[%1], Queue@front_%0 = INVALID_QUEUE_VALUE, Queue@back_%0 = INVALID_QUEUE_VALUE, Queue@count_%0, Queue@size_%0 = %1

#define QueueArray:%0[%1]<%2> /*1d array support*/ \
        Queue@%0[%1][%2], Queue@front_%0[%1] = {INVALID_QUEUE_VALUE, ...}, Queue@back_%0[%1] = {INVALID_QUEUE_VALUE, ...}, Queue@count_%0[%1], Queue@size_%0[%1] = {%2, ...}

// ------------------------------------- //
//        Foreach Implementation         //
// ------------------------------------- //

#define Queue_Foreach(new%0:%1) \
        if(Queue@count_%1) for(new Q_Foreach@count, Q_Foreach@idx = Queue@front_%1, %0 = Queue@%1[Q_Foreach@idx]; Q_Foreach@count++ < Queue@count_%1; Q_Foreach@idx = (Q_Foreach@idx + 1) % Queue@size_%1, %0 = Queue@%1[Q_Foreach@idx])

#define Queue_ForeachEx(new%0,%2:%1) \
        if(Queue@count_%1) for(new Q_Foreach@count, %2 = Queue@front_%1, %0 = Queue@%1[%2]; Q_Foreach@count++ < Queue@count_%1; %2 = (%2 + 1) % Queue@size_%1, %0 = Queue@%1[%2])

// ------------------------------------- //
//              Functions                //
// ------------------------------------- //

#define Queue_IsFull(%0) \
        (Queue@count_%0 == Queue@size_%0)

/* ---------------------------------------------------------------- */
/*  Queue_IsFull(queue)                                             */
/*                                                                  */
/*  Check if the queue is full.                                     */
/*                                                                  */
/*                                                                  */
/*  Returns true if the queue is full, otherwise false.             */
/* ---------------------------------------------------------------- */

#define Queue_IsEmpty(%0) \
        (!Queue@count_%0)

/* ---------------------------------------------------------------- */
/*  Queue_IsEmpty(queue)                                            */
/*                                                                  */
/*  Check if the queue is empty.                                    */
/*                                                                  */
/*                                                                  */
/*  Returns true if the queue is empty, otherwise false.            */
/* ---------------------------------------------------------------- */

#define Queue_Count(%0) \
        Queue@count_%0

/* ---------------------------------------------------------------- */
/*  Queue_Count(queue)                                              */
/*                                                                  */
/*  Returns the count of the elements from the queue.               */
/* ---------------------------------------------------------------- */

#define Queue_GetBackValue(%0) \
        _Queue_GetBackValue(Queue@%0, Queue@back_%0)

stock _Queue_GetBackValue(const queue[], back) 
    return back != INVALID_QUEUE_VALUE ? queue[back] : INVALID_QUEUE_VALUE;

/* ---------------------------------------------------------------- */
/*  Queue_GetBackValue(queue)                                       */
/*                                                                  */
/*  Get the back (last) value from the queue.                       */
/*                                                                  */
/*                                                                  */
/*  Returns the back (last) value from the queue, otherwise         */
/*  INVALID_QUEUE_VALUE.                                            */
/* ---------------------------------------------------------------- */

#define Queue_GetFrontValue(%0) \
        _Queue_GetFrontValue(Queue@%0, Queue@front_%0)

stock _Queue_GetFrontValue(const queue[], front) 
    return front != INVALID_QUEUE_VALUE ? queue[front] : INVALID_QUEUE_VALUE;

/* ---------------------------------------------------------------- */
/*  Queue_GetFrontValue(queue)                                      */
/*                                                                  */
/*  Get the front (first) value from the queue.                     */
/*                                                                  */
/*  Returns the front (first) value from the queue, otherwise       */
/*  INVALID_QUEUE_VALUE.                                            */
/* ---------------------------------------------------------------- */

#define Queue_InsertValue(%0,%1) \
        _Queue_InsertValue(Queue@%0, Queue@front_%0, Queue@back_%0, Queue@count_%0, Queue@size_%0, _Queue_GetValueIndex(Queue@%0, Queue@front_%0, Queue@back_%0, Queue@size_%0, Queue@count_%0, %1), %1)

stock bool:_Queue_InsertValue(queue[], &front, &back, &count, size, value_index, value) {
    if(count == size || value_index != INVALID_QUEUE_VALUE)
        return false;

    if(front != INVALID_QUEUE_VALUE) 
        back = (back + 1) % size;

    else 
        front = back = 0;
    
    queue[back] = value;

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
        _Queue_RemoveValue(Queue@%0, Queue@size_%0, Queue@front_%0, Queue@back_%0, Queue@count_%0, _Queue_GetValueIndex(Queue@%0, Queue@front_%0, Queue@back_%0, Queue@size_%0, Queue@count_%0, %1)) 

stock bool:_Queue_RemoveValue(queue[], size, &front, &back, &count, value_index) {
    if(value_index == INVALID_QUEUE_VALUE) 
        return false;

    if(front == back)
        front = back = INVALID_QUEUE_VALUE;

    else if(front == value_index) 
        front = (front + 1) % size;
    
    else if(back == value_index) 
        back = (back - 1) % size;

    else {
        for(new i = value_index; i != back; i = (i + 1) % size) 
            queue[i] = queue[(i + 1) % size];

        back = (back - 1) % size;   
    }
    
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
        _Queue_RemoveFrontValue(Queue@%0, Queue@front_%0, Queue@back_%0, Queue@count_%0, Queue@size_%0)

stock _Queue_RemoveFrontValue(const queue[], &front, &back, &count, size) {
    if(!count) 
        return INVALID_QUEUE_VALUE;

    new const value = queue[front];

    count --;

    if(front == back)
        front = back = INVALID_QUEUE_VALUE;

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
/*  Returns the removed value, otherwise INVALID_QUEUE_VALUE        */
/*  if function failed.                                             */
/* ---------------------------------------------------------------- */

#define Queue_Clear(%0) \
        _Queue_Clear(Queue@count_%0, Queue@front_%0, Queue@back_%0)

stock _Queue_Clear(&count, &front, &back)  {
    if(count) { 
        count = 0;
        front = back = INVALID_QUEUE_VALUE; 
    }
}

/* ---------------------------------------------------------------- */
/*  Queue_Clear(queue)                                              */
/*                                                                  */
/*  Clear the queue.                                                */
/*                                                                  */
/*                                                                  */
/*  Doesn't return anything.                                        */
/* ---------------------------------------------------------------- */

#define Queue_GetValuePos(%0,%1) \
        _Queue_GetValuePos(Queue@size_%0, Queue@front_%0, Queue@back_%0, _Queue_GetValueIndex(Queue@%0, Queue@front_%0, Queue@back_%0, Queue@size_%0, Queue@count_%0, %1))

stock _Queue_GetValuePos(size, front, back, value_index) {
    if(value_index == INVALID_QUEUE_VALUE)
        return INVALID_QUEUE_VALUE;

    if(back < front && value_index <= back)
        return size + (value_index - front + 1);

    return value_index - front + 1;
}

/* ---------------------------------------------------------------- */
/*  Queue_GetValuePos(queue, value)                                 */
/*                                                                  */
/*  Get the position of an element from the queue.                  */
/*                                                                  */
/*                                                                  */
/*  Returns the position of the element, otherwise                  */
/*  INVALID_QUEUE_VALUE.                                            */
/* ---------------------------------------------------------------- */

#define Queue_Contains(%0,%1) \
        (_Queue_GetValueIndex(Queue@%0, Queue@front_%0, Queue@back_%0, Queue@size_%0, Queue@count_%0, %1) != INVALID_QUEUE_VALUE)

/* ---------------------------------------------------------------- */
/*  Queue_Contains(queue, value)                                    */
/*                                                                  */
/*  Check if an value exists in the queue.                          */
/*                                                                  */
/*                                                                  */
/*  Returns true if value exists, otherwise false.                  */
/* ---------------------------------------------------------------- */

// ------------------------------------- //
//          Internal Functions           //
// ------------------------------------- //

stock _Queue_GetValueIndex(const queue[], idx, end, size, count, value) {
    if(!count)
        return INVALID_QUEUE_VALUE;

    if(queue[end] == value)
        return end;

    while(idx != end) {
        if(queue[idx] == value)
            return idx;

        idx = (idx + 1) % size;
    }
    return INVALID_QUEUE_VALUE;
}

/* ---------------------------------------------------------------- */
/*  _Queue_GetValueIndex(queue, value)                              */
/*                                                                  */
/*  Get the index for a specific value from queue.                  */
/*                                                                  */
/*                                                                  */
/*  Returns the value's index, otherwise INVALID_QUEUE_VALUE.       */
/* ---------------------------------------------------------------- */