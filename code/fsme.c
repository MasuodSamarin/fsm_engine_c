/*
 * =====================================================================================
 *
 *       Filename:  fsme.c
 *
 *    Description:  finite state machine engine 
 *
 *        Version:  1.0
 *        Created:  08/19/2017 03:21:40 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  masuod samarin
 *   Organization:  
 *
 * =====================================================================================
 */

/******************************************start of the state machine core***************************************************************************/

#include    <stdio.h>
#include    "fsme.h"


static FSME_TRANS * _t; 
static FSME_STATE * _s; 
static void FSME_UpdateState( FSME_FSM * F ) 
{ 
     uint8_t _i = 0; 
     uint8_t _n; 
// set a variable to point to current transition table  
     _t = F->Trans;    
// set a variable to current value of transitions count for current state  
     _n = F->TransNO; 
// loop for all possible transitions from current state 
     for ( ; _i < _n ; _i++ ) 
     { 
// check if the events have occured (conditions are true for a transition to take place) 
          if ( FSME_EVENT_FALSE !=  _t[ _i ].Event()) 
          { 
// update current state 
             F->CurrentState = _t[ _i ].NextState; 
// get a pointer to current state 
            _s =  & ( F->States[ F->CurrentState ]);   
// update current transition table according to current state 
            F->Trans = _s->Trans; 
// update current transitions number according to current state 
            F->TransNO = _s->TransNO;    
// set state changed flag  
            F->StateChanged = FSME_STATE_CHANGED;  
// leave the for loop and function 
            break; 
          } 
     } 
} 

static void FSME_Action( FSME_FSM * F ) 
{ 
     F->States[F->CurrentState].Action(); 
} 


void FSM_Status_Enable( FSME_FSM * F ) 
{ 
     F->Enable = FSME_ENABLE; 
} 
void FSM_Status_Disable( FSME_FSM * F ) 
{ 
     F->Enable = FSME_DISABLE; 
} 
uint8_t FSM_Get_Status( FSME_FSM * F )
{
    return F->Enable;
}


void FSM_Run( FSME_FSM * F ) 
{ 
     if ( !FSM_Get_Status(F) ) 
     { 
// TODO: may reset the FSM into initial state and deactivate outputs 
        printf("\nfsm is disable");
        return; 
     } 
     FSME_UpdateState( F ); 
     FSME_Action( F ); 
} 



//* **********************************************end of state machine core************************************************************************ */


