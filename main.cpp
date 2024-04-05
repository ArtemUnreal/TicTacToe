#include <iostream>
#include <vector>

struct List
{
    char board[3][3];
    List* next;
};

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
    if (board[0][0] == board[1][1] && board[0][0] == board[2][2] && board[0][0] != '_')
        return board[0][0];

    for (int i = 0; i < 3; ++i)
    {
        if (board[0][i] == board[1][i] && board[0][i] == board[2][i] && board[0][i] != '_')
            return board[0][i];
    }

    for (int i = 0; i < 3; ++i)
    {
        if (board[i][0] == board[i][1] && board[i][0] == board[i][2] && board[i][0] != '_')
            return board[i][0];
    }

    return '_';
}

bool isFilled(char board[3][3])
{
    int filled = 0;

    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            if (board[i][j] == 'X' || board[i][j] == 'O')
            {
                filled++;  
            }
        }
    }

    return filled == 9 ? true : false;
}

char changeElement(char elem)
{
    char res = 'X';

    if (elem == 'X')
    {
    res = 'O';
    }

    return res;
}

int maxElement(std::vector<int> vec)
{
    int m = -1;
    for (int i = 0; i < vec.size(); ++i)
    {
	if (vec[i] > m)
	{
	    m = vec[i];
	}
    }

    return m;
}

int minElement(std::vector<int> vec)
{
    int m = 1;
    for (int i = 0; i < vec.size(); ++i)
    {
	    if (vec[i] < m)
	    {
	        m = vec[i];
	    }
    }

    return m;
}

int evaluate(char board[3][3], char element)
{
    char eval = whoWins(board);

    if (eval == 'X')
    {
	    return -1;
    }
    
    if (eval == 'O')
    {
	    return 1;
    }

    if(isFilled(board))
    {
	    return 0;
    }

    List* variant = perVariants(board, element);
    int res = 0;
    std::vector<int> all_res;

    while (variant != NULL)
    {
	    char t = changeElement(element);
	    all_res.push_back(evaluate(variant->board, t));
    }
    
    if (element == 'X')
    {
	    res = minElement(all_res);
    }
    
    if (element == 'O')
    {
	    res = maxElement(all_res);
    }
    
    // Сделать функцию которая берет доску и игрока и возвращает доску для которой функция evaluate вернулы бы
    // маскимальное значение 

    //Порождать списко возможных досок и находить оценку

    return res;
}

int allNextVariant(char board[3][3], char element)
{
    if (isFilled(board))
    {
	return 1;
    }
    
    char win = whoWins(board);

    if (win == 'X' || win == 'O')
    {
	return 1;
    }
    
    List* variant  = NULL;

    variant = perVariants(board, element);
    int res = 1;

    while (variant != NULL)
    {
	char t = changeElement(element);
	int tmp = allNextVariant(variant->board, t);
	res += tmp;
	variant = variant->next;
    }
    
    return res;
}

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

void insertBoard(char board[3][3], char elem, int num)
{
    int cnt = 1;

    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            if (cnt == num)
            {
                board[i][j] = elem;
                return;
            }

            cnt++;
        }
    }
}

void Interface(char board[3][3])
{
    char res;
    bool isWin = false;
    char player = 'X';

    while (!isWin)
    {
        // enter a number and a element
        std::cout << "Enter a number, which on the screen and a X or O, for example X 1" << std::endl;
        smartDraw(board); 

        std::cout << "Turn " << player << "." << std::endl; 
       
        char elem;
        std::cin >> elem; 

        int num;
        std::cin >> num;

        if (elem != 'X' && elem != 'O')
        {
            std::cout << "Incorrect symbol. Please, enter X or O." << std::endl;
            continue;
        }

        if (num < 1 || num > 9)
        {
            std::cout << "The cell number must be between 1 and 9." << std::endl;
            continue;
        }

        if (elem != player)
        {
            std::cout << "You play for another symbol" << std::endl;
            continue;
        }

        if (board[(num - 1) / 3][(num - 1) % 3] != '_')
        {
            std::cout << "The cage is already occupied. Please select a different one." << std::endl;
            continue;
        }

        // put a sign in board
        insertBoard(board, elem, num);

        //check the result
        res = whoWins(board);

        if (isFilled(board))
        {
            isWin = true;
        }

        if (res == 'X' || res == 'O')
        {
            isWin = true;
        }

        if (player == 'X')
        {
            player = 'O';
        }
        else
        {
            player = 'X';
        }
    }

    std::cout << "Congrate, " << res << " win" << std::endl;

    smartDraw(board);
}

// for person - X, for computer - O
 
int main()
{
    char board[3][3] = {{'X', 'O', 'X'}, {'O', 'O', 'X'}, {'_', '_', '_'}};
    char elem = 'X';
    //Interface(board);
    //int result = allNextVariant(board, elem);
    
    int result;
    std::cout << result << std::endl;
    return 0;
}