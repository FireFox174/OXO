#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <SDL2\SDL.h>
#include <SDL2/SDL_error.h>

// Vars
SDL_Window* window;
SDL_Renderer *Render;
SDL_Event event;
int running;
// Game state vars
char string[];
int player;
int winner;
int isfull, isempty = 0;

// Visual grid 
SDL_Rect Grid[3][3] = 
{
    {
        {0, 0, 100, 100},
        {0, 100, 100, 100},
        {0, 200, 100, 100}
    },
    {
        {100, 0, 100, 100},
        {100, 100, 100, 100},
        {100, 200, 100, 100}
    },
    {
        {200, 0, 100, 100},
        {200, 100, 100, 100},
        {200, 200, 100, 100}
    },
};
// Logical grid
int GridState[3][3] =
{
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0}
};
// Set up message box button data
int buttonid;
const SDL_MessageBoxButtonData buttons[] = 
{
    {SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 2, "Yes"},
    {SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, 1, "No"}
};

    // Set up color scheme for the message box
const SDL_MessageBoxColorScheme colorScheme = 
{
    {
        // [SDL_MESSAGEBOX_COLOR_BACKGROUND]
        {255, 0, 0},
        // [SDL_MESSAGEBOX_COLOR_TEXT]
        {0, 255, 0},
        // [SDL_MESSAGEBOX_COLOR_BUTTON_BORDER]
        {255, 255, 0},
        // [SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND]
        {0, 0, 255},
        // [SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED]
        {255, 0, 255}
    }
};

// Set up message box data
SDL_MessageBoxData MessageBox;

    
// Main function
int WinMain(int argc, char *argv[])
{
    // Set vars
    
    running = 1;
    player = 1;
    winner = 1; 
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) 
    {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "error", SDL_GetError(), NULL);
        return SDL_Error;
    }
    // Open window
    window = SDL_CreateWindow("Tic Tac Toe", 
            SDL_WINDOWPOS_CENTERED, 
            SDL_WINDOWPOS_CENTERED,
                300,
                300,
                0);
    // Create render
    Render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    // Create message box
    MessageBox = (SDL_MessageBoxData){
        SDL_MESSAGEBOX_INFORMATION, 
        window,
        "Play Again?",
        "",
        SDL_arraysize(buttons),
        buttons,
        &colorScheme
    };

    // Game loop
    while (running)
    {
        // Get events
        while (SDL_PollEvent(&event))
        {
            // Check if game should close
            if (event.type == SDL_QUIT)
            {
                running = 0;
                break;
            }
            UpdateGrid();
        }
        // Render game
        SDL_SetRenderDrawColor(Render, 255, 255, 255, 255);
        SDL_RenderClear(Render); 
        DrawGrid();
        SDL_RenderPresent(Render);
        OnWin();
    }
    // Close game
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

void UpdateGrid()
{
    // Check each cell
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            // Mouse position
            SDL_Point Pos = { 0, 0 };
            SDL_GetMouseState(&Pos.x, &Pos.y);
            // Check if mouse is in the cell and mouse clicked
            if (SDL_PointInRect(&Pos, &Grid[i][j]) 
            && GridState[i][j] == 0 &&
            event.type == SDL_MOUSEBUTTONDOWN && 
            event.button.button == SDL_BUTTON_LEFT
            && isfull < 9)
            { 
                // Set X
                if (player) GridState[i][j] = 1;
                // Set 0
                if (!player) GridState[i][j] = -1;
                player = !player;
                isfull++;
                printf("T1\n");
            }
        }
    }
}

void OnWin()
{
    if (CheckGrid(GridState) && winner != 0)
    {
        if (!player) MessageBox.message = "Player 1 has Won!!!";
        if (player) MessageBox.message = "Player 2 has Won!!!";
        SDL_ShowMessageBox(&MessageBox, &buttonid);
        if (buttonid == 2)
        {
            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    GridState[i][j] = 0;
                }
            }
            printf("T2\n");
            isfull = 0;
            isempty = 0; 
        }
        if (buttonid == 1)
        {
            winner = 0;
            SDL_PushEvent(SDL_QUIT);
        }              
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                GridState[i][j] = 0;
            }
        }
        isfull = 0;
        isempty = 0; 
    }
}

int CheckGrid(int GridState[3][3]) 
{
    
    // Check rows for a win
    for (int i = 0; i < 3; i++) 
    {
        if (GridState[i][0] + GridState[i][1] + GridState[i][2] == 3 ||  // Check for 3 X's in a row
            GridState[i][0] + GridState[i][1] + GridState[i][2] == -3) // Check for 3 O's in a row
        {  
            return 1;
        }
    }

    // Check columns for a win
    for (int j = 0; j < 3; j++) 
    {
        if (GridState[0][j] + GridState[1][j] + GridState[2][j] == 3 ||  // Check for 3 X's in a column
            GridState[0][j] + GridState[1][j] + GridState[2][j] == -3) // Check for 3 O's in a column
        {  
            return 1;  // Found a winning column
        }
    }

    // Check diagonals for a win
    if ((GridState[0][0] + GridState[1][1] + GridState[2][2] == 3 ||  // Check for 3 X's in the main diagonal
         GridState[0][0] + GridState[1][1] + GridState[2][2] == -3) ||  // Check for 3 O's in the main diagonal
        (GridState[0][2] + GridState[1][1] + GridState[2][0] == 3 ||  // Check for 3 X's in the other diagonal
         GridState[0][2] + GridState[1][1] + GridState[2][0] == -3))  // Check for 3 O's in the other diagonalrunning = 0;
    {
        return 1;  // Found a winning diagonal
    } 
    if (isfull >= 9) 
    {
        isempty = 0;
        isfull = 0; 
        printf("T3\n");
    }
    if (isfull >= 9)
    {
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                GridState[i][j] = 0;
            }
        }
        printf("T4\n");
        isempty++;
    }

    return 0;  // No winning combinations found
}

void DrawGrid()
{
    // Goes through each cell
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            // Draws X as red
            if (GridState[i][j] == 1)
            {
                SDL_SetRenderDrawColor(Render, 255, 0, 0, 255);
                SDL_RenderFillRect(Render, &Grid[i][j]);
                SDL_RenderDrawRect(Render, &Grid[i][j]);
            }
            // Draws 0 as blue
            else if (GridState[i][j] == -1)
            {
                SDL_SetRenderDrawColor(Render, 0, 0, 255, 255);
                SDL_RenderFillRect(Render, &Grid[i][j]);
                SDL_RenderDrawRect(Render, &Grid[i][j]);
            }
            // Draws white for null
            else
            {
                SDL_SetRenderDrawColor(Render, 0, 0, 0, 255);
                SDL_RenderDrawRect(Render, &Grid[i][j]);
            }
        }
    }
}
