/*#define SK_DISABLE_LOGS*/
/*#define SK_DISABLE_INFO*/

#include <sanskrit/sklog.h>

int main()
{
   sklog_init();

   sklog("sklog!\n");
   skdebug("skdebug!\n");
   skwarn("skwarn!\n");
   skerr("skerr!\n");

   sklog_destroy();
   return 0;
}