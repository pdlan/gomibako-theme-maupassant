#ifndef GOMIBAKO_SRC_THEME_CLEAN_LAYOUT_HPP
#define GOMIBAKO_SRC_THEME_CLEAN_LAYOUT_HPP
#include <string>
#include <sstream>
#include <cmath>
#include "theme_api.h"

using namespace gomibako;

enum class PageType {
    Page, Article, CustomPage, Archives, Tag, Tags, Error
};

inline void sidebar(std::ostringstream &out, const SiteInformation &site_information,
                    std::shared_ptr<URLMaker> url_maker) {
    out <<
R"(<div id="secondary">
    <section class="widget">
        <h3 class="widget-title">Tags</h3>
)";
    for (auto &&i : *site_information.tags) {
        int size = round(log10(i.second) * 10 + 10);
        out << "<a style=\"padding:5px;font-size:" << size << "px;\" href=\"" 
            << url_maker->url_tag(i.first) << "\">" << i.first << " ("
            << i.second << ")</a>";
    }
    out <<
R"(
    </section>
)";
    out <<
R"(<div id="secondary">
    <section class="widget">
        <h3 class="widget-title">Site</h3>
        <ul class="widget-list">
            <li><a href="/feed.xml">Feed</a></li>
            <li><a href="/admin/">Admin</a></li>
        </ul>
    </section>
)";
}

inline void header(std::ostringstream &out, const SiteInformation &site_information,
                   std::shared_ptr<URLMaker> url_maker, const std::string &title,
                   PageType page_type, const std::string &current_page = "") {
    out <<
R"(<!DOCTYPE HTML>
<html>
<head>
    <meta charset="utf-8" />
    <meta name="viewport" content="width=device-width,user-scalable=no">
    <title>)" << title << R"(</title>
    <link rel="stylesheet" href=")" << url_maker->url_static("css/normalize.css") << R"(">
    <link rel="stylesheet" href=")" << url_maker->url_static("css/style.css") << R"(">
</head>
<body>

<header id="header" class="clearfix">
    <div class="container">
        <div class="col-group">
            <div class="site-name ">
                )";
    if (page_type == PageType::Page) {
        out << "<h1>";
    }
    out << R"(<a id="logo" href=")" << url_maker->url_index() << "\">" << site_information.name << "</a>";
    if (page_type == PageType::Page) {
        out << "</h1>";
    }
    out <<
R"(                <p class="description">)" << site_information.description << R"(</p>
            </div>
            <div>
                <nav id="nav-menu" class="clearfix">
                    <a)";
    if (page_type == PageType::Page || page_type == PageType::Article) {
        out << R"( class="current")";
    }
    out << R"( href=")" << url_maker->url_index() << R"(">Blog</a>)";
    out << "<a";
    if (page_type == PageType::Tags) {
        out << R"( class="current")";
    }
    out << R"( href=")" << url_maker->url_tags() << R"(">Tags</a>)";
    out << "<a";
    if (page_type == PageType::Archives) {
        out << R"( class="current")";
    }
    out << R"( href=")" << url_maker->url_archives() << R"(">Archives</a>)";
    for (auto &&page: *site_information.pages) {
        if (page.id == current_page) {
            out << R"(<a class="current" href=")" << url_maker->url_custom_page(page.id)
                << "\">" << page.title << "</a>\n";
        } else {
            out << R"(<a href=")" << url_maker->url_custom_page(page.id)
                << "\">" << page.title << "</a>\n";
        }
    }
    out <<
R"(                </nav>
            </div>
        </div>
    </div>
</header>
<div id="body">
    <div class="container">
        <div class="col-group">
            <div class="col-8" id="main">
                <div class="res-cons">)";
}

inline void footer(std::ostringstream &out, const SiteInformation &site_information,
                   std::shared_ptr<URLMaker> url_maker) {
    time_t time_now = time(nullptr);
    out <<
R"(
                </div>
            </div>)";
    sidebar(out, site_information, url_maker);
    out <<
R"(
        </div>
    </div>
</div>
<footer id="footer">
    <div class="container">&copy; )" << localtime(&time_now)->tm_year + 1900
     << R"(
        <a rel="nofollow" href=")" << url_maker->url_index() << "\">"
        << site_information.name << R"(</a>. Powered by <a href="https://github.com/pdlan/gomibako">Gomibako</a>.
        Template Made by <a href="http://pagecho.com">cho</a>.)" <<
R"(    </div>
</footer>
</body>
</html>)";
}
#endif