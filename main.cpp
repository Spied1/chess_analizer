#include<iostream>
#include<vector>
#include<string>

class chess
{
private:
	std::vector<std::vector<std::string>> m_chess_board;
public:
	chess()
	{
		std::vector<std::vector<std::string>> matrix(8, std::vector<std::string>(8, "XX"));
		m_chess_board = matrix;
	}

	void add_figure(int x, int y,std::string figure)
	{
		if (m_chess_board[x][y] != "XX")
		{
			std::cout << "error, place already taken" << std::endl;
			return;
		}
        if (figure == "KW")
        {
            for (int i = -1; i <= 1; ++i)
            {
                for (int j = -1; j <= 1; ++j)
                {
                    if (x + i < -1 || y + j < -1 || x + i > 7 || y + j > 7)
                    {
                        continue;
                    }
                    if (m_chess_board[x + i][y + j] == "KB")
                    {
                        std::cout << "ilegal move" << std::endl;
                        return;
                    }
                }
            }
        }

        if (figure == "KB")
        {
            for (int i = -1; i <= 1; ++i)
            {
                for (int j = -1; j <= 1; ++j)
                {
                    if (x + i < -1 || y + j < -1 || x + i > 7 || y + j > 7)
                    {
                        continue;
                    }
                    if (m_chess_board[x + i][y + j] == "KW")
                    {
                        std::cout << "ilegal move" << std::endl;
                        return;
                    }
                }
            }
        }

		m_chess_board[x][y] = figure;
	}

    void delete_figure(int x, int y)
    {
        m_chess_board[x][y] = "XX";
    }

	void draw()
	{
		for (int i = 0; i < 8; ++i)
		{
			for (int j = 0; j < 8; ++j)
			{
				std::cout << m_chess_board[i][j] << " ";
			}

			std::cout << std::endl;
			std::cout << std::endl;
		}
	}

	std::vector<std::vector<std::string>> get_board()
	{
		return m_chess_board;
	}

    bool isValidMove(int x, int y)
    {
        return x >= 0 && x < 8 && y >= 0 && y < 8;
    }

