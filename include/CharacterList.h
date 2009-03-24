#ifndef CHARACTERLIST_H_
#define CHARACTERLIST_H_
#include "Character.h"
#include <stdlib.h>

/**
 *  List of characters to display, check for collisions, etc
 */
class CharacterList
{

  public:

      Character* c;

      CharacterList* next;

      CharacterList(){next = NULL;}

      ~CharacterList()
      {

          if(next != NULL)
          {

              delete next;
          }

      }
      CharacterList(Character* c1)
      { 

          c=c1; next = NULL;
      }

      void add(Character* c1)
      {

          if(next == NULL)
          {

              next = new CharacterList(c1);
          }
          else
          {

              next->add(c1);
          }

      }

};

#endif /*CHARACTERLIST_H_*/

