#include "sharedWhiteboard/SharedWhiteboard.h"
#include "whiteboard/WhiteBoardCV.h"

int main()
{
	wboard::shared::SharedWhiteboard board(wboard::WhiteBoard(new wboard::WhiteBoardCv()), "localhost", "1111");
	board.Run();
}