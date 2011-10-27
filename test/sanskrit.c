/*#define SK_DISABLE_LOGS*/
/*#define SK_DISABLE_INFO*/

#include <sanskrit/sklog.h>

int main()
{
   sklog("sklog!\n");
   skdebug("skdebug!\n");
   skwarn("skwarn!\n");
   skerr("skerr!\n");

   return 0;
}