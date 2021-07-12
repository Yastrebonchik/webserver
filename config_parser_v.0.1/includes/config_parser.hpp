#ifndef CONFIG_PARSER_HPP
#define CONFIG_PARSER_HPP
#define DEFAULT_SERVER_NAME ""
#define DEFAULT_LISTEN "0.0.0.0:0"
#define DEFAULT_ERROR_PAGE ""
#define DEFAULT_CLIENT_BODY_SIZE ""
#define DEFAULT_ROOT ""
#define DEFAULT_INDEX ""
# include "config.hpp"
# include <cstring>
# include <cstdlib>
# include <algorithm>

int config_parser(char *file, std::vector<ConfigClass*> &conf);
void free_conf(std::vector<ConfigClass *> &conf);

#endif
