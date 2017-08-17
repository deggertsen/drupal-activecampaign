ActiveCampaign Module for Drupal 7
----------------------------------

Provides ActiveCampaign integration for Drupal 7. This module
includes support for both Composer Manager and the Libraries
API.

Install
----------

To get started using the API, you will need to go through an initial set-up
process. The result of the setup process will be an encrypted key that you
will need for authentication.

1. Enable the ActiveCampaign API and obtain an API Key, instructions here:
   https://help.activecampaign.com/hc/en-us/articles/207317590-Getting-started-with-the-API
2. Write down the encrypted key - it will be essential to getting the API to work
3. Install the drupal module in the usual way. See here for more information
   http://drupal.org/documentation/install/modules-themes
4. On your Drupal site fill out the information on admin/config/services/activecampaign.
5. Map fields using the provided UI or using the provided API. Go to admin/config/services/activecampaign/fields for the UI or see activecampaign.api.php for the API.
6. Once you have completed the above go to any Drupal user page and click the ActiveCampaign tab. This will automatically cause the module to search for an ActiveCampaign contact associated with the user email. If a contact is found it will sync the contact with mapped fields. If no contact is found it will provide a button that you can click to create a new contact.
