#include <iostream>
#include <Wt/WTemplate.h>
#include <Wt/WApplication.h>
#include <Wt/WBreak.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WImage.h>
#include <Wt/WLink.h>
#include <Wt/WAnchor.h>
#include <Wt/WPushButton.h>
#include <Wt/WText.h>
#include <Wt/WVideo.h>

class MovieApplication : public Wt::WApplication
{
public:
    MovieApplication(const Wt::WEnvironment& env);
};

MovieApplication::MovieApplication(const Wt::WEnvironment& env)
    : Wt::WApplication(env)
{
    root()->addWidget(std::make_unique<Wt::WBreak>());
    root()->addWidget(std::make_unique<Wt::WBreak>());
    root()->addWidget(std::make_unique<Wt::WBreak>());
    root()->addWidget(std::make_unique<Wt::WBreak>());

    std::string mp4Video = "http://127.0.0.1:8000/mp4/tr.mp4";
    
//    std::cin << mp4Video;
    
    auto container = root()->addWidget(std::make_unique<Wt::WContainerWidget>());
    auto video = container->addNew<Wt::WVideo>();
    video->addSource(Wt::WLink(mp4Video));
    video->resize(640, 360);
    
    Wt::WText *out = container->addNew<Wt::WText>();

    video->playbackStarted().connect([=] {
        out->setText("<p>Video playing</p>");
    });

    video->playbackPaused().connect([=] {
        out->setText("<p>Video paused</p>");
    });
    
    video->ended().connect([=] {
        out->setText("<p>Video ended</p>");
    });

    video->volumeChanged().connect([=] {
        out->setText("<p>Volume changed</p>");
    });
}

int main(int argc, char **argv) {
    return Wt::WRun(argc, argv, [](const Wt::WEnvironment& env) {
        return std::make_unique<MovieApplication>(env);
    });
}
