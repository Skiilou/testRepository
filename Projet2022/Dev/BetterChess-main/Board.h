#pragma once
#include "SDL.h"
#include "Move.h"
#include "BoardState.h"
#include "Box.h"
#include "MoveStack.h"
#include "PieceLocations.h"
#include "KingThreatenedInfo.h"
#include <vector>
class Board
{
private:

	SDL_Color boardColor1;
	SDL_Color boardColor2;
	

	BoardState* boardState;
	
	PieceLocations whiteLocations;
	PieceLocations blackLocations;

	KingThreatenedInfo whiteThreatened;
	KingThreatenedInfo blackThreatened;



	

	//moving piece stuff.
	bool draggingPiece;
	Box draggingPieceBox;
	SDL_Texture* draggingPieceTexture;

	//Move stuff
	std::vector<Move> pseudoLegalMoves;
	std::vector<Move> legalMoves;

	std::vector<Box> highlightBoxes;

	Box highlightKingBox;
	Box winnerKing;

	Move promotionMove;
	bool gameOver;

	bool waitingForPromotionChoice;

	char winner;

	MoveStack moveStack;




	//Fonction d'initialisation et de rendu du plateau ainsi que des fonctions pour prendre une pièce et la déplacer
public:
	static int boxXWidth;
	static int boxYHeight;
	static int boardXBoxes;
	static int boardYBoxes;

	~Board();
	void update();
	void render(BoardState*);
	void resize();
	void init();
	void renderBoard();
	void renderDraggedPiece();

	void handleMouseButtonDown(SDL_MouseButtonEvent&, BoardState*);
	void attemptPickupPiece(int x, int y,BoardState*);
	void attemptPlacePiece(int x, int y,BoardState*);
	void stopDraggingPiece();

	int getWidth();
	int getHeight();
	BoardState* getBoardState();

	void printBoardState(BoardState*);

	void renderPieces(BoardState*);
	void renderPiece(Box,BoardState*);
	void renderPieceTexture(SDL_Texture*, int x, int y);
	
	SDL_Texture* getTextureAtLocation(int x, int y,BoardState*);

	void loadBoardFromFen(const char* fen,BoardState*);

	bool pieceIsCurrentPlayersPiece(int x, int y,BoardState*);

	


	void switchTurns(BoardState*);

	//Fonction pour le mouvement en passant
	void updateEnPassant(Box fromBox, Box toBox, BoardState*);
	bool isEnPassant(Box fromBox, Box toBox, BoardState*);

	//Fonction pour le roque
	void updateCastling(Box fromBox, Box toBox, BoardState*);

	//Calcul des coups légaux
	void clearMoves();
	std::vector<Move> calculatePseudoLegalMoves(BoardState*);
	std::vector<Move> calculateLegalMoves(BoardState*);

	
	//Calculer les mouvements des différentes pièces
	void calculateRookMoves(Box,BoardState*, std::vector<Move>&);
	void calculateBishopMoves(Box,BoardState*, std::vector<Move>&);
	void calculateKnightMoves(Box,BoardState*, std::vector<Move>&);
	void calculateKingMoves(Box,BoardState*, std::vector<Move>&);
	void calculateQueenMoves(Box,BoardState*, std::vector<Move>&);
	void calculatePawnUpMoves(Box,BoardState*, std::vector<Move>&);
	void calculatePawnDownMoves(Box, BoardState*, std::vector<Move>&);
	void calculateCastlingMoves(Box,BoardState*, std::vector<Move>&);


	//Calcul des mouvements permettant de prendre des pièces adversaires
	void calculateRookLegalMoves(Box,Box,BoardState*, std::vector<Move>&,KingThreatenedInfo);
	void calculateKingLegalMoves(Box, BoardState*, std::vector<Move>&, KingThreatenedInfo);
	void calculateBishopLegalMoves(Box, Box,BoardState*, std::vector<Move>&,KingThreatenedInfo);
	void calculateQueenLegalMoves(Box, Box, BoardState*, std::vector<Move>&, KingThreatenedInfo);
	void calculatePawnLegalMoves(Box, Box, BoardState*, std::vector<Move>&, KingThreatenedInfo);
	void calculateKnightLegalMoves(Box, Box, BoardState*, std::vector<Move>&, KingThreatenedInfo);
	void calculateCastlingLegalMoves(Box, BoardState*, std::vector<Move>&);

