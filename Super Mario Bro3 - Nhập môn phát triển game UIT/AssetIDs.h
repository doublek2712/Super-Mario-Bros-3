#pragma once

//
// This file contains all IDs of game assets 
//

#define ID_TEX_MARIO 0
#define ID_TEX_ENEMY 10
#define ID_TEX_MISC 20


#define OBJECT_TYPE_MARIO	0
#define OBJECT_TYPE_BLOCK	1
#define OBJECT_TYPE_GOOMBA	2
#define OBJECT_TYPE_KOOPA	3
#define OBJECT_TYPE_COIN 4
#define OBJECT_TYPE_PLATFORM 5
#define OBJECT_TYPE_GROUND 6
#define OBJECT_TYPE_PIPE 7
#define OBJECT_TYPE_WOOD 8
#define OBJECT_TYPE_VENUS 9
#define OBJECT_TYPE_PARA_GOOMBA 10
#define OBJECT_TYPE_PARA_KOOPA 11
#define OBJECT_TYPE_BRICK 12
#define OBJECT_TYPE_ROULETTE_CARD 13

#define OBJECT_TYPE_PORTAL	50


#pragma region MARIO 

#define ID_SPRITE_MARIO 10000
#define ID_SPRITE_MARIO_BIG (ID_SPRITE_MARIO + 1000)
#define ID_SPRITE_MARIO_BIG_IDLE (ID_SPRITE_MARIO_BIG + 100)
#define ID_SPRITE_MARIO_BIG_IDLE_LEFT (ID_SPRITE_MARIO_BIG_IDLE + 10)
#define ID_SPRITE_MARIO_BIG_IDLE_RIGHT (ID_SPRITE_MARIO_BIG_IDLE + 20)

#define ID_SPRITE_MARIO_BIG_WALKING (ID_SPRITE_MARIO_BIG + 200)
#define ID_SPRITE_MARIO_BIG_WALKING_LEFT (ID_SPRITE_MARIO_BIG_WALKING + 10)
#define ID_SPRITE_MARIO_BIG_WALKING_RIGHT (ID_SPRITE_MARIO_BIG_WALKING + 20)
#define ID_SPRITE_MARIO_BIG_RUNNING (ID_SPRITE_MARIO_BIG + 300)
#define ID_SPRITE_MARIO_BIG_RUNNING_LEFT (ID_SPRITE_MARIO_BIG_RUNNING + 10)
#define ID_SPRITE_MARIO_BIG_RUNNING_RIGHT (ID_SPRITE_MARIO_BIG_RUNNING + 20)
#define ID_SPRITE_MARIO_BIG_JUMP (ID_SPRITE_MARIO_BIG + 400)
#define ID_SPRITE_MARIO_BIG_JUMP_WALK (ID_SPRITE_MARIO_BIG_JUMP + 10)
#define ID_SPRITE_MARIO_BIG_JUMP_WALK_LEFT (ID_SPRITE_MARIO_BIG_JUMP_WALK + 2)
#define ID_SPRITE_MARIO_BIG_JUMP_WALK_RIGHT (ID_SPRITE_MARIO_BIG_JUMP_WALK + 6)
#define ID_SPRITE_MARIO_BIG_JUMP_RUN (ID_SPRITE_MARIO_BIG_JUMP + 20)
#define ID_SPRITE_MARIO_BIG_JUMP_RUN_LEFT (ID_SPRITE_MARIO_BIG_JUMP_RUN + 2)
#define ID_SPRITE_MARIO_BIG_JUMP_RUN_RIGHT (ID_SPRITE_MARIO_BIG_JUMP_RUN + 6)
#define ID_SPRITE_MARIO_BIG_SIT (ID_SPRITE_MARIO_BIG + 500)
#define ID_SPRITE_MARIO_BIG_SIT_LEFT (ID_SPRITE_MARIO_BIG_SIT + 10)
#define ID_SPRITE_MARIO_BIG_SIT_RIGHT (ID_SPRITE_MARIO_BIG_SIT + 20)
#define ID_SPRITE_MARIO_BIG_BRACE (ID_SPRITE_MARIO_BIG + 600)
#define ID_SPRITE_MARIO_BIG_BRACE_LEFT (ID_SPRITE_MARIO_BIG_BRACE + 10)
#define ID_SPRITE_MARIO_BIG_BRACE_RIGHT (ID_SPRITE_MARIO_BIG_BRACE + 20)

#define ID_SPRITE_MARIO_DIE (ID_SPRITE_MARIO + 3000)

