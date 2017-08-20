/*
 * =====================================================================================
 *
 *       Filename:  fsme.h
 *
 *    Description:  finite state machine engine
 *
 *        Version:  1.0
 *        Created:  08/19/2017 03:22:11 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  masuod samarin
 *   Organization:  
 *
 * =====================================================================================
 */


#ifndef FSME_H
#define FSME_H


typedef unsigned char uint8_t;

#define FSME_EVENT_FALSE    0
#define FSME_EVENT_TRUE     (!FSME_EVENT_FALSE)
#define FSME_STATE_CHANGED      1
#define FSME_STATE_NOT_CHANGED  0
#define FSME_DISABLE    0
#define FSME_ENABLE     1



// function pointer type – for event update functions 
typedef uint8_t (*FSME_PF_EV) (void); 
// transition type  
// describes a transition using the following fields: 
// Event > a pointer to an event (input) function  
// NextState > the next state for the transition  
typedef struct FSME_TRANS FSME_TRANS;
typedef struct  FSME_TRANS{ 
	FSME_PF_EV Event; 
	uint8_t NextState; 
} FSME_TRANS; 


// function pointer type – for action (output) functions 
typedef void (*FSME_PF) (void); 
// state type 
// describes a FSM state using the following fields: 
// Action > a pointer to an action (output) function;  
// the outputs of the FSM that are activated in this state 
// TransNO > the number of transitions from the state 
// Trans > an array that contains the actual transitions infromation: pairs (event, next state) 
typedef struct FSME_STATE FSME_STATE;
typedef  struct FSME_STATE{ 
	FSME_PF Action; 
	uint8_t TransNO; 
	FSME_TRANS  * Trans; 
} FSME_STATE; 




// FSM type 
// describes a FSM using: 
// Enable  > a flag that indicates the state of FSM: enabled or disabled 
// CurrentState > the current state of the FSM 
// StateChanged >flag that indicates a state change  
// StatesNO > the number of states of the FSM 
// States   > an array that contains the states and transitions of the FSM 
// TransNO > the number of transitions from current  state 
// Trans > a reference to an array with the transitions form current state  
typedef struct FSME_FSM FSME_FSM;
typedef struct FSME_FSM{ 
	uint8_t Enable; 
	uint8_t CurrentState; 
	uint8_t StateChanged; 
	uint8_t StatesNO; 
	FSME_STATE  * States; 
	uint8_t TransNO; 
	FSME_TRANS  * Trans; 
} FSME_FSM; 




void FSM_Status_Enable( FSME_FSM * F ); 
void FSM_Status_Disable( FSME_FSM * F ); 
uint8_t FSM_Get_Status( FSME_FSM * F );


void FSM_Run( FSME_FSM * F ); 


#endif //FSME_H
