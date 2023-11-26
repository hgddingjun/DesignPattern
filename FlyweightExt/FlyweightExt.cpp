#include <iostream>
#include <string>
#include <vector>
using namespace std;

enum PieceColor { BLACK, WHITE };

struct PiecePos {
	int m_x;
	int m_y;
	PiecePos(int a, int b) :m_x(a), m_y(b) {

	}
};

class Piece {
protected:
	PieceColor m_color;

public:
	Piece(PieceColor color) :m_color(color) {

	}
	virtual ~Piece() {

	}
	virtual void draw() {

	}
};

class BlackPiece :public Piece {
public:
	BlackPiece(PieceColor color) : Piece(color) {}
	~BlackPiece() {}
	void draw() {
		std::cout << "Draw a Black Piece." << std::endl;
	}
};


class WhitePiece :public Piece {
public:
	WhitePiece(PieceColor color) : Piece(color) {}
	~WhitePiece() {}
	void draw() {
		std::cout << "Draw a White Piece." << std::endl;
	}
};

class PieceBoard {
public:
	PieceBoard(string black, string white) : m_blackName(black), m_whiteName(white) {
		m_pBlackPiece = nullptr;
		m_pWhitePiece = nullptr;
	}
	~PieceBoard() {
		clear();
	}
	void setPiece(PieceColor color, PiecePos pos) {
		if (color == BLACK) {
			if (m_pBlackPiece == nullptr) {
				m_pBlackPiece = new BlackPiece(color);
			}
			
			std::cout << m_blackName << " Took a step at position (" << pos.m_x << "," << pos.m_y << ")" << std::endl;
			m_pBlackPiece->draw();
		}
		else {
			if (m_pWhitePiece == nullptr) {
				m_pWhitePiece = new WhitePiece(color);
			}
			
			std::cout << m_whiteName << " Took a step at position (" << pos.m_x << "," << pos.m_y << ")" << std::endl;
			m_pWhitePiece->draw();
		}

		m_vecPiecePos.push_back(pos);
	}
	void clear() {
		if (m_pBlackPiece != nullptr) {
			delete m_pBlackPiece;
			m_pBlackPiece = nullptr;
		}
		if (m_pWhitePiece != nullptr) {
			delete m_pWhitePiece;
			m_pWhitePiece = nullptr;
		}
		

	}
private:
	vector<PiecePos> m_vecPiecePos;
	string m_blackName;
	string m_whiteName;
	Piece* m_pBlackPiece;
	Piece* m_pWhitePiece;

};

int main()
{
	PieceBoard pieceBoard("JackMa","PonyMa");
	pieceBoard.setPiece(BLACK, PiecePos(33, 22));
	pieceBoard.setPiece(WHITE, PiecePos(17, 25));
	pieceBoard.setPiece(BLACK, PiecePos(11, 27));
	pieceBoard.setPiece(WHITE, PiecePos(54, 65));
	return 0;
}