    void checkLinearMoves(int x, int y, const std::string& piece, const std::string& targetKing)
    {
        std::vector<std::vector<int>> directions = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };
        for (auto& dir : directions)
        {
            int nx = x + dir[0], ny = y + dir[1];
            while (isValidMove(nx, ny))
            {
                if (m_chess_board[nx][ny] == targetKing)
                {
                    std::cout << "check with " << piece << "->" << targetKing << std::endl;
                    return;
                }
                else if (m_chess_board[nx][ny] != "XX") 
                {
                    break;
                }
                nx += dir[0];
                ny += dir[1];
            }
        }
    }

    void checkDiagonalMoves(int x, int y, const std::string& piece, const std::string& targetKing)
    {
        std::vector<std::vector<int>> directions = { {1, 1}, {1, -1}, {-1, 1}, {-1, -1} };
        for (auto& dir : directions)
        {
            int nx = x + dir[0], ny = y + dir[1];
            while (isValidMove(nx, ny))
            {
                if (m_chess_board[nx][ny] == targetKing)
                {
                    std::cout << "check with " << piece << "->" << targetKing << std::endl;
                    return;
                }
                else if (m_chess_board[nx][ny] != "XX") 
                {
                    break;
                }
                nx += dir[0];
                ny += dir[1];
            }
        }
    }

    void checkKnightMoves(int x, int y, const std::string& piece, const std::string& targetKing)
    {
        std::vector<std::vector<int>> moves = { {2, 1}, {2, -1}, {-2, 1}, {-2, -1}, {1, 2}, {1, -2}, {-1, 2}, {-1, -2} };
        for (auto& move : moves)
        {
            int nx = x + move[0], ny = y + move[1];
            if (isValidMove(nx, ny) && m_chess_board[nx][ny] == targetKing)
            {
                std::cout << "check with " << piece << "->" << targetKing << std::endl;
                return;
            }
        }
    }

    void analizer_lvl1()
    {
        for (int i = 0; i < 8; ++i)
        {
            for (int j = 0; j < 8; ++j)
            {
                // pawn white
                if (m_chess_board[i][j] == "PW")
                {
                    if (i < 7) 
                    {
                        std::cout << i << " " << j << std::endl;
                        
                        if (m_chess_board[i + 1][j - 1] == "KB")
                        {
                            //std::cout << i + 1 << " " << j - 1 << std::endl;
                            std::cout << "check with " << "PW->" << "KB" << std::endl;
                        }
                        //std::cout << i + 1 << " " << j - 1;
                        //std::cout << m_chess_board[i][j];
                        //std::cout << m_chess_board[i + 1][j - 1];
                        
                        if (m_chess_board[i + 1][j + 1] == "KB")
                        {
                            //std::cout << i + 1 << " " << j + 1 << std::endl;
                            std::cout << "check with " << "PW->" << "KB" << std::endl;
                        }
                    }
                }

                // pawn black
                else if (m_chess_board[i][j] == "PB")
                {
                    if (i > 0) 
                    {
                        
                        if (j > 0 && m_chess_board[i + 1][j - 1] == "KW")
                        {
                            std::cout << "check with " << "PB->" << "KW" << std::endl;
                        }

                        if (j < 7 && m_chess_board[i - 1][j + 1] == "KW")
                        {
                            std::cout << "check with " << "PB->" << "KW" << std::endl;
                        }
                    }
                }

                // king white
                else if (m_chess_board[i][j] == "KW")
                {
                    for (int x = -1; x <= 1; ++x)
                    {
                        for (int y = -1; y <= 1; ++y)
                        {
                            if (x != 0 || y != 0)
                            {
                                if (isValidMove(i + x, j + y) && m_chess_board[i + x][j + y] == "KB")
                                {
                                    std::cout << "check with " << "KW->" << "KB" << std::endl;
                                }
                            }
                        }
                    }
                }

                // king black
                else if (m_chess_board[i][j] == "KB")
                {
                    for (int x = -1; x <= 1; ++x)
                    {
                        for (int y = -1; y <= 1; ++y)
                        {
                            if (x != 0 || y != 0)
                            {
                                if (isValidMove(i + x, j + y) && m_chess_board[i + x][j + y] == "KW")
                                {
                                    std::cout << "check with " << "KB->" << "KW" << std::endl;
                                }
                            }
                        }
                    }
                }

                // rook white
                else if (m_chess_board[i][j] == "RW")
                {
                    checkLinearMoves(i, j, "RW", "KB");
                }

                // rook black
                else if (m_chess_board[i][j] == "RB")
                {
                    checkLinearMoves(i, j, "RB", "KW");
                }

                // bishop white
                else if (m_chess_board[i][j] == "BW")
                {
                    checkDiagonalMoves(i, j, "BW", "KB");
                }

                // bishop black
                else if (m_chess_board[i][j] == "BB")
                {
                    checkDiagonalMoves(i, j, "BB", "KW");
                }

                // knight white
                else if (m_chess_board[i][j] == "NW")
                {
                    checkKnightMoves(i, j, "NW", "KB");
                }

                // knight black
                else if (m_chess_board[i][j] == "NB")
                {
                    checkKnightMoves(i, j, "NB", "KW");
                }

                // queen white
                else if (m_chess_board[i][j] == "QW")
                {
                    checkLinearMoves(i, j, "QW", "KB");
                    checkDiagonalMoves(i, j, "QW", "KB");
                }

                // queen black
                else if (m_chess_board[i][j] == "QB")
                {
                    checkLinearMoves(i, j, "QB", "KW");
                    checkDiagonalMoves(i, j, "QB", "KW");
                }
            }
        }
    }

    void make_move()
    {

    }
};


int main()
{
    chess first;

    //first.add_figure(1, 1, "PW");
    //first.add_figure(2, 2, "KB");

    //first.add_figure(4, 4, "RB");
    //first.add_figure(4, 7, "KW");

    first.add_figure(5, 2, "NB");
    first.add_figure(7, 3, "KW");

    //first.add_figure(2, 3, "BW");
    //first.add_figure(5, 6, "KB");

    first.add_figure(1, 1, "QB");
    first.add_figure(1, 7, "KW");

    //first.add_figure(3, 3, "QW");
    //first.add_figure(0, 3, "KB");

    first.add_figure(2, 2, "KB");
    first.add_figure(1, 2, "KW");

    first.draw();
    first.analizer_lvl1();

    return 0;
}
