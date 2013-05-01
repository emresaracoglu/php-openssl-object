<?php
  // plain prototyp
  $publickey = '';
  $privatekey = '';
  $res = '';
  $passphrase = 'pass';
  $options = array(
    'private_key_bits' => 4096,
    'private_key_type' => OPENSSL_KEYTYPE_RSA,
  );

  if($passphrase) {
    // privatekey
    $res = openssl_pkey_new($options);
    openssl_pkey_export($res,$privatekey,$passphrase);
    //publickey
    $publickey = openssl_pkey_get_details($res);
    $publickey = $publickey["key"];
  }
  openssl_pkey_export_to_file($res, 'privatekey', $passphrase);
  file_put_contents('publickey', $publickey);

  // some data to encrypt
  $sensitiveData = 'my string';
  $pubKey = openssl_pkey_get_public(file_get_contents('publickey'));
  openssl_public_encrypt($sensitiveData, $encryptedData, $pubKey);
  var_dump($encryptedData);
  $privateKey = openssl_pkey_get_private(file_get_contents('privatekey'), $passphrase);
  openssl_private_decrypt($encryptedData, $output, $privateKey);
  var_dump($output);
?>
