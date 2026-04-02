#include "Keyboard.h"
#include "../../Input/Keyboard.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Input;

bool E3DRSP_Keyboard_IsKeyDown(E3DRSP_Keyboard* kb, E3DRSP_Key key)
{
    if(kb == nullptr) return false;
    return (reinterpret_cast<Keyboard*>(kb))->IsKeyDown(static_cast<Key>(key));
}

bool E3DRSP_Keyboard_IsKeyUp(E3DRSP_Keyboard* kb, E3DRSP_Key key)
{
    if(kb == nullptr) return false;
    return (reinterpret_cast<Keyboard*>(kb))->IsKeyUp(static_cast<Key>(key));
}

bool E3DRSP_Keyboard_IsAnyKeyDown(E3DRSP_Keyboard* kb)
{
    if(kb == nullptr) return false;
    return (reinterpret_cast<Keyboard*>(kb)->IsAnyKeyDown());
}

E3DRSP_KeyState E3DRSP_Keyboard_At(E3DRSP_Keyboard* kb, E3DRSP_Key key)
{
    if(kb == nullptr) return E3DRSP_KeyState_Down;
    return static_cast<E3DRSP_KeyState>((reinterpret_cast<Keyboard*>(kb))->operator[](static_cast<Key>(key)));
}
