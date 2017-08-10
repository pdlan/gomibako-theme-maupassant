#include <string>
#include <sstream>
#include <fstream>
#include "theme_api.h"

using namespace std;
using namespace gomibako;

string comment_html;
string custom_sidebar_html;

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
        {"fonts/icomoon.ttf", "font/ttf"},
        {"fonts/icomoon.eot", "application/vnd.ms-fontobject"},
        {"fonts/icomoon.woff", "font/woff"}
    };
    config.error_codes = {404};
    ifstream fs1("comment.html");
    if (fs1) {
        ostringstream ss;
        ss << fs1.rdbuf();
        comment_html = ss.str();
        fs1.close();
    }
    ifstream fs2("custom_sidebar.html");
    if (fs2) {
        ostringstream ss;
        ss << fs2.rdbuf();
        custom_sidebar_html = ss.str();
        fs2.close();
    }
    return true;
}

extern"C" void finalize(void) {}