#define ID_SPRITE_MARIO_SMALL (ID_SPRITE_MARIO + 2000)
#define ID_SPRITE_MARIO_SMALL_IDLE (ID_SPRITE_MARIO_SMALL + 100)
#define ID_SPRITE_MARIO_SMALL_IDLE_LEFT (ID_SPRITE_MARIO_SMALL_IDLE + 10)
#define ID_SPRITE_MARIO_SMALL_IDLE_RIGHT (ID_SPRITE_MARIO_SMALL_IDLE + 20)

#define ID_SPRITE_MARIO_SMALL_WALKING (ID_SPRITE_MARIO_SMALL + 200)
#define ID_SPRITE_MARIO_SMALL_WALKING_LEFT (ID_SPRITE_MARIO_SMALL_WALKING + 10)
#define ID_SPRITE_MARIO_SMALL_WALKING_RIGHT (ID_SPRITE_MARIO_SMALL_WALKING + 20)
#define ID_SPRITE_MARIO_SMALL_RUNNING (ID_SPRITE_MARIO_SMALL + 300)
#define ID_SPRITE_MARIO_SMALL_RUNNING_LEFT (ID_SPRITE_MARIO_SMALL_RUNNING + 10)
#define ID_SPRITE_MARIO_SMALL_RUNNING_RIGHT (ID_SPRITE_MARIO_SMALL_RUNNING + 20)
#define ID_SPRITE_MARIO_SMALL_JUMP (ID_SPRITE_MARIO_SMALL + 400)
#define ID_SPRITE_MARIO_SMALL_JUMP_WALK (ID_SPRITE_MARIO_SMALL_JUMP + 10)
#define ID_SPRITE_MARIO_SMALL_JUMP_WALK_LEFT (ID_SPRITE_MARIO_SMALL_JUMP_WALK + 2)
#define ID_SPRITE_MARIO_SMALL_JUMP_WALK_RIGHT (ID_SPRITE_MARIO_SMALL_JUMP_WALK + 6)
#define ID_SPRITE_MARIO_SMALL_JUMP_RUN (ID_SPRITE_MARIO_SMALL_JUMP + 20)
#define ID_SPRITE_MARIO_SMALL_JUMP_RUN_LEFT (ID_SPRITE_MARIO_SMALL_JUMP_RUN + 2)
#define ID_SPRITE_MARIO_SMALL_JUMP_RUN_RIGHT (ID_SPRITE_MARIO_SMALL_JUMP_RUN + 6)

#define ID_SPRITE_MARIO_SMALL_SIT (ID_SPRITE_MARIO_SMALL + 500)
#define ID_SPRITE_MARIO_SMALL_SIT_LEFT (ID_SPRITE_MARIO_SMALL_SIT + 10)
#define ID_SPRITE_MARIO_SMALL_SIT_RIGHT (ID_SPRITE_MARIO_SMALL_SIT + 20)

#define ID_SPRITE_MARIO_SMALL_BRACE (ID_SPRITE_MARIO_SMALL + 500)
#define ID_SPRITE_MARIO_SMALL_BRACE_LEFT (ID_SPRITE_MARIO_SMALL_BRACE + 10)
#define ID_SPRITE_MARIO_SMALL_BRACE_RIGHT (ID_SPRITE_MARIO_SMALL_BRACE + 20)

#pragma endregion 

#define ID_SPRITE_BG_ELEMENT -10000
#define ID_SPRITE_BG_COLOR_BLUE	-10001
#define ID_SPRITE_BG_COLOR_BLACK	-10002

#define ID_SPRITE_BRICK 21000
#define ID_SPRITE_WOOD 23000

#define ID_SPRITE_GOOMBA 30000
#define ID_SPRITE_GOOMBA_WALK_1 (ID_SPRITE_GOOMBA + 1001)
#define ID_SPRITE_GOOMBA_WALK_2 (ID_SPRITE_GOOMBA + 1002)
#define ID_SPRITE_GOOMBA_DIE (ID_SPRITE_GOOMBA + 2001)

#define ID_SPRITE_PARAGOOMBA (ID_SPRITE_GOOMBA+2000)
#define ID_SPRITE_PARAGOOMBA_NO_WING_WALK_1 (ID_SPRITE_PARAGOOMBA + 1)
#define ID_SPRITE_PARAGOOMBA_NO_WING_WALK_2 (ID_SPRITE_PARAGOOMBA + 2)

#define ID_SPRITE_COIN 40000

#define ID_SPRITE_CLOUD 50000

#define ID_SPRITE_GROUND 60000
#define ID_SPRITE_GROUND_TOP_LEFT (ID_SPRITE_GROUND+1000)
#define ID_SPRITE_GROUND_TOP_CEN (ID_SPRITE_GROUND+2000)
#define ID_SPRITE_GROUND_TOP_RIGHT (ID_SPRITE_GROUND+3000)
#define ID_SPRITE_GROUND_MID_LEFT (ID_SPRITE_GROUND+4000)
#define ID_SPRITE_GROUND_MID_CEN (ID_SPRITE_GROUND+5000)
#define ID_SPRITE_GROUND_MID_RIGHT (ID_SPRITE_GROUND+6000)

