#ifndef MOVE_HPP
#define MOVE_HPP

// Metoda do ruchu gracza
void movePlayer(char direction, Board& board, Position& playerPosition) {
    int dx = 0, dy = 0;

    switch (direction) {
        case 'w':
            dy = -1;
            break;
        case 's':
            dy = 1;
            break;
        case 'a':
            dx = -1;
            break;
        case 'd':
            dx = 1;
            break;
        default:
            return;
    }

    int newX = playerPosition.x + dx;
    int newY = playerPosition.y + dy;

    // Sprawdzenie czy nowa pozycja jest prawidlowa
    if (newX >= 0 && newX < board.getWidth() && newY >= 0 && newY < board.getHeight() && !board.isWall(newX, newY)) {
        // Aktualizacja pozycji gracza
        if ((board.getCell(newX, newY) == EMPTY || board.getCell(newX, newY) == TARGET) && board.getCell(playerPosition.x, playerPosition.y) == PLAYER) {
            board.setCell(playerPosition.x, playerPosition.y, EMPTY);
            playerPosition.x = newX;
            playerPosition.y = newY;
            if (board.getCell(newX, newY) == TARGET) {
                board.setCell(newX, newY, PLAYER_ON_TARGET);
            } else {
                board.setCell(newX, newY, PLAYER);
            }
        } else if ((board.getCell(newX, newY) == EMPTY || board.getCell(newX, newY) == TARGET) && board.getCell(playerPosition.x, playerPosition.y) == PLAYER_ON_TARGET) {
            board.setCell(playerPosition.x, playerPosition.y, TARGET);
            playerPosition.x = newX;
            playerPosition.y = newY;
            if (board.getCell(newX, newY) == TARGET) {
                board.setCell(newX, newY, PLAYER_ON_TARGET);
            } else {
                board.setCell(newX, newY, PLAYER);
            }
        } else if (board.getCell(newX, newY) == BOX || board.getCell(newX, newY) == BOX_ON_TARGET) {
            int boxNewX = newX + dx;
            int boxNewY = newY + dy;

            // Sprawdzenie czy nowa pozycja pudelka jest prawidlowa
            if (boxNewX >= 0 && boxNewX < board.getWidth() && boxNewY >= 0 && boxNewY < board.getHeight() && !board.isWall(boxNewX, boxNewY)) {
                if ((board.getCell(boxNewX, boxNewY) == EMPTY || board.getCell(boxNewX, boxNewY) == TARGET) && board.getCell(playerPosition.x, playerPosition.y) == PLAYER) {
                    // Aktualizacja pozycji pudelka
                    board.setCell(playerPosition.x, playerPosition.y, EMPTY);
                    playerPosition.x = newX;
                    playerPosition.y = newY;
                    if (board.getCell(newX + dx, newY + dy) == TARGET) {
                        board.setCell(newX + dx, newY + dy, BOX_ON_TARGET);
                    } else {
                        board.setCell(newX + dx, newY + dy, BOX);
                    }
                    if (board.getCell(newX, newY) == BOX_ON_TARGET) {
                        board.setCell(newX, newY, PLAYER_ON_TARGET);
                    } else {
                        board.setCell(newX, newY, PLAYER);
                    }
                } else if ((board.getCell(boxNewX, boxNewY) == EMPTY || board.getCell(boxNewX, boxNewY) == TARGET) && board.getCell(playerPosition.x, playerPosition.y) == PLAYER_ON_TARGET){
                    board.setCell(playerPosition.x, playerPosition.y, TARGET);
                    playerPosition.x = newX;
                    playerPosition.y = newY;
                    if (board.getCell(newX + dx, newY + dy) == TARGET) {
                        board.setCell(newX + dx, newY + dy, BOX_ON_TARGET);
                    } else {
                        board.setCell(newX + dx, newY + dy, BOX);
                    }
                    if (board.getCell(newX, newY) == BOX_ON_TARGET) {
                        board.setCell(newX, newY, PLAYER_ON_TARGET);
                    } else {
                        board.setCell(newX, newY, PLAYER);
                    }
                }
            }
        }
    }
}

#endif