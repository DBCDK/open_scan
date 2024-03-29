<?php

/**
 * @file
 * datawellScan : open_scan class
 * @see ting_client.module
 * @see ting_client_admin_webservices_settings
 **/

class datawellScanRequest extends TingClientRequest Implements ITingClientRequestCache {

  /**
   * Request action.
   * @var string
   */
  protected $action;

  /**
   * CURL options.
   * @var array
   */
  public $curlOptions = NULL;

  /**
   * Request object.
   * @var object
   */
  private $requestParameters;


  /* Get cURL options.
   *
   * we include CURL options in the request, in order to be able configure MicroCURL,
   * but the params are unset before we do TingRestClient->call().
   *
   * @return array
   */
  public function getCurlOptions() {
    return $this->curlOptions;
  }

  /* Set cURL options.
   *
   * @param array $options
   */
  public function setCurlOptions($options) {
    $this->curlOptions = $options;
  }

  /*
   * Get JSON request object.
   *
   * @return object
   */
  public function getRequestParameters() {
    return $this->requestParameters;
  }

  /*
   * Set JSON request object.
   *
   * @param object $requestParameters
   */
  public function setRequestParameters($requestParameters) {
    $this->requestParameters = $requestParameters;
  }


  /* Implementation of ITingClientRequestCache */

  /** \brief ITingClientRequestCache::checkResponse;
   * Check if response is empty. If so, tell ting-client not to cache
   * @param $response
   * @return bool
   */
  public function checkResponse($response) {
    $response = json_decode($response);
    // do NOT cache if result is empty
    if (!$response || empty($response->data)) {
      return FALSE;
    }
    return TRUE;
  }


  /** \brief ITingClientRequestCache::cacheEnable; Check if cache is enabled
   *
   * @return value of variable (drupal_get)
   **/
  public function cacheEnable($value = NULL) {
    $class_name = get_class($this);
    return variable_get($class_name . TingClientRequest::cache_enable);
  }


  /** \brief ITingClientRequestCache::cacheTimeout; Set timeout of cache
   *
   * @return mixed value of variable (variable_get)
   **/
  public function cacheTimeout($value = NULL) {
    $class_name = get_class($this);
    return variable_get($class_name . TingClientRequest::cache_lifetime, '1');
  }


  /** \brief ITingClientRequestCache::cacheBin;
   *
   * @return string; name of cachebin
   **/
  public function cacheBin() {
    return 'cache_open_scan';
  }

  /*
   * Implements TingClientRequest::setAction.
   */
  public function setAction($value = NULL) {
    $this->action = $value;
  }

  /*
   * Implements TingClientRequest::getAction.
   */
  public function getAction() {
    return $this->action;
  }

  /*
   * Extend TingClientRequest::getClientType to use REST client.
   */
  public function getClientType() {
    return 'REST';
  }

  /*
   * Implements TingClientRequest::processResponse.
   */
  public function processResponse(stdClass $response) {
    // ting_client returns false if something goes wrong
    if ($response === FALSE) {
      return (object) array(
        'error' => '400',
        'errorMessage' => 'Null response from ting_client:scan.',
        'result' => (object) array()
      );
    }
    return $response;
  }
}
