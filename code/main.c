/*
 * =====================================================================================
 *
 *       Filename:  fsm.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  08/17/2017 01:46:05 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  masuod samarin
 *   Organization:  
 *
 * =====================================================================================
 */
#include	<stdlib.h>
#include    <stdio.h>
#include    <time.h>

#include    "fsme.h"

typedef unsigned char uint8_t;





typedef enum {

    FSM1_S0 = 0,
    FSM1_S1,
    FSM1_S2,
    FSM1_S3,
    FSM1_MAX_STATE

}FSM1_STATES; 

int in, out;


/*
 * inputs (events) prototype
 */
static uint8_t FSM1_EventsUpdate0( void );
static uint8_t FSM1_EventsUpdate1( void ); 

/*
 * outputs (actions) prototype
 */
static void FSM1_ActionClr( void );
static void FSM1_ActionSet( void ); 



// state transitions for each state
static FSME_TRANS FSM1_S0_TRANS[] =  
{
    { FSM1_EventsUpdate0, FSM1_S1 } 
}; 

static FSME_TRANS FSM1_S1_TRANS[] =  
{
    { FSM1_EventsUpdate0, FSM1_S2 }, 
    { FSM1_EventsUpdate1, FSM1_S0 } 
}; 

static FSME_TRANS FSM1_S2_TRANS[] =  
{ 
    { FSM1_EventsUpdate1, FSM1_S3 } 
}; 

static FSME_TRANS FSM1_S3_TRANS[] =  
{
    { FSM1_EventsUpdate0, FSM1_S1 },  
    { FSM1_EventsUpdate1, FSM1_S0 }
}; 


// state outputs and transitions; entire table
static FSME_STATE FSM1_STATES_TABLE[] = 
{ 
    { FSM1_ActionClr, 1, FSM1_S0_TRANS }, 
    { FSM1_ActionClr, 2, FSM1_S1_TRANS }, 
    { FSM1_ActionClr, 1, FSM1_S2_TRANS },     
    { FSM1_ActionSet, 2, FSM1_S3_TRANS } 
}; 

/*
 * instance of FSM
 * wrap all data which handle by FSM_Run
 */
static FSME_FSM FSM1 =  { 
    .Enable = FSME_ENABLE,
    .CurrentState = FSM1_S0,  
    .StateChanged = FSME_STATE_CHANGED, 
    .StatesNO = FSM1_MAX_STATE, 
    .States = FSM1_STATES_TABLE, 
    .TransNO = 1, 
    .Trans = FSM1_S0_TRANS  
}; 


/*
 * inputs and outputs (events and actions) implementation
 */
static uint8_t FSM1_EventsUpdate0( void )
{ 
    return ( in == 0 ); 
} 
static uint8_t FSM1_EventsUpdate1( void ) 
{ 
    return ( in == 1 ); 
} 

static void FSM1_ActionClr( void )
{ 
    if ( FSM1.StateChanged == FSME_STATE_CHANGED )  
    { 
        //actions to be executed only once in this state at the state change 
         out = 0; 
//         printf("\n\t FSM1_ActionClr ----> state change");
         // reset state changed flag 
         FSM1.StateChanged =     
         FSME_STATE_NOT_CHANGED; 
    } 
    else 
    { 
     // actions to be executed continuously in this state 
//         printf("\n\t FSM1_ActionClr ----------------> executed continouslly");
    } 
} 
static void FSM1_ActionSet( void ) 
{ 
    if ( FSM1.StateChanged  ==  FSME_STATE_CHANGED )  
    { 
        // actions to be executed only once in this state at the state change 
        out = 1; 
//         printf("\n\t FSM1_ActionSet ----> state change");
        // reset state changed flag 
        FSM1.StateChanged =    
        FSME_STATE_NOT_CHANGED; 
    } 
    else 
    { 
        // actions to be executed continouslly in this state 
//         printf("\n\t FSM1_ActionSet ----------------> executed continouslly");
    } 
} 






/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  
 * =====================================================================================
 */
    int
main ( int argc, char *argv[] )
{

    printf("\n  simple fsm demo \n");
    int i=0;
    srand(time(NULL));
    FSM_Status_Enable(&FSM1);

    printf ("\n\tin: ");
    for (; i<100; i++){

        in = rand() % 2;
        FSM_Run(&FSM1);
        if (out){
            printf("%d, ", in);
            printf ("\n\e[1;34m-->out:%d\e[0m", out);
            printf ("\n\tin: ");
        }
        else
            printf("%d, ", in);
    
    }
    printf("\n");

    return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */

