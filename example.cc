#include <iostream>
#include "oauth/account.h"
#include "oauth/oauth.h"

int main() {
  // set consumer key
  twitpp::oauth::account account("CONSUMER", "CONSUMER_SECRET");

  try {
    // get authorization url
    if (account.get_authorize_url() == 0) {
      std::cout << account.authorize_url() << std::endl;
    } else {
      std::cerr << "ERROR" << std::endl;
      return -1;
    }

    // input pin
    std::string pin;
    std::cout << "Input PIN: ";
    std::cin >> pin;

    // get oauth token
    if (account.get_oauth_token(pin) == 0) {
      std::cout << "consumer_key:    " << account.consumer_key() << std::endl;
      std::cout << "consumer_secret: " << account.consumer_secret() << std::endl;
      std::cout << "oauth_token:     " << account.oauth_token() << std::endl;
      std::cout << "oauth_secret:    " << account.oauth_token_secret() << std::endl;
    } else {
      std::cerr << "ERROR" << std::endl;
      return -1;
    }

    twitpp::oauth::client oauth(account);

    // update
    auto res = oauth.post("https://api.twitter.com/1.1/statuses/update.json", {{"status", "Test Tweet!"}});
    std::cout << res.response_body << std::endl;

    // userstream
    oauth.get("userstream.twitter.com", "/1.1/user.json", [](int& status, std::string& text) {
      if (status != 200) {
        std::cerr << "Error!!" << std::endl;
        return;
      }

      std::cout << text << std::endl;
      text.clear();
    });
  } catch (std::exception& e) {
    std::cerr << "An exception occurred: " << e.what() << std::endl;
    return -1;
  }
}