#define ID_SPRITE_POWERUP 70000
#define ID_SPRITE_POWERUP_MUSHROOM (ID_SPRITE_POWERUP+1000)
#define ID_SPRITE_POWERUP_LEAF_LEFT (ID_SPRITE_POWERUP+2001)
#define ID_SPRITE_POWERUP_LEAF_RIGHT (ID_SPRITE_POWERUP+2002)

#define ID_SPRITE_PIPE 80000
#define ID_SPRITE_PIPE_HEAD_LEFT (ID_SPRITE_PIPE+1001)
#define ID_SPRITE_PIPE_HEAD_RIGHT (ID_SPRITE_PIPE+1002)
#define ID_SPRITE_PIPE_BODY_LEFT (ID_SPRITE_PIPE+2001)
#define ID_SPRITE_PIPE_BODY_RIGHT (ID_SPRITE_PIPE+2002)
#define ID_SPRITE_PIPE_FOOT_LEFT (ID_SPRITE_PIPE+3001)
#define ID_SPRITE_PIPE_FOOT_RIGHT (ID_SPRITE_PIPE+3002)
#define ID_SPRITE_HIDDEN_PIPE_BODY_LEFT (ID_SPRITE_PIPE+4011)
#define ID_SPRITE_HIDDEN_PIPE_BODY_RIGHT (ID_SPRITE_PIPE+4012)
#define ID_SPRITE_HIDDEN_PIPE_FOOT_LEFT (ID_SPRITE_PIPE+4001)
#define ID_SPRITE_HIDDEN_PIPE_FOOT_RIGHT (ID_SPRITE_PIPE+4002)

#define ID_SPRITE_PIRANHA 90000
#define ID_SPRITE_VENUS_TALL (ID_SPRITE_PIRANHA+1000)
#define ID_SPRITE_VENUS_TALL_LEFT_DOWN_OPEN (ID_SPRITE_VENUS_TALL+111)
#define ID_SPRITE_VENUS_TALL_LEFT_DOWN_CLOSE (ID_SPRITE_VENUS_TALL+112)
#define ID_SPRITE_VENUS_TALL_LEFT_UP_OPEN (ID_SPRITE_VENUS_TALL+121)
#define ID_SPRITE_VENUS_TALL_LEFT_UP_CLOSE (ID_SPRITE_VENUS_TALL+122)
#define ID_SPRITE_VENUS_TALL_RIGHT_DOWN_OPEN (ID_SPRITE_VENUS_TALL+211)
#define ID_SPRITE_VENUS_TALL_RIGHT_DOWN_CLOSE (ID_SPRITE_VENUS_TALL+212)
#define ID_SPRITE_VENUS_TALL_RIGHT_UP_OPEN (ID_SPRITE_VENUS_TALL+221)
#define ID_SPRITE_VENUS_TALL_RIGHT_UP_CLOSE (ID_SPRITE_VENUS_TALL+222)
#define ID_SPRITE_VENUS_SHORT (ID_SPRITE_PIRANHA+2000)
#define ID_SPRITE_VENUS_SHORT_LEFT_DOWN_OPEN (ID_SPRITE_VENUS_SHORT+111)
#define ID_SPRITE_VENUS_SHORT_LEFT_DOWN_CLOSE (ID_SPRITE_VENUS_SHORT+112)
#define ID_SPRITE_VENUS_SHORT_LEFT_UP_OPEN (ID_SPRITE_VENUS_SHORT+121)
#define ID_SPRITE_VENUS_SHORT_LEFT_UP_CLOSE (ID_SPRITE_VENUS_SHORT+122)
#define ID_SPRITE_VENUS_SHORT_RIGHT_DOWN_OPEN (ID_SPRITE_VENUS_SHORT+211)
#define ID_SPRITE_VENUS_SHORT_RIGHT_DOWN_CLOSE (ID_SPRITE_VENUS_SHORT+212)
#define ID_SPRITE_VENUS_SHORT_RIGHT_UP_OPEN (ID_SPRITE_VENUS_SHORT+221)
#define ID_SPRITE_VENUS_SHORT_RIGHT_UP_CLOSE (ID_SPRITE_VENUS_SHORT+222)

