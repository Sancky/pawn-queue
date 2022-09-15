#if defined _queue_included_ 
    #endinput
#endif
#define _queue_included_

// ------------------------------------- //
//              Definition               //
// ------------------------------------- //

#define Queue:%0<%1,%2> \
        Queue@%0[%1], Queue@idx_%0[%2 + 1] = {-1, ...}, Queue@front_%0 = -1, Queue@back_%0 = -1, Queue@count_%0[2]

/*
    e.g: 

        new Queue:queueName<100, 1000>;

        100 = size of the queue.
        1000 = maximum value which can be inserted in queue.
*/

// ------------------------------------- //
//        Foreach Implementation         //
// ------------------------------------- //

#define Queue_Foreach(new%0:<%1>) \
        Queue@count_%1[1] = 0; \
        for(new idx = Queue@front_%1, %0 = Queue@%1[idx == -1 ? 0 : idx]; Queue@count_%1[1] < Queue@count_%1[0]; idx = (idx + 1) % sizeof Queue@%1, %0 = Queue@%1[idx], ++Queue@count_%1[1])
        
/*
    e.g: 

        Queue_Foreach(new val : <queueName>) 
        {
            
        }

        Loop through an queue elements.
*/

// ------------------------------------- //
//              Functions                //
// ------------------------------------- //

#define Queue_IsFull(%0) \
        Queue@count_%0[0] == (sizeof Queue@%0)

/* ---------------------------------------------------------------- */
/*  Queue_IsFull(queue)                                             */
/*                                                                  */
/*  Check if the queue is full.                                     */
/*                                                                  */
/*                                                                  */
/*  Returns an boolean value.                                       */
/* ---------------------------------------------------------------- */

#define Queue_IsEmpty(%0) \
        !Queue@count_%0[0]

/* ---------------------------------------------------------------- */
/*  Queue_IsEmpty(queue)                                            */
/*                                                                  */
/*  Check if the queue is empty.                                    */
/*                                                                  */
/*                                                                  */
/*  Returns an boolean value.                                       */
/* ---------------------------------------------------------------- */

#define Queue_Count(%0) \
        Queue@count_%0[0]

/* ---------------------------------------------------------------- */
/*  Queue_Count(queue)                                              */
/*                                                                  */
/*  Returns the count of the elements from the queue.               */
/* ---------------------------------------------------------------- */

#define Queue_GetBackValue(%0) \
        (Queue@back_%0 != -1 ? Queue@%0[Queue@back_%0] : -1)

/* ---------------------------------------------------------------- */
/*  Queue_GetBackValue(queue)                                       */
/*                                                                  */
/*  Get the back (last) value from the queue.                       */
/*                                                                  */
/*                                                                  */
/*  Return the back (last) value from the queue.                    */
/*  Returns -1 if it doesn't exist.                                 */
/* ---------------------------------------------------------------- */

#define Queue_GetFrontValue(%0) \
        (Queue@front_%0 != -1 ? Queue@%0[Queue@front_%0] : -1)

/* ---------------------------------------------------------------- */
/*  Queue_GetFrontValue(queue)                                      */
/*                                                                  */
/*  Get the front (first) value from the queue.                     */
/*                                                                  */
/*                                                                  */
/*  Return the front (first) value from the queue.                  */
/*  Returns -1 if it doesn't exist.                                 */
/* ---------------------------------------------------------------- */

#define Queue_InsertValue(%0,%1) \
        _Queue_InsertValue(Queue@%0, Queue@idx_%0, Queue@front_%0, Queue@back_%0, Queue@count_%0[0], sizeof Queue@%0, sizeof Queue@idx_%0, %1)

stock _Queue_InsertValue(queue[], indexes[], &front, &back, &count, size_queue, size_indexes, value) {
    if(count == size_queue || (value < 0 || value >= size_indexes) || indexes[value] != -1)
        return 0;

    if(front == -1) 
        front = 0;

    back = (back + 1) % size_queue;
    queue[back] = value;
    indexes[value] = back;

    count ++;
    return 1;
}

