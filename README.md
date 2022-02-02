# php-crypt-gensalt
use crypt_gensalt() from crypt.h in php

## Information

This project is designed for directly calling system crypt_gensalt() function.

PHP provides a crypt() interface to use system crypt(). However, crypt_gensalt() is not provided so php programs have to generate password hash themselves. In addition, if setting is `NULL` or not passed to crypt(), it will generate a `$1$` shadow, instead of the strongest one, which the system crypt() does.

## Build
```bash
$ phpize
$ ./configure
$ make
# make install
```

## Usage
First you need to load `crypt_gensalt.so`. You can use `dl()` (not safe) or `extension=/path/to/crypt_gensalt.so` in configuration file.

It can be called like
```
crypt_gensalt(string $prefix, int $count, string $rbytes): string
system_crypt(string $phrase, string $setting): string
```
The `rbytes` parameter is optional. Theoretically, all parameters can be optional, and there should be 4 parameters (`char *crypt_gensalt(const char *prefix, unsigned long count, const char *rbytes, int nrbytes)`). This is alpha version so they can be changed.