#define ID_SPRITE_KOOPA 100000
#define ID_SPRITE_KOOPA_GREEN (ID_SPRITE_KOOPA)
#define ID_SPRITE_KOOPA_GREEN_WALKING (ID_SPRITE_KOOPA_GREEN + 100)
#define ID_SPRITE_KOOPA_GREEN_WALKING_LEFT_1 (ID_SPRITE_KOOPA_GREEN_WALKING + 11)
#define ID_SPRITE_KOOPA_GREEN_WALKING_LEFT_2 (ID_SPRITE_KOOPA_GREEN_WALKING + 12)
#define ID_SPRITE_KOOPA_GREEN_WALKING_RIGHT_1 (ID_SPRITE_KOOPA_GREEN_WALKING + 21)
#define ID_SPRITE_KOOPA_GREEN_WALKING_RIGHT_2 (ID_SPRITE_KOOPA_GREEN_WALKING + 22)
#define ID_SPRITE_KOOPA_GREEN_SHELL (ID_SPRITE_KOOPA_GREEN + 200)
#define ID_SPRITE_KOOPA_GREEN_SHELL_IDLE (ID_SPRITE_KOOPA_GREEN_SHELL + 1)
#define ID_SPRITE_KOOPA_GREEN_SHELL_MOVE_1 (ID_SPRITE_KOOPA_GREEN_SHELL + 2)
#define ID_SPRITE_KOOPA_GREEN_SHELL_MOVE_2 (ID_SPRITE_KOOPA_GREEN_SHELL + 3)
#define ID_SPRITE_KOOPA_GREEN_SHELL_MOVE_3 (ID_SPRITE_KOOPA_GREEN_SHELL + 4)

#define ID_SPRITE_KOOPA_RED (ID_SPRITE_KOOPA + 1000)
#define ID_SPRITE_KOOPA_RED_WALKING (ID_SPRITE_KOOPA_RED + 100)
#define ID_SPRITE_KOOPA_RED_WALKING_LEFT_1 (ID_SPRITE_KOOPA_RED_WALKING + 11)
#define ID_SPRITE_KOOPA_RED_WALKING_LEFT_2 (ID_SPRITE_KOOPA_RED_WALKING + 12)
#define ID_SPRITE_KOOPA_RED_WALKING_RIGHT_1 (ID_SPRITE_KOOPA_RED_WALKING + 21)
#define ID_SPRITE_KOOPA_RED_WALKING_RIGHT_2 (ID_SPRITE_KOOPA_RED_WALKING + 22)
#define ID_SPRITE_KOOPA_RED_SHELL (ID_SPRITE_KOOPA_RED + 200)
#define ID_SPRITE_KOOPA_RED_SHELL_IDLE (ID_SPRITE_KOOPA_RED_SHELL + 1)
#define ID_SPRITE_KOOPA_RED_SHELL_MOVE_1 (ID_SPRITE_KOOPA_RED_SHELL + 2)
#define ID_SPRITE_KOOPA_RED_SHELL_MOVE_2 (ID_SPRITE_KOOPA_RED_SHELL + 3)
#define ID_SPRITE_KOOPA_RED_SHELL_MOVE_3 (ID_SPRITE_KOOPA_RED_SHELL + 4)

#define ID_SPRITE_BUTTON	110000

#define ID_SPRITE_HUD_PANEL	130001
#define ID_SPRITE_HUD_P_BADGE_WHITE	130011
#define ID_SPRITE_HUD_TRIANGLE	130021


// each number's sprite corresponding to ID_SPRITE_NUMBER + <number> 
#define ID_SPRITE_NUMBER	131000

// each alphabet character's sprite corresponding to ID_SPRITE_ALPHABET + <ASCII - 'A'>
#define ID_SPRITE_ALPHABET	132000

#define ID_SPRITE_CARD		133000
#define ID_SPRITE_CARD_BLANK	(ID_SPRITE_CARD+0)
#define ID_SPRITE_CARD_MUSHROOM	(ID_SPRITE_CARD+1)
#define ID_SPRITE_CARD_FLOWER	(ID_SPRITE_CARD+2)
#define ID_SPRITE_CARD_STAR		(ID_SPRITE_CARD+3)

#define ID_SPRITE_PORTAL_PASS	-49999

// each portal contain number have sprite ID_SPRITE_PORTAL_NUMBER - <number>
#define ID_SPRITE_PORTAL_NUMBER	-40000
#define ID_SPRITE_PORTAL_START	-40000

#define ID_SPRITE_ROULETTE_CARD	-11000
#define ID_SPRITE_ROULETTE_CARD_MUSHROOM	(ID_SPRITE_ROULETTE_CARD - 1)
#define ID_SPRITE_ROULETTE_CARD_FLOWER		(ID_SPRITE_ROULETTE_CARD - 2)
#define ID_SPRITE_ROULETTE_CARD_STAR		(ID_SPRITE_ROULETTE_CARD - 3)