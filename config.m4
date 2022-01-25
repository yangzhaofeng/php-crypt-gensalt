PHP_ARG_WITH(crypt_gensalt)

if test "$PHP_CRYPT_GENSALT" != "no"; then
    dnl Check for required libcrypt library
    AC_MSG_CHECKING([for libcrypt])
    for i in $PHP_CRYPT_GENSALT /usr/local /usr; do
        if test -f "$i/include/crypt.h"; then
            PHP_CRYPT_DIR=$i
            break
        fi
    done
    if test -z "$PHP_CRYPT_DIR"; then
        AC_MSG_ERROR([not found])
    fi

    dnl Found libcrypt's header
    AC_MSG_RESULT([found in $PHP_CRYPT_DIR])

    dnl Update library list and include paths for libcrypt
    PHP_ADD_INCLUDE($PHP_CRYPT_DIR/include)
    PHP_ADD_LIBRARY_WITH_PATH(crypt, $PHP_CRYPT_DIR/$PHP_LIB_DIR, CRYPT_GENSALT_SHARED_LIBADD)
    PHP_SUBST(CRYPT_GENSALT_SHARED_LIBADD)

    PHP_NEW_EXTENSION(crypt_gensalt, php_crypt_gensalt.c, $ext_shared)
fi
