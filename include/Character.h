// 
// File:   Character.h
// Author: kyle2
//
// Created on June 9, 2007, 12:12 PM
//
#ifndef _Character_H
#define	_Character_H

#include "gba_data_types.h"
#include "Sprites.h"
#include "CollisionBox.h"
#include "Vertex2D.h"

//***********************************************************************
/**
 *  Base class for all characters to animate in game (Not needed?)
 */
class Character
{

    //--------------------------------------------
    //      Member attributes
    //--------------------------------------------
public:

    CollisionBox collision_box;

    /// The current position of the character*/
    Vector2D position;

    /// The current velocity the character has */
    Vector2D velocity_vector;

protected:

    /// The sprite index the hardware had a reference to*/
    u8 sprite_index;

    // Debug cord
    int starting_y;	 

    int in_motion;     
    /// This character's pallet number*/
    u8 pallet_number;

    /// The Object Attribute memory associated with this sprite */
    OAM_Entry oam;

    //--------------------------------------------
    //  private Function prototypes 
    //--------------------------------------------

    virtual void init(unsigned char* tiles, int tiles_size, 
            int tiles_loaded, int color_code,
            u8 pallet_number, int sprite_size_code, 
            int position_x, int position_y,
            int velocity_vector_x, int velocity_vector_y);

public: 

    Character();
    Character(int pallet_number2){pallet_number = pallet_number2;}
    Character(unsigned char* tiles, int tiles_size,
            int tiles_loaded, int color_code, int pallet_number2, 
            int sprite_size_code);
    virtual ~Character();

    //--------------------------------------------
    // Public member function prototypes
    //--------------------------------------------
    virtual void moveUp(){position.y--;};
    virtual void moveDown(){position.y++;};
    virtual void moveLeft(){position.x--;};
    virtual void moveRight(){position.x++;};

    //virtual void setInMotion();        
    virtual u8 getSpriteIndex(){return sprite_index; }
    virtual u8 getPalletNumber(){return pallet_number;}
    virtual void init();
    void enableSprite();

    ///   Set the character in motion */
    void setInMotion(int in_motion1)
    {

        in_motion = in_motion1;
    }

    int getPositionX();
    int getPositionY();
    void setPosition(int x, int y);
    void setPosition(Vertex2D v);
    void setPositionX(int x);
    void setPositionY(int y);
    Vector2D getPosition();
    Vector2D getVelocityVector();

    /*
    Character(u8 sprite_index, int position_x, int position_y, 
	int in_motion);
    Character(int position_x, int position_y, 
	int in_motion);
    */

    virtual void updateGraphic()
    {

	Sprites::setSpritePosition(position.x, 
                position.y,sprite_index);

    }

};

//********************************************************

inline Vector2D Character::getPosition()
{

    return position;
}

//********************************************************

inline Vector2D Character::getVelocityVector()
{

    return velocity_vector;
}

//********************************************************
/**
 * 		\return the X cord of this char
 */

inline int Character::getPositionX()
{

    return Sprites::getSpriteXCord(sprite_index);
}
//********************************************************
/**
 *   \return the Y cord of this char
 */

inline int Character::getPositionY()
{

    return Sprites::getSpriteYCord(sprite_index);
}
//*******************************************************
/**
 *  Set the characters position with (x,y) cords
 */

inline void Character::setPosition(int x, int y)
{

    setPositionX(x);
    setPositionY(y);

}

//********************************************************
/**
 *	Set the characters position with a Vertex double
 */

inline void Character::setPosition(Vertex2D v)
{

    setPositionX(v.x);
    setPositionY(v.y);

}

//********************************************************

inline void Character::setPositionX(int x)
{

    Sprites::setSpriteXCord(x, sprite_index);

}

//********************************************************

inline void Character::setPositionY(int y)
{

    Sprites::setSpriteYCord(y, sprite_index);

}

//-------------------------------------------------------------
// Put all small member functions here and make inline
//********************************************************
/**
*   Enable sprite
*/

inline void Character::enableSprite()
{

    Sprites::enableSprite(this->sprite_index);

}

#endif	/* _Character_H */


