#include "Keyboard.hpp"
#include "Keyboard.h"

using namespace Engine3DRadSpace::Input;

void Keyboard::_addKey(uint8_t k)
{
    for (int i = 0; i < 10; i++)
    {
        if (_keys[i] == k) return; //Do not duplicate keys.
        if (_keys[i] == 0)
        {
            _keys[i] = k;
            break;
        }
    }
}

void Keyboard::_removeKey(uint8_t k)
{
    for (int i = 0; i < 10; i++)
    {
        if (k == _keys[i]) _keys[i] = 0;
    }
}

void Keyboard::_erase()
{
    for (int i = 0; i < 10; i++)
    {
        _keys[i] = 0;
    }
}

Keyboard::Keyboard() :
    _keys{0}
{
}

bool Keyboard::IsKeyDown(Key k) const noexcept
{
    for (int i = 0; i < 10; i++)
    {
        if (static_cast<uint8_t>(k) == _keys[i])\
            return true;
    }
    return false;
}

bool Keyboard::IsKeyUp(Key k) const noexcept
{
    for (int i = 0; i < 10; i++)
    {
        if (static_cast<uint8_t>(k) == _keys[i])  
            return false;
    }
    return true;
}

bool Engine3DRadSpace::Input::Keyboard::IsAnyKeyDown() const noexcept
{
    for (int i = 0; i < 10; i++)
    {
        if (_keys[i] != 0) return true;
    }
    return false;
}

KeyState Keyboard::operator[](const Key k)
{
    for (int i = 0; i < 10; i++)
    {
        if (static_cast<uint8_t>(k) == _keys[i]) 
            return KeyState::Up;
    }
    return KeyState::Down;
}

bool E3DRSP_Keyboard_IsKeyDown(E3DRSP_Keyboard* kb, E3DRSP_Key key)
{
    return (reinterpret_cast<Keyboard*>(kb))->IsKeyDown(static_cast<Key>(key));
}

bool E3DRSP_Keyboard_IsKeyUp(E3DRSP_Keyboard* kb, E3DRSP_Key key)
{
    return (reinterpret_cast<Keyboard*>(kb))->IsKeyUp(static_cast<Key>(key));
}

bool E3DRSP_Keyboard_IsAnyKeyDown(E3DRSP_Keyboard* kb)
{
    return (reinterpret_cast<Keyboard*>(kb)->IsAnyKeyDown());
}

E3DRSP_KeyState E3DRSP_Keyboard_At(E3DRSP_Keyboard* kb, E3DRSP_Key key)
{
    return static_cast<E3DRSP_KeyState>((reinterpret_cast<Keyboard*>(kb))->operator[](static_cast<Key>(key)));
}
