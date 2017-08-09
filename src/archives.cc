#include <string>
#include <sstream>
#include <iomanip>
#include <ctime>
#include "theme_api.h"
#include "layout.hpp"

using namespace std;
using namespace gomibako;

extern"C" void render_archives(ostringstream &out, const vector<ArticleMetadata> &metadata,
                               int page, int pages, const SiteInformation &site_information,
                               shared_ptr<URLMaker> url_maker) {
    header(out, site_information, url_maker, "Archives | " + site_information.name, PageType::Archives);
    out <<
R"(<article class="post">
    <div class="post-content-pages">
        <div id="archives">)";
    int prev_year;
    for (size_t i = 0; i < metadata.size(); ++i) {
        tm *tm_ = localtime(&metadata[i].timestamp);
        int year = tm_->tm_year + 1900;
        int month = tm_->tm_mon;
        if (i == 0) {
            prev_year = year;
            out << R"(<div class="al_year">)" << year << "</div>\n<ul class=\"al_mon_list\">";
        }
        if (year != prev_year) {
            out << R"(</ul><div class="al_year">)" << year << "</div>\n<ul class=\"al_mon_list\">";
            prev_year = year;
        }
        out << R"(<li>)" << put_time(tm_, "%m/%d") << R"(<a href=")"
            << url_maker->url_article(metadata[i].id) << "\">" << metadata[i].title << "</a></li>\n";
        if (i == (metadata.size() - 1)) {
            out << "</ul>";
        }
    }
    out << "</div></article>";
    out << R"(<div class="page-navigator">
)";
    if (page != 1) {
        out << R"(<a class="prev" href=")" << url_maker->url_archives(page - 1) << "\">&larr; Previous</a>\n";
    }
    if (page != pages) {
        out << R"(<a class="next" href=")" << url_maker->url_archives(page + 1) << "\">Next &rarr;</a>\n";
    }
    out << "</div>";
    footer(out, site_information, url_maker);
}