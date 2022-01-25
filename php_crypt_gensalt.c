#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <php.h>
#include <crypt.h>
#include "php_crypt_gensalt.h"

zend_function_entry crypt_gensalt_functions[] = {
	PHP_FE(crypt_gensalt, NULL) {NULL, NULL, NULL}
};

zend_module_entry crypt_gensalt_module_entry = {
	STANDARD_MODULE_HEADER,
	PHP_CRYPT_GENSALT_EXTNAME,
	crypt_gensalt_functions,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	PHP_CRYPT_GENSALT_VERSION,
	STANDARD_MODULE_PROPERTIES
};

ZEND_GET_MODULE(crypt_gensalt);

PHP_FUNCTION(crypt_gensalt) {
	const char *prefix;
	unsigned long count;
	const char *rbytes;
	int nrbytes;

	char* prefix_get = NULL;
	size_t prefix_len = 0;
	zend_long count_get = 0;
	char* rbytes_get = NULL;
	size_t rbytes_len = 0;

	if(zend_parse_parameters(ZEND_NUM_ARGS(), "s!l|s!l", &prefix_get, &prefix_len, &count_get, &rbytes_get, &rbytes_len) == FAILURE){
		return;
	}

	prefix = prefix_get;
	count = count_get;
	rbytes = rbytes_get;
	nrbytes = rbytes_len;

	const char* setting = strdup(crypt_gensalt(prefix, count, rbytes, nrbytes));
	//php_printf(setting);
	RETURN_STRING(setting);
}
