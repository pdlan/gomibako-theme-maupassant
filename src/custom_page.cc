#include <string>
#include <sstream>
#include <algorithm>
#include <set>
#include <iomanip>
#include <ctime>
#include "theme_api.h"
#include "layout.hpp"

using namespace std;
using namespace gomibako;

extern string comment_html;

extern"C" void render_custom_page(ostringstream &out, const CustomPage &page,
                                  const SiteInformation &site_information,
                                  shared_ptr<URLMaker> url_maker) {
    ostringstream title;
    title << page.title << " | " << site_information.name;
    header(out, site_information, url_maker, title.str(), PageType::CustomPage, page.id);
    out <<
R"(<article class="post">
    <header>
        <h1 class="post-title">)" << page.title << R"(</h1>
    </header>
    <div class="page-content post-content">
)" << page.content << R"(
    </div>
</article>
)" << comment_html;
    footer(out, site_information, url_maker);
}