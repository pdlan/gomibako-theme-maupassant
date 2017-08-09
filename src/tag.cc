#include <string>
#include <sstream>
#include <iomanip>
#include <functional>
#include <ctime>
#include "theme_api.h"
#include "layout.hpp"

using namespace std;
using namespace gomibako;

extern"C" void render_tag(ostringstream &out, const vector<ArticleMetadata> &metadata,
                          const std::function<bool (const std::string &, std::ostringstream &)> &get_content,
                          const std::string &tag,
                          int page, int pages, const SiteInformation &site_information,
                          shared_ptr<URLMaker> url_maker) {
    ostringstream title;
    title << tag << " | " << site_information.name;
    header(out, site_information, url_maker, title.str(), PageType::Tag);
    out <<
R"(
        <h3 class="archive-title">Post Tagged with )" << tag << "</h3>\n";
    for (auto &&i : metadata) {
        out <<
R"(<article class="post">
    <header>
        <h2 class="post-title">
            <a href=")" << url_maker->url_article(i.id) << "\">" << i.title << R"(</a>
        </h2>
    </header>
    <date class="post-meta">)" << put_time(localtime(&i.timestamp), "%b %e, %Y") << R"(</date>
    <div class="post-content ellipsis">)";
    ostringstream content;
    get_content(i.id, content);
    out << content.str() << R"(</div>
</article>
)";
    }
    out << R"(<div class="page-navigator">
)";
    if (page != 1) {
        out << R"(<a class="prev" href=")" << url_maker->url_page(page - 1) << "\">&larr; Previous</a>\n";
    }
    if (page != pages) {
        out << R"(<a class="next" href=")" << url_maker->url_page(page + 1) << "\">Next &rarr;</a>\n";
    }
    out << "</div>";
    footer(out, site_information, url_maker);
}