ActiveCampaign Module for Drupal 7
----------------------------------

Provides ActiveCampaign integration for Drupal 7. This module
includes support for both Composer Manager and the Libraries
API.

INSTALLATION
------------

 * Make sure that you have the Libraries or Composer Manager modules installed so that the ActiveCampaign API PHP library will be installed correctly.
 * Install the ActiveCampaign drupal module in the usual way. See here for more information
   http://drupal.org/documentation/install/modules-themes

CONFIGURATION
-------------

 * Enable the ActiveCampaign API and obtain an API Key, instructions here:
   https://help.activecampaign.com/hc/en-us/articles/207317590-Getting-started-with-the-API
 * On your Drupal site fill out the information on admin/config/services/activecampaign.
 * Map fields using the provided UI or using the provided API. Go to admin/config/services/activecampaign/fields for the UI or see activecampaign.api.php for the API.
 * Once you have completed the above go to any Drupal user page and click the ActiveCampaign tab. This will automatically cause the module to search for an ActiveCampaign contact associated with the user email. If a contact is found it will sync the contact with mapped fields. If no contact is found it will provide a button that you can click to create a new contact.

 MAINTAINERS
-----------

Current maintainer:
 * David Eggertsen (deggertsen) - https://www.drupal.org/u/deggertsen

This project has been sponsored by:
 * The Freedom Catalyst
   Specialized in training people to become Enrollment Masters. http://thefreedomcatalyst.com