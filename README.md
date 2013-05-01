php-openssl-object
==================

Php object to generate asymetric keys, encrypt/decrypt data using openssl module.
http://www.php.net/manual/en/book.openssl.php


How to use
==========
```php
// load inc
include('openssl.inc');

$stringprivate = "-----BEGIN ENCRYPTED PRIVATE KEY-----
MIIJjjBABgkqhkiG9w0BBQ0wMzAbBgkqhkiG9w0BBQwwDgQIBdkgIY0LuHwC...";

  $stringpublic = "-----BEGIN PUBLIC KEY-----
MIICIjANBgkqhkiG9w0BAQEFAAOCAg8AMIICCgKCAgEAv7sklYrUXggIy9...";

// init
$ssl = new openssl();

// set passphrase
$ssl->set_passphrase('pass');

// set keys from file
$ssl->set_key(false,'path/to/file/publickey');
$ssl->set_key(true,'path/to/file/privatekey');

// set keys from string
$ssl->set_key(false,false,$stringpublic);
$ssl->set_key(true,false,$stringprivate);

//generate new keypair
$ssl->genrate_keypair('keyname');

// output privatekey
var_dump($ssl->get_key(true));
// output publickey
var_dump($ssl->get_key());

// encrypt data, don't forget to set the public key before
var_dump($ssl->encrypt('some data'));

// decrypt data, set passphrase and privatekey before
var_dump($ssl->decrypt('some encrypted data'));
```

 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <adn:@westberliner> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return. Patrick Herzberg
 * ----------------------------------------------------------------------------
 * http://en.wikipedia.org/wiki/Beerware
 *
 *
 * Switch beer with whiskey ;)
