#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <php.h>
#include <crypt.h>
#include <string.h>
#include "php_crypt_gensalt.h"

zend_function_entry crypt_gensalt_functions[] = {
	PHP_FE(crypt_gensalt, NULL)
	PHP_FE(system_crypt, NULL)
	{NULL, NULL, NULL}
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

PHP_FUNCTION(system_crypt) {
	const char *phrase;
	const char *setting;

	char* phrase_get = NULL;
	size_t phrase_len = 0;
	char* setting_get = NULL;
	size_t setting_len = 0;

	if(zend_parse_parameters(ZEND_NUM_ARGS(), "ss", &phrase_get, &phrase_len, &setting_get, &setting_len) == FAILURE){
		RETURN_NULL();
	}
	phrase = phrase_get;
	setting = setting_get;

	struct crypt_data nr_crypt_ctx;
	const char* challenge = strdup(crypt_r(phrase, setting, &nr_crypt_ctx)); // safe because crypt will return "*0" if generation failed
	if(strncmp(challenge, "*0", 2)){
		RETURN_STRING(challenge);
	}else{
		RETURN_NULL();
	}
}

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

	if(zend_parse_parameters(ZEND_NUM_ARGS(), "s!l|s!", &prefix_get, &prefix_len, &count_get, &rbytes_get, &rbytes_len) == FAILURE){
		RETURN_NULL();
	}

	prefix = prefix_get;
	count = count_get;
	rbytes = rbytes_get;
	nrbytes = rbytes_len;

	char output[CRYPT_GENSALT_OUTPUT_SIZE];
	const char* setting = (setting = crypt_gensalt_rn(prefix, count, rbytes, nrbytes, output, sizeof (output))) ? strdup(setting) : NULL;
	//php_printf(setting);
	if(setting){
		RETURN_STRING(setting);
	}else{
		RETURN_NULL();
	}
}
