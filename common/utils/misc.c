/*
  +----------------------------------------------------------------------+
  | Common utility function for PHP extensions                           |
  +----------------------------------------------------------------------+
  | Copyright (c) 2015 The PHP Group                                     |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt.                                 |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author: Francois Laupretre <francois@tekwire.net>                    |
  +----------------------------------------------------------------------+
*/

#include "main/SAPI.h"

/*============================================================================*/

static int ut_is_web()
{
	static int init_done = 0;
	static int web;

	if (!init_done)
		{
		web = strcmp(sapi_module.name, "cli");
		init_done = 1;
		}
	return web;
}

/*------------------*/

static int ut_extension_loaded(char *name, int len TSRMLS_DC)
{
	int status;

#ifdef PHP_7
	status = zend_hash_str_exists(&module_registry, name, len);
#else
	status = zend_hash_exists(&module_registry, name, len + 1);
#endif

	DBG_MSG2("Checking if extension %s is loaded: %s",name,(status ? "yes" : "no"));
	return status;
}

/*============================================================================*/