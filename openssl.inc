<?php
class openssl {
  protected $publickey;
  protected $privatekey;
  protected $passphrase;
  protected $res;
  protected $options = array(
    'private_key_bits' => 4096,
    'private_key_type' => OPENSSL_KEYTYPE_RSA,
  );

  public function __construct($object = NULL) {
    // nothing to do here right now
  }

  // setup
  // keypair (public/private)
  public function genrate_keypair($tofile = '') {
    if(!empty($this->passphrase)) {
      // privatekey
      $res = openssl_pkey_new($this->options);
      openssl_pkey_export($res,$privatekey,$this->passphrase);
      $this->privatekey = $privatekey;
      $this->res = $res;
      //publickey
      $publickey = openssl_pkey_get_details($res);
      $this->publickey = $publickey["key"];
      // save to file
      if (!empty($tofile)) {
        $this->export_to_file($tofile);
      }
    }
  }
  protected function export_to_file($tofile) {
    openssl_pkey_export_to_file($this->res, $tofile.'.key', $this->passphrase);
    file_put_contents($tofile.'public.key', $this->publickey);
  }
  public function set_key($private = false, $fromfile = false, $key = '') {
    // from file?
    if($fromfile) {
      if($content = file_get_contents($fromfile)) {
        $key = $content;
      }
    }
    if($private) {
      $this->privatekey = $key;
    } else {
      $this->publickey = $key;
    }
  }
  public function get_key($private = false) {
    return $private ? $this->privatekey : $this->publickey;
  }

  // passphrase
  public function set_passphrase($passphrase = '') {
    $this->passphrase = $passphrase;
  }

  // actions
  public function encrypt($data) {
    if($publickey = openssl_pkey_get_public($this->publickey)) {
      openssl_public_encrypt($data, $encryptedData, $publickey);
      return $encryptedData;
    }
  }
  public function decrypt($data) {
    if( !empty($this->passphrase) &&
        $privatekey = openssl_pkey_get_private($this->privatekey, $this->passphrase)
    ) {
      openssl_private_decrypt($data, $output, $privatekey);
      return $output;
    }
  }
}

/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <adn:@westberliner> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return Patrick Herzberg
 * ----------------------------------------------------------------------------
 * http://en.wikipedia.org/wiki/Beerware
 *
 *
 * Switch beer with whiskey ;)
 */
