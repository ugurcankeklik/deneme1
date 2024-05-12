/* 
    These functions are compulsory for search algorithms but they are specific
    to problems. More clearly, you must must update their blocks but do not change
    their input and output parameters.
    
    Also, you can add new functions at the end of file by declaring them in GRAPH_SEARCH.h
*/

#include "GRAPH_SEARCH.h"
#include "data_types.h"
#include <stdio.h>
#include <stdlib.h>

//______________________________________________________________________________
State* Create_State()
{
    State *state = (State *)malloc(sizeof(State));
    if(state == NULL)
        Warning_Memory_Allocation(); 
    
    // Initialize the puzzle with a default configuration
    state->board[0][0] = 0; state->board[0][1] = 2; state->board[0][2] = 3;
    state->board[1][0] = 4; state->board[1][1] = 5; state->board[1][2] = 6;
    state->board[2][0] = 7; state->board[2][1] = 8; state->board[2][2] = 1;
    
    return state;    
}

//______________________________________________________________________________
void Print_State(const State *const state)
{
    printf("\n");
    int i;
    for(i = 0; i < BOARD_SIZE; i++) {
    	int j;
        for (j = 0; j < BOARD_SIZE; j++) {
            if (state->board[i][j] == 0)
                printf("  "); // Print two spaces for the empty tile
            else
                printf("%2d", state->board[i][j]);
            printf(" ");
        }
        printf("\n");
    }
}

//______________________________________________________________________________
void Print_Action(const enum ACTIONS action)
{
    switch(action){
        case Move_Left:  printf("Move_Left\n");  break;
        case Move_Right: printf("Move_Right\n"); break;
        case Move_Up:    printf("Move_Up\n");    break;
        case Move_Down:  printf("Move_Down\n");  break;
    }        
}

//______________________________________________________________________________
int Result(const State *const parent_state, const enum ACTIONS action, Transition_Model *const trans_model)
{
    int empty_row, empty_col;
    
    // Find the position of the empty tile (0)
    int i;
    for(i = 0; i < BOARD_SIZE; i++) {
    	int j;
        for(j = 0; j < BOARD_SIZE; j++) {
            if (parent_state->board[i][j] == 0) {
                empty_row = i;
                empty_col = j;
                break;
            }
        }
    }
    
    // Check if the action is valid based on the position of the empty tile
    if (action == Move_Left && empty_col > 0) {
        // Swap the empty tile with the tile to its left
        trans_model->new_state = *parent_state;
        trans_model->new_state.board[empty_row][empty_col] = parent_state->board[empty_row][empty_col - 1];
        trans_model->new_state.board[empty_row][empty_col - 1] = 0;
        trans_model->step_cost = 1;
        return TRUE;
    } else if (action == Move_Right && empty_col < BOARD_SIZE - 1) {
        // Swap the empty tile with the tile to its right
        trans_model->new_state = *parent_state;
        trans_model->new_state.board[empty_row][empty_col] = parent_state->board[empty_row][empty_col + 1];
        trans_model->new_state.board[empty_row][empty_col + 1] = 0;
        trans_model->step_cost = 1;
        return TRUE;
    } else if (action == Move_Up && empty_row > 0) {
        // Swap the empty tile with the tile above it
        trans_model->new_state = *parent_state;
        trans_model->new_state.board[empty_row][empty_col] = parent_state->board[empty_row - 1][empty_col];
        trans_model->new_state.board[empty_row - 1][empty_col] = 0;
        trans_model->step_cost = 1;
        return TRUE;
    } else if (action == Move_Down && empty_row < BOARD_SIZE - 1) {
        // Swap the empty tile with the tile below it
        trans_model->new_state = *parent_state;
        trans_model->new_state.board[empty_row][empty_col] = parent_state->board[empty_row + 1][empty_col];
        trans_model->new_state.board[empty_row + 1][empty_col] = 0;
        trans_model->step_cost = 1;
        return TRUE;
    }
    
    // Action is not valid
    return FALSE;
}

//______________________________________________________________________________
float Compute_Heuristic_Function(const State *const state, const State *const goal)
{
    float h = 0;
    
    // Compute the Manhattan distance heuristic
    int i;
    for(i = 0; i < BOARD_SIZE; i++) {
    	int j;
        for(j = 0; j < BOARD_SIZE; j++) {
            int value = state->board[i][j];
            if (value != 0) {
                int target_row = (value - 1) / BOARD_SIZE;
                int target_col = (value - 1) % BOARD_SIZE;
                h += abs(i - target_row) + abs(j - target_col);
            }
        }
    }
    
    return h;
}

//_______________ Update if your goal state is not determined initially ___________________________________
int Goal_Test(const State *const state, const State *const goal_state)
{
    // Check if the current state matches the goal state
    int i;
    for(i = 0; i < BOARD_SIZE; i++) {
    	int j;
        for(j = 0; j < BOARD_SIZE; j++) {
            if (state->board[i][j] != goal_state->board[i][j]) {
                return FALSE; // Current state does not match goal state
            }
        }
    }
    return TRUE; 
}


