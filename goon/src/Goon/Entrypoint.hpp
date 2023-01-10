#ifdef GN_PLATFORM_MACOS

extern Goon::Application *Goon::CreateApplication();

int main(int , char** )
{
    Goon::Log::Init();
    auto app = Goon::CreateApplication();
    app->Run();
    delete app;
}
#endif

#ifdef GN_PLATFORM_WINDOWS
extern Goon::Application *Goon::CreateApplication();
int main(int , char** )
{
    Goon::Log::Init();
    auto app = Goon::CreateApplication();
    app->Run();
    delete app;
}

int main(int argc, char *argv[])
{
    Goon::Log::Init();
    auto app = Goon::CreateApplication();
    app->Run();
    delete app;
}

#endif

#ifdef GN_PLATFORM_LINUX
extern Goon::Application *Goon::CreateApplication();
int main(int , char** )
{
    Goon::Log::Init();
    auto app = Goon::CreateApplication();
    app->Run();
    delete app;
}

#endif

