#include <iostream>

struct List
{
    char board[3][3];
    List* next;
};


void smartDraw(char board[3][3])
{
    int cnt = 1;
    for (int i = 0; i < 3; ++i)
    {
	    for (int j = 0; j < 3; ++j)
	    {
	        if (board[i][j] == '_')
	        {
		        std::cout << cnt << ' ';
	        }
	        else
	        {
		        std::cout << board[i][j] << ' ';
	        }

	        cnt++;
	    }
    
	    std::cout << std::endl;
    }

    std::cout << "\n-------------\n";
}

void draw(char board[3][3])
{
    for (int i = 0; i < 3; ++i)
    {
	    for (int j = 0; j < 3; ++j)
	    {
    	    std::cout << board[i][j] << ' ';
	    }
    
	    std::cout << std::endl;
    }

    std::cout << "\n-------------\n";
}


void Print(List* list)
{
    List* current = list;
    while (current != NULL)
    {
        draw(current->board);
        current = current->next;
    }

    std::cout << std::endl;
}

List* append(List* list1, List* list2)
{
    if (list1 == NULL)
    {
        return list2;
    }

    List* res = list1;

    while (list1->next != NULL)
    {
        list1 = list1->next;
    }

    list1->next = list2;

    return res;
}

List* add_front(char brd[3][3], List* list)
{
    List* res = new List;
    
    for (int i = 0; i < 3; ++i)
    {
	    for (int j = 0; j < 3; ++j)
	    {
	        res->board[i][j] = brd[i][j];
	    }
    }
    
    res->next = list;
    return res;    
}

void copy(char board1[3][3], char board2[3][3])
{
    for (int i = 0; i < 3; ++i)
    {
	    for (int j = 0; j < 3; ++j)
	    {
	        board1[i][j] = board2[i][j];
	    }
    }
}

List* perVariants(char board[3][3], char element)
{
    List* res = NULL;
    
    char tmp[3][3];

    for (int i = 0; i < 3; ++i)
    {
	    for (int j = 0; j < 3; ++j)
	    {
	        copy(tmp, board);
	    
	        if (board[i][j] == '_')
	        {
		        tmp[i][j] = element;
		        res = add_front(tmp, res);
	        }
	    }
    }

    return res;
}


//123
//456
//789

//X2O
//OO6
//XO9

// 1)interface for game, that player can play with himself
// 2) fucntion which check can I put X or O
// 3) Who wins ..

char whoWins(char board[3][3])
{
    if (board[0][0] == board[1][1] && board[0][0] == board[2][2])
        return board[0][0];

    for (int i = 0; i < 3; ++i)
    {
        if (board[0][i] == board[1][i] && board[0][i] == board[2][i])
            return board[0][i];
    }

    for (int i = 0; i < 3; ++i)
    {
        if (board[i][0] == board[i][1] && board[i][0] == board[i][2])
            return board[i][0];
    }

    return '_';
}


int main()
{
    char board[3][3] = {{'X', 'O', 'X'}, {'X', 'X', 'O'}, {'_', 'O', 'O'}};
    
    char elem = 'X';
    //std::cin >> elem;
    
    List* var = perVariants(board, elem);
    
    //Print(var);

    smartDraw(board);

    char win = whoWins(board);

    std::cout << win << std::endl;

    return 0;
}