	void attemptAddMove(Move move, BoardState* currentBoardState, std::vector<Move>& moves);

	void addStraightUpMoves(Box, BoardState*, std::vector<Move>&);
	void addStraightDownMoves(Box, BoardState*, std::vector<Move>&);
	void addStraightLeftMoves(Box, BoardState*, std::vector<Move>&);
	void addStraightRightMoves(Box, BoardState*, std::vector<Move>&);

	void addUpRightMoves(Box, BoardState*, std::vector<Move>&);
	void addDownRightMoves(Box, BoardState*, std::vector<Move>&);
	void addUpLeftMoves(Box, BoardState*, std::vector<Move>&);
	void addDownLeftMoves(Box, BoardState*, std::vector<Move>&);
	// Fonction pour le déplacement des pions
	void addStraightUpPawnMoves(Box, BoardState*, std::vector<Move>&);
	void addStraightDownPawnMoves(Box, BoardState*, std::vector<Move>&);
	void addDownLeftPawnMoves(Box, BoardState*, std::vector<Move>&);
	void addDownRightPawnMoves(Box, BoardState*, std::vector<Move>&);
	void addUpRightPawnMoves(Box, BoardState*, std::vector<Move>&);
	void addUpLeftPawnMoves(Box, BoardState*, std::vector<Move>&);

	//Fonction pour savoir si une pièce est dans la même ligne ou la même colonne que la pièce
	bool inSameRow(Box, Box);
	bool inSameCol(Box, Box);

	bool inSameDiagonal(Box, Box);

	bool inSameReverseDiagonal(Box, Box);


	void nextTurn(BoardState* boardState);
	bool inLegalMoves(struct Move&);
	bool inPseudoMoves(struct Move&);

	void makeMove(struct Move, BoardState*);

	bool canEnPassant(Box, Box, BoardState*);

	//Fonctions pouvant gérer les menaces liées au roi
	void updateAllThreats(char curentTurn, BoardState* currentBoardState);
	void updateMoveToThreats(Move, BoardState*);
	void updateThreats(Move, BoardState*);
	void updateStraightUpThreats(char currentTurn, BoardState*);
	void updateStraightLeftThreats(char currentTurn,BoardState* boardState);
	void updateStraightDownThreats(char currentTurn, BoardState*);
	void updateStraightRightThreats(char currentTurn, BoardState* boardState);

	void updateUpLeftThreats(char currentTurn, BoardState*);
	void updateUpRightThreats(char currentTurn, BoardState* boardState);
	void updateDownLeftThreats(char currentTurn, BoardState*);
	void updateDownRightThreats(char currentTurn, BoardState* boardState);
	
	void initializeKingsThreatened(BoardState*);


	bool kingAttacked(BoardState* currentBoardState);

	bool doesBoxBlockAttack(Box, BoardState* currentBoardState);


	void unMakeMove(BoardState*);


	void renderAttackedSquares();


	void renderBox(Box, SDL_Color);
	//Mettre les mouvements disponibles en surbrillance et les mouvements précédent de case plus foncées
	void renderHighlightMoves();
	void renderPreviousMove();
	void createHighlightMoves(int x, int y);

	//Fonction permettant de savoir si le roi est en echec
	bool kingInCheck(BoardState* currentBoardState);
	void findKingLocation(int*, int*, BoardState*);
	bool squareAttacked(Box box, BoardState* currentBoardState);
	
	
	void updateHighlightKingBox();
	void renderKingBox();

	//Fonction lorsque le roi est en echec et mat et la partie est finie
	int isGameOver(BoardState* currentBoardState);
	
	void reset();

	int totalPossibleFutureBoardPositions(BoardState*, int depth);
	void calculateBoardStates();

	//Fonction qui gèrent les promotions des pions
	void renderPromotionOptions();
	void togglePromotionOptions();
	void tryPickingPromotionPiece(int, int, BoardState*);

	void promoteQueen(BoardState*);
	void promoteRook(BoardState*);
	void promoteBishop(BoardState*);
	void promoteKnight(BoardState*);

	

	void makeRandomMove(BoardState*);



	//Fonction pour initialiser les pièces sur le plateau
	void initializePieceLocations(BoardState*);


};

