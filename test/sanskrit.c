/*#define SK_DISABLE_LOGS*/
/*#define SK_DISABLE_INFO*/

#include <sanskrit/sklog.h>

int main()
{
   sklog_init();

   sklog("sklog!");
   skdebug("skdebug!");
   skwarn("skwarn!");
   skerr("skerr!");

   sklog_destroy();
   return 0;
}
