#include <string>
#include <sstream>
#include <fstream>
#include "theme_api.h"

using namespace std;
using namespace gomibako;

string comment_html;

extern"C" bool initialize(ThemeConfiguration &config) {
    config.articles_per_page = 10;
    config.articles_per_page_tag = 10;
    config.articles_per_page_archives = 20;
    config.static_directory = "theme/maupassant_static";
    config.static_files  = {
        {"css/style.css", "text/css"},
        {"css/normalize.css", "text/css"},
        {"img/404.jpg", "image/jpeg"},
        {"fonts/icomoon.svg", "image/svg+xml"},
        {"fonts/icomoon.ttf", "application/font-sfnt"},
        {"fonts/icomoon.eot", "application/vnd.ms-fontobject"},
        {"fonts/icomoon.woff", "application/font-woff"}
    };
    config.error_codes = {404};
    fstream fs("comment.html");
    if (fs) {
        ostringstream ss;
        ss << fs.rdbuf();
        comment_html = ss.str();
        fs.close();
    }
    return true;
}

extern"C" void finalize(void) {}