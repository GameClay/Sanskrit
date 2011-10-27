/* -*- Mode: C; tab-width: 3; c-basic-offset: 3; indent-tabs-mode: nil -*- */
/* vim: set filetype=C tabstop=3 softtabstop=3 shiftwidth=3 expandtab: */

/* Sanskrit -- Copyright (C) 2011 GameClay LLC
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef _SANSKRIT_H_
#define _SANSKRIT_H_

#include <asl.h>

#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>

#if 0
#  define SK_INLINE inline
#else
#  define SK_INLINE
#endif

#define _SKLOG_IMPL(LOG_LEVEL)                        \
   {                                                  \
      va_list vl;                                     \
      va_start(vl, format);                           \
      sklogv(LOG_LEVEL, format, vl);                  \
      va_end(vl);                                     \
   }

static aslclient _sklog_asl_client;
static int _sklog_enabled = 1;

static void sklogv(int log_level, const char* format, va_list vargs)
{
   if(_sklog_asl_client == NULL)
   {
      _sklog_asl_client = asl_open("SkLog", "com.apple.console", ASL_OPT_STDERR | ASL_OPT_NO_DELAY);
      if(_sklog_asl_client == NULL)
      {
         fprintf(stderr, "[Sanskrit]: Unable to create ASL client. Disabling logging.\n");
         _sklog_enabled = 0;
      }
   }

   if(_sklog_enabled)
   {
      aslmsg msg = asl_new(ASL_TYPE_MSG);
      asl_set(msg, ASL_KEY_FACILITY, "com.apple.console");
      asl_vlog(_sklog_asl_client, msg, log_level, format, vargs);
   }
}

/* sklog == skinfo */
#define sklog skinfo

#ifndef SK_DISABLE_LOGS

/* Info */
#  ifndef SK_DISABLE_INFO
static SK_INLINE void skinfo(const char* format, ...)
{
   _SKLOG_IMPL(ASL_LEVEL_INFO);
}
#  else
static SK_INLINE void skinfo(const char* format, ...) {}
#  endif

/* Debug */
#  ifndef SK_DISABLE_WARN
static SK_INLINE void skdebug(const char* format, ...)
{
   _SKLOG_IMPL(ASL_LEVEL_DEBUG);
}
#  else
static SK_INLINE void skdebug(const char* format, ...) {}
#  endif

/* Warning */
#  ifndef SK_DISABLE_WARN
static SK_INLINE void skwarn(const char* format, ...)
{
   _SKLOG_IMPL(ASL_LEVEL_WARNING);
}
#  else
static SK_INLINE void skwarn(const char* format, ...) {}
#  endif

/* Error */
#  ifndef SK_DISABLE_ERROR
static SK_INLINE void skerr(const char* format, ...)
{
   _SKLOG_IMPL(ASL_LEVEL_ERR);
}
#  else
static SK_INLINE void skerr(const char* format, ...) {}
#  endif

#else
/* Disable all the things */
static SK_INLINE void skinfo(const char* format, ...) {}
static SK_INLINE void skdebug(const char* format, ...) {}
static SK_INLINE void skwarn(const char* format, ...) {}
static SK_INLINE void skerr(const char* format, ...) {}
#endif

#endif
