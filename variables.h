#ifndef VARIABLES_H
#define VARIABLES_H


/* RULES */
#define UGOLKI_MAXIMUM_TURNS_IN_HOUSE 40
//max size 11
#define DESK_SIZE 8
#define UGOLKI_HOUSE_WIDTH 3
#define UGOLKI_HOUSE_HEIGHT 3


/* BOT */
#define AI_GAME_TREE_DEPTH 3

#define AI_MEAN 15

#define AI_CRITERIA_DISTANCE_TO_HOUSE 100.0
#define AI_CRITERIA_DISTANCE_TO_HOUSE_GRADE 3
#define AI_CRITERIA_PIECES_IN_HOUSE 150000.0
#define AI_CRITERIA_HOUSE_PUNISHMENT 0.000000003
#define AI_HOUSE_PUNISHMENT_PIECES_IN_HOUSE_TURN_GRADE 3
#define AI_HOUSE_PUNISHMENT_DISTANCE_TO_OPPONENT_TURN_GRADE 0

#define AI_WON_REWARD 2000000


/* *********************************** */


/* implementation stuff, not recommended to change */
/*
0 — игра с ботом
1 — игра двух игроков за одним компьютером
2 — игра двух игроков по сети
*/
#define UGOLKI_MODES 3

#define UGOLKI_MODE_AI 0
#define UGOLKI_MODE_MULTIPLAYER 1
#define UGOLKI_MODE_NETWORK 2

#define UGOLKI_PLAYER_1 0
#define UGOLKI_PLAYER_2 1
#define UGOLKI_BOT 1
#define UGOLKI_PLAYER_EMPTY -1

#define UGOLKI_MAXPLAYERS 2


/* DESIGN */
#define NOTIFICATION_FONT_SIZE_PIXEL 30
#define MENU_BUTTONS_FONT_SIZE_PIXEL 30
#define MENU_BUTTONS_HEIGHT_FOR_FONT_MULTIPLICATOR 2


#define DESK_SIZE_PIXEL 400

#define DESK_CELL_FONT_PIXEL_SIZE 60

#define DESK_WIDGET_HEIGHT 100
#define DESK_WIDGET_WIDTH 300

#define DESK_INFORMATION_TABLE_PIXEL_HEIGHT 70

#define STRING_MODE_NETWORK "Network Game"
#define STRING_MODE_AI "Artificial Intelligence"
#define STRING_MODE_MULTIPLAYER "Two Players"

#define STRING_MAIN_MENU "Main Menu"
#define STRING_BACK_TO_MENU "Back to menu"
#define STRING_APPLICATION_NAME "Ugolki"
#define STRING_NOTIFICATION "Notification"
#define STRING_BUTTON_SEND "Send"

#define STRING_YOU_LOST "Game over. You lost"
#define STRING_YOU_WON "Congratulations! You won!"
#define STRING_DRAW "Nobody won!"
#define STRING_PLAYER "Player"
#define STRING_WON "is the winner!"

#define STRING_ERROR_DATA_PROTOCOL "Data/Protocol Error"

#define STRING_NOT_IMPLEMENTED "Not implemented yet"
#endif // VARIABLES_H
