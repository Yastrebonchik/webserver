#ifndef CONFIG_PARSER_HPP
#define CONFIG_PARSER_HPP
#define DEFAULT_SERVER_NAME "default"
#define DEFAULT_LISTEN "0.0.0.0:80"
#define DEFAULT_ERROR_PAGE "error.html"
#define DEFAULT_CLIENT_BODY_SIZE "100"
#define DEFAULT_ROOT "./"
#define DEFAULT_INDEX "index.html"
# include "config.hpp"

int config_parser(char *file, std::vector<ConfigClass> &conf);

#endif
