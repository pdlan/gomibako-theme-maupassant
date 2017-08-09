#include <string>
#include <sstream>
#include <set>
#include <iomanip>
#include <ctime>
#include "theme_api.h"
#include "layout.hpp"

using namespace std;
using namespace gomibako;

extern string comment_html;

extern"C" void render_article(ostringstream &out, const ArticleMetadata &metadata, const string &content,
                              const SiteInformation &site_information, shared_ptr<URLMaker> url_maker) {
    ostringstream title;
    title << metadata.title << " | " << site_information.name;
    header(out, site_information, url_maker, title.str(), PageType::Article);
    out <<
R"(<article class="post">
    <header>
        <h1 class="post-title">)" << metadata.title << R"(</h1>
    </header>
    <date class="post-meta">)" << put_time(localtime(&metadata.timestamp), "%b %e, %Y") << R"(</date>
    <div class="post-content">
)" <<  content << R"(
        </div>
    </article>
    <div class="tags">
        Tagged in:
)";
    for (auto &&tag : metadata.tags) {
        out << "<a href=\"" << url_maker->url_tag(tag) << "\">" << tag << "</a>\n";
    }
    out <<
R"(
        </div>
)"
    << comment_html;
    footer(out, site_information, url_maker);
}