#include "kbd.h"

Cmd checkKeyboard()
{
    if (IsKeyDown(KEY_LEFT))
        return CMD_MOVE_LEFT;
    if (IsKeyDown(KEY_RIGHT))
        return CMD_MOVE_RIGHT;
    if (IsKeyDown(KEY_UP))
        return CMD_MOVE_UP;
    if (IsKeyDown(KEY_DOWN))
        return CMD_MOVE_DOWN;
    if (IsKeyDown(KEY_LEFT_CONTROL))
        return CMD_MOVE_IN;
    if (IsKeyDown(KEY_RIGHT_CONTROL))
        return CMD_MOVE_OUT;
    if (IsKeyDown(KEY_HOME))
        return CMD_MOVE_HOME;
    return CMD_UNDEFINED;
}
