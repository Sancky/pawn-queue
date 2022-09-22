#include <a_samp>
#include <queue>

new 
	Queue:loginQueue<MAX_PLAYERS, MAX_PLAYERS>; // Create an global queue variable with MAX_PLAYERS sizes.

public OnPlayerConnect(playerid) {
	// When a player connects, add him in queue and if is first show him the login/register dialog.

	Queue_InsertValue(loginQueue, playerid); 

	if(Queue_GetFrontValue(loginQueue) == playerid) { 
		ShowPlayerDialog(playerid, ...); 
	}
	return 1;
}

public OnPlayerDisconnect(playerid, reason) {
	// If the player is in queue, remove him, but if is first in queue we need to show the next player login/register dialog.

	if(Queue_Contains(loginQueue, playerid)) {
		if(Queue_GetFrontValue(loginQueue) == playerid) { 
			Queue_RemoveFrontValue(loginQueue); 
			
			if(!Queue_IsEmpty(loginQueue)) { // Sanity check in case if the queue is empty. 
				ShowPlayerDialog(Queue_GetFrontValue(loginQueue), ...);		
			}
		}
		else { 
			Queue_RemoveValue(loginQueue, playerid); 
		}
	}
	return 1;
}

public OnPlayerLoginOrRegister() { // (just an example of function, the code below should be called when a player log in or register)
	// When a player log in or register, remove him from queue and show the next player the login/register dialog.

	Queue_RemoveFrontValue(loginQueue); 

	if(!Queue_IsEmpty(loginQueue)) { // Sanity check in case if the queue is empty.
		ShowPlayerDialog(Queue_GetFrontValue(loginQueue), ...);	
	}
}