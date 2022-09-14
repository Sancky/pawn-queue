#include <queue>

_@Queue_Foreach_Test_() {
	print("\n\n\n ---- Test started ---- \n\n\n");

	new 
		Queue:queueTest<10, 5000>;

	Queue_InsertValue(queueTest, -500000); //error
	Queue_InsertValue(queueTest, (sizeof Queue@queueTest) + 500000); //error
	Queue_InsertValue(queueTest, -1); //error

	Queue_InsertValue(queueTest, 65); //removed
	Queue_InsertValue(queueTest, 70); //removed
	Queue_InsertValue(queueTest, 85); //removed
	Queue_InsertValue(queueTest, 90); //removed
	Queue_InsertValue(queueTest, 100);
	Queue_InsertValue(queueTest, 223);

	Queue_RemoveFrontValue(queueTest); //65
	Queue_RemoveFrontValue(queueTest); //70
	Queue_RemoveFrontValue(queueTest); //85

	Queue_InsertValue(queueTest, 54);
	Queue_InsertValue(queueTest, 69);
	Queue_InsertValue(queueTest, 79);
	Queue_InsertValue(queueTest, 27);
	Queue_InsertValue(queueTest, 47);
	Queue_InsertValue(queueTest, 65);
	Queue_InsertValue(queueTest, 85);
	Queue_RemoveFrontValue(queueTest); //90
	Queue_InsertValue(queueTest, 0);
	Queue_InsertValue(queueTest, 150); //full queue, not added

	new 
		string[256] = "Queue Elements: ";

	Queue_Foreach(new i : <queueTest>) {
		format(string, sizeof string, Queue_GetBackValue(queueTest) == i ? "%s%d." : "%s%d, ", string, i);
	}

	printf("%s (expected values: 100, 223, 54, 69, 79, 27, 47, 65, 85, 0)", string);

	Queue_Clear(queueTest);

	Queue_InsertValue(queueTest, 65); 
	Queue_InsertValue(queueTest, 70); 
	Queue_InsertValue(queueTest, 85); 
	Queue_InsertValue(queueTest, 90); 
	Queue_InsertValue(queueTest, 100);
	Queue_InsertValue(queueTest, 223);

	string = "Queue Elements: ";

	Queue_Foreach(new i : <queueTest>) {
		format(string, sizeof string, Queue_GetBackValue(queueTest) == i ? "%s%d." : "%s%d, ", string, i);
	}

	printf("%s (expected values: 65, 70, 85, 90, 100, 223)", string);

	Queue_Clear(queueTest);

	print("\n\n\n ---- Testing done successfully ---- \n\n\n");
}

_@Queue_Full_Test_() { 
	print("\n\n\n ---- Test started ---- \n\n\n");

	new 
		Queue:queueTest<10, 5000>;

	Queue_InsertValue(queueTest, -5); //error
	Queue_InsertValue(queueTest, 60000); //error

	printf("Queue Count: %d (expected: 0)", Queue_Count(queueTest));

	Queue_InsertValue(queueTest, 8);
	Queue_InsertValue(queueTest, 2);
	Queue_InsertValue(queueTest, 3);
	Queue_InsertValue(queueTest, 9);
	Queue_InsertValue(queueTest, 8); //duplicate
	Queue_InsertValue(queueTest, 3); //duplicate

	printf("Queue Count: %d (expected: 4)", Queue_Count(queueTest));

	new 
		string[256] = "Queue Elements: ";

	Queue_Foreach(new i : <queueTest>) {
		format(string, sizeof string, Queue_GetBackValue(queueTest) == i ? "%s%d." : "%s%d, ", string, i);
	}

	printf("%s (expected values: 8, 2, 3, 9)", string);

	Queue_RemoveFrontValue(queueTest); //removing 8
	Queue_RemoveFrontValue(queueTest); //removing 2

	string = "Queue Elements: ";

	Queue_Foreach(new i : <queueTest>) {
		format(string, sizeof string, Queue_GetBackValue(queueTest) == i ? "%s%d." : "%s%d, ", string, i);
	}

	printf("%s (expected values: 3, 9)", string);

	printf("Queue Elements Positions: 3 (%d, expected 1), 9 (%d, expected 2), 5 (%d, expected -1)", Queue_GetValuePos(queueTest, 3), Queue_GetValuePos(queueTest, 9), Queue_GetValuePos(queueTest, 5));

	Queue_InsertValue(queueTest, 65);
	Queue_InsertValue(queueTest, 70);
	Queue_InsertValue(queueTest, 85);
	Queue_InsertValue(queueTest, 90);
	Queue_InsertValue(queueTest, 100);
	Queue_InsertValue(queueTest, 223);
	Queue_InsertValue(queueTest, 89);
	Queue_InsertValue(queueTest, 4999); 
	Queue_InsertValue(queueTest, 18); //full queue, not added
	Queue_InsertValue(queueTest, sizeof Queue@queueTest); //error

	string = "Queue Elements: ";

	Queue_Foreach(new i : <queueTest>) {
		format(string, sizeof string, Queue_GetBackValue(queueTest) == i ? "%s%d." : "%s%d, ", string, i);
	}

	printf("%s (expected values: 3, 9, 65, 70, 85, 90, 100, 223, 89, 4999)", string);	

	printf("IsFull: %d (expected: 1), IsEmpty: %d (expected: 0), Count: %d (expected: 10), BackValue: %d (expected: 4999 (%d)), FrontValue: %d (expected: 3 (%d))", Queue_IsFull(queueTest), Queue_IsEmpty(queueTest), Queue_Count(queueTest), Queue_GetBackValue(queueTest), Queue@idx_queueTest[4999], Queue_GetFrontValue(queueTest), Queue@idx_queueTest[3]);

	Queue_Clear(queueTest);

	printf("Count: %d (expected: 0), Back: %d (expected: -1), Front: %d (expected: -1), Indexes: 3 (%d, expected: -1), 4999 (%d, expected: -1)", Queue_Count(queueTest), Queue_GetBackValue(queueTest), Queue_GetFrontValue(queueTest), Queue@idx_queueTest[3], Queue@idx_queueTest[4999]);

	print("\n\n\n ---- Testing done successfully! ----");
}