/* ---------------------------------------------------------------- */
/*  Queue_InsertValue(queue, value)                                 */
/*                                                                  */
/*  Insert an value in queue.                                       */
/*                                                                  */
/*                                                                  */
/*  Returns 0 if the queue is full, if the value is lower than 0    */
/*  or higher than the maximum allowed value, if the value exists   */
/*  already in queue.                                               */
/*  Returns 1 for success.                                          */
/* ---------------------------------------------------------------- */

#define Queue_RemoveFrontValue(%0) \
        _Queue_RemoveFrontValue(Queue@%0, Queue@idx_%0, Queue@front_%0, Queue@back_%0, Queue@count_%0[0], sizeof Queue@%0)

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
/*  Returns -1 if the queue is empty.                               */
/*  Returns the value removed.                                      */
/* ---------------------------------------------------------------- */

#if defined MemSet || defined memset
    #define Queue_Clear(%0) \
            _Queue_Clear(Queue@idx_%0, sizeof Queue@idx_%0, Queue@count_%0[0], Queue@front_%0, Queue@back_%0)

    stock _Queue_Clear(const indexes[], size_indexes, &count, &front, &back) 
#else
    #define Queue_Clear(%0) \
            _Queue_Clear(Queue@%0, Queue@idx_%0, sizeof Queue@%0, Queue@count_%0[0], Queue@front_%0, Queue@back_%0)

    stock _Queue_Clear(const queue[], indexes[], size_queue, &count, &front, &back) 
#endif
{
    if(count) { 
        #if defined MemSet
            MemSet(indexes, -1, size_indexes);
        #elseif defined memset 
            memset(indexes, -1, size_indexes);
        #else 
            for(new idx = front;; idx = (idx + 1) % size_queue) {
                indexes[queue[idx]] = -1;
                
                if(idx == back)
                    break;
            }
        #endif
 
        count = 0;
        front = back = -1; 
        return 1;
    }
    return 0;
}

/* ---------------------------------------------------------------- */
/*  Queue_Clear(queue)                                              */
/*                                                                  */
/*  Clear the queue.                                                */
/*                                                                  */
/*                                                                  */
/*  Returns 1 if the queue is cleared, otherwise 0 (if the queue    */
/*  is empty).                                                      */
/* ---------------------------------------------------------------- */

#define Queue_GetValuePos(%0,%1) \
        _Queue_GetValuePos(Queue@idx_%0, sizeof Queue@idx_%0, Queue@front_%0, Queue@count_%0[0], %1)

stock _Queue_GetValuePos(const indexes[], size_indexes, front, count, value) 
    return (count && (value >= 0 && value < size_indexes) && indexes[value] != -1) ? indexes[value] - front + 1 : -1;

/* ---------------------------------------------------------------- */
/*  Queue_GetValuePos(queue, value)                                 */
/*                                                                  */
/*  Get the position of an element from the queue.                  */
/*                                                                  */
/*                                                                  */
/*  Returns the position of the element.                            */
/*  Returns -1 if the queue is empty, if the value is lower than 0  */
/*  or higher than the maximum value allowed, if the value doesn't  */
/*  exists in the queue.                                            */
/* ---------------------------------------------------------------- */

#define Queue_Contains(%0,%1) \
        _Queue_Contains(Queue@idx_%0, sizeof Queue@idx_%0, Queue@count_%0[0], %1)

stock bool:_Queue_Contains(const indexes[], size_indexes, count, value) 
    return (count && (value >= 0 && value < size_indexes) && indexes[value] != -1);

/* ---------------------------------------------------------------- */
/*  Queue_Contains(queue, value)                                    */
/*                                                                  */
/*  Check if an value exists in the queue.                          */
/*                                                                  */
/*                                                                  */
/*  Returns an boolean value (true if value exists, otherwise false */
/*  ).                                                              */
/*  Returns -1 if the queue is empty, if the value is lower         */
/*  than 0 or higher than the maximum value allowed, if the value   */
/*  doesn't exists in the queue.                                    */
/* ---------------------------------------------------------------- */
