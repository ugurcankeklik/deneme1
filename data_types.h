#ifndef DATA_TYPES_H
#define DATA_TYPES_H

// ==================== WRITE YOUR OPTIONAL DATA TYPES IF YOU NEED =============

enum TILES 
{
	Tile_1, Tile_2, Tile_3,
    Tile_4, Tile_5, Tile_6,
    Tile_7, Tile_8, Tile_Empty

};


// ====== WRITE YOUR COMPULSORY (BUT SPECIFIC TO THE PROBLEM) DATA TYPES =======

enum ACTIONS // All possible actions
{
	Move_Up, Move_Down, Move_Left, Move_Right
};

typedef struct State  
{
    enum TILES board[3][3];  //3*3 matris
    float h_n;   // Heuristic function
      
}State;

// ================== YOU DO NOT NEED TO CHANGE THIS PART ======================

enum METHODS
{
	BreastFirstSearch = 1,   UniformCostSearch = 2,        DepthFirstSearch = 3,    
	DepthLimitedSearch= 4,   IterativeDeepeningSearch = 5, GreedySearch = 6,
    AStarSearch = 7, GeneralizedAStarSearch = 8  
};

// This struct is used to determine a new state and action in transition model
typedef struct Transition_Model
{
    State new_state;
    float step_cost;
}Transition_Model;

typedef struct Node
{
    State state;
    float path_cost;
    enum ACTIONS action; //The action applied to the parent to generate this node
    struct Node *parent;
    int Number_of_Child; // required for depth-first search algorithms
}Node;

typedef struct Queue  // Used for frontier
{
    Node *node;
    struct Queue *next;
}Queue;



#endif
