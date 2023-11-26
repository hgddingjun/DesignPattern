#include <iostream>
#include <string>
#include <vector>
using namespace std;

enum PieceColor{ BLACK, WHITE };

struct PiecePos {
	int m_x;
	int m_y;
	PiecePos(int a, int b) :m_x(a), m_y(b) {

	}
};

class Piece {
protected:
	PieceColor m_color;
	PiecePos m_pos;
public:
	Piece(PieceColor color, PiecePos pos) :m_color(color), m_pos(pos) {

	}
	virtual ~Piece() {

	}
	virtual void draw() {

	}
};

class BlackPiece :public Piece {
public:
	BlackPiece(PieceColor color, PiecePos pos): Piece(color,pos) {}
	~BlackPiece(){}
	void draw() {
		std::cout << "Draw a Black Piece." << std::endl;
	}
};


class WhitePiece :public Piece {
public:
	WhitePiece(PieceColor color, PiecePos pos) : Piece(color, pos) {}
	~WhitePiece() {}
	void draw() {
		std::cout << "Draw a White Piece." << std::endl;
	}
};

class PieceBoard {
public:
	PieceBoard(string black, string white): m_blackName(black), m_whiteName(white) {}
	~PieceBoard() {
		clear();
	}
	void setPiece(PieceColor color, PiecePos pos) {
		Piece* pPiece = nullptr;
		if (color == BLACK) {
			pPiece = new BlackPiece(color, pos);
			std::cout << m_blackName << " Took a step at position (" << pos.m_x << "," << pos.m_y << ")" <<std:: endl;
		}
		else {
			pPiece = new WhitePiece(color, pos);
			std::cout << m_whiteName << " Took a step at position (" << pos.m_x << "," << pos.m_y << ")" << std::endl;
		}

		pPiece->draw();

		m_vecPiece.push_back(pPiece);
	}
	void clear() {
		for (auto iter = m_vecPiece.begin(); iter != m_vecPiece.end();iter++) {
			delete (*iter);
		}
	}
private:
	vector<Piece*> m_vecPiece;
	string m_blackName;
	string m_whiteName;
};

int main() 
{
	return 0;
}