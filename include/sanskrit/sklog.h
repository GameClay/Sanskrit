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

/* Disable unused function warnings for GCC */
#if (__GNUC__ >= 4) && (__GNUC_MINOR__ >= 6)
#  define _SK_UNUSED_FUNC_WARNING_DISABLED_
#  pragma GCC diagnostic push
#  pragma GCC diagnostic ignored "-Wunused-function"
#endif

#if 0
#  define SK_INLINE inline
#else
#  define SK_INLINE
#endif

/* Log levels */
#if 1 /* ASL */
#  define SKLOG_LEVEL_INFO    ASL_LEVEL_INFO
#  define SKLOG_LEVEL_DEBUG   ASL_LEVEL_DEBUG
#  define SKLOG_LEVEL_WARN    ASL_LEVEL_WARNING
#  define SKLOG_LEVEL_ERR     ASL_LEVEL_ERR
#endif

/* Redefine this to change the source-name of the log messages */
#ifndef SK_LOG_IDENT
#  define SK_LOG_IDENT Sanskrit
#endif
#define _SK_STRINGIFY(x) #x
#define SK_STRINGIFY(x) _SK_STRINGIFY(x)

#define _SKLOG_IMPL(LOG_LEVEL)                        \
   {                                                  \
      va_list vl;                                     \
      va_start(vl, format);                           \
      sklogv(LOG_LEVEL, format, vl);                  \
      va_end(vl);                                     \
   }

static aslclient _sklog_asl_client;
static int _sklog_enabled = 0;

static int sklog_init()
{
   _sklog_asl_client = asl_open(SK_STRINGIFY(SK_LOG_IDENT), "com.apple.console", ASL_OPT_STDERR | ASL_OPT_NO_DELAY);
   _sklog_enabled = (_sklog_asl_client == NULL ? 0 : 1);
   return (_sklog_enabled == 1 ? 0 : -1);
}

static void sklog_destroy()
{
   _sklog_enabled = 0;
   if(_sklog_asl_client != NULL)
   {
      asl_close(_sklog_asl_client);
   }
}

static void sklogv(int log_level, const char* format, va_list vargs)
{
   if(_sklog_enabled)
   {
      aslmsg msg = asl_new(ASL_TYPE_MSG);
      asl_set(msg, ASL_KEY_FACILITY, "com.apple.console");
      asl_vlog(_sklog_asl_client, msg, log_level, format, vargs);
      asl_free(msg);
   }
}

/* sklog == skinfo */
#define sklog skinfo

#ifndef SK_DISABLE_LOGS

/* Info */
#  ifndef SK_DISABLE_INFO
static SK_INLINE void skinfo(const char* format, ...)
{
   _SKLOG_IMPL(SKLOG_LEVEL_INFO);
}
#  else
static SK_INLINE void skinfo(const char* format, ...) {}
#  endif

/* Debug */
#  ifndef SK_DISABLE_DEBUG
static SK_INLINE void skdebug(const char* format, ...)
{
   _SKLOG_IMPL(SKLOG_LEVEL_DEBUG);
}
#  else
static SK_INLINE void skdebug(const char* format, ...) {}
#  endif

/* Warning */
#  ifndef SK_DISABLE_WARN
static SK_INLINE void skwarn(const char* format, ...)
{
   _SKLOG_IMPL(SKLOG_LEVEL_WARN);
}
#  else
static SK_INLINE void skwarn(const char* format, ...) {}
#  endif

/* Error */
#  ifndef SK_DISABLE_ERROR
static SK_INLINE void skerr(const char* format, ...)
{
   _SKLOG_IMPL(SKLOG_LEVEL_ERR);
}
#  else
static SK_INLINE void skerr(const char* format, ...) {}
#  endif

/* Prevent warnings/errors about unused functions */
#ifndef _SK_UNUSED_FUNC_WARNING_DISABLED_
static void _sk_disable_unused_never_call_this_()
{
   sklog_init();
   sklog_destroy();
   skinfo("");
   skdebug("");
   skwarn("");
   skerr("");
   _sk_disable_unused_never_call_this_();
}
#endif

#else
/* Disable all the things */
static SK_INLINE void skinfo(const char* format, ...) {}
static SK_INLINE void skdebug(const char* format, ...) {}
static SK_INLINE void skwarn(const char* format, ...) {}
static SK_INLINE void skerr(const char* format, ...) {}
#endif

#endif

#if (__GNUC__ >= 4) && (__GNUC_MINOR__ >= 6)
#     pragma GCC diagnostic pop
